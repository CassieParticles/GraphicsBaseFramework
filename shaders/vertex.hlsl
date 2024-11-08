struct VSInput
{
    float3 position : POSITION0;
    float3 normal : NORMAL0;
    float2 uv : TEXCOORD0;
};

struct VSOutput
{
    float4 position : SV_Position;
    float3 normal : NORMAL0;
    float2 uv : TEXCOORD0;
};

cbuffer CameraMatrix : register(b0)
{
    float4x4 cameraMatrix;
};

cbuffer WorldMatrix : register(b1)
{
    float4x4 worldMatrix;
}

VSOutput Main(VSInput input)
{
    VSOutput outVal;
    outVal.position = float4(input.position, 1.0);
    outVal.position = mul(worldMatrix, outVal.position);//Into world space
    outVal.position = mul(cameraMatrix, outVal.position);//Into clip space
    
    outVal.normal = input.normal;
    outVal.normal = mul((float3x3) worldMatrix, outVal.normal);
    
    
    outVal.uv = input.uv;
    return outVal;
}