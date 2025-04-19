#include "Bount/GL/Precompiled.hpp"
#include "Bount/GL/Shader.hpp"
#include <Bount/Core/Filesystem.hpp>
#include <fstream>
#include <list>

namespace Bount::GL::Shader
{
BOUNT_GL_API Source::Source(Type type, const String& source)
    : _type(type)
    , _source(source)
{
}
BOUNT_GL_API Source::Source(Type type, const File& file)
    : _type(type)
{
    auto sourcePath = Filesystem::Path(Filesystem::Path::Base::Resources, file.path).toString();
    std::ifstream source_fstream(sourcePath);
    if (!source_fstream.is_open())
    {
        _source = "";
        return;
    }
    std::stringstream buffer;
    buffer << source_fstream.rdbuf();
    _source = buffer.str();
}
BOUNT_GL_API GLenum Source::getGLType() const
{
    switch(_type)
    {
    case Type::Vert:
        return GL_VERTEX_SHADER;
    case Type::Geom:
        return GL_GEOMETRY_SHADER;
    case Type::Frag:
        return GL_FRAGMENT_SHADER;
    case Type::Tese:
        return GL_TESS_EVALUATION_SHADER;
    case Type::Tesc:
        return GL_TESS_CONTROL_SHADER;
    case Type::Comp:
        return GL_COMPUTE_SHADER;
    }
    return 0;
}
BOUNT_GL_API Type Source::getType() const
{
    return _type;
}
BOUNT_GL_API const String& Source::getContent() const
{
    return _source;
}
BOUNT_GL_API Program::Program(const std::initializer_list<Source>& shaders)
{
    std::list<GLuint> link_shaders;
    for (auto& shader : shaders)
    {
        GLuint glShader = glCreateShader(shader.getGLType());
        auto source = shader.getContent().c_str();
        glShaderSource(glShader, 1, &source, NULL);
        glCompileShader(glShader);
        link_shaders.push_back(glShader);
    }

    GLuint program = glCreateProgram();
    for (auto compiled_shader : link_shaders)
    {
        glAttachShader(program, compiled_shader);
    }

    glLinkProgram(program);

    for (auto compiled_shader : link_shaders)
    {
        glDeleteShader(compiled_shader);
    }

    _glProgram = program;
}

BOUNT_GL_API void Program::use()
{
    glUseProgram(_glProgram);
}

// Integer Uniforms

BOUNT_GL_API void Program::setUniformInt(const String& name, I32 x)
{
    glUniform1i(glGetUniformLocation(_glProgram, name.c_str()), x);
}
BOUNT_GL_API void Program::setUniformInt(const String& name, I32 x, I32 y)
{
    glUniform2i(glGetUniformLocation(_glProgram, name.c_str()), x, y);
}
BOUNT_GL_API void Program::setUniformInt(const String& name, I32 x, I32 y, I32 z)
{
    glUniform3i(glGetUniformLocation(_glProgram, name.c_str()), x, y, z);
}
BOUNT_GL_API void Program::setUniformInt(const String& name, I32 x, I32 y, I32 z, I32 w)
{
    glUniform4i(glGetUniformLocation(_glProgram, name.c_str()), x, y, z, w);
}

// Unsigned Integer Uniforms

BOUNT_GL_API void Program::setUniformUInt(const String& name, U32 x)
{
    glUniform1ui(glGetUniformLocation(_glProgram, name.c_str()), x);
}
BOUNT_GL_API void Program::setUniformUInt(const String& name, U32 x, U32 y)
{
    glUniform2ui(glGetUniformLocation(_glProgram, name.c_str()), x, y);
}
BOUNT_GL_API void Program::setUniformUInt(const String& name, U32 x, U32 y, U32 z)
{
    glUniform3ui(glGetUniformLocation(_glProgram, name.c_str()), x, y, z);
}
BOUNT_GL_API void Program::setUniformUInt(const String& name, U32 x, U32 y, U32 z, U32 w)
{
    glUniform4ui(glGetUniformLocation(_glProgram, name.c_str()), x, y, z, w);
}

// Floating-Point Uniforms

BOUNT_GL_API void Program::setUniformFloat(const String& name, F32 x)
{
    glUniform1f(glGetUniformLocation(_glProgram, name.c_str()), x);
}
BOUNT_GL_API void Program::setUniformFloat(const String& name, F32 x, F32 y)
{
    glUniform2f(glGetUniformLocation(_glProgram, name.c_str()), x, y);
}
BOUNT_GL_API void Program::setUniformFloat(const String& name, F32 x, F32 y, F32 z)
{
    glUniform3f(glGetUniformLocation(_glProgram, name.c_str()), x, y, z);
}
BOUNT_GL_API void Program::setUniformFloat(const String& name, F32 x, F32 y, F32 z, F32 w)
{
    glUniform4f(glGetUniformLocation(_glProgram, name.c_str()), x, y, z, w);
}

// Double-Precision Floating-Point Uniforms

BOUNT_GL_API void Program::setUniformDouble(const String& name, F64 x)
{
    glUniform1d(glGetUniformLocation(_glProgram, name.c_str()), x);
}
BOUNT_GL_API void Program::setUniformDouble(const String& name, F64 x, F64 y)
{
    glUniform2d(glGetUniformLocation(_glProgram, name.c_str()), x, y);
}
BOUNT_GL_API void Program::setUniformDouble(const String& name, F64 x, F64 y, F64 z)
{
    glUniform3d(glGetUniformLocation(_glProgram, name.c_str()), x, y, z);
}
BOUNT_GL_API void Program::setUniformDouble(const String& name, F64 x, F64 y, F64 z, F64 w)
{
    glUniform4d(glGetUniformLocation(_glProgram, name.c_str()), x, y, z, w);
}
}