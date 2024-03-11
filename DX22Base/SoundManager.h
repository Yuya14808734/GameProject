#pragma once
#include "Sound.h"
#include <map>
#include <string>

class SoundManager
{
public:
	static BGM* AddBGM(const std::string& BGM_Name, const char* pFilePath,bool Loop);
	static SE*  AddSE(const std::string& SE_Name, const char* pFilePath);
	static void PlayBGM(const std::string& BGM_Name);
	static void PlaySE(const std::string& SE_Name);
	static BGM* GetBGM(const std::string& BGM_Name);
	static SE*  GetSE(const std::string& SE_Name);
	static void DestroyBGM(const std::string& BGM_Name,bool MemoryDelete = true);
	static void DestroySE(const std::string& SE_Name, bool MemoryDelete = true);
	static void DestroyAllBGM();
	static void DestroyAllSE();
	static void DestroyAll();

private:
	static std::map<std::string, BGM*> m_BGM_Map;
	static std::map<std::string, SE*> m_SE_Map;
};

