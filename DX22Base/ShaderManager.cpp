#include "ShaderManager.h"

std::map<std::string, VertexShader*> ShaderManager::m_pVertexShaders;
std::map<std::string, PixelShader*> ShaderManager::m_pPixelShaders;

void ShaderManager::InitShaders()
{
}

void ShaderManager::UninitShaders()
{
	AllReleaseShader();
}

VertexShader* ShaderManager::CreateVertexShader(const std::string & ShaderName, const char * FilePath)
{
	auto it = m_pVertexShaders.find(ShaderName);

	//���̖��O�̃V�F�[�_�[�����݂����ꍇ
	if (it != m_pVertexShaders.end())
	{
		return (*it).second;
	}

	//�V�F�[�_�[���쐬
	HRESULT hr;
	VertexShader* pVS = new VertexShader();
	hr = pVS->Load(FilePath);

	if (FAILED(hr))
	{
		//�V�F�[�_�[���쐬�ł��Ȃ������ꍇ
		delete pVS;
		return nullptr;
	}

	//�V�F�[�_�[��z��ɒǉ�
	m_pVertexShaders.insert(std::make_pair(ShaderName, pVS));
	return pVS;
}

PixelShader* ShaderManager::CreatePixelShader(const std::string & ShaderName, const char * FilePath)
{
	auto it = m_pPixelShaders.find(ShaderName);

	//���̖��O�̃V�F�[�_�[�����݂����ꍇ
	if (it != m_pPixelShaders.end())
	{
		return (*it).second;
	}

	//�V�F�[�_�[���쐬
	HRESULT hr;
	PixelShader* pPS = new PixelShader();
	hr = pPS->Load(FilePath);

	if (FAILED(hr))
	{
		//�V�F�[�_�[���쐬�ł��Ȃ������ꍇ
		delete pPS;
		return nullptr;
	}

	//�V�F�[�_�[��z��ɒǉ�
	m_pPixelShaders.insert(std::make_pair(ShaderName, pPS));
	return pPS;
}

bool ShaderManager::SetNewVertexShader(const std::string& ShaderName, VertexShader* pVertexShader)
{
	//�ݒ肷��V�F�[�_�[��nullptr�̏ꍇ
	if (pVertexShader == nullptr)
	{
		return false;
	}

	//�ݒ肷��V�F�[�_�[���������쐬����Ă����ꍇ
	if (m_pVertexShaders.find(ShaderName) != m_pVertexShaders.end())
	{
		return false;
	}

	//��̓�̏������N���A���Ă���ꍇ
	m_pVertexShaders.insert(std::make_pair(ShaderName, pVertexShader));
	return true;
}

bool ShaderManager::SetNewPixelShader(const std::string& ShaderName, PixelShader* pPixelShader)
{
	//�ݒ肷��V�F�[�_�[��nullptr�̏ꍇ
	if (pPixelShader == nullptr)
	{
		return false;
	}

	//�ݒ肷��V�F�[�_�[���������쐬����Ă����ꍇ
	if (m_pPixelShaders.find(ShaderName) == m_pPixelShaders.end())
	{
		return false;
	}

	//��̓�̏������N���A���Ă���ꍇ
	m_pPixelShaders.insert(std::make_pair(ShaderName, pPixelShader));
	return true;
}

VertexShader* ShaderManager::GetVertexShader(const std::string& Name)
{
	//���̃V�F�[�_�[������Ă��Ȃ��ꍇ
	if (m_pVertexShaders.find(Name) == m_pVertexShaders.end())
	{
		return nullptr;
	}
	return m_pVertexShaders[Name];
}

PixelShader* ShaderManager::GetPixelShader(const std::string& Name)
{
	//���̃V�F�[�_�[������Ă��Ȃ��ꍇ
	if (m_pPixelShaders.find(Name) == m_pPixelShaders.end())
	{
		return nullptr;
	}
	return m_pPixelShaders[Name];
}

bool ShaderManager::ReleaseVertexShader(const std::string& ShaderName)
{
	//���̃V�F�[�_�[������Ă��Ȃ��ꍇ
	if (m_pVertexShaders.find(ShaderName) == m_pVertexShaders.end())
	{
		return false;
	}

	//�폜������
	delete m_pVertexShaders[ShaderName];
	m_pVertexShaders.erase(ShaderName);

	return true;
}

bool ShaderManager::ReleasePixelShader(const std::string& ShaderName)
{
	//���̃V�F�[�_�[������Ă��Ȃ��ꍇ
	if (m_pPixelShaders.find(ShaderName) == m_pPixelShaders.end())
	{
		return false;
	}

	//�폜������
	delete m_pPixelShaders[ShaderName];
	m_pPixelShaders.erase(ShaderName);

	return true;
}

void ShaderManager::AllReleaseShader()
{
	//===<�S�ẴV�F�[�_�[���폜����>===
	for (auto VertexShader : m_pVertexShaders)
	{
		delete VertexShader.second;
	}

	for (auto PixelShader : m_pVertexShaders)
	{
		delete PixelShader.second;
	}
	//=================================

	m_pVertexShaders.clear();
	m_pPixelShaders.clear();
}
