#include "ModelDrawer.h"
#include "CameraManager.h"
#include <Windows.h>
#include "ShaderManager.h"

std::map<std::string, ModelDrawer::ModelInformation*> ModelDrawer::m_Models;
ConstantBuffer* ModelDrawer::m_pConstantBuffer = nullptr;
VertexShader* ModelDrawer::m_pDefaultVertexShader = nullptr;

void ModelDrawer::InitModels()
{
	//�V�F�[�_�[�ǂݍ��ݏ���(�O��쐬����ModelVS.cso��ǂݍ���)
	m_pDefaultVertexShader = new VertexShader;
	if (FAILED(m_pDefaultVertexShader->Load("Assets/Shader/ModelVS.cso")))
	{
		MessageBox(nullptr, "ModelVS.cso", "Error", MB_OK);
	}

	//�萔�o�b�t�@�쐬(���[���h�A�r���[�A�v���W�F�N�V�����̃f�[�^���V�F�[�_�ɑ���
	m_pConstantBuffer = new ConstantBuffer();
	m_pConstantBuffer->Create(sizeof(DirectX::XMFLOAT4X4) * 3);
}

void ModelDrawer::UninitModels()
{
	DestroyAllModel(true);
	delete m_pConstantBuffer;
	m_pConstantBuffer = nullptr;
	delete m_pDefaultVertexShader;
	m_pDefaultVertexShader = nullptr;
}

bool ModelDrawer::LoadModel(const char* FilePath, const std::string& ModelName, float Scale)
{
	//���f�������邩��T��
	std::map<std::string, ModelInformation*>::iterator it = m_Models.find(ModelName);

	if (it != m_Models.end())
	{
		return true;
	}

	ModelInformation* ModelInfo = new ModelInformation();
	ModelInfo->model = new Model();

	if (!ModelInfo->model->Load(FilePath,Scale, false))
	{
		//MessageBox(nullptr, "���f���ǂݍ��݃G���[", ModelName.c_str(), MB_OK);
		//delete ModelInfo;
		//return false;
	}

	ModelInfo->model->SetVertexShader(m_pDefaultVertexShader);
	
	//���f�����̐ݒ�
	m_Models.insert(std::make_pair(ModelName, ModelInfo));

	return true;
}

bool ModelDrawer::LoadModelAndTexture(const char * ModelFilePath, const char * TextureFilePath, const std::string & ModelName, float Scale)
{
	//���f�������邩��T��
	std::map<std::string, ModelInformation*>::iterator it = m_Models.find(ModelName);

	if (it != m_Models.end())
	{
		return true;
	}

	ModelInformation* ModelInfo = new ModelInformation();
	ModelInfo->model = new Model();

		if (!ModelInfo->model->LoadAndTexture(ModelFilePath, TextureFilePath, Scale, false))
	{
		//MessageBox(nullptr, "���f���ǂݍ��݃G���[", ModelName.c_str(), MB_OK);
		//delete ModelInfo;
		//return false;
	}

	ModelInfo->model->SetVertexShader(m_pDefaultVertexShader);

	//���f�����̐ݒ�
	m_Models.insert(std::make_pair(ModelName, ModelInfo));

	return true;
}

bool ModelDrawer::LoadAnime(const char* FilePath, const std::string& AnimeName, const std::string& ModelName)
{
	//�܂��ݒ肵�������f��������̂�
	std::map<std::string, ModelInformation*>::iterator 
		model_it = m_Models.find(ModelName);

	if(model_it == m_Models.end())
	{
		std::string ErrorTitle = ModelName + "/" + AnimeName;
		MessageBox(nullptr, "���[�V������ǉ����������f�����ǉ�����Ă܂���", ErrorTitle.c_str(), MB_OK);
		return false;
	}
	//���������T���ɍs���̂��ʓ|�Ȃ̂ŃA�h���X���������܂�
	ModelInformation* pModelInfo = (*model_it).second;

	//���f���̐��������܂������Ă��Ȃ����
	if (pModelInfo->model == nullptr)
	{
		std::string ErrorTitle = ModelName + "/" + AnimeName;
		MessageBox(nullptr, "���[�V������ǉ����������f�����������Ă܂���", ErrorTitle.c_str(), MB_OK);
		return false;
	}

	std::map<std::string, Model::AnimeNo>::iterator anime_it = 
		pModelInfo->animation.find(AnimeName);

	//�ݒ肵�����A�j���[�V�����������ݒ肳��Ă����
	if (anime_it != pModelInfo->animation.end())
	{
		return true;
	}

	//�����ŃA�j���[�V������ǉ�����
	pModelInfo->animation.insert(std::make_pair(AnimeName,
		pModelInfo->model->AddAnimation(FilePath)));

	if (pModelInfo->animation[AnimeName] == Model::ANIME_NONE)
	{
		std::string ErrorTitle = ModelName + "/" + AnimeName;
		MessageBox(nullptr, "�A�j���[�V�����̓ǂݍ��݃G���[�ł�", ErrorTitle.c_str(), MB_OK);
		return false;
	}

	return true;
}

