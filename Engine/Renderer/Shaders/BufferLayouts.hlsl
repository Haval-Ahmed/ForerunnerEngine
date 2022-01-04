//Constant Buffer Variables
cbuffer constantObjects : register (b0)
{
    matrix World;
    matrix View;
    matrix Projection;
    float4 lightDirection[3];
    float4 lightColor[3];
    float4 outputColor;
}

struct directionalLight
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float3 direction;
    float padding;
};

struct objectMaterial
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float4 reflection;
};