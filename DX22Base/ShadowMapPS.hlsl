struct PS_IN
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 WorldPos : POSITION0;
};

cbuffer CameraPlane : register(b0)
{
	float4 Plane;
};

float4 main(PS_IN pin) : SV_TARGET
{
	//•½–Ê‚Ì•û’ö®‚ğg‚Á‚Ä[‚³‚ğ’²‚×‚é
	float Depth =
	Plane.x * pin.WorldPos.x +
	Plane.y * pin.WorldPos.y +
	Plane.z * pin.WorldPos.z +
	Plane.w;

	Depth /= 10.0f;

	return float4(Depth, Depth, Depth, 1.0f);
}