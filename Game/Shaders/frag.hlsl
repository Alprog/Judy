
#pragma ps psmain

struct PSInput
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

float4 psmain(PSInput input) : SV_TARGET 
{   
	return float4(0, 0, 0, 0); 
}