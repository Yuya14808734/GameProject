#include "ModelDrawer.h"

std::map<std::string, ModelDrawer::ModelInformation> ModelDrawer::m_Models;
ConstantBuffer* ModelDrawer::m_pConstantBuffer;
VertexShader* ModelDrawer::m_pVertexShader;

void ModelDrawer::LoadModel(const char* FilePath, std::string& ModelName)
{
	//モデルがあるかを探す
	std::map<std::string, ModelInformation>::iterator it = m_Models.find(ModelName);

	if (it != m_Models.end())
	{
		return;
	}

	//モデル情報の設定
	m_Models.insert(std::make_pair(ModelName, ModelInformation{nullptr}));

	m_Models[ModelName].model = new Model();
	m_Models[ModelName].model->SetVertexShader(m_pVertexShader);

	if (!m_Models[ModelName].model->Load(FilePath, false))
	{
		MessageBox(nullptr, "モデル読み込みエラー", ModelName.c_str(), MB_OK);
	}
}

void ModelDrawer::LoadAnime(const char* FilePath, std::string& AnimeName, std::string& ModelName)
{
	//まず設定したいモデルがあるのか
	std::map<std::string, ModelInformation>::iterator 
		model_it = m_Models.find(ModelName);

	if(model_it != m_Models.end())
	{
		std::string ErrorTitle = ModelName + "/" + AnimeName;
		MessageBox(nullptr, "モーションを追加したいモデルが追加されてません", ErrorTitle.c_str(), MB_OK);
		return;
	}
	//いちいち探しに行くのが面倒なのでアドレスを持たせます
	ModelInformation* pModelInfo = &((*model_it).second);

	//モデルの生成がうまくいっていなければ
	if (pModelInfo->model == nullptr)
	{
		std::string ErrorTitle = ModelName + "/" + AnimeName;
		MessageBox(nullptr, "モーションを追加したいモデルが生成してません", ErrorTitle.c_str(), MB_OK);
		return;
	}

	std::map<std::string, Model::AnimeNo>::iterator anime_it = 
		pModelInfo->animation.find(AnimeName);

	//設定したいアニメーションがもう設定されていれば
	if (anime_it != pModelInfo->animation.end())
	{
		std::string ErrorTitle = ModelName + "/" + AnimeName;
		MessageBox(nullptr, "その名前でモーションが設定してあります", ErrorTitle.c_str(), MB_OK);
	}

	//ここでアニメーションを追加する
	pModelInfo->animation.insert(std::make_pair(AnimeName,
		pModelInfo->model->AddAnimation(FilePath)));

	if (pModelInfo->animation[AnimeName] == Model::ANIME_NONE)
	{
		std::string ErrorTitle = ModelName + "/" + AnimeName;
		MessageBox(nullptr, "アニメーションの読み込みエラーです", ErrorTitle.c_str(), MB_OK);
	}
}

Model* ModelDrawer::GetModel(const std::string& ModelName)
{
	//取得したいモデルがあるか
	std::map<std::string, ModelInformation>::iterator
		model_it = m_Models.find(ModelName);
	if (model_it != m_Models.end())
	{
		//なかった場合はnullptrを返します
		return nullptr;
	}
	return (*model_it).second.model;
}

void ModelDrawer::DrawModel(std::string& ModelName, CVector3& pos, CVector3& scale, CVector3& rotate)
{
	std::map<std::string, ModelInformation>::iterator
		model_it = m_Models.find(ModelName);
	if (model_it == m_Models.end())
	{
		//モデルが見つからなかった場合
		std::string ErrorTitle = ModelName;
		MessageBox(nullptr, "モデルがありません", ErrorTitle.c_str(), MB_OK);
		return;
	}

	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX scalemat, rotmat, transmat;
	scalemat = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	rotmat = DirectX::XMMatrixRotationRollPitchYaw(rotate.x, rotate.y, rotate.z);
	transmat = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	DirectX::XMStoreFloat4x4(&mat[0], scalemat * rotmat * transmat);

	
}