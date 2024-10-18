struct VSInput
{
    float3 position : POSITION0;
    float3 normal : NORMAL0;
    float2 uv : TEXCOORD0;
};

struct VSOutput
{
    float4 position : SV_Position;
};

VSOutput Main(VSInput input)
{
    VSOutput outVal;
    outVal.position = float4(input.position,1);
    return outVal;
}