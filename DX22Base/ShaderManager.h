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
	static VertexShader* CreateVertexShader(const std::string& ShaderName, const char* FilePath);	//VSシェーダーの追加
	static PixelShader* CreatePixelShader(const std::string& ShaderName, const char* FilePath);		//PSシェーダーの追加
	static bool SetPointerVertexShader(const std::string& ShaderName,VertexShader* pVertexShader);		//VSシェーダーの追加
	static bool SetPointerPixelShader(const std::string& ShaderName, PixelShader* pPixelShader);		//PSシェーダーの追加
	static VertexShader* GetVertexShader(const std::string& Name);									//VSシェーダーの取得
	static PixelShader* GetPixelShader(const std::string& Name);									//PSシェーダーの取得
	static bool ReleaseVertexShader(const std::string& ShaderName);
	static bool ReleasePixelShader(const std::string& ShaderName);
	static void AllReleaseShader();

	static void SetUseAllObjectVS(bool use);							//すべてのオブジェクトに設定するシェーダ
	static void SetUseAllObjectPS(bool use);							//すべてのオブジェクトに設定するシェーダ
	static VertexShader* SetAllObjectVS(const std::string& ShaderName);		//すべてのオブジェクトに設定するシェーダ
	static PixelShader* SetAllObjectPS(const std::string& ShaderName);			//すべてのオブジェクトに設定するシェーダ
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