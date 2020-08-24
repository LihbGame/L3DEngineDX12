#pragma once

#include "L3DUtil.h"
#include "L3DMathHelper.h"
#include "L3DUploadBuffer.h"
#include "L3DVertex.h"

#define MAXSubMesh 10
struct ObjectConstants
{
    DirectX::XMFLOAT4X4 World = MathHelper::Identity4x4();
    DirectX::XMFLOAT4X4 TexTransform = MathHelper::Identity4x4();
    UINT     MaterialIndex;
    UINT     ObjPad0;
    UINT     ObjPad1;
    UINT     ObjPad2;
};


struct SkinnedConstants
{
    DirectX::XMFLOAT4X4 BoneTransforms[96];
};

struct InstanceConstants
{
    DirectX::XMFLOAT4X4 World = MathHelper::Identity4x4();
    DirectX::XMFLOAT4X4 TexTransform = MathHelper::Identity4x4();
    UINT     MaterialIndex;
    UINT     ObjPad0;
    UINT     ObjPad1;
    UINT     ObjPad2;
};

struct MaterialData
{
    DirectX::XMFLOAT4 DiffuseAlbedo = { 1.0f, 1.0f, 1.0f, 1.0f };
    DirectX::XMFLOAT3 FresnelR0 = { 0.01f, 0.01f, 0.01f };
    UINT RoughnessSrvHeapIndex = 0;

    // Used in texture mapping.
    DirectX::XMFLOAT4X4 MatTransform = MathHelper::Identity4x4();

    UINT DiffuseMapIndex = 0;
    UINT NormalSrvHeapIndex = 0;
    UINT MetallicSrvHeapIndex = 0;
    UINT AOSrvHeapIndex = 0;
    UINT HeightSrvHeapIndex = 0;
    float     height_scale = 0.0f;
    UINT     MaterialPad1;
    UINT     MaterialPad2;
};

struct PassConstants
{
    DirectX::XMFLOAT4X4 View = MathHelper::Identity4x4();
    DirectX::XMFLOAT4X4 InvView = MathHelper::Identity4x4();
    DirectX::XMFLOAT4X4 Proj = MathHelper::Identity4x4();
    DirectX::XMFLOAT4X4 InvProj = MathHelper::Identity4x4();
    DirectX::XMFLOAT4X4 ViewProj = MathHelper::Identity4x4();
    DirectX::XMFLOAT4X4 InvViewProj = MathHelper::Identity4x4();
    DirectX::XMFLOAT4X4 ShadowTransform = MathHelper::Identity4x4();
    DirectX::XMFLOAT3 EyePosW = { 0.0f, 0.0f, 0.0f };
    float cbPerObjectPad1 = 0.0f;
    DirectX::XMFLOAT2 RenderTargetSize = { 0.0f, 0.0f };
    DirectX::XMFLOAT2 InvRenderTargetSize = { 0.0f, 0.0f };
    float NearZ = 0.0f;
    float FarZ = 0.0f;
    float TotalTime = 0.0f;
    float DeltaTime = 0.0f;

    DirectX::XMFLOAT4 AmbientLight = { 0.0f, 0.0f, 0.0f, 1.0f };

    // Indices [0, NUM_DIR_LIGHTS) are directional lights;
    // indices [NUM_DIR_LIGHTS, NUM_DIR_LIGHTS+NUM_POINT_LIGHTS) are point lights;
    // indices [NUM_DIR_LIGHTS+NUM_POINT_LIGHTS, NUM_DIR_LIGHTS+NUM_POINT_LIGHT+NUM_SPOT_LIGHTS)
    // are spot lights for a maximum of MaxLights per object.
    Light Lights[MaxLights];
};


//存储CPU为框架构建命令列表所需的资源。
struct FrameResource
{
public:
    
    FrameResource(ID3D12Device* device, UINT passCount,UINT InstanceModelSubMeshNum, UINT  skinnedObjectCount, UINT objectCount, UINT materialCount, UINT waveVertCount);
    FrameResource(const FrameResource& rhs) = delete;
    FrameResource& operator=(const FrameResource& rhs) = delete;
    ~FrameResource();

    //在GPU完成处理命令之前，我们无法重置分配器。 
    //因此，每个帧都需要有自己的分配器。
    Microsoft::WRL::ComPtr<ID3D12CommandAllocator> CmdListAlloc;

    //在GPU完成处理命令之前，我们无法重置分配器。 
    //因此，每个帧都需要有自己的分配器。
    //std::unique_ptr<UploadBuffer<FrameConstants>> FrameCB = nullptr;
    std::unique_ptr<UploadBuffer<PassConstants>> PassCB = nullptr;
    std::unique_ptr<UploadBuffer<MaterialData>> MaterialBuffer = nullptr;
    std::unique_ptr<UploadBuffer<ObjectConstants>> SimpleObjectCB = nullptr;
    std::unique_ptr<UploadBuffer<SkinnedConstants>> SkinnedCB = nullptr;
    vector<std::unique_ptr<UploadBuffer<InstanceConstants>>> InstanceSimpleObjectCB ;

    // 在GPU处理完引用它的命令之前，我们无法更新动态顶点缓冲区。 
    //因此，每个框架都需要自己的框架。
    std::unique_ptr<UploadBuffer<PosNormalTexc>> WavesVB = nullptr;

    //围栏值，以将命令标记到该围栏点。 
    //这使我们可以检查GPU是否仍在使用这些帧资源。 
    UINT64 Fence = 0;
};