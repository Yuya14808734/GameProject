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

	//事前に調べたファイルサイズと読み込んだファイルサイズを比較
	if (readSize != fileSize)
	{
		MessageBox(NULL, "ファイルの読み込みに失敗", "SE.cpp", MB_OK | MB_ICONERROR);
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

	rewind(fp); //ファイル位置を先頭(0)に戻す
	fclose(fp); //ファイルを閉じる

	return fileSize;
}
