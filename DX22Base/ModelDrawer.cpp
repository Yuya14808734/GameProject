#include "ModelDrawer.h"
#include "CameraManager.h"
#include <Windows.h>

std::map<std::string, ModelDrawer::ModelInformation*> ModelDrawer::m_Models;
ConstantBuffer* ModelDrawer::m_pConstantBuffer = nullptr;
VertexShader* ModelDrawer::m_pVertexShader = nullptr;

void ModelDrawer::InitModels()
{
	//シェーダー読み込み処理(前回作成したModelVS.csoを読み込む)
	m_pVertexShader = new VertexShader;
	if (FAILED(m_pVertexShader->Load("Assets/Shader/ModelVS.cso")))
	{
		MessageBox(nullptr, "ModelVS.cso", "Error", MB_OK);
	}

	//定数バッファ作成(ワールド、ビュー、プロジェクションのデータをシェーダに送る
	m_pConstantBuffer = new ConstantBuffer();
	m_pConstantBuffer->Create(sizeof(DirectX::XMFLOAT4X4) * 3);
}

void ModelDrawer::UninitModels()
{
	DestroyAllModel(true);
	delete m_pConstantBuffer;
	delete m_pVertexShader;
}

bool ModelDrawer::LoadModel(const char* FilePath, std::string& ModelName)
{
	//モデルがあるかを探す
	std::map<std::string, ModelInformation*>::iterator it = m_Models.find(ModelName);

	if (it != m_Models.end())
	{
		return false;
	}

	ModelInformation* ModelInfo = new ModelInformation();
	ModelInfo->model = new Model();
	ModelInfo->model->SetVertexShader(m_pVertexShader);

	if (!ModelInfo->model->Load(FilePath, false))
	{
		MessageBox(nullptr, "モデル読み込みエラー", ModelName.c_str(), MB_OK);
		delete ModelInfo;
		return false;
	}

	//モデル情報の設定
	m_Models.insert(std::make_pair(ModelName, ModelInfo));

	return true;
}

bool ModelDrawer::LoadAnime(const char* FilePath, std::string& AnimeName, std::string& ModelName)
{
	//まず設定したいモデルがあるのか
	std::map<std::string, ModelInformation*>::iterator 
		model_it = m_Models.find(ModelName);

	if(model_it == m_Models.end())
	{
		std::string ErrorTitle = ModelName + "/" + AnimeName;
		MessageBox(nullptr, "モーションを追加したいモデルが追加されてません", ErrorTitle.c_str(), MB_OK);
		return false;
	}
	//いちいち探しに行くのが面倒なのでアドレスを持たせます
	ModelInformation* pModelInfo = (*model_it).second;

	//モデルの生成がうまくいっていなければ
	if (pModelInfo->model == nullptr)
	{
		std::string ErrorTitle = ModelName + "/" + AnimeName;
		MessageBox(nullptr, "モーションを追加したいモデルが生成してません", ErrorTitle.c_str(), MB_OK);
		return false;
	}

	std::map<std::string, Model::AnimeNo>::iterator anime_it = 
		pModelInfo->animation.find(AnimeName);

	//設定したいアニメーションがもう設定されていれば
	if (anime_it != pModelInfo->animation.end())
	{
		std::string ErrorTitle = ModelName + "/" + AnimeName;
		MessageBox(nullptr, "その名前でモーションが設定してあります", ErrorTitle.c_str(), MB_OK);
		return false;
	}

	//ここでアニメーションを追加する
	pModelInfo->animation.insert(std::make_pair(AnimeName,
		pModelInfo->model->AddAnimation(FilePath)));

	if (pModelInfo->animation[AnimeName] == Model::ANIME_NONE)
	{
		std::string ErrorTitle = ModelName + "/" + AnimeName;
		MessageBox(nullptr, "アニメーションの読み込みエラーです", ErrorTitle.c_str(), MB_OK);
		return false;
	}

	return true;
}

Model* ModelDrawer::GetModel(const std::string& ModelName)
{
	//取得したいモデルがあるか
	std::map<std::string, ModelInformation*>::iterator
		model_it = m_Models.find(ModelName);
	if (model_it == m_Models.end())
	{
		//なかった場合はnullptrを返します
		return nullptr;
	}
	return (*model_it).second->model;
}

