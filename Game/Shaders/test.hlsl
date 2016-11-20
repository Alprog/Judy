
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

PSInput vsmain(float3 _position : POSITION, float4 _uv : TEXCOORD)
{
	PSInput result;
   
	result.position = float4(_position, 1) + float4(0, 0.1, 0, 0); 
	result.uv = _uv;
    
	return result;
}

float4 psmain(PSInput input) : SV_TARGET 
{   
	return float4(1, 0, 0, 0); 
}