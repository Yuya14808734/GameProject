//-------------------------------------------------------------
//　内容：BGMクラス、SEクラス
//
//　クラス単位でBGM・SEを扱うことができます
//
//　delete を忘れると、とんでもない量のメモリリークが
//　発生する恐れがあるので気を付けてください
//　
//　両方とも wavファイル しか読み込めないので、
//　mp3などを読み込みたい場合は
//　　https://online-audio-converter.com/ja/
//　で wavファイル に変換してください
//
//　BGMのプログラム例
//　　BGM* bgm = new BGM("Sounds/bgm.wav", true);
//　　bgm->Start();　　　　　Sleep(10000);
//　　bgm->SetVolume(0.5f);　Sleep(10000);
//　　bgm->Stop();
//　　delete bgm;
//
//　SEのプログラム例
//　　SE* se = new SE("Sounds/se.wav");
//　　se->Play();　Sleep(500);
//　　se->Play();　Sleep(500);
//　　se->Play();
//　　delete se;
//-------------------------------------------------------------

#ifndef ___SOUND_H___
#define ___SOUND_H___

#include <stdio.h>
#include <Windows.h>
#include <mmsystem.h>
#include <tchar.h>
#include <stdint.h>
#include <xaudio2.h>


//-----------------------------------
//　この2つは必ず呼び出してください
//-----------------------------------
HRESULT InitXAudio2();
void UninitXAudio2();


class BGM
{
public:
	//コンストラクタ
	//	const char* filePath : 音声ファイルのパス
	//	bool loop (=false) : ループ設定(省略可)
	BGM(const char* filePath, bool loop = false);

	//デストラクタ
	~BGM();

	//再生開始
	void Start();

	//再生終了
	void Stop();

	//ボリューム設定
	//	float volume : ボリューム(0.0f ～ 1.0f)
	void SetVolume(float volume);


private:
	WAVEFORMATEXTENSIBLE m_wfx{ 0 };
	XAUDIO2_BUFFER m_buffer{ 0 };
	IXAudio2SourceVoice* m_pSourceVoice;
};


class SE
{
public:
	//コンストラクタ
	//	const char* filePath : 音声ファイルへのパス
	SE(const char* filePath);

	//デストラクタ
	~SE();

	//再生
	void Play();

private:
	char* m_soundData;
};


#endif // !___SOUND_H___

