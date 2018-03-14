#pragma once

#include <atlbase.h>
#include <d3d11.h>

#include <memory>

#include "RenderNode.h"
#include "Sprite.h"
#include "FontFactory.h"

#include <trview.ui/Control.h>

namespace trview
{
    namespace ui
    {
        namespace render
        {
            class Renderer
            {
            public:
                explicit Renderer(CComPtr<ID3D11Device> device, uint32_t host_width, uint32_t host_height);

                // Examine a control heirarchy and create the appropriate structures
                // required to render it. This will replace any existing rendering
                // structures.
                void load(Control* control);

                void render(CComPtr<ID3D11DeviceContext> context);
            private:
                std::unique_ptr<RenderNode> process_control(Control* control);

                std::unique_ptr<RenderNode>      _root_node;
                std::unique_ptr<Sprite>          _sprite;
                std::unique_ptr<FontFactory>     _font_factory;
                CComPtr<ID3D11Device>            _device;
                CComPtr<ID3D11DepthStencilState> _depth_stencil_state;
                uint32_t                         _host_width;
                uint32_t                         _host_height;
                
            };
        }
    }
}