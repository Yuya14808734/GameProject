struct PS_IN
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};

float4 main(PS_IN pin) : SV_TARGET
{
	return float4(0.5f, 0.5f, 0.5f, 1.0f);
}