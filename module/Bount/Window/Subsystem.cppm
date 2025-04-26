module;

#include "Bount/Window/StandardMacros.hpp"
#include "Bount/Subsystem/Generic.hpp"

#include <SDL3/SDL.h>

export module Bount.Window.Subsystem;
import Bount.Graphics.Layer;
import Bount.Subsystem;

export namespace Bount::Window
{
/** @brief
 * Standard Window Subsystem. 
 * Manages Window-based resources and global operations.
 */
class Subsystem final : public Bount::Subsystem::Generic<Window::Subsystem>
{
    Graphics::LayerGroup _layers;

    SDL_Window* _handle;
    SDL_GLContext _glContext;

    BOUNT_WINDOW_API Subsystem() noexcept;
    BOUNT_WINDOW_API ~Subsystem() noexcept;

public:
    friend class Bount::Subsystem::Generic<Window::Subsystem>;
    friend class Bount::Singleton::Generic<Window::Subsystem>;

    BOUNT_WINDOW_API void onStartup() override;
    BOUNT_WINDOW_API void onShutdown() noexcept override;

    BOUNT_WINDOW_API void show() noexcept;
    BOUNT_WINDOW_API void hide() noexcept;

    BOUNT_WINDOW_API void swap() noexcept;

    BOUNT_WINDOW_API Graphics::LayerGroup& getLayers() noexcept;

    BOUNT_WINDOW_API SDL_Window* const getSDLHandle() const noexcept;
    BOUNT_WINDOW_API SDL_GLContext const getGLContext() const noexcept;
};
}
