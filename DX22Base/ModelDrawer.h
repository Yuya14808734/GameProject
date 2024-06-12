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
	void Draw();											//モデルの描画
	void SetModel(const std::string& ModelName);			//モデルの設定
	ModelInformation* GetModel();							//設定しているモデル情報の取得
	void PlayAnime(const std::string& AnimeName,bool Loop);	//アニメーションの再生
	void SetAnimeTime(float time);							//再生時間設定(0～アニメーション終了時間)
	void SetAnimeLerp(float value);							//再生時間設定(0～1)
	float GetAnimeTime();									//今の再生時間取得
	float GetAnimeEndTime();								//再生しているアニメーションの終了時間取
	void SetPosition(const CVector3& pos);					//描画する位置を設定
	const CVector3& GetPosition();							//描画する位置を取得
	void SetRotatePosShiftVector(const CVector3& vector);	//回転する原点位置をずらす
	const CVector3& GetRotatePosShiftVector();				//ずらしたベクトルを取得
	void SetRotatePosShift(bool shift);						//回転する原点位置をずらすか設定
	bool IsRotatePosShift();								//回転する原点位置をずらしているか取得
	void SetScale(const CVector3& scale);					//大きさ設定
	const CVector3& GetScale();								//大きさ取得
	void SetRotate(const CQuaternion& rotate);				//回転設定(クォータニオンで設定)
	void SetRotate(const CVector3& rotate);					//回転設定(ピッチローヨーで設定)
	const CQuaternion& GetRotate();							//姿勢を取得(クォータニオン)
	void SetCulling(bool culling, float Length);			//視錐台による描画判定するか(大きさ設定)
	void SetVertexShader(VertexShader* pVertexShader);		//頂点シェーダー設定
	void SetDefaultVertexShader();							//元のシェーダーに戻す
	void SetPixelShader(PixelShader* pPixelShader);			//ピクセルシェーダー設定
	void SetDefaultPixelShader();

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
