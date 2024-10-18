struct VSInput
{
    float4 position;
    float4 normal;
    float2 uv;
};

struct VSOutput
{
    float4 position : SV_Position;
    float2 uv : TEXCOORD0;
};

VSOutput Main(VSInput input)
{
    VSOutput outVal;
    outVal.position = float4(input.position, 0, 1);
    outVal.uv = input.uv;
    return outVal;
}