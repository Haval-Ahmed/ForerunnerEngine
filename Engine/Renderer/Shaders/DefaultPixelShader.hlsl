#include "bufferInformation.hlsli"

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 normal : TEXCOORD0;
};


float4 PS(PS_INPUT input) : SV_TARGET
{
    float4 finalColor = 0;

    for (int i = 0; i < 3; i++)
    {
        finalColor += saturate(dot((float3)lightDirection[i], input.normal) * lightColor[i]);
    }
    finalColor.a = 1;

    return finalColor;
}