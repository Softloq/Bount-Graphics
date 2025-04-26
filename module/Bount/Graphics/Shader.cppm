module;

#include "Bount/Graphics/StandardMacros.hpp"

#include <GL/glew.h>
#include <initializer_list>

export module Bount.Graphics.Shader;
export namespace Bount::Graphics::Shader
{
struct File { String path; };

enum class Type { Vert, Geom, Frag, Tese, Tesc, Comp};

class Source
{
    Type _type;
    String _source;

public:
    BOUNT_GRAPHICS_API Source(Type type, const String& source);
    BOUNT_GRAPHICS_API Source(Type type, const File& file);

    BOUNT_GRAPHICS_API Type getType() const;
    BOUNT_GRAPHICS_API GLenum getGLType() const;
    BOUNT_GRAPHICS_API const String& getContent() const;
};

class Program
{
    U32 _glProgram;

public:
    BOUNT_GRAPHICS_API Program(const std::initializer_list<Source>& shaders);

    BOUNT_GRAPHICS_API void use();

    // Integer Uniforms

    BOUNT_GRAPHICS_API void setUniformInt(const String& name, I32 x);
    BOUNT_GRAPHICS_API void setUniformInt(const String& name, I32 x, I32 y);
    BOUNT_GRAPHICS_API void setUniformInt(const String& name, I32 x, I32 y, I32 z);
    BOUNT_GRAPHICS_API void setUniformInt(const String& name, I32 x, I32 y, I32 z, I32 w);

    // Unsigned Integer Uniforms

    BOUNT_GRAPHICS_API void setUniformUInt(const String& name, U32 x);
    BOUNT_GRAPHICS_API void setUniformUInt(const String& name, U32 x, U32 y);
    BOUNT_GRAPHICS_API void setUniformUInt(const String& name, U32 x, U32 y, U32 z);
    BOUNT_GRAPHICS_API void setUniformUInt(const String& name, U32 x, U32 y, U32 z, U32 w);

    // Floating-Point Uniforms

    BOUNT_GRAPHICS_API void setUniformFloat(const String& name, F32 x);
    BOUNT_GRAPHICS_API void setUniformFloat(const String& name, F32 x, F32 y);
    BOUNT_GRAPHICS_API void setUniformFloat(const String& name, F32 x, F32 y, F32 z);
    BOUNT_GRAPHICS_API void setUniformFloat(const String& name, F32 x, F32 y, F32 z, F32 w);

    // Double-Precision Floating-Point Uniforms

    BOUNT_GRAPHICS_API void setUniformDouble(const String& name, F64 x);
    BOUNT_GRAPHICS_API void setUniformDouble(const String& name, F64 x, F64 y);
    BOUNT_GRAPHICS_API void setUniformDouble(const String& name, F64 x, F64 y, F64 z);
    BOUNT_GRAPHICS_API void setUniformDouble(const String& name, F64 x, F64 y, F64 z, F64 w);

};
}
