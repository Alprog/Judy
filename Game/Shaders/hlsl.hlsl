
cbuffer ConstantBuffer : register(b0)
{
	row_major float4x4 MVP;
}; 

struct PSInput
{
	float4 position : SV_POSITION;
};

PSInput main(float4 position : POSITION)
{ 
	PSInput result;
	result.position = mul(position, MVP);
	return result;
} 