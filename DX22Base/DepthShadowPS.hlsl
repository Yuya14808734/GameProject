// �s�N�Z���V�F�[�_�[�ւ̓���
struct PS_IN
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
    float4 WorldPos : POSITION0;
    // ���C�g�r���[�X�N���[����Ԃł̍��W��ǉ�
    float4 posInLVP : TEXCOORD1;    // ���C�g�r���[�X�N���[����Ԃł̃s�N�Z���̍��W
};

Texture2D tex : register(t0);
Texture2D shadowMap : register(t1);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
    float4 color = tex.Sample(samp, pin.uv);

    // ���C�g�r���[�X�N���[����Ԃ���UV��Ԃɍ��W�ϊ�
    float2 shadowMapUV = pin.posInLVP.xy / pin.posInLVP.w;
    shadowMapUV *= float2(0.5f, -0.5f);
    shadowMapUV += 0.5f;

    //���C�g�r���[�X�N���[����Ԃł�Z�l���v�Z
    //���ʂ̕��������g���Đ[���𒲂ׂ�
    float zInLVP = pin.posInLVP.z / pin.posInLVP.w;

    if (shadowMapUV.x > 0.0f && shadowMapUV.x < 1.0f
        && shadowMapUV.y > 0.0f && shadowMapUV.y < 1.0f)
    {
        float zInShadowMap = shadowMap.Sample(samp, shadowMapUV).r;

        if (zInLVP > zInShadowMap)
        {
            //�Ւf����Ă���
            color.xyz *= 0.5f;
        }
    }

    return color;
}