Model* ModelDrawer::GetModel(const std::string& ModelName)
{
	//�擾���������f�������邩
	std::map<std::string, ModelInformation*>::iterator
		model_it = m_Models.find(ModelName);
	if (model_it == m_Models.end())
	{
		//�Ȃ������ꍇ��nullptr��Ԃ��܂�
		return nullptr;
	}
	return (*model_it).second->model;
}

void ModelDrawer::DrawModel(const std::string& ModelName, const CVector3& pos, const CVector3& scale, const CVector3& rotate)
{
	CameraBase* pCamera = CameraManager::GetInstance().GetSceneCamera();

	if(pCamera == nullptr)
	{
		return;
	}

	std::map<std::string, ModelInformation*>::iterator
		model_it = m_Models.find(ModelName);

	if (model_it == m_Models.end())
	{
		//���f����������Ȃ������ꍇ
		std::string ErrorTitle = ModelName;
		MessageBox(nullptr, "���f��������܂���", ErrorTitle.c_str(), MB_OK);
		return;
	}

	CVector3 RadianRotate;
	RadianRotate.x = DirectX::XMConvertToRadians(rotate.x);
	RadianRotate.y = DirectX::XMConvertToRadians(rotate.y);
	RadianRotate.z = DirectX::XMConvertToRadians(rotate.z);

	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX worldMat;
	worldMat = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	worldMat *= DirectX::XMMatrixRotationRollPitchYaw(RadianRotate.x, RadianRotate.y, RadianRotate.z);
	worldMat *= DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(worldMat));
	mat[1] = pCamera->GetViewMatrix();				//�J�����̏�񂪕����莟�����
	mat[2] = pCamera->GetProjectionMatrix();		//�J�����̏�񂪕����莟�����
	
	//�萔�o�b�t�@�[�Ŏ󂯓n��
	m_pConstantBuffer->Write(mat);
	m_pConstantBuffer->BindVS(0);

	(*model_it).second->model->Draw();
}

void ModelDrawer::DestroyModel(const std::string& ModelName, bool MemoryDelete)
{
	//�J���������邩��T��
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

ModelDrawer::ModelDrawer()
	:m_pModelInfo(nullptr),
	m_pos(CVector3(0.0f,0.0f,0.0f)),
	m_scale(CVector3(1.0f,1.0f,1.0f)),
	m_rotate(CVector3(0.0f,0.0f,0.0f)),
	m_RotatePosShift(false),
	m_RotatePosShiftVector(CVector3(0.0f, 0.0f, 0.0f)),
	m_NowPlayAnimeNo(0),
	m_AnimTime(0.0f),
	m_AnimeNow(false),
	m_AnimeLoop(false),
	m_isCheckDraw(false),
	m_ObjectSize(0.0f),
	m_pVertexShader(m_pDefaultVertexShader),
	m_pPixelShader(nullptr)
{
}

ModelDrawer::~ModelDrawer()
{
}

void ModelDrawer::Draw()
{
	CameraBase* pCamera = 
		CameraManager::GetInstance().GetSceneCamera();

	if (pCamera == nullptr)
	{
		return;
	}

	if(m_isCheckDraw)
	{
		//������̒��ɓ����Ă��邩�ŕ`�悷�邩�����߂�
		if (!pCamera->CheckInObject(m_pos, m_ObjectSize))
		{
			return;
		}
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
	DirectX::XMMATRIX worldmat;

	worldmat = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	
	//��]�̒��S�̈ʒu���ړ����������Ƃ��Ɏg��
	if (m_RotatePosShift)
	{
		worldmat *= DirectX::XMMatrixTranslation(
			m_RotatePosShiftVector.x,
			m_RotatePosShiftVector.y,
			m_RotatePosShiftVector.z);
	}

	worldmat *= DirectX::XMMatrixRotationQuaternion(m_rotate.v);
	worldmat *= DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);

	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(worldmat));
	mat[1] = pCamera->GetViewMatrix();				//�J�����̏�񂪕����莟�����
	mat[2] = pCamera->GetProjectionMatrix();		//�J�����̏�񂪕����莟�����

	//�萔�o�b�t�@�[�Ŏ󂯓n��
	m_pConstantBuffer->Write(mat);
	m_pConstantBuffer->BindVS(0);

	//�A�j���[�V�����̐ݒ�
	if (m_AnimeNow)
	{
		m_pModelInfo->model->Play(m_NowPlayAnimeNo, m_AnimeLoop);
		m_pModelInfo->model->SetAnimeTime(m_NowPlayAnimeNo, m_AnimTime);
	}

	VertexShader* pNowVS = m_pVertexShader;
	PixelShader* pNowPS = m_pPixelShader;

	//�I�u�W�F�N�g���Ƃ̃V�F�[�_�[���g���Ă悢��
	if (ShaderManager::GetUseAllObjectVS())
	{
		pNowVS = ShaderManager::GetAllObjectVS();
	}

	if (ShaderManager::GetUseAllObjectPS())
	{
		pNowPS = ShaderManager::GetAllObjectPS();
	}

	m_pModelInfo->model->SetVertexShader(pNowVS);
	m_pModelInfo->model->SetPixelShader(pNowPS);
	m_pModelInfo->model->Draw();
}

