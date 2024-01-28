struct PS_IN
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
	float2 SecondUV : TEXCOORD1;
};

Texture2D ShapeTex : register(t0);
Texture2D PatternTex : register(t1);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = ShapeTex.Sample(samp, pin.uv) * pin.color;
	float4 PatternColor = PatternTex.Sample(samp, pin.SecondUV);

	//”’‚¶‚á‚È‚¯‚ê‚Î•`‰æ‚µ‚È‚¢
	clip(color.r + color.g + color.b - 1.0f);

	color.r = color.r * PatternColor.r;
	color.g = color.g * PatternColor.g;
	color.b = color.b * PatternColor.b;
	color.w = color.w * PatternColor.w;
	return color;
}