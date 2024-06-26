#include "ShaderManager.h"

std::map<std::string, VertexShader*> ShaderManager::m_pVertexShaders;
std::map<std::string, PixelShader*> ShaderManager::m_pPixelShaders;

bool			ShaderManager::m_isUseAllObjectShader_VS = false;
VertexShader*	ShaderManager::m_pAllObjectShader_VS = nullptr;
bool			ShaderManager::m_isUseAllObjectShader_PS = false;
PixelShader*	ShaderManager::m_pAllObjectShader_PS = nullptr;

void ShaderManager::InitShaders()
{
	m_isUseAllObjectShader_VS = false;
	m_pAllObjectShader_VS = nullptr;
	m_isUseAllObjectShader_PS = false;
	m_pAllObjectShader_PS = nullptr;
}

void ShaderManager::UninitShaders()
{
	AllReleaseShader();
}

VertexShader* ShaderManager::CreateVertexShader(const std::string & ShaderName, const char * FilePath)
{
	auto it = m_pVertexShaders.find(ShaderName);

	//その名前のシェーダーが存在した場合
	if (it != m_pVertexShaders.end())
	{
		return (*it).second;
	}

	//シェーダーを作成
	HRESULT hr;
	VertexShader* pVS = new VertexShader();
	hr = pVS->Load(FilePath);

	if (FAILED(hr))
	{
		//シェーダーが作成できなかった場合
		delete pVS;
		return nullptr;
	}

	//シェーダーを配列に追加
	m_pVertexShaders.insert(std::make_pair(ShaderName, pVS));
	return pVS;
}

PixelShader* ShaderManager::CreatePixelShader(const std::string & ShaderName, const char * FilePath)
{
	auto it = m_pPixelShaders.find(ShaderName);

	//その名前のシェーダーが存在した場合
	if (it != m_pPixelShaders.end())
	{
		return (*it).second;
	}

	//シェーダーを作成
	HRESULT hr;
	PixelShader* pPS = new PixelShader();
	hr = pPS->Load(FilePath);

	if (FAILED(hr))
	{
		//シェーダーが作成できなかった場合
		delete pPS;
		return nullptr;
	}

	//シェーダーを配列に追加
	m_pPixelShaders.insert(std::make_pair(ShaderName, pPS));
	return pPS;
}

bool ShaderManager::SetPointerVertexShader(const std::string& ShaderName, VertexShader* pVertexShader)
{
	//設定するシェーダーがnullptrの場合
	if (pVertexShader == nullptr)
	{
		return false;
	}

	//設定するシェーダー名がもう作成されていた場合
	if (m_pVertexShaders.find(ShaderName) != m_pVertexShaders.end())
	{
		return false;
	}

	//上の二つの条件をクリアしている場合
	m_pVertexShaders.insert(std::make_pair(ShaderName, pVertexShader));
	return true;
}

bool ShaderManager::SetPointerPixelShader(const std::string& ShaderName, PixelShader* pPixelShader)
{
	//設定するシェーダーがnullptrの場合
	if (pPixelShader == nullptr)
	{
		return false;
	}

	//設定するシェーダー名がもう作成されていた場合
	if (m_pPixelShaders.find(ShaderName) == m_pPixelShaders.end())
	{
		return false;
	}

	//上の二つの条件をクリアしている場合
	m_pPixelShaders.insert(std::make_pair(ShaderName, pPixelShader));
	return true;
}

VertexShader* ShaderManager::GetVertexShader(const std::string& Name)
{
	//そのシェーダーを作っていない場合
	if (m_pVertexShaders.find(Name) == m_pVertexShaders.end())
	{
		return nullptr;
	}
	return m_pVertexShaders[Name];
}

PixelShader* ShaderManager::GetPixelShader(const std::string& Name)
{
	//そのシェーダーを作っていない場合
	if (m_pPixelShaders.find(Name) == m_pPixelShaders.end())
	{
		return nullptr;
	}
	return m_pPixelShaders[Name];
}

bool ShaderManager::ReleaseVertexShader(const std::string& ShaderName)
{
	//そのシェーダーを作っていない場合
	if (m_pVertexShaders.find(ShaderName) == m_pVertexShaders.end())
	{
		return false;
	}

	//削除をする
	delete m_pVertexShaders[ShaderName];
	m_pVertexShaders.erase(ShaderName);

	return true;
}

bool ShaderManager::ReleasePixelShader(const std::string& ShaderName)
{
	//そのシェーダーを作っていない場合
	if (m_pPixelShaders.find(ShaderName) == m_pPixelShaders.end())
	{
		return false;
	}

	//削除をする
	delete m_pPixelShaders[ShaderName];
	m_pPixelShaders.erase(ShaderName);

	return true;
}

void ShaderManager::AllReleaseShader()
{
	//===<全てのシェーダーを削除する>===
	for (auto VertexShader : m_pVertexShaders)
	{
		delete VertexShader.second;
	}
	m_pVertexShaders.clear();

	for (auto PixelShader : m_pPixelShaders)
	{
		delete PixelShader.second;
	}
	//=================================

	m_pPixelShaders.clear();
}

void ShaderManager::SetUseAllObjectVS(bool use)
{
	m_isUseAllObjectShader_VS = use;
}

void ShaderManager::SetUseAllObjectPS(bool use)
{
	m_isUseAllObjectShader_PS = use;
}

VertexShader* ShaderManager::SetAllObjectVS(const std::string& ShaderName)
{
	//シェーダーの取得
	m_pAllObjectShader_VS = GetVertexShader(ShaderName);
	return m_pAllObjectShader_VS;
}

PixelShader* ShaderManager::SetAllObjectPS(const std::string& ShaderName)
{
	//シェーダーの取得
	m_pAllObjectShader_PS = GetPixelShader(ShaderName);
	return m_pAllObjectShader_PS;
}

bool ShaderManager::GetUseAllObjectVS()
{
	return m_isUseAllObjectShader_VS;
}

bool ShaderManager::GetUseAllObjectPS()
{
	return m_isUseAllObjectShader_PS;
}

VertexShader* ShaderManager::GetAllObjectVS()
{
	return m_pAllObjectShader_VS;
}

PixelShader* ShaderManager::GetAllObjectPS()
{
	return m_pAllObjectShader_PS;
}
