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
	static VertexShader* CreateVertexShader(const std::string& ShaderName, const char* FilePath);
	static PixelShader* CreatePixelShader(const std::string& ShaderName, const char* FilePath);
	static bool SetNewVertexShader(const std::string& ShaderName,VertexShader* pVertexShader);
	static bool SetNewPixelShader(const std::string& ShaderName, PixelShader* pPixelShader);
	static VertexShader* GetVertexShader(const std::string& Name);
	static PixelShader* GetPixelShader(const std::string& Name);
	static bool ReleaseVertexShader(const std::string& ShaderName);
	static bool ReleasePixelShader(const std::string& ShaderName);
	static void AllReleaseShader();

private:
	static std::map<std::string, VertexShader*> m_pVertexShaders;
	static std::map<std::string, PixelShader*> m_pPixelShaders;
};