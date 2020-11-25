#include "HeightmapTerrain.h"

HeightmapTerrain::HeightmapTerrain()
{
}

HeightmapTerrain::~HeightmapTerrain()
{
}

float HeightmapTerrain::GetWidth() const
{
	return 0.0f;
}

float HeightmapTerrain::GetDepth() const
{
	return 0.0f;
}

float HeightmapTerrain::GetHeight(float x, float z) const
{
	return 0.0f;
}

XMMATRIX HeightmapTerrain::GetWorld() const
{
	return XMMATRIX();
}

void HeightmapTerrain::SetWorld(CXMMATRIX M)
{
}

void HeightmapTerrain::Init(ID3D11Device* device, ID3D11DeviceContext* dc, const InitInfo& initInfo, ID3D11ShaderResourceView* RandomTexSRV)
{
}

void HeightmapTerrain::Draw(ID3D11DeviceContext* dc, const Camera& cam, bool isReflection)
{
}

void HeightmapTerrain::Update(float dt)
{
}

void HeightmapTerrain::LoadHeightmapAsset()
{







}

void HeightmapTerrain::Smooth()
{
}

bool HeightmapTerrain::InBounds(int i, int j)
{
	return false;
}

float HeightmapTerrain::Average(int i, int j)
{
	return 0.0f;
}

void HeightmapTerrain::CalcAllPatchBoundsY()
{
}

void HeightmapTerrain::CalcPatchBoundsY(UINT i, UINT j)
{
}

void HeightmapTerrain::BuildQuadPatchVB(ID3D12Device* device)
{
}

void HeightmapTerrain::BuildQuadPatchIB(ID3D12Device* device)
{
}

void HeightmapTerrain::BuildHeightmapSRV(ID3D12Device* device)
{
}
