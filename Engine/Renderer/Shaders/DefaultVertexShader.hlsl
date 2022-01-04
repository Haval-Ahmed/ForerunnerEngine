#include "bufferInformation.hlsli"

// Input Structure
struct VS_INPUT
{
    float3 inputPosition : POSITION0;
    float3 inputNormal: NORMAL0;
};

// Output Structure
struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
};


VS_OUTPUT VS(VS_INPUT input)
{
    // Create Pixel Shader output
    VS_OUTPUT output;

    float4 pos = float4(input.inputPosition, 1.0f);

    // Multiple to get worldViewProject for object position
    output.position = mul(pos, World);
    output.position = mul(output.position, View);
    output.position = mul(output.position, Projection);

    // Get normal 
    output.normal = mul(float4(input.inputNormal, 1), World).xyz;

    // Return position and color to PS
    return output;
}
