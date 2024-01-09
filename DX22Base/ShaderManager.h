#pragma once
#include "Shader.h"
#include "ConstantBuffer.h"
#include <map>
#include <string>

class ShaderManager
{
public:
	static bool SetVertexShader(const std::string& ShaderName,VertexShader* pVertexShader);
	static bool SetPixelShader(const std::string& ShaderName, PixelShader* pPixelShader);
	static VertexShader* GetVertexShader(const std::string& Name);
	static PixelShader* GetPixelShader(const std::string& Name);
	static bool ReleaseVertexShader(const std::string& ShaderName);
	static bool ReleasePixelShader(const std::string& ShaderName);
	static void AllReleaseShader();

private:
	static std::map<std::string, VertexShader*> m_pVertexShaders;
	static std::map<std::string, PixelShader*> m_pPixelShaders;
};