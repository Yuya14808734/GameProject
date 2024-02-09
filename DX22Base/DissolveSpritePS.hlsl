struct PS_IN
{
	float4 pos		: SV_POSITION;
	float2 uv		: TEXCOORD0;
	float4 color	: COLOR0;
};

cbuffer Parameter : register(b0)
{
	float dissolveRate;		//��������(0/�S�\��,1/�S����)
	float dissolveRange;	//�ω�����͈�
	float2 dummy;			//���g�p
}

Texture2D tex : register(t0);
Texture2D dissolve : register(t1);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = float4(0.0f, 0.0f, 0.0f, 0.0f);
	color = tex.Sample(samp, pin.uv);

	//�����x���قڂȂ��ꍇ
	float value = color.a - 0.5f;
	// - 0.01;

	clip(value);

	//�f�B�]���u
	/*value = dissolve.Sample(samp, pin.uv).r - 0.01f;

	clip(value);*/

	return color;
}