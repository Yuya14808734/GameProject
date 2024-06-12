struct PS_IN
{
    float4 pos: SV_POSITION0;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL0;
};

//ライトの情報
cbuffer Light : register(b0)
{
    float4 lightColor;
    float4 lightAmbient;
    float4 lightDir;
}

Texture2D tex: register(t0);
Texture2D rampTex : register(t1);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
    float4 color = float4(1.0f,1.0f,1.0f,1.0f);

    float3 N = normalize(pin.normal);
    float3 L = normalize(lightDir.xyz);

    L = -L;

    float diffuse = saturate(dot(N, L));

#if 1

    float2 rampUV = float2(diffuse * 0.98f + 0.01f, 0.5f);
    diffuse = rampTex.Sample(samp, rampUV).r;

#else
    //diffuseの値を段階に分ける
    //0~1→0, 0.5, 1.0
    diffuse = 2.0f;    //一度数値の範囲を広げる
    diffuse += 0.5f;
    //小数を切り捨てた値を取得
    diffuse = floor(diffuse);
    //広げた範囲と同等の数値で割る
    diffuse /= 2.0f;

#endif
    //テクスチャの色も考慮して影をつける
    float4 texColor = tex.Sample(samp, pin.uv);
    color.rgb = texColor.rgb(diffuse + lightAmbient.rgb);

    return color;
}