// ピクセルシェーダーへの入力
struct PS_IN
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
    float4 WorldPos : POSITION0;
    // ライトビュースクリーン空間での座標を追加
    float4 posInLVP : TEXCOORD1;    // ライトビュースクリーン空間でのピクセルの座標
};

Texture2D tex : register(t0);
Texture2D shadowMap : register(t1);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
    float4 color = tex.Sample(samp, pin.uv);

    // ライトビュースクリーン空間からUV空間に座標変換
    float2 shadowMapUV = pin.posInLVP.xy / pin.posInLVP.w;
    shadowMapUV *= float2(0.5f, -0.5f);
    shadowMapUV += 0.5f;

    //ライトビュースクリーン空間でのZ値を計算
    //平面の方程式を使って深さを調べる
    float zInLVP = pin.posInLVP.z / pin.posInLVP.w;

    if (shadowMapUV.x > 0.0f && shadowMapUV.x < 1.0f
        && shadowMapUV.y > 0.0f && shadowMapUV.y < 1.0f)
    {
        float zInShadowMap = shadowMap.Sample(samp, shadowMapUV).r;

        if (zInLVP > zInShadowMap)
        {
            //遮断されている
            color.xyz *= 0.5f;
        }
    }

    return color;
}