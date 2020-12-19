#include "SimpleGeoInstance.h"
#include "L3DMaterial.h"

SimpleGeoInstance::SimpleGeoInstance(ID3D12GraphicsCommandList* pCommandList, ID3D12Device* pd3dDevice)
{
    this->pd3dDevice = pd3dDevice;
    this->pCommandList = pCommandList;
}





SimpleGeoInstance::~SimpleGeoInstance()
{

}



void SimpleGeoInstance::BuildSimpleGeometryMesh(SimpleGeometry GeoType)
{
    GeometryGenerator Geo;
    GeometryGenerator::MeshData SimpleGeoMesh;
    std::string MeshName;
    XMFLOAT3 BoundsExtents = XMFLOAT3(0.0f, 0.0f, 0.0f);

    switch (GeoType)
    {
    case SimpleGeometry::Box:
    {
        SimpleGeoMesh = Geo.CreateBox(5, 5, 5, 0);
        MeshName = "Box";
        BoundsExtents = XMFLOAT3(2.5f, 2.5f, 2.5f);
        break;
    }
    case SimpleGeometry::Sphere:
    {
        SimpleGeoMesh = Geo.CreateSphere(10.0f, 50, 50);
        BoundsExtents = XMFLOAT3(5.0f, 5.0f, 5.0f);
        MeshName = "Sphere";
        break;
    }
    case SimpleGeometry::Cylinder:
    {
        SimpleGeoMesh = Geo.CreateCylinder(10.0f, 5.0f, 20.0f, 10, 10);
        BoundsExtents = XMFLOAT3(5.0f, 10.0f, 5.0f);
        MeshName = "Cylinder";
        break;
    }
    case SimpleGeometry::Grid:
    {
        SimpleGeoMesh = Geo.CreateGrid(100, 100, 10, 10);
        BoundsExtents = XMFLOAT3(50.0f, 1.0f, 50.0f);
        MeshName = "Grid";
        break;
    }
    case SimpleGeometry::Quad:
    {
        SimpleGeoMesh = Geo.CreateQuad(0.0f, 0.0f, 200.0f, 200.0f, 0.0f);
        MeshName = "Quad";
        break;
    }
    default:
        break;
    }


    std::vector<L3DVertice::PosNormalTangentTexc> vertices(SimpleGeoMesh.Vertices.size());
    for (size_t i = 0; i < SimpleGeoMesh.Vertices.size(); ++i)
    {
        vertices[i].Pos = SimpleGeoMesh.Vertices[i].Position;
        vertices[i].Normal = SimpleGeoMesh.Vertices[i].Normal;
        vertices[i].Tangent = SimpleGeoMesh.Vertices[i].TangentU;
        vertices[i].Texc = SimpleGeoMesh.Vertices[i].TexC;
    }
    const UINT vbByteSize = (UINT)vertices.size() * sizeof(L3DVertice::PosNormalTangentTexc);
    std::vector<std::uint16_t> indices = SimpleGeoMesh.GetIndices16();
    const UINT ibByteSize = (UINT)indices.size() * sizeof(std::uint16_t);



    mSimpleMesh = std::make_unique<MeshGeometry>();
    mSimpleMesh->Name = MeshName;

    //CPU Vertex Buffer
    ThrowIfFailed(D3DCreateBlob(vbByteSize, &mSimpleMesh->VertexBufferCPU));
    CopyMemory(mSimpleMesh->VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);


    //CPU Index Buffer
    ThrowIfFailed(D3DCreateBlob(ibByteSize, &mSimpleMesh->IndexBufferCPU));
    CopyMemory(mSimpleMesh->IndexBufferCPU->GetBufferPointer(), indices.data(), ibByteSize);

    //GPU Buffer
    mSimpleMesh->VertexBufferGPU = L3DUtil::CreateDefaultBuffer(pd3dDevice,
        pCommandList, vertices.data(), vbByteSize, mSimpleMesh->VertexBufferUploader);


    mSimpleMesh->IndexBufferGPU = L3DUtil::CreateDefaultBuffer(pd3dDevice,
        pCommandList, indices.data(), ibByteSize, mSimpleMesh->IndexBufferUploader);

    mSimpleMesh->VertexByteStride = sizeof(L3DVertice::PosNormalTangentTexc);
    mSimpleMesh->VertexBufferByteSize = vbByteSize;
    mSimpleMesh->IndexFormat = DXGI_FORMAT_R16_UINT;
    mSimpleMesh->IndexBufferByteSize = ibByteSize;

    SubmeshGeometry submesh;
    submesh.IndexCount = (UINT)indices.size();
    submesh.StartIndexLocation = 0;
    submesh.BaseVertexLocation = 0;
    submesh.Bounds.Center = XMFLOAT3(0.0f, 0.0f, 0.0f);
    submesh.Bounds.Extents = BoundsExtents;
    mSimpleMesh->DrawArgs[MeshName] = submesh;//now only have one submesh we use mesh name
}



std::unique_ptr<MeshGeometry>& SimpleGeoInstance::GetSimpleGeoMesh(SimpleGeometry GeoType)

{
    BuildSimpleGeometryMesh(GeoType);
    return mSimpleMesh;

}

void SimpleGeoInstance::BuildMaterials()
{
    XMFLOAT4X4  MatTransform = MathHelper::Identity4x4();

    L3DMaterial::GetL3DMaterialInstance()->BuildMaterials(
        L"PBRwhite_spruce_tree_bark",
        0.09f,
        XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
        XMFLOAT3(0.1f, 0.1f, 0.1f),
        MatTransform,
        MaterialType::NormalPBRMat);
    mPBRTextureName.push_back(L"PBRwhite_spruce_tree_bark");

	//PBRharshbricks Material
    L3DMaterial::GetL3DMaterialInstance()->BuildMaterials(
		L"PBRharshbricks",
		0.05f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.1f, 0.1f, 0.1f),
		MatTransform,
        MaterialType::NormalPBRMat);
    mPBRTextureName.push_back(L"PBRharshbricks");

	//PBRrocky_shoreline1 Material
    L3DMaterial::GetL3DMaterialInstance()->BuildMaterials(
		L"PBRrocky_shoreline1",
		0.05f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.1f, 0.1f, 0.1f),
		MatTransform,
		MaterialType::NormalPBRMat);
    mPBRTextureName.push_back(L"PBRrocky_shoreline1");

	//PBRstylized_grass1 Material
    L3DMaterial::GetL3DMaterialInstance()->BuildMaterials(
		L"PBRstylized_grass1",
		0.09f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.1f, 0.1f, 0.1f),
		MatTransform,
		MaterialType::NormalPBRMat);
    mPBRTextureName.push_back(L"PBRstylized_grass1");

	//PBRIndustrial_narrow_brick Material
    L3DMaterial::GetL3DMaterialInstance()->BuildMaterials(
		L"PBRIndustrial_narrow_brick",
		0.05f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.1f, 0.1f, 0.1f),
		MatTransform,
		MaterialType::NormalPBRMat);
    mPBRTextureName.push_back(L"PBRIndustrial_narrow_brick");

	//PBRBrass Material
	XMStoreFloat4x4(&MatTransform, XMMatrixScaling(0.1f, 0.1f, 0.1f));
    L3DMaterial::GetL3DMaterialInstance()->BuildMaterials(
		L"PBRBrass",
		0.01f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
		XMFLOAT3(0.1f, 0.1f, 0.1f),
		MatTransform,
		MaterialType::NormalPBRMat);
    mPBRTextureName.push_back(L"PBRBrass");
#pragma endregion

}
