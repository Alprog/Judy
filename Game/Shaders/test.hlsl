
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

PSInput vsmain(float3 position_ : POSITION, float4 uv_ : TEXCOORD)
{
	PSInput result;
 
	result.position = float4(position_, 1); 
	result.uv = uv_;  
    
	return result;
}

PSInput vsmain2(float3 position_ : POSITION, float4 uv_ : TEXCOORD)
{
	PSInput result;
 
	result.position = float4(position_, 1); 
	result.uv = uv_;  
    
	return result;
}

float4 psmain(PSInput input) : SV_TARGET 
{   
	return float4(0, 0, 0, 0); 
}

float4 psmain2(PSInput input) : SV_TARGET 
{   
	return float4(0, 0, 0, 0); 
}