
#pragma pack_matrix( row_major )

cbuffer MatrixBuffer
{
	matrix WVP;
	matrix M1;
	matrix M2;
};

struct VertexInputType
{
    float4 position : POSITION;
    float4 color : COLOR;
	float2 uv : TEXCOORD;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
	float2 uv : TEXCOORD;
};

PixelInputType ColorVertexShader(VertexInputType input)
{
    PixelInputType output;
    

	// Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;
	output.position = input.position;
	
	output.position = mul(output.position, M2);
	output.position = mul(output.position, M1);
    
	// Store the input color for the pixel shader to use.
    output.color = input.color;
    output.uv = input.uv;
	
    return output;
}