void ModelDrawer::SetModel(const std::string& ModelName)
{
	std::map<std::string, ModelInformation*>::iterator
		model_it = m_Models.find(ModelName);
	if (model_it == m_Models.end())
	{
		//���f����������Ȃ������ꍇ
		std::string ErrorTitle = ModelName;
		MessageBox(nullptr, "���f��������܂���", ErrorTitle.c_str(), MB_OK);
		return;
	}

	m_pModelInfo = (*model_it).second;
}

ModelDrawer::ModelInformation* ModelDrawer::GetModel()
{
	return m_pModelInfo;
}

void ModelDrawer::PlayAnime(const std::string& AnimeName,bool Loop)
{
	//���f����񂪂Ȃ��ꍇ
	if (m_pModelInfo == nullptr)
	{
		return;
	}

	//���f�����̐��������Ă��Ȃ�
	if (m_pModelInfo->model == nullptr)
	{
		return;
	}

	//�A�j���[�V������T��
	std::map<std::string, Model::AnimeNo>::iterator it =
		m_pModelInfo->animation.find(AnimeName);
	if (it == m_pModelInfo->animation.end())
	{
		return;
	}

	//�A�j���[�V�����̍Đ�
	m_NowPlayAnimeNo = (*it).second;
	m_AnimeNow = true;
	m_AnimeLoop = Loop;
}

void ModelDrawer::SetAnimeTime(float time)
{
	m_AnimTime = time;
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

	float AnimeStartTime = m_pModelInfo->model->AnimeStartTime(m_NowPlayAnimeNo);
	float AnimeTotalTime = m_pModelInfo->model->AnimeTotalTime(m_NowPlayAnimeNo);

	SetAnimeTime((AnimeTotalTime - AnimeStartTime) * value + AnimeStartTime);
}

float ModelDrawer::GetAnimeTime()
{
	return m_pModelInfo->model->AnimeStartTime(m_NowPlayAnimeNo);
}

float ModelDrawer::GetAnimeEndTime()
{
	return m_pModelInfo->model->AnimeTotalTime(m_NowPlayAnimeNo);
}

void ModelDrawer::SetPosition(const CVector3& pos)
{
	m_pos = pos;
}

const CVector3& ModelDrawer::GetPosition()
{
	return m_pos;
}

void ModelDrawer::SetRotatePosShiftVector(const CVector3& vector)
{
	m_RotatePosShiftVector = vector;
}

const CVector3& ModelDrawer::GetRotatePosShiftVector()
{
	return m_RotatePosShiftVector;
}

void ModelDrawer::SetRotatePosShift(bool shift)
{
	m_RotatePosShift = shift;
}

bool ModelDrawer::IsRotatePosShift()
{
	return m_RotatePosShift;
}

void ModelDrawer::SetScale(const CVector3& scale)
{
	m_scale = scale;
}

const CVector3& ModelDrawer::GetScale()
{
	return m_scale;
}

void ModelDrawer::SetRotate(const CQuaternion& rotate)
{
	m_rotate = rotate;
}

void ModelDrawer::SetRotate(const CVector3& rotate)
{
	m_rotate.v = DirectX::XMQuaternionRotationRollPitchYaw(
		DirectX::XMConvertToRadians(rotate.x), 
		DirectX::XMConvertToRadians(rotate.y),
		DirectX::XMConvertToRadians(rotate.z));
}

const CQuaternion& ModelDrawer::GetRotate()
{
	return m_rotate;
}

void ModelDrawer::SetCulling(bool culling, float size)
{
	m_isCheckDraw = culling;
	m_ObjectSize = size;
}

void ModelDrawer::SetVertexShader(VertexShader* pVertexShader)
{
	m_pVertexShader = pVertexShader;
}

void ModelDrawer::SetPixelShader(PixelShader* pPixelShader)
{
	m_pPixelShader = pPixelShader;
}
