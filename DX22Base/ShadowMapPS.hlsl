struct PS_IN
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 WorldPos : POSITION0;
};

float4 main(PS_IN pin) : SV_TARGET
{
	return float4(pin.pos.z, 0.0f, 0.0f, 1.0f);
}