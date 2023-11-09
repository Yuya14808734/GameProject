//-------------------------------------------------------------
//�@���e�FBGM�N���X�ASE�N���X
//
//�@�N���X�P�ʂ�BGM�ESE���������Ƃ��ł��܂�
//
//�@delete ��Y���ƁA�Ƃ�ł��Ȃ��ʂ̃��������[�N��
//�@�������鋰�ꂪ����̂ŋC��t���Ă�������
//�@
//�@�����Ƃ� wav�t�@�C�� �����ǂݍ��߂Ȃ��̂ŁA
//�@mp3�Ȃǂ�ǂݍ��݂����ꍇ��
//�@�@https://online-audio-converter.com/ja/
//�@�� wav�t�@�C�� �ɕϊ����Ă�������
//
//�@BGM�̃v���O������
//�@�@BGM* bgm = new BGM("Sounds/bgm.wav", true);
//�@�@bgm->Start();�@�@�@�@�@Sleep(10000);
//�@�@bgm->SetVolume(0.5f);�@Sleep(10000);
//�@�@bgm->Stop();
//�@�@delete bgm;
//
//�@SE�̃v���O������
//�@�@SE* se = new SE("Sounds/se.wav");
//�@�@se->Play();�@Sleep(500);
//�@�@se->Play();�@Sleep(500);
//�@�@se->Play();
//�@�@delete se;
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
//�@����2�͕K���Ăяo���Ă�������
//-----------------------------------
HRESULT InitXAudio2();
void UninitXAudio2();


class BGM
{
public:
	//�R���X�g���N�^
	//	const char* filePath : �����t�@�C���̃p�X
	//	bool loop (=false) : ���[�v�ݒ�(�ȗ���)
	BGM(const char* filePath, bool loop = false);

	//�f�X�g���N�^
	~BGM();

	//�Đ��J�n
	void Start();

	//�Đ��I��
	void Stop();

	//�{�����[���ݒ�
	//	float volume : �{�����[��(0.0f �` 1.0f)
	void SetVolume(float volume);


private:
	WAVEFORMATEXTENSIBLE m_wfx{ 0 };
	XAUDIO2_BUFFER m_buffer{ 0 };
	IXAudio2SourceVoice* m_pSourceVoice;
};


class SE
{
public:
	//�R���X�g���N�^
	//	const char* filePath : �����t�@�C���ւ̃p�X
	SE(const char* filePath);

	//�f�X�g���N�^
	~SE();

	//�Đ�
	void Play();

private:
	char* m_soundData;
};


#endif // !___SOUND_H___

