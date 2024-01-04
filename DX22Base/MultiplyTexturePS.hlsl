struct PS_IN 
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};

Texture2D BaseTex : register(t0);
Texture2D MultiplyTex : register(t1);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
	return float4(1.0f,1.0f,1.0f,1.0f);
}