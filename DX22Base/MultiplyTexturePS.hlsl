struct PS_IN 
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
	float2 SecondUV : TEXCOORD1;
};

Texture2D BaseTex : register(t0);
Texture2D MultiplyTex : register(t1);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = BaseTex.Sample(samp, pin.uv) * pin.color;
	float4 MultiplyColor = MultiplyTex.Sample(samp, pin.SecondUV);
	color.r = color.r * MultiplyColor.r;
	color.g = color.g * MultiplyColor.g;
	color.b = color.b * MultiplyColor.b;
	color.w = color.w * MultiplyColor.w;
	return color;
}