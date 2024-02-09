struct PS_IN
{
	float4 pos		: SV_POSITION;
	float2 uv		: TEXCOORD0;
	float4 color	: COLOR0;
};

cbuffer Parameter : register(b0)
{
	float dissolveRate;		//消す割合(0/全表示,1/全消し)
	float dissolveRange;	//変化する範囲
	float2 dummy;			//未使用
}

Texture2D tex : register(t0);
Texture2D dissolve : register(t1);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = float4(0.0f, 0.0f, 0.0f, 0.0f);
	color = tex.Sample(samp, pin.uv);

	//透明度がほぼない場合
	float value = color.a - 0.5f;
	// - 0.01;

	clip(value);

	//ディゾルブ
	/*value = dissolve.Sample(samp, pin.uv).r - 0.01f;

	clip(value);*/

	return color;
}