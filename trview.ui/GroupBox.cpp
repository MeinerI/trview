#include "GroupBox.h"
#include "Label.h"

namespace trview
{
    namespace ui
    {
        GroupBox::GroupBox(Point point, Size size, Colour background_colour, Colour border_colour, const std::wstring& text)
            : Window(point, size, background_colour), _border_colour(border_colour), _text(text)
        {
            auto top = std::make_unique<Window>(Point(0, 5), Size(size.width, 2), border_colour);
            auto left = std::make_unique<Window>(Point(0, 5), Size(2, size.height - 10), border_colour);
            auto bottom = std::make_unique<Window>(Point(0, size.height - 2 - 5), Size(size.width, 2), border_colour);
            auto right = std::make_unique<Window>(Point(size.width - 2, 5), Size(2, size.height - 10), border_colour);
            auto label = std::make_unique<Label>(Point(10, 0), Size(55, 20), background_colour, text, 10.f);

            add_child(std::move(top));
            add_child(std::move(left));
            add_child(std::move(bottom));
            add_child(std::move(right));
            add_child(std::move(label));
        }
    }
}