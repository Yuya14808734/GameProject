#include "ModelDrawer.h"

std::map<std::string, ModelDrawer::ModelInformation> ModelDrawer::m_Models;
ConstantBuffer* ModelDrawer::m_pConstantBuffer;
VertexShader* ModelDrawer::m_pVertexShader;

void ModelDrawer::LoadModel(const char* FilePath, std::string& ModelName)
{
	//���f�������邩��T��
	std::map<std::string, ModelInformation>::iterator it = m_Models.find(ModelName);

	if (it != m_Models.end())
	{
		return;
	}

	//���f�����̐ݒ�
	m_Models.insert(std::make_pair(ModelName, ModelInformation{nullptr}));

	m_Models[ModelName].model = new Model();
	m_Models[ModelName].model->SetVertexShader(m_pVertexShader);

	if (!m_Models[ModelName].model->Load(FilePath, false))
	{
		MessageBox(nullptr, "���f���ǂݍ��݃G���[", ModelName.c_str(), MB_OK);
	}
}

void ModelDrawer::LoadAnime(const char* FilePath, std::string& AnimeName, std::string& ModelName)
{
	//�܂��ݒ肵�������f��������̂�
	std::map<std::string, ModelInformation>::iterator 
		model_it = m_Models.find(ModelName);

	if(model_it != m_Models.end())
	{
		std::string ErrorTitle = ModelName + "/" + AnimeName;
		MessageBox(nullptr, "���[�V������ǉ����������f�����ǉ�����Ă܂���", ErrorTitle.c_str(), MB_OK);
		return;
	}
	//���������T���ɍs���̂��ʓ|�Ȃ̂ŃA�h���X���������܂�
	ModelInformation* pModelInfo = &((*model_it).second);

	//���f���̐��������܂������Ă��Ȃ����
	if (pModelInfo->model == nullptr)
	{
		std::string ErrorTitle = ModelName + "/" + AnimeName;
		MessageBox(nullptr, "���[�V������ǉ����������f�����������Ă܂���", ErrorTitle.c_str(), MB_OK);
		return;
	}

	std::map<std::string, Model::AnimeNo>::iterator anime_it = 
		pModelInfo->animation.find(AnimeName);

	//�ݒ肵�����A�j���[�V�����������ݒ肳��Ă����
	if (anime_it != pModelInfo->animation.end())
	{
		std::string ErrorTitle = ModelName + "/" + AnimeName;
		MessageBox(nullptr, "���̖��O�Ń��[�V�������ݒ肵�Ă���܂�", ErrorTitle.c_str(), MB_OK);
	}

	//�����ŃA�j���[�V������ǉ�����
	pModelInfo->animation.insert(std::make_pair(AnimeName,
		pModelInfo->model->AddAnimation(FilePath)));

	if (pModelInfo->animation[AnimeName] == Model::ANIME_NONE)
	{
		std::string ErrorTitle = ModelName + "/" + AnimeName;
		MessageBox(nullptr, "�A�j���[�V�����̓ǂݍ��݃G���[�ł�", ErrorTitle.c_str(), MB_OK);
	}
}

Model* ModelDrawer::GetModel(const std::string& ModelName)
{
	//�擾���������f�������邩
	std::map<std::string, ModelInformation>::iterator
		model_it = m_Models.find(ModelName);
	if (model_it != m_Models.end())
	{
		//�Ȃ������ꍇ��nullptr��Ԃ��܂�
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
		//���f����������Ȃ������ꍇ
		std::string ErrorTitle = ModelName;
		MessageBox(nullptr, "���f��������܂���", ErrorTitle.c_str(), MB_OK);
		return;
	}

	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX scalemat, rotmat, transmat;
	scalemat = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	rotmat = DirectX::XMMatrixRotationRollPitchYaw(rotate.x, rotate.y, rotate.z);
	transmat = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	DirectX::XMStoreFloat4x4(&mat[0], scalemat * rotmat * transmat);

	
}