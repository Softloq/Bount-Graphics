/**
 * @file Subsystem.hpp
 * @brief Standard Window Subsystem. Must start up before using any window-based components.
 * @author Brandon Foster (Paradox Gene)
 */

#ifndef BOUNT_WINDOW_SUBSYSTEM_HPP
#define BOUNT_WINDOW_SUBSYSTEM_HPP

#include "Bount/Window/StandardMacros.hpp"
#include "Bount/GL/Layer.hpp"
#include <Bount/Core/Subsystem.hpp>

#include <SDL3/SDL.h>
#include <functional>
#include <mutex>

namespace Bount::Window
{
/** @brief Window Subsystem Functionalities. */
class Subsystem_ final : public SubsystemBase<Subsystem_>
{
    GL::LayerGroup _layers;

    SDL_Window* _handle;
    SDL_GLContext _glContext;

public:
    BOUNT_WINDOW_API Subsystem_() noexcept;

    BOUNT_WINDOW_API void onStartup() override;
    BOUNT_WINDOW_API void onShutdown() noexcept override;

    BOUNT_WINDOW_API void show() noexcept;
    BOUNT_WINDOW_API void hide() noexcept;

    BOUNT_WINDOW_API void swap() noexcept;

    BOUNT_WINDOW_API GL::LayerGroup& getLayers() noexcept;

    BOUNT_WINDOW_API SDL_Window* const getSDLHandle() const noexcept;
    BOUNT_WINDOW_API SDL_GLContext const getGLContext() const noexcept;
};
/** @brief
 * Standard Window Subsystem. 
 * Manages Window-based resources and global operations.
 */
using Subsystem = Bount::Subsystem<Subsystem_>;
}

#endif