/// @file CameraControls.h
/// @brief UI element that contains the camera modes and settings.
/// 
/// Creates elements that the user can click to change the behaviour of the camera and switch
/// between different cameras.

#pragma once

#include <trview.common/Event.h>
#include <trview.common/TokenStore.h>
#include <trview.app/Camera/CameraMode.h>

namespace trview
{
    namespace ui
    {
        class Control;
        class Checkbox;
    }

    /// The camera controls control has settings for the operation mode of the camera and
    /// other camera related settings.
    class CameraControls
    {
    public:
        /// Creates an instance of the CameraControls class.
        /// @param parent The control to which the instance will be added as a child.
        explicit CameraControls(ui::Control& parent);

        /// Event raised when the camera mode has been selected by the user. The newly selected
        /// camera mode is passed as a parameter when the event is raised.
        /// @remarks This event is not raised by the set_mode function.
        Event<CameraMode> on_mode_selected;

        /// Event raised when the user clicks the reset button.
        Event<> on_reset;

        /// Set the current camera mode. This will not raise the on_mode_selected event.
        /// @param mode The camera mode to change to.
        /// @remarks This will not raise the on_mode_selected event.
        void set_mode(CameraMode mode);
    private:
        /// Set the current camera mode.
        /// @param mode The new camera mode.
        /// @remarks This will raise the on_mode_selected_event.
        void change_mode(CameraMode mode);

        ui::Checkbox* _orbit;
        ui::Checkbox* _free;
        ui::Checkbox* _axis;
        TokenStore _token_store;
    };
}
