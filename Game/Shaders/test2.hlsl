
cbuffer ConstantBuffer : register(b0)
{
	row_major float4x4 MVP;
};

struct Vertex
{
	float3 position : POSITION;
	float4 uv : TEXCOORD;
};

struct Gradient
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

Texture2D g_texture : register(t0);
SamplerState g_sampler : register(s0);

Gradient vsmain(Vertex v)
{
	Gradient result;  
 
	result.position = mul(float4(v.position, 1), MVP);
	result.uv = v.uv; 
    
	return result;
}

float4 psmain_normal(Gradient in) : SV_TARGET 
{   
	return g_texture.Sample(g_sampler, in.uv);
}

float4 psmain_grayscale(Gradient p) : SV_TARGET 
{   
	float4 color = g_texture.Sample(g_sampler, in.uv);
	color.rgb = color.r * 0.3 + color.g * 0.59 + color.b * 0.11
	return color;
}