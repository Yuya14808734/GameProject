#include "Sound.h"

#pragma comment(lib, "winmm.lib")

unsigned long GetFileSize(const char* filePath);


SE::SE(const char* filePath)
{
	unsigned long fileSize = GetFileSize(filePath);
	m_soundData = new char[fileSize + 1];

	FILE* fp = fopen(filePath, "rb");
	unsigned long readSize = fread(m_soundData, sizeof(char), fileSize, fp);
	fclose(fp);

	//���O�ɒ��ׂ��t�@�C���T�C�Y�Ɠǂݍ��񂾃t�@�C���T�C�Y���r
	if (readSize != fileSize)
	{
		MessageBox(NULL, "�t�@�C���̓ǂݍ��݂Ɏ��s", "SE.cpp", MB_OK | MB_ICONERROR);
		return;
	}
}

SE::~SE()
{
	delete[] m_soundData;
}

void SE::Play()
{
	PlaySound(m_soundData, NULL, SND_MEMORY | SND_ASYNC | SND_NODEFAULT);
}



unsigned long GetFileSize(const char* filePath)
{
	FILE* fp = fopen(filePath, "rb");
	fseek(fp, 0, SEEK_END);

	unsigned long fileSize = 0;
	fileSize = ftell(fp);

	rewind(fp); //�t�@�C���ʒu��擪(0)�ɖ߂�
	fclose(fp); //�t�@�C�������

	return fileSize;
}
