// 输入控制点
struct VS_CONTROL_POINT_OUTPUT
{
	float3 vPosition : WORLDPOS;
	// TODO:  更改/添加其他资料
};

// 输出控制点
struct HS_CONTROL_POINT_OUTPUT
{
	float3 vPosition : WORLDPOS; 
};

// 输出修补程序常量数据。
struct HS_CONSTANT_DATA_OUTPUT
{
	float EdgeTessFactor[3]			: SV_TessFactor; // 例如，对于四象限域，将为 [4]
	float InsideTessFactor			: SV_InsideTessFactor; // 例如，对于四象限域，将为 Inside[2]
	// TODO:  更改/添加其他资料
};

#define NUM_CONTROL_POINTS 3

// 修补程序常量函数
HS_CONSTANT_DATA_OUTPUT CalcHSPatchConstants(
	InputPatch<VS_CONTROL_POINT_OUTPUT, NUM_CONTROL_POINTS> ip,
	uint PatchID : SV_PrimitiveID)
{
	HS_CONSTANT_DATA_OUTPUT Output;

	// 在此处插入代码以计算输出
	Output.EdgeTessFactor[0] = 
		Output.EdgeTessFactor[1] = 
		Output.EdgeTessFactor[2] = 
		Output.InsideTessFactor = 15; // 例如，可改为计算动态分割因子

	return Output;
}

[domain("tri")]
[partitioning("fractional_odd")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(3)]
[patchconstantfunc("CalcHSPatchConstants")]
HS_CONTROL_POINT_OUTPUT HS( 
	InputPatch<VS_CONTROL_POINT_OUTPUT, NUM_CONTROL_POINTS> ip, 
	uint i : SV_OutputControlPointID,
	uint PatchID : SV_PrimitiveID )
{
	HS_CONTROL_POINT_OUTPUT Output;

	// 在此处插入代码以计算输出
	Output.vPosition = ip[i].vPosition;

	return Output;
}
