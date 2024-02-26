#include "SoundManager.h"

std::map<std::string, BGM*> SoundManager::m_BGM_Map;
std::map<std::string, SE*> SoundManager::m_SE_Map;

BGM * SoundManager::AddBGM(const std::string & BGM_Name, const char * pFilePath,bool Loop)
{
	std::map<std::string, BGM*>::iterator it = m_BGM_Map.find(BGM_Name);

	//å©Ç¬ÇØÇΩèÍçá
	if (it != m_BGM_Map.end())
	{
		return (*it).second;
	}

	BGM* pBGM = new BGM(pFilePath,Loop);

	m_BGM_Map.insert(std::pair(BGM_Name, pBGM));

	return pBGM;
}

SE * SoundManager::AddSE(const std::string & SE_Name, const char * pFilePath)
{
	std::map<std::string, SE*>::iterator it = m_SE_Map.find(SE_Name);

	//å©Ç¬ÇØÇΩèÍçá
	if (it != m_SE_Map.end())
	{
		return (*it).second;
	}

	SE* pSE = new SE(pFilePath);

	m_SE_Map.insert(std::pair(SE_Name, pSE));

	return pSE;
}

BGM * SoundManager::GetBGM(const std::string & BGM_Name)
{
	std::map<std::string, BGM*>::iterator it = m_BGM_Map.find(BGM_Name);

	if (it == m_BGM_Map.end())
	{
		return nullptr;
	}

	return (*it).second;
}

SE * SoundManager::GetSE(const std::string & SE_Name)
{
	std::map<std::string, SE*>::iterator it = m_SE_Map.find(SE_Name);

	if (it == m_SE_Map.end())
	{
		return nullptr;
	}

	return (*it).second;
}

void SoundManager::DestroyBGM(const std::string & BGM_Name, bool MemoryDelete = true)
{
	std::map<std::string, BGM*>::iterator it = m_BGM_Map.find(BGM_Name);

	//Ç‹Ç∏ÇªÇÃñºëOÇÃBGMÇ™Ç»Ç¢
	if (it == m_BGM_Map.end())
	{
		return;
	}

	if (MemoryDelete)
	{
		delete (*it).second;
	}
	
	m_BGM_Map.erase(it);
}

void SoundManager::DestroySE(const std::string & SE_Name, bool MemoryDelete = true)
{
	std::map<std::string, SE*>::iterator it = m_SE_Map.find(SE_Name);

	//Ç‹Ç∏ÇªÇÃñºëOÇÃSEÇ™Ç»Ç¢
	if (it == m_SE_Map.end())
	{
		return;
	}

	if (MemoryDelete)
	{
		delete (*it).second;
	}

	m_SE_Map.erase(it);
}

void SoundManager::DestroyAllBGM()
{
	for (std::map<std::string, BGM*>::iterator it = m_BGM_Map.begin();
		it != m_BGM_Map.end();)
	{
		delete (*it).second;
		it = m_BGM_Map.erase(it);
	}
}

void SoundManager::DestroyAllSE()
{
	for (std::map<std::string, SE*>::iterator it = m_SE_Map.begin();
		it != m_SE_Map.end();)
	{
		delete (*it).second;
		it = m_SE_Map.erase(it);
	}
}

void SoundManager::DestroyAll()
{
	DestroyAllBGM();
	DestroyAllSE();
}
