#pragma once
#include "Model.h"
#include <string>
#include <map>
#include "Calculation.h"
#include "ConstantBuffer.h"
#include "Shader.h"

class ModelDrawer
{
private:
	struct ModelInformation
	{
		Model* model = nullptr;
		std::map<std::string, Model::AnimeNo> animation;
	};

public:
	static void LoadModel(const char*, std::string&);
	static void LoadAnime(const char*, std::string&, std::string&);
	static Model* GetModel(const std::string&);
	static void DrawModel(std::string& ModelName,CVector3& pos,CVector3& scale,CVector3& rotate);

private:
	static std::map<std::string, ModelInformation> m_Models;
	static ConstantBuffer* m_pConstantBuffer;
	static VertexShader* m_pVertexShader;

public:
	void SetModel(Model*);
	Model* GetModel();
	void PlayAnime(std::string&);
	void SetPosition(CVector3&);
	void SetSize(CVector3&);
	void SetRotate(CQuaternion&);
	void SetRotate(CVector3&);

private:
	Model* m_pModel = nullptr;
	CVector3 m_pos;
	CVector3 m_size;
	CQuaternion m_rotate;
	float m_AnimTime = 0.0f;
};
