
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};

cbuffer WipeCB : register(b0)
{
	float2 wipeDirection;	//���C�v����
	float wipeSize;			//���C�v�̃T�C�Y
	float dummy;			//�_�~�[
}

Texture2D BaseTex : register(t0);	//���C�v�p�̃e�N�X�`��
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
	 float4 color = BaseTex.Sample(samp, pin.uv);

	 //�s�N�Z�����W�����C�v�����Ɏˉe����
	 float t = dot(wipeDirection, pin.uv.xy);
	 clip(t - wipeSize);

	 return color;
}