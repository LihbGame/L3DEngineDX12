#include "Common.hlsli"
#include "TerrainConstBuffer.hlsli"
struct GSOutput
{
	float4 pos : SV_POSITION;
	float3 PosW    : POSITION;
	float3 NormalW : NORMAL;
	float3 TangentW:TANGENT;
	float2 Tex  : TEXCOORD;
};



float4 PS(GSOutput pin) : SV_TARGET
{
	// Fetch the material data.
	MaterialData matData = gMaterialData[gMaterialIndex];
	float4 diffuseAlbedo = gSRVMap[matData.DiffuseMapIndex].Sample(gsamLinearWrap, pin.Tex);
	diffuseAlbedo.xyz = float3(0.0f, 1.0f - pin.Tex.y , 0.0f)+gGrassColor;
	//float Roughness = gSRVMap[matData.RoughnessMapIndex].Sample(gsamLinearWrap, pin.Tex).x;
	//float Metallic = gSRVMap[matData.MetallicMapIndex].Sample(gsamLinearWrap, pin.Tex).x;
	//float AO = gSRVMap[matData.AOMapIndex].Sample(gsamLinearWrap, pin.Tex).x;

	// Indirect lighting.
	float4 ambient = gAmbientLight * diffuseAlbedo;


	////Sample normal
	//float3 normalMapSample = gSRVMap[matData.NormalMapIndex].Sample(gsamLinearWrap, pin.Tex).xyz;
	////tansform normal
	//float3 bumpedNormalW = NormalSampleToModelSpace(normalMapSample, pin.NormalW, pin.TangentW);
	//bumpedNormalW = normalize(bumpedNormalW);


	Material mat = { diffuseAlbedo, matData.FresnelR0, 0.5,0,0};

	// Only the first light casts a shadow.
	float3 toEyeW = normalize(gEyePosW - pin.PosW);
	float3 shadowFactor = float3(1.0f, 1.0f, 1.0f);
	float4 directLight = ComputeLighting(gLights, mat, pin.PosW,
		pin.NormalW, toEyeW, shadowFactor);
	 
	float4 litColor = ambient + directLight;

	//
	// Fogging
	//
	float4 texColor = litColor;
	if (gFogEnabled)
	{
		float distToEye = length(gEyePosW - pin.PosW);
		float fogLerp = saturate((distToEye - gFogStart) / gFogRange);
		// Blend the fog color and the lit color.
		texColor.rgb = lerp(texColor.rgb, gFogColor.rgb, fogLerp);
	}

	clip(diffuseAlbedo.a - 0.1f);
	return texColor;
}