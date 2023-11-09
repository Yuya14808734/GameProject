#include "Sound.h"
#include <atlbase.h>

#pragma comment(lib, "xaudio2.lib")

#ifdef _XBOX
	#define fourccRIFF 'RIFF'
	#define fourccData 'data'
	#define fourccFMT  'fmt '
	#define fourccWAVE 'WAVE'
	#define fourccXWMA 'XWMA'
	#define fourccWSMP 'wsmp'
	#define fourccSMPL 'smpl'
	#define fourccDPDS 'dpds'
	#define fourccSEEK 'seek'
#endif // _XBOX

#ifndef _XBOX
	#define fourccRIFF 'FFIR'
	#define fourccDATA 'atad'
	#define fourccFMT  ' tmf'
	#define fourccWAVE 'EVAW'
	#define fourccXWMA 'AMWX'
	#define fourccWSMP 'pmsw'
	#define fourccSMPL 'lpms'
	#define fourccDPDS 'sdpd'
	#define fourccSEEK 'kees'
#endif // !_XBOX


static CComPtr<IXAudio2> pXAudio2;
static IXAudio2MasteringVoice* pMasteringVoice;


HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void* buffer, DWORD dwBufferSize, DWORD dwBufferOffset);




HRESULT InitXAudio2()
{
	HRESULT hr;

	//COMコンポーネントの初期化
	hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		MessageBox(NULL, "COMコンポーネントの初期化に失敗", "BGM.cpp", MB_OK | MB_ICONERROR);
		return hr;
	}

	//XAudio2の初期化
	hr = XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	if (FAILED(hr))
	{
		MessageBox(NULL, "XAudio2の初期化に失敗", "BGM.cpp", MB_OK | MB_ICONERROR);
		return hr;
	}

	//マスターボイスの作成
	hr = pXAudio2->CreateMasteringVoice(&pMasteringVoice);
	if (FAILED(hr))
	{
		MessageBox(NULL, "マスターボイスの作成に失敗", "BGM.cpp", MB_OK | MB_ICONERROR);
		return hr;
	}

	return hr;
}

void UninitXAudio2()
{
	//マスターボイスの削除
	pMasteringVoice->DestroyVoice();

	//XAudio2の終了
	pXAudio2.Release();

	//COMコンポーネントの終了
	CoUninitialize();
}




BGM::BGM(const char* filePath, bool loop)
{
	HRESULT hr;

	//オーディオファイルを開く
	HANDLE hFile = CreateFile(filePath, GENERIC_READ, FILE_SHARE_READ | XAUDIO2_VOICE_NOPITCH | XAUDIO2_VOICE_NOSRC, NULL, OPEN_EXISTING, 0, NULL);
	SetFilePointer(hFile, 0, NULL, FILE_BEGIN);


	//ファイルの種類を確認
	DWORD dwChunkSize;
	DWORD dwChunkPosition;
	FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);

	DWORD dwFileType;
	ReadChunkData(hFile, &dwFileType, sizeof(DWORD), dwChunkPosition);
	

	//fmtチャンク を WAVEFORMATEXTENSIBLE構造体 にコピー
	FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
	ReadChunkData(hFile, &m_wfx, dwChunkSize, dwChunkPosition);


	//dataチャンク をバッファーに読み取り
	FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
	
	BYTE* pDataBuffer = new BYTE[dwChunkSize];
	ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);
	

	//XAUDIO2_BUFFER構造体 に値を設定
	m_buffer.AudioBytes = dwChunkSize; //オーディオバッファーのサイズ(バイト単位)
	m_buffer.pAudioData = pDataBuffer; //バッファーにデータを格納
	m_buffer.Flags = XAUDIO2_END_OF_STREAM;
	if (loop) { m_buffer.LoopCount = XAUDIO2_LOOP_INFINITE; }


	//ソース音声を作成
	hr = pXAudio2->CreateSourceVoice(&m_pSourceVoice, (WAVEFORMATEX*)&m_wfx);
	if (FAILED(hr))
	{
		MessageBox(NULL, "SourceVoiceの作成に失敗", "BGM.cpp", MB_OK | MB_ICONERROR);
	}

	//ソース音声に XAUDIO2_BUFFER を送信
	hr = m_pSourceVoice->SubmitSourceBuffer(&m_buffer);
	if (FAILED(hr))
	{
		MessageBox(NULL, "XAUDIO2_BUFFERの送信に失敗", "BGM.cpp", MB_OK | MB_ICONERROR);
	}
}

BGM::~BGM()
{
	m_pSourceVoice->DestroyVoice();
	delete[] m_buffer.pAudioData;
}



void BGM::Start()
{
	m_pSourceVoice->Start();
}

void BGM::Stop()
{
	m_pSourceVoice->Stop();
}

void BGM::SetVolume(float volume)
{
	m_pSourceVoice->SetVolume(volume);
}





//FindChunk() : RIFFファイルでチャンクを検索する
// ファイルへのポインタ : HANDLE hFile
// データフォーマット : DWORD fourcc
// チャンクのサイズ : DWORD& dwChunkSize
// チャンクの場所 : DWORD& dwChunkDataPosition
HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition)
{
	HRESULT hr = S_OK;

	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD bytesRead = 0;
	DWORD dwOffset = 0;

	while (hr == S_OK)
	{
		DWORD dwRead;

		if (!(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL)))
		{
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (!(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL)))
		{
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case fourccRIFF: //RIFFファイル
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;

			if (!(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL)))
			{
				hr = HRESULT_FROM_WIN32(GetLastError());
			}

			break;

		default: //その他のファイル
			if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
			{
				return HRESULT_FROM_WIN32(GetLastError());
			}

			break;
		}

		dwOffset += sizeof(DWORD) * 2;

		if (dwChunkType == fourcc)
		{
			dwChunkSize = dwChunkDataSize;
			dwChunkDataPosition = dwOffset;
			return S_OK;
		}

		dwOffset += dwChunkDataSize;

		if (bytesRead >= dwRIFFDataSize) { return S_FALSE; }
	}

	return S_OK;
}


//ReadChunkData() : チャンクからデータを読み取る
// ファイルへのポインタ : HANDLE hFile
// バッファーへのポインタ : void* buffer
// バッファーのサイズ : DWORD dwBifferSize
// バッファーの距離 : DWORD dwBufferOffset
HRESULT ReadChunkData(HANDLE hFile, void* buffer, DWORD dwBufferSize, DWORD dwBufferOffset)
{
	HRESULT hr = S_OK;

	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwBufferOffset, NULL, FILE_BEGIN))
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	DWORD dwRead;
	if (!(ReadFile(hFile, buffer, dwBufferSize, &dwRead, NULL)))
	{
		hr = HRESULT_FROM_WIN32(GetLastError());
	}

	return hr;
}

