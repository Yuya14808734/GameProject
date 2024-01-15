struct PS_IN
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};

//��r����F(���̐F�Ɣ�ׂđ傫�������g��)
cbuffer COMPARISONCOLOR : register(b0) {
	float4 ComparisonColor;
};

Texture2D BaseTex : register(t0);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
	float4 Color = BaseTex.Sample(samp, pin.uv) * pin.color;

	//��r���s�����l���傫�������g��
	Color.x = max(ComparisonColor.x, Color.x);
	Color.y = max(ComparisonColor.y, Color.y);
	Color.z = max(ComparisonColor.z, Color.z);
	Color.w = max(ComparisonColor.w, Color.w);
	return Color;
}