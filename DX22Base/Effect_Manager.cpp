#include "Effect_Manager.h"
#include <Effekseer.h>//インクルードディレクトリを変更した後これを書く
#include <EffekseerRendererDX11.h>
#include "DirectX.h"

//実体づくり
Effekseer::ManagerRef Effect_Manager::m_efkManager;
EffekseerRendererDX11::RendererRef Effect_Manager::m_efkRenderer;
std::map<std::string, Effect_Manager::Effect_Info> Effect_Manager::m_Effect;


void Effect_Manager::Effect_Init()
{
	//EffeckSeerの初期化
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

	Add_Effect("KIRAKIRA", u"Assets/Effect/Kirakira.efkefc");

}
void Effect_Manager::Effect_Uninit()
{
	//EffeckSeerの終了処理
	for (auto copy : m_Effect)
	{
		copy.second.effect.Reset();
	}
	m_Effect.clear();
	
	m_efkRenderer.Reset();
	m_efkManager.Reset();
	//-----------------------------------------
}

Effekseer::ManagerRef Effect_Manager::GetManager()
{
	return m_efkManager;
}

Effekseer::EffectRef Effect_Manager::GetEffect(std::string EffectName)
{
	return m_Effect[EffectName].effect;
}

void Effect_Manager::Add_Effect(std::string EffectName, const char16_t* FileName)
{
	std::map<std::string, Effect_Info>::iterator it = m_Effect.find(EffectName);

	//見つかった場合
	if (it != m_Effect.end()) {
		//MessageBox(nullptr, "もうその名前で作られています", "Error", MB_OK);
		return;
	}
	//追加
	m_Effect.insert(std::make_pair(EffectName, Effect_Info{}));

	Effekseer::ManagerRef n_efkManager;
	m_Effect[EffectName].effect = 
		Effekseer::Effect::Create(m_efkManager,FileName);
}

//エフェクトを再生する
void Effect_Manager::Play_Effect(std::string EffectName,DirectX::XMFLOAT3 Position)
{
	m_Effect[EffectName].Handle = m_efkManager->Play(m_Effect[EffectName].effect, Position.x, -Position.y, Position.z);
}

void Effect_Manager::Play_Effect(std::string EffectName, DirectX::XMFLOAT3 Position, DirectX::XMFLOAT3 Size)
{
	m_Effect[EffectName].Handle = m_efkManager->Play(m_Effect[EffectName].effect, Position.x, Position.y, Position.z);
	m_efkManager->SetScale(m_Effect[EffectName].Handle, Size.x, Size.y, Size.z);
}

void Effect_Manager::Stop_Effect(std::string EffectName)
{
	m_efkManager->StopEffect(m_Effect[EffectName].Handle);
}

//エフェクトを描画する
void Effect_Manager::Draw_Effect(CameraBase* pCamera)
{
	//EffekSeer-------------------------------------------------------------------------
	const unsigned int SCREEN_WIDTH = 1280;
	const unsigned int SCREEN_HEIGHT = 720;

	static int Time = 0;

	DirectX::XMFLOAT3 Camera_Pos = pCamera->GetPos();
	DirectX::XMFLOAT3 Camera_Look = pCamera->GetLook();

	//---effekseerの描画

	//視点位置を設定
	auto viewrPosition = Effekseer::Vector3D(Camera_Pos.x,Camera_Pos.y, -Camera_Pos.z);
	auto lookPosition = Effekseer::Vector3D(Camera_Look.x, Camera_Look.y, -Camera_Look.z);

	//投影行列を設定(作成)
	Effekseer::Matrix44 projectMatrix;
	projectMatrix.PerspectiveFovRH(
		80.0f / 180.0f * 3.14f, (float)SCREEN_WIDTH / SCREEN_HEIGHT,
		1.0f, 500.0f);

	//カメラ行列を設定(作成)
	Effekseer::Matrix44 cameraMatrix;
	cameraMatrix.LookAtRH(viewrPosition,lookPosition,Effekseer::Vector3D(0.0f, 1.0f, 0.0f));

	//レイヤーパラメータの設定
	Effekseer::Manager::LayerParameter layerParameter;
	layerParameter.ViewerPosition = viewrPosition;
	m_efkManager->SetLayerParameter(0, layerParameter);

	//時間を更新する
	m_efkRenderer->SetTime(Time);

	//マネージャーの更新
	Effekseer::Manager::UpdateParameter updateParameter;
	m_efkManager->Update(updateParameter);

	//投影行列を設定
	m_efkRenderer->SetProjectionMatrix(projectMatrix);

	//カメラ行列を設定
	m_efkRenderer->SetCameraMatrix(cameraMatrix);
	//エフェクトの描画開始処理を行う
	m_efkRenderer->BeginRendering();

		//エフェクトの描画を行う
		Effekseer::Manager::DrawParameter drawParameter;
		drawParameter.ZNear = 0.0f;
		drawParameter.ZFar = 1.0f;
		drawParameter.ViewProjectionMatrix =
			m_efkRenderer->GetCameraProjectionMatrix();
		m_efkManager->Draw(drawParameter);

	//エフェクトの描画終了処理を行う
	m_efkRenderer->EndRendering();

	Time++;
}