#include "Number2D.h"
#include "Main.h"

Number2D::Number2D()
	:m_pTexture(nullptr)
	, m_pVertexShader(nullptr)
	, m_pPixelShader(nullptr)
	, m_pos({ 0.0f,0.0f,0.0f })
	, m_size({ 1.0f,1.0f })
	, m_UVpos({ 0.0f,0.0f })
	, m_UVsize({ 1.0f,1.0f })
	, m_color({ 1.0f,1.0f,1.0f,1.0f })
	, m_Number(0)
	, m_SplitX(1)
	, m_SplitY(1)
{
}

Number2D::~Number2D()
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

void Number2D::Update()
{
}

void Number2D::PrevDraw()
{
	
}

void Number2D::Draw()
{
	if (m_pTexture == nullptr)
	{
		return;
	}

	PrevDraw();

	//�V�F�[�_�[�̕ύX
	if (m_pVertexShader != nullptr)
	{
		Sprite::SetVertexShader(m_pVertexShader);
	}
	else
	{
		Sprite::SetDefaultVertexShader();
	}

	if (m_pPixelShader != nullptr)
	{
		Sprite::SetPixelShader(m_pPixelShader);
	}
	else
	{
		Sprite::SetDefaultPixelShader();
	}

	DirectX::XMFLOAT4X4 fView;
	DirectX::XMStoreFloat4x4(&fView,
		DirectX::XMMatrixIdentity());

	//�A�v���W�F�N�V�����s�񂪏d�v
	//���̍s���2D�̃X�N���[���̑傫�������߂�
	DirectX::XMFLOAT4X4 fProj;
	DirectX::XMStoreFloat4x4(&fProj,
		DirectX::XMMatrixTranspose(
			DirectX::XMMatrixOrthographicOffCenterLH(
				0.0f,//��ʍ��[�̍��W
				GetAppWidth(),//��ʉE�[�̍��W
				GetAppHeight(),	//��ʉ��[�̍��W
				0.0f,	//��ʏ�[�̍��W
				-1.0f,	//2�����Ŏʂ���ŏ��l
				1.0f	//2�����Ŏʂ���ő�l
			)
		));

	CVector3 DrawPos = m_pos;	//��ԍŏ��̐������`�悳���ꏊ
								//���ɐ����͕`�悳���

	int DrawNums = m_Number;
	//�����̕`��
	do
	{
		int DrawNum = DrawNums % 10;	//�`�悷���̐���

		//�e�N�X�`����UV���W������o��
		m_UVpos.x = static_cast<float>(DrawNum % m_SplitX) * m_UVsize.x;
		m_UVpos.y = static_cast<float>(DrawNum / m_SplitX) * m_UVsize.y;

		//���[���h�s��ŉ�ʂ̕\���ʒu���v�Z
		DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(
			DrawPos.x, DrawPos.y, DrawPos.z);
		DirectX::XMFLOAT4X4 fWorld;
		DirectX::XMStoreFloat4x4(&fWorld,
			DirectX::XMMatrixTranspose(T));

		//�X�v���C�g�̐ݒ�
		Sprite::SetWorld(fWorld);
		Sprite::SetView(fView);
		Sprite::SetProjection(fProj);
		Sprite::SetSize(m_size.f);
		Sprite::SetUVPos(m_UVpos.f);
		Sprite::SetUVScale(m_UVsize.f);
		Sprite::SetTexture(m_pTexture);
		Sprite::SetColor(m_color);
		Sprite::Draw();

		//���̐�����`�悷��Ƃ��ɂ��炵�Ă��
		DrawPos.x -= m_size.x;

		DrawNums /= 10;

	} while (DrawNums != 0);
}

void Number2D::SetPos(const DirectX::XMFLOAT3& pos)
{
	m_pos.f = pos;
}

void Number2D::SetPos(const CVector2& pos)
{
	m_pos = pos;
}

const CVector2& Number2D::GetPos()
{
	return m_pos;
}

void Number2D::SetSize(const DirectX::XMFLOAT2& size)
{
	m_size.f = size;
}

void Number2D::SetSize(const CVector2& size)
{
	m_size = size;
}

const CVector2& Number2D::GetSize()
{
	return m_size;
}

void Number2D::SetNumberTexture(const char* FilePath, int SplitX, int SplitY)
{
	//�摜�Ɋւ��Ă͏ォ��E�ɂ����Đ���������ł���悤��
	//�e�N�X�`���ł͂Ȃ��Ƃ��������Ȃ�܂��B
	//�܂�0�͈�ԍ���ɒu���Ă��������B
	//��)
	//0 1 2 3
	//4 5 6 7
	//8 9

	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	LoadTextureFromFile(FilePath, &m_pTexture);

	//0��������ƃo�O��̂�1�����܂�
	m_SplitX = SplitX == 0 ? 1 : SplitX;
	m_SplitY = SplitY == 0 ? 1 : SplitY;

	m_UVsize.x = 1.0f / static_cast<float>(m_SplitX);
	m_UVsize.y = 1.0f / static_cast<float>(m_SplitY);
}

void Number2D::SetNumber(int Num)
{
	m_Number = Num;
}

void Number2D::SetVertexShader(VertexShader* pVS)
{
	if (m_pVertexShader != nullptr)
	{
		delete m_pVertexShader;
		m_pVertexShader = nullptr;
	}

	m_pVertexShader = pVS;
}

void Number2D::SetPixelShader(PixelShader* pPS)
{
	if (m_pPixelShader != nullptr)
	{
		delete m_pPixelShader;
		m_pPixelShader = nullptr;
	}

	m_pPixelShader = pPS;
}
