#pragma once

#include <vector>
#include <SimpleMath.h>
#include <atlbase.h>
#include <d3d11.h>
#include "MeshVertex.h"
#include "TransparentTriangle.h"

namespace trview
{
    struct ILevelTextureStorage;
    struct ICamera;

    // Collects transparent triangles to be rendered and provides
    // the buffers required for rendering.
    class TransparencyBuffer
    {
    public:
        explicit TransparencyBuffer(CComPtr<ID3D11Device> device);
        TransparencyBuffer(const TransparencyBuffer&) = delete;
        TransparencyBuffer& operator=(const TransparencyBuffer&) = delete;

        // Add a triangle to the transparency buffer. The triangle will be added to the end
        // of the collection.
        // triangle: The triangle to add.
        void add(const TransparentTriangle& triangle);

        // Sort the accumulated transparent triangles in order of farthest to
        // nearest, based on the position of the camera.
        // eye_position: The position of the camera.
        void sort(const DirectX::SimpleMath::Vector3& eye_position);

        // Render the accumulated transparent triangles. Sort should be called before this
        // function is called.
        // context: Current device context.
        // camera: The current camera.
        // texture_storage: Texture storage for the level.
        void render(CComPtr<ID3D11DeviceContext> context, const ICamera& camera, const ILevelTextureStorage& texture_storage);

        // Reset the triangles buffer.
        void reset();
    private:
        void create_buffer();
        void create_matrix_buffer();
        void complete();

        CComPtr<ID3D11Device> _device;
        CComPtr<ID3D11Buffer> _vertex_buffer;
        CComPtr<ID3D11Buffer> _matrix_buffer;
        std::vector<TransparentTriangle> _triangles;
        std::vector<MeshVertex> _vertices;

        struct TextureRun
        {
            uint32_t texture;
            uint32_t count;
        };

        std::vector<TextureRun> _texture_run;
    };
}