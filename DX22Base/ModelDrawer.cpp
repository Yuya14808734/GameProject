#include "ModelDrawer.h"

std::map<std::string, ModelDrawer::ModelInformation> ModelDrawer::m_Models;

void ModelDrawer::LoadModel(const char* FilePath, std::string& ModelName)
{
	std::map<std::string, ModelInformation>::iterator it = m_Models.find(ModelName);

	if (it != m_Models.end())
	{
		return;
	}

	m_Models.insert(std::make_pair(ModelName, ModelInformation{nullptr}));

	m_Models[ModelName].model = new Model();
	m_Models[ModelName].model->SetVertexShader(m_pVertexShader);

	if (!m_Models[ModelName].model->Load(FilePath, false))
	{
		MessageBox(nullptr, "ÉÇÉfÉãì«Ç›çûÇ›ÉGÉâÅ[", ModelName.c_str(), MB_OK);
	}
}

void ModelDrawer::LoadAnime(const char*, std::string&, std::string&)
{
}

Model* ModelDrawer::GetModel(const std::string&)
{
	return nullptr;
}

void ModelDrawer::DrawModel(std::string&, CVector3& pos, CVector3& size, CVector3& rotate)
{
}
