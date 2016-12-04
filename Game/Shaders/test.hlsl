
#pragma vs vsmain
#pragma ps psmain

cbuffer ConstantBuffer : register(b0)
{
	row_major float4x4 MVP;
};

Texture2D g_texture : register(t0);
SamplerState g_sampler : register(s0);

struct PSInput
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
}; 

PSInput vsmain(float3 _position : POSITION, float4 _uv : TEXCOORD)
{
	PSInput result;
	result.position = mul(float4(_position, 1), MVP); 
	result.uv = _uv;
	return result;
}

float4 psmain(PSInput input) : SV_TARGET 
{   
	return g_texture.Sample(g_sampler, input.uv);
}