#pragma once
#include "Shader.h"
#include "ConstantBuffer.h"
#include <map>
#include <string>

#define CreateShaderPath(ShaderName) ((std::string("Assets/Shader/") + std::string(ShaderName) + std::string(".cso")).c_str())

class ShaderManager
{
public:
	static void InitShaders();
	static void UninitShaders();
	static VertexShader* CreateVertexShader(const std::string& ShaderName, const char* FilePath);	//VS�V�F�[�_�[�̒ǉ�
	static PixelShader* CreatePixelShader(const std::string& ShaderName, const char* FilePath);		//PS�V�F�[�_�[�̒ǉ�
	static bool SetPointerVertexShader(const std::string& ShaderName,VertexShader* pVertexShader);		//VS�V�F�[�_�[�̒ǉ�
	static bool SetPointerPixelShader(const std::string& ShaderName, PixelShader* pPixelShader);		//PS�V�F�[�_�[�̒ǉ�
	static VertexShader* GetVertexShader(const std::string& Name);									//VS�V�F�[�_�[�̎擾
	static PixelShader* GetPixelShader(const std::string& Name);									//PS�V�F�[�_�[�̎擾
	static bool ReleaseVertexShader(const std::string& ShaderName);
	static bool ReleasePixelShader(const std::string& ShaderName);
	static void AllReleaseShader();

	static void SetUseAllObjectVS(bool use);							//���ׂẴI�u�W�F�N�g�ɐݒ肷��V�F�[�_
	static void SetUseAllObjectPS(bool use);							//���ׂẴI�u�W�F�N�g�ɐݒ肷��V�F�[�_
	static VertexShader* SetAllObjectVS(const std::string& ShaderName);		//���ׂẴI�u�W�F�N�g�ɐݒ肷��V�F�[�_
	static PixelShader* SetAllObjectPS(const std::string& ShaderName);			//���ׂẴI�u�W�F�N�g�ɐݒ肷��V�F�[�_
	static bool GetUseAllObjectVS();
	static bool GetUseAllObjectPS();
	static VertexShader* GetAllObjectVS();
	static PixelShader* GetAllObjectPS();

private:
	static std::map<std::string, VertexShader*> m_pVertexShaders;
	static std::map<std::string, PixelShader*> m_pPixelShaders;

	static bool m_isUseAllObjectShader_VS;
	static VertexShader* m_pAllObjectShader_VS;
	static bool m_isUseAllObjectShader_PS;
	static PixelShader* m_pAllObjectShader_PS;
};