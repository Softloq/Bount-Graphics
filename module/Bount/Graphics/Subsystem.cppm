/**
 * @file Subsystem.hpp
 * @brief Standard Graphics Library Subsystem. Must start up before using any graphics-based components.
 * @author Brandon Foster (Paradox Gene)
 */

module;
 
#include "Bount/Graphics/StandardMacros.hpp"
#include "Bount/Subsystem/Generic.hpp"

export module Bount.Graphics.Subsystem;
import Bount.Subsystem;

export namespace Bount::Graphics
{
/** @brief
 * Standard Graphics Subsystem. 
 * Manages Graphics-based resources and global operations.
 */
class Subsystem final : public Bount::Subsystem::Generic<Subsystem>
{
    Bool _initSDL;
    Bool _initGLEW;
    Bool _running;

    BOUNT_GRAPHICS_API Subsystem() noexcept;
    BOUNT_GRAPHICS_API ~Subsystem() noexcept;

public:
    friend class Bount::Subsystem::Generic<Subsystem>;
    friend class Bount::Singleton::Generic<Subsystem>;

    BOUNT_GRAPHICS_API void onStartup() override;
    BOUNT_GRAPHICS_API void onShutdown() noexcept override;

    BOUNT_GRAPHICS_API void runGameLoop() noexcept;
};
}

