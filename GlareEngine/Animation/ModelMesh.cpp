#include "ModelMesh.h"


ModelMesh::ModelMesh(ID3D12Device* dev, ID3D12GraphicsCommandList* CommandList, vector<L3DVertice::PosNormalTangentTexc> vertices, vector<UINT> indices, vector<Texture> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    this->dev = dev;
    this->pCommandList = CommandList;

    this->SetupMesh();
}


ModelMesh::~ModelMesh()
{
}



// Initializes all the buffer objects/arrays
void ModelMesh::SetupMesh()
{
    const UINT vbByteSize = (UINT)vertices.size() * sizeof(L3DVertice::PosNormalTangentTexc);
    const UINT ibByteSize = (UINT)indices.size() * sizeof(UINT);

    mMeshGeo.Name = "Model Mesh";
    ThrowIfFailed(D3DCreateBlob(vbByteSize, &mMeshGeo.VertexBufferCPU));
    CopyMemory(mMeshGeo.VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);


    ThrowIfFailed(D3DCreateBlob(ibByteSize, &mMeshGeo.IndexBufferCPU));
    CopyMemory(mMeshGeo.IndexBufferCPU->GetBufferPointer(), indices.data(), ibByteSize);


    mMeshGeo.VertexBufferGPU = L3DUtil::CreateDefaultBuffer(dev,
        pCommandList, vertices.data(), vbByteSize, mMeshGeo.VertexBufferUploader);


    mMeshGeo.IndexBufferGPU = L3DUtil::CreateDefaultBuffer(dev,
        pCommandList, indices.data(), ibByteSize, mMeshGeo.IndexBufferUploader);


    mMeshGeo.VertexByteStride = sizeof(L3DVertice::PosNormalTangentTexc);
    mMeshGeo.VertexBufferByteSize = vbByteSize;
    mMeshGeo.IndexFormat = DXGI_FORMAT_R32_UINT;
    mMeshGeo.IndexBufferByteSize = ibByteSize;


   
    SubmeshGeometry submesh;
    submesh.IndexCount = (UINT)indices.size();
    submesh.StartIndexLocation = 0;
    submesh.BaseVertexLocation = 0;
    mMeshGeo.DrawArgs["Model Mesh"] = submesh;
}