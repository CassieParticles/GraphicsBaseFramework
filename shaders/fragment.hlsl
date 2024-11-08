struct PSInput
{
    float4 position : SV_Position;
    float3 normal : NORMAL0;
    float2 uv : TEXCOORD0;
};

struct PSOutput
{
    float4 colour : SV_Target0;
};


PSOutput Main(PSInput input)
{
    PSOutput output = { input.normal / 2 + 0.5, 1 };
    return output;
}