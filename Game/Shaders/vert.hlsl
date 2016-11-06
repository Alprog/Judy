
#pragma main vs

#pragma aaa ps
#pragma bbb ps
#pragma ccc ps

cbuffer ConstantBuffer : register(b0)
{
	row_major float4x4 MVP;
};

struct PSInput
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

Texture2D g_texture : register(t0); 
SamplerState g_sampler : register(s0);  
 
PSInput main(float3 position : POSITION, float4 uv : TEXCOORD)
{
	PSInput result;  
 
	result.position = mul(float4(position, 1), MVP); 
	result.uv = uv;
    
	return result;
}
 
float4 aaa(PSInput input) : SV_TARGET 
{   
	return g_texture.Sample(g_sampler, input.uv); 
} 

float4 bbb(PSInput input) : SV_TARGET 
{   
	return g_texture.Sample(g_sampler, input.uv); 
} 

float4 ccc(PSInput input) : SV_TARGET 
{   
	return g_texture.Sample(g_sampler, input.uv); 
}