void ModelDrawer::DrawModel(std::string& ModelName, CVector3& pos, CVector3& scale, CVector3& rotate)
{
	CameraBase* pCamera = CameraManger::GetInstance().GetSceneCamera();

	if(pCamera == nullptr)
	{
		return;
	}

	std::map<std::string, ModelInformation*>::iterator
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
	mat[1] = pCamera->GetViewMatrix();		//カメラの情報が分かり次第実装
	mat[2] = pCamera->GetProjectionMatrix();		//カメラの情報が分かり次第実装
	
	//定数バッファーで受け渡し
	m_pConstantBuffer->Write(mat);
	m_pConstantBuffer->BindVS(0);

	(*model_it).second->model->Draw();
}

void ModelDrawer::DestroyModel(std::string& ModelName, bool MemoryDelete)
{
	//カメラがあるかを探す
	std::map<std::string, ModelInformation*>::iterator it = m_Models.find(ModelName);

	if (it == m_Models.end())
	{
		return;
	}

	if (MemoryDelete)
	{
		(*it).second->animation.clear();
		delete (*it).second->model;
		delete (*it).second;
	}

	m_Models.erase(it);
}

void ModelDrawer::DestroyAllModel(bool MemoryDelete)
{
	if (MemoryDelete)
	{
		for (std::pair<std::string, ModelInformation*> modelInfo : m_Models)
		{
			modelInfo.second->animation.clear();
			delete modelInfo.second->model;
			delete modelInfo.second;
		}
	}

	m_Models.clear();
}

void ModelDrawer::Draw()
{
	CameraBase* pCamera = CameraManger::GetInstance().GetSceneCamera();

	if (pCamera == nullptr)
	{
		return;
	}

	if (m_pModelInfo == nullptr)
	{
		return;
	}

	if (m_pModelInfo->model == nullptr)
	{
		return;
	}

	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX scalemat, rotmat, transmat;
	scalemat = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	rotmat = DirectX::XMMatrixRotationQuaternion(m_rotate.v);
	transmat = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	DirectX::XMStoreFloat4x4(&mat[0], scalemat * rotmat * transmat);
	mat[1] = pCamera->GetViewMatrix();		//カメラの情報が分かり次第実装
	mat[2] = pCamera->GetProjectionMatrix();		//カメラの情報が分かり次第実装

	//定数バッファーで受け渡し
	m_pConstantBuffer->Write(mat);
	m_pConstantBuffer->BindVS(0);

	m_pModelInfo->model->Draw();
}

void ModelDrawer::SetModel(std::string ModelName)
{
	std::map<std::string, ModelInformation*>::iterator
		model_it = m_Models.find(ModelName);
	if (model_it == m_Models.end())
	{
		//モデルが見つからなかった場合
		std::string ErrorTitle = ModelName;
		MessageBox(nullptr, "モデルがありません", ErrorTitle.c_str(), MB_OK);
		return;
	}

	m_pModelInfo = (*model_it).second;
}

ModelDrawer::ModelInformation* ModelDrawer::GetModel()
{
	return m_pModelInfo;
}

void ModelDrawer::PlayAnime(std::string& AnimeName,bool Loop)
{
	if (m_pModelInfo == nullptr)
	{
		return;
	}

	if (m_pModelInfo->model == nullptr)
	{
		return;
	}

	std::map<std::string, Model::AnimeNo>::iterator it =
		m_pModelInfo->animation.find(AnimeName);
	if (it == m_pModelInfo->animation.end())
	{
		return;
	}

	m_pModelInfo->model->Play((*it).second, Loop);
}

void ModelDrawer::SetAnimeTime(float time)
{
	m_pModelInfo->model->SetAnimeTime(m_AnimeNo, time);
}

void ModelDrawer::SetAnimeLerp(float value)
{
	if (value > 1.0f)
	{
		value = 1.0f;
	}

	if (value < 0.0f)
	{
		value = 0.0f;
	}

	float AnimeStartTime = m_pModelInfo->model->AnimeStartTime(m_AnimeNo);
	float AnimeTotalTime = m_pModelInfo->model->AnimeTotalTime(m_AnimeNo);

	SetAnimeTime((AnimeTotalTime - AnimeStartTime) * value + AnimeStartTime);
}

void ModelDrawer::SetPosition(CVector3& pos)
{
	m_pos = pos;
}

void ModelDrawer::SetScale(CVector3& scale)
{
	m_scale = scale;
}

void ModelDrawer::SetRotate(CQuaternion& rotate)
{
	m_rotate = rotate;
}

void ModelDrawer::SetRotate(CVector3& rotate)
{
	m_rotate.v = DirectX::XMQuaternionRotationRollPitchYaw(
		DirectX::XMConvertToRadians(rotate.x), 
		DirectX::XMConvertToRadians(rotate.y),
		DirectX::XMConvertToRadians(rotate.z));
}
