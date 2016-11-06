
#pragma ps

struct PSInput
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

Texture2D g_texture : register(t0);
SamplerState g_sampler : register(s0);

float4 vsmain(PSInput input) : SV_TARGET
{ 
	return g_texture.Sample(g_sampler, input.uv) + float4(0, 0, 1, 0);
} 