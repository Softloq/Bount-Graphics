/**
 * @file Subsystem.hpp
 * @brief Standard Graphics Library Subsystem. Must start up before using any graphics-based components.
 * @author Brandon Foster (Paradox Gene)
 */

#ifndef BOUNT_GL_SUBSYSTEM_HPP
#define BOUNT_GL_SUBSYSTEM_HPP

#include "Bount/GL/StandardMacros.hpp"
#include <Bount/Core/Subsystem.hpp>

namespace Bount::GL
{
/** @brief Graphics Subsystem Functionalities. */
class Subsystem_ final : public SubsystemBase<Subsystem_>
{
    Bool _initSDL;
    Bool _initGLEW;
    Bool _running;

public:
    BOUNT_GL_API Subsystem_() noexcept;

    BOUNT_GL_API void onStartup() override;
    BOUNT_GL_API void onShutdown() noexcept override;

    BOUNT_GL_API void runGameLoop() noexcept;
};
/** @brief
 * Standard Graphics Subsystem. 
 * Manages Graphics-based resources and global operations.
 */
using Subsystem = Bount::Subsystem<Subsystem_>;
}

#endif
