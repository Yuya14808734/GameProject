struct VS_IN
{
	float3 pos : POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
	float4 weight : WEIGHT;
	uint4 index : INDEX;
};

struct VS_OUT
{
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD0;
	float4 WorldPos : POSITION0;
	// ���C�g�r���[�X�N���[����Ԃł̍��W��ǉ�
	float4 posInLVP : TEXCOORD1;    // ���C�g�r���[�X�N���[����Ԃł̃s�N�Z���̍��W
};

cbuffer WVP : register(b0)
{
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};
cbuffer Anime : register(b1)
{
	float4x4 bones[200];
};

cbuffer ShadowCb : register(b2)
{
	float4x4 mLVP;
}

VS_OUT main(VS_IN vin)
{
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	float4x4 mat =
		bones[vin.index.x] * vin.weight.x +
		bones[vin.index.y] * vin.weight.y +
		bones[vin.index.z] * vin.weight.z +
		bones[vin.index.w] * vin.weight.w;
	vout.pos = mul(vout.pos, mat);

	vout.WorldPos = mul(vout.pos, world);
	vout.pos = mul(vout.WorldPos, view);
	vout.pos = mul(vout.pos, proj);
	vout.uv = vin.uv;

	// ���C�g�r���[�X�N���[����Ԃ̍��W���v�Z����
	vout.posInLVP = mul(vout.WorldPos, mLVP);

	return vout;
}