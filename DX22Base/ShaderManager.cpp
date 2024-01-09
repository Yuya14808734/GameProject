#include "ShaderManager.h"

std::map<std::string, VertexShader*> ShaderManager::m_pVertexShaders;
std::map<std::string, PixelShader*> ShaderManager::m_pPixelShaders;

bool ShaderManager::SetVertexShader(const std::string& ShaderName, VertexShader* pVertexShader)
{
	if (pVertexShader == nullptr)
	{
		return false;
	}

	if (m_pVertexShaders.find(ShaderName) != m_pVertexShaders.end())
	{
		return false;
	}

	m_pVertexShaders.insert(std::make_pair(ShaderName, pVertexShader));
	return true;
}

bool ShaderManager::SetPixelShader(const std::string& ShaderName, PixelShader* pPixelShader)
{
	if (pPixelShader == nullptr)
	{
		return false;
	}

	if (m_pPixelShaders.find(ShaderName) == m_pPixelShaders.end())
	{
		return false;
	}

	m_pPixelShaders.insert(std::make_pair(ShaderName, pPixelShader));
	return true;
}

VertexShader* ShaderManager::GetVertexShader(const std::string& Name)
{
	if (m_pVertexShaders.find(Name) == m_pVertexShaders.end())
	{
		return nullptr;
	}
	return m_pVertexShaders[Name];
}

PixelShader* ShaderManager::GetPixelShader(const std::string& Name)
{
	if (m_pPixelShaders.find(Name) == m_pPixelShaders.end())
	{
		return nullptr;
	}
	return m_pPixelShaders[Name];
}

bool ShaderManager::ReleaseVertexShader(const std::string& ShaderName)
{
	if (m_pVertexShaders.find(ShaderName) == m_pVertexShaders.end())
	{
		return false;
	}

	delete m_pVertexShaders[ShaderName];

	m_pVertexShaders.erase(ShaderName);

	return true;
}

bool ShaderManager::ReleasePixelShader(const std::string& ShaderName)
{
	if (m_pPixelShaders.find(ShaderName) == m_pPixelShaders.end())
	{
		return false;
	}

	delete m_pPixelShaders[ShaderName];

	m_pPixelShaders.erase(ShaderName);

	return true;
}

void ShaderManager::AllReleaseShader()
{
	for (auto VertexShader : m_pVertexShaders)
	{
		delete VertexShader.second;
	}

	for (auto PixelShader : m_pVertexShaders)
	{
		delete PixelShader.second;
	}

	m_pVertexShaders.clear();
	m_pPixelShaders.clear();
}
