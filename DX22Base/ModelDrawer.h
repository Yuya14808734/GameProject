#pragma once
#include "Model.h"
#include <string>
#include <map>
#include "Calculation.h"
#include "ConstantBuffer.h"
#include "Shader.h"

class ModelDrawer
{
public:
	struct ModelInformation
	{
		Model* model = nullptr;
		std::map<std::string, Model::AnimeNo> animation;
	};

public:
	static void InitModels();
	static void UninitModels();
	static bool LoadModel(const char* FilePath, const std::string& ModelName, float Scale = 1.0f);
	static bool LoadModelAndTexture(const char* ModelFilePath, const char* TextureFilePath, const std::string& ModelName, float Scale = 1.0f);
	static bool LoadAnime(const char* FilePath, const std::string& AnimeName, const std::string& ModelName);
	static Model* GetModel(const std::string& ModelName);
	static void DrawModel(const std::string& ModelName, const CVector3& pos, const CVector3& scale, const CVector3& rotate);
	static void DestroyModel(const std::string& ModelName, bool MemoryDelete);
	static void DestroyAllModel(bool MemoryDelete);

private:
	static std::map<std::string, ModelInformation*> m_Models;
	static ConstantBuffer* m_pConstantBuffer;
	static VertexShader* m_pDefaultVertexShader;

public:
	ModelDrawer();
	~ModelDrawer();
	void Draw();
	void SetModel(const std::string& ModelName);
	ModelInformation* GetModel();
	void PlayAnime(const std::string& AnimeName,bool Loop);
	void SetAnimeTime(float time);
	void SetAnimeLerp(float value);
	float GetAnimeTime();
	float GetAnimeEndTime();
	void SetPosition(const CVector3& pos);
	const CVector3& GetPosition();
	void SetRotatePosShiftVector(const CVector3& vector);
	const CVector3& GetRotatePosShiftVector();
	void SetRotatePosShift(bool shift);
	bool IsRotatePosShift();
	void SetScale(const CVector3& scale);
	const CVector3& GetScale();
	void SetRotate(const CQuaternion& rotate);
	void SetRotate(const CVector3& rotate);
	const CQuaternion& GetRotate();
	void SetCulling(bool culling, float Length);

private:
	ModelInformation* m_pModelInfo = nullptr;
	CVector3 m_pos;
	CVector3 m_scale;
	CQuaternion m_rotate;
	bool m_RotatePosShift = false;
	CVector3 m_RotatePosShiftVector;
	Model::AnimeNo m_NowPlayAnimeNo = 0;
	float m_AnimTime = 0.0f;
	bool m_AnimeNow = false;
	bool m_AnimeLoop = false;
	bool m_isCheckDraw = false;
	float m_ObjectSize = 0.0f;
	VertexShader* m_pVertexShader = nullptr;
	PixelShader* m_pPixelShader = nullptr;
};
