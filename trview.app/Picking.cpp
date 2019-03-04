#include "Picking.h"
#include "ICamera.h"

#include <trview.common/Point.h>
#include <trview.common/Window.h>
#include <SimpleMath.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

namespace trview
{
    void Picking::pick(const Window& window, const ICamera& camera)
    {
        const Vector3 position = camera.position();
        const auto world = Matrix::CreateTranslation(position);
        const auto projection = camera.projection();
        const auto view = camera.view();
        const auto window_size = window.size();

        const Point mouse_pos = client_cursor_position(window);
        Vector3 direction = XMVector3Unproject(Vector3(mouse_pos.x, mouse_pos.y, 1), 0, 0,
            window_size.width, window_size.height, 0, 1.0f, projection, view, world);
        direction.Normalize();

        // Call the registered pickers.
        PickInfo info{ camera.view_size(), mouse_pos, position, direction };
        PickResult result{};
        pick_sources(info, result);

        on_pick(info, result);
    }
}
