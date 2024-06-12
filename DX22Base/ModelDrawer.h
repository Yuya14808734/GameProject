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
	void Draw();											//���f���̕`��
	void SetModel(const std::string& ModelName);			//���f���̐ݒ�
	ModelInformation* GetModel();							//�ݒ肵�Ă��郂�f�����̎擾
	void PlayAnime(const std::string& AnimeName,bool Loop);	//�A�j���[�V�����̍Đ�
	void SetAnimeTime(float time);							//�Đ����Ԑݒ�(0�`�A�j���[�V�����I������)
	void SetAnimeLerp(float value);							//�Đ����Ԑݒ�(0�`1)
	float GetAnimeTime();									//���̍Đ����Ԏ擾
	float GetAnimeEndTime();								//�Đ����Ă���A�j���[�V�����̏I�����Ԏ�
	void SetPosition(const CVector3& pos);					//�`�悷��ʒu��ݒ�
	const CVector3& GetPosition();							//�`�悷��ʒu���擾
	void SetRotatePosShiftVector(const CVector3& vector);	//��]���錴�_�ʒu�����炷
	const CVector3& GetRotatePosShiftVector();				//���炵���x�N�g�����擾
	void SetRotatePosShift(bool shift);						//��]���錴�_�ʒu�����炷���ݒ�
	bool IsRotatePosShift();								//��]���錴�_�ʒu�����炵�Ă��邩�擾
	void SetScale(const CVector3& scale);					//�傫���ݒ�
	const CVector3& GetScale();								//�傫���擾
	void SetRotate(const CQuaternion& rotate);				//��]�ݒ�(�N�H�[�^�j�I���Őݒ�)
	void SetRotate(const CVector3& rotate);					//��]�ݒ�(�s�b�`���[���[�Őݒ�)
	const CQuaternion& GetRotate();							//�p�����擾(�N�H�[�^�j�I��)
	void SetCulling(bool culling, float Length);			//������ɂ��`�攻�肷�邩(�傫���ݒ�)
	void SetVertexShader(VertexShader* pVertexShader);		//���_�V�F�[�_�[�ݒ�
	void SetDefaultVertexShader();							//���̃V�F�[�_�[�ɖ߂�
	void SetPixelShader(PixelShader* pPixelShader);			//�s�N�Z���V�F�[�_�[�ݒ�
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
