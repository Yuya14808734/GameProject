
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};

cbuffer WipeCB : register(b0)
{
	float2 wipeDirection;	//ワイプ方向
	float wipeSize;			//ワイプのサイズ
	float dummy;			//ダミー
}

Texture2D BaseTex : register(t0);	//ワイプ用のテクスチャ
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
	 float4 color = BaseTex.Sample(samp, pin.uv);

	 //ピクセル座標をワイプ方向に射影する
	 float t = dot(wipeDirection, pin.uv.xy);
	 clip(t - wipeSize);

	 return color;
}