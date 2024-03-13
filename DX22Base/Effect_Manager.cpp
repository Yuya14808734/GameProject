#include "Effect_Manager.h"
#include "Scene.h"
#include "CameraManager.h"
#include "DirectX.h"
#include "main.h"

//���̂Â���
Effekseer::ManagerRef EffectManager::m_efkManager;
EffekseerRendererDX11::RendererRef EffectManager::m_efkRenderer;
std::map<std::string, Effekseer::EffectRef> EffectManager::m_Effect;
unsigned int EffectManager::m_EffectTimeCount;
bool EffectManager::m_IsDrawEffect = false;

void EffectManager::EffectInit()
{
	//EffeckSeer�̏�����
	m_efkManager = Effekseer::Manager::Create(1000);

	auto graphicsDevice =
		EffekseerRendererDX11::CreateGraphicsDevice(
			GetDevice(), GetContext());

	m_efkRenderer = EffekseerRendererDX11::Renderer::Create(graphicsDevice, 8000);

	m_efkManager->SetSpriteRenderer(m_efkRenderer->CreateSpriteRenderer());
	m_efkManager->SetRibbonRenderer(m_efkRenderer->CreateRibbonRenderer());
	m_efkManager->SetRingRenderer(m_efkRenderer->CreateRingRenderer());
	m_efkManager->SetTrackRenderer(m_efkRenderer->CreateTrackRenderer());
	m_efkManager->SetModelRenderer(m_efkRenderer->CreateModelRenderer());

	m_efkManager->SetTextureLoader(m_efkRenderer->CreateTextureLoader());
	m_efkManager->SetModelLoader(m_efkRenderer->CreateModelLoader());
	m_efkManager->SetMaterialLoader(m_efkRenderer->CreateMaterialLoader());
	m_efkManager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());

	m_EffectTimeCount = 0;

	//===============================================================================
	//�G�t�F�N�g�̒ǉ�
	EffectManager::Add_Effect("LaserEffect", u"Asset/Effect/Laser01.efkefc");
	EffectManager::Add_Effect("RingEffect", u"Asset/Effect/ShiningRing.efkefc");
	EffectManager::Add_Effect("C00_S2", u"Assets/Effect/Character00/Character00_AttackS2.efkefc");
	EffectManager::Add_Effect("C00_AirN", u"Assets/Effect/Character00/Character00_AttackAirN.efkefc");
	EffectManager::Add_Effect("DeadEffect", u"Assets/Effect/GameEffect/DeadEffect.efkefc");
	EffectManager::Add_Effect("WinnerEffect", u"Assets/Effect/WinnerEffect.efkefc");
	EffectManager::Add_Effect("FireSparksEffect", u"Assets/Effect/FireSparks.efkefc");
	//EffectManager::Add_Effect("DamageEffect00", u"Assets/Effect/DamageEffect00.efkefc");
	EffectManager::Add_Effect("DamageEffect01", u"Assets/Effect/DamageEffect01.efkefc");
	EffectManager::Add_Effect("DamageEffect02", u"Assets/Effect/DamageEffect02.efkefc");
	EffectManager::Add_Effect("DashEffect01", u"Assets/Effect/DashEffect.efkefc");

	//===============================================================================

	m_IsDrawEffect = false;
}

void EffectManager::EffectUninit()
{
	//EffeckSeer�̏I������
	for (auto copy : m_Effect)
	{
		copy.second.Reset();
	}
	m_Effect.clear();

	m_efkRenderer.Reset();
	m_efkManager.Reset();
}

Effekseer::ManagerRef& EffectManager::GetManager()
{
	return m_efkManager;
}

Effekseer::EffectRef EffectManager::GetEffect(std::string EffectName)
{
	return m_Effect[EffectName];
}

void EffectManager::EffectUpdate()
{
	m_EffectTimeCount++;
}

void EffectManager::EffectDraw(Effekseer::Handle Handle)
{
	if (!m_IsDrawEffect)
	{
		return;
	}

	//�J�����������Ă���
	CameraBase* pCamera = CameraManager::GetInstance().GetSceneCamera();

	if (pCamera == nullptr)
	{
		return;
	}

	//EffekSeer-------------------------------------------------------------------------

	DirectX::XMFLOAT3 Camera_Pos = pCamera->GetPos_xmfloat();
	DirectX::XMFLOAT3 Camera_Look = pCamera->GetLook_xmfloat();

	//---effekseer�̕`��

	//���_�ʒu��ݒ�
	auto viewrPosition = Effekseer::Vector3D(Camera_Pos.x, Camera_Pos.y, -Camera_Pos.z);
	auto lookPosition = Effekseer::Vector3D(Camera_Look.x, Camera_Look.y, -Camera_Look.z);

	//���e�s���ݒ�(�쐬)
	Effekseer::Matrix44 projectMatrix;
	projectMatrix.PerspectiveFovRH(
		pCamera->GetFovAngle() / 180.0f * 3.14f, static_cast<float>(GetAppWidth()) / static_cast<float>(GetAppHeight()),
		pCamera->GetNearLength(), pCamera->GetFarLength());

	//�J�����s���ݒ�(�쐬)
	Effekseer::Matrix44 cameraMatrix;
	cameraMatrix.LookAtRH(viewrPosition, lookPosition, Effekseer::Vector3D(0.0f, 1.0f, 0.0f));

	//���C���[�p�����[�^�̐ݒ�
	Effekseer::Manager::LayerParameter layerParameter;
	layerParameter.ViewerPosition = viewrPosition;
	m_efkManager->SetLayerParameter(0, layerParameter);

	//���Ԃ��X�V����
	m_efkRenderer->SetTime(static_cast<float>(m_EffectTimeCount));

	//�}�l�[�W���[�̍X�V
	Effekseer::Manager::UpdateParameter updateParameter;
	m_efkManager->Update(updateParameter);

	//���e�s���ݒ�
	m_efkRenderer->SetProjectionMatrix(projectMatrix);

	//�J�����s���ݒ�
	m_efkRenderer->SetCameraMatrix(cameraMatrix);

	m_efkManager;

	//�G�t�F�N�g�̕`��J�n�������s��
	m_efkRenderer->BeginRendering();

	//�G�t�F�N�g�̕`����s��
	Effekseer::Manager::DrawParameter drawParameter;
	drawParameter.ZNear = 0.0f;
	drawParameter.ZFar = 1.0f;
	drawParameter.ViewProjectionMatrix =
		m_efkRenderer->GetCameraProjectionMatrix();
	m_efkManager->DrawHandle(Handle);

	//�G�t�F�N�g�̕`��I���������s��
	m_efkRenderer->EndRendering();

}

void EffectManager::SetIsDrawEffect(bool IsDraw)
{
	m_IsDrawEffect = IsDraw;
}

void EffectManager::Add_Effect(std::string name, const char16_t* filePath)
{
	std::map<std::string, Effekseer::EffectRef>::iterator it = m_Effect.find(name);

	//���������ꍇ
	if (it != m_Effect.end()) {
		return;
	}
	//�ǉ�
	m_Effect.insert(std::make_pair(name, Effekseer::EffectRef{}));

	m_Effect[name] =
		Effekseer::Effect::Create(m_efkManager, filePath);
}