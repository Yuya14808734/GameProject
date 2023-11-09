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

	//COM�R���|�[�l���g�̏�����
	hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		MessageBox(NULL, "COM�R���|�[�l���g�̏������Ɏ��s", "BGM.cpp", MB_OK | MB_ICONERROR);
		return hr;
	}

	//XAudio2�̏�����
	hr = XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	if (FAILED(hr))
	{
		MessageBox(NULL, "XAudio2�̏������Ɏ��s", "BGM.cpp", MB_OK | MB_ICONERROR);
		return hr;
	}

	//�}�X�^�[�{�C�X�̍쐬
	hr = pXAudio2->CreateMasteringVoice(&pMasteringVoice);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�}�X�^�[�{�C�X�̍쐬�Ɏ��s", "BGM.cpp", MB_OK | MB_ICONERROR);
		return hr;
	}

	return hr;
}

void UninitXAudio2()
{
	//�}�X�^�[�{�C�X�̍폜
	pMasteringVoice->DestroyVoice();

	//XAudio2�̏I��
	pXAudio2.Release();

	//COM�R���|�[�l���g�̏I��
	CoUninitialize();
}




BGM::BGM(const char* filePath, bool loop)
{
	HRESULT hr;

	//�I�[�f�B�I�t�@�C�����J��
	HANDLE hFile = CreateFile(filePath, GENERIC_READ, FILE_SHARE_READ | XAUDIO2_VOICE_NOPITCH | XAUDIO2_VOICE_NOSRC, NULL, OPEN_EXISTING, 0, NULL);
	SetFilePointer(hFile, 0, NULL, FILE_BEGIN);


	//�t�@�C���̎�ނ��m�F
	DWORD dwChunkSize;
	DWORD dwChunkPosition;
	FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);

	DWORD dwFileType;
	ReadChunkData(hFile, &dwFileType, sizeof(DWORD), dwChunkPosition);
	

	//fmt�`�����N �� WAVEFORMATEXTENSIBLE�\���� �ɃR�s�[
	FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
	ReadChunkData(hFile, &m_wfx, dwChunkSize, dwChunkPosition);


	//data�`�����N ���o�b�t�@�[�ɓǂݎ��
	FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
	
	BYTE* pDataBuffer = new BYTE[dwChunkSize];
	ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);
	

	//XAUDIO2_BUFFER�\���� �ɒl��ݒ�
	m_buffer.AudioBytes = dwChunkSize; //�I�[�f�B�I�o�b�t�@�[�̃T�C�Y(�o�C�g�P��)
	m_buffer.pAudioData = pDataBuffer; //�o�b�t�@�[�Ƀf�[�^���i�[
	m_buffer.Flags = XAUDIO2_END_OF_STREAM;
	if (loop) { m_buffer.LoopCount = XAUDIO2_LOOP_INFINITE; }


	//�\�[�X�������쐬
	hr = pXAudio2->CreateSourceVoice(&m_pSourceVoice, (WAVEFORMATEX*)&m_wfx);
	if (FAILED(hr))
	{
		MessageBox(NULL, "SourceVoice�̍쐬�Ɏ��s", "BGM.cpp", MB_OK | MB_ICONERROR);
	}

	//�\�[�X������ XAUDIO2_BUFFER �𑗐M
	hr = m_pSourceVoice->SubmitSourceBuffer(&m_buffer);
	if (FAILED(hr))
	{
		MessageBox(NULL, "XAUDIO2_BUFFER�̑��M�Ɏ��s", "BGM.cpp", MB_OK | MB_ICONERROR);
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





//FindChunk() : RIFF�t�@�C���Ń`�����N����������
// �t�@�C���ւ̃|�C���^ : HANDLE hFile
// �f�[�^�t�H�[�}�b�g : DWORD fourcc
// �`�����N�̃T�C�Y : DWORD& dwChunkSize
// �`�����N�̏ꏊ : DWORD& dwChunkDataPosition
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
		case fourccRIFF: //RIFF�t�@�C��
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;

			if (!(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL)))
			{
				hr = HRESULT_FROM_WIN32(GetLastError());
			}

			break;

		default: //���̑��̃t�@�C��
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


//ReadChunkData() : �`�����N����f�[�^��ǂݎ��
// �t�@�C���ւ̃|�C���^ : HANDLE hFile
// �o�b�t�@�[�ւ̃|�C���^ : void* buffer
// �o�b�t�@�[�̃T�C�Y : DWORD dwBifferSize
// �o�b�t�@�[�̋��� : DWORD dwBufferOffset
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

