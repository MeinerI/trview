#include "RenderNode.h"
#include <vector>

#include <trview.ui/Control.h>
#include "Sprite.h"
#include "RenderTargetStore.h"

namespace trview
{
    namespace ui
    {
        namespace render
        {
            RenderNode::RenderNode(CComPtr<ID3D11Device> device, Control* control)
                : _control(control)
            {
                auto size = control->size();
                uint32_t width = size.width;
                uint32_t height = size.height;

                std::vector<uint32_t> pixels(width * height, 0x00000000);

                D3D11_SUBRESOURCE_DATA srd;
                memset(&srd, 0, sizeof(srd));
                srd.pSysMem = &pixels[0];
                srd.SysMemPitch = sizeof(uint32_t) * width;

                D3D11_TEXTURE2D_DESC desc;
                memset(&desc, 0, sizeof(desc));
                desc.Width = width;
                desc.Height = height;
                desc.MipLevels = desc.ArraySize = 1;
                desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                desc.SampleDesc.Count = 1;
                desc.Usage = D3D11_USAGE_DEFAULT;
                desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
                desc.CPUAccessFlags = 0;
                desc.MiscFlags = 0;

                device->CreateTexture2D(&desc, &srd, &_node_texture);
                device->CreateShaderResourceView(_node_texture, nullptr, &_node_texture_view);
                device->CreateRenderTargetView(_node_texture, nullptr, &_render_target_view);
            }

            RenderNode::~RenderNode()
            {
            }

            CComPtr<ID3D11ShaderResourceView> RenderNode::node_texture_view() const
            {
                return _node_texture_view;
            }

            void RenderNode::render(CComPtr<ID3D11DeviceContext> context, Sprite& sprite)
            {
                if (!visible())
                {
                    return;
                }

                for (auto& child : _child_nodes)
                {
                    child->render(context, sprite);
                }

                RenderTargetStore render_target_store(context);
                render_self(context, sprite);
                context->OMSetRenderTargets(1, &_render_target_view.p, nullptr);
                for (auto& child : _child_nodes)
                {
                    if (!child->visible())
                    {
                        continue;
                    }

                    // Render the child in the correct position on the render target.
                    auto pos = child->position();
                    auto size = child->size();
                    sprite.render(context, child->node_texture_view(), pos.x, pos.y, size.width, size.height);
                }
            }

            void RenderNode::add_child(std::unique_ptr<RenderNode>&& child)
            {
                _child_nodes.push_back(std::move(child));
            }

            ui::Point RenderNode::position() const
            {
                return _control->position();
            }

            ui::Size RenderNode::size() const
            {
                return _control->size();
            }

            bool RenderNode::visible() const
            {
                return _control->visible();
            }
        }
    }
}