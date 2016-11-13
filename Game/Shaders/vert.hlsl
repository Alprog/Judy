
#pragma vs vsmain
#pragma ps psmain

cbuffer ConstantBuffer : register(b0)
{
	row_major float4x4 MVP;
};

struct PSInput
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

PSInput vsmain(float3 position : POSITION, float4 uv : TEXCOORD)
{
	PSInput result;  
 
	result.position = float4(position, 1); 
	result.uv = uv;
    
	return result;
}
