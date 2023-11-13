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
	static void InitModels();
	static void UninitModels();
	static bool LoadModel(const char*, std::string&);
	static bool LoadAnime(const char*, std::string&, std::string&);
	static Model* GetModel(const std::string&);
	static void DrawModel(std::string& ModelName,CVector3& pos,CVector3& scale,CVector3& rotate);
	static void DestroyModel(std::string& ModelName, bool MemoryDelete);
	static void DestroyAllModel(bool MemoryDelete);

private:
	static std::map<std::string, ModelInformation*> m_Models;
	static ConstantBuffer* m_pConstantBuffer;
	static VertexShader* m_pVertexShader;

public:
	void Draw();
	void SetModel(std::string ModelName);
	ModelInformation* GetModel();
	void PlayAnime(std::string& AnimeName,bool Loop);
	void SetAnimeTime(float time);
	void SetAnimeLerp(float value);
	void SetPosition(CVector3& pos);
	void SetScale(CVector3& scale);
	void SetRotate(CQuaternion& rotate);
	void SetRotate(CVector3& rotate);

private:
	ModelInformation* m_pModelInfo = nullptr;
	CVector3 m_pos;
	CVector3 m_scale;
	CQuaternion m_rotate;
	Model::AnimeNo m_AnimeNo = 0;
	float m_AnimTime = 0.0f;
};
