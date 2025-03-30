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
    std::ifstream source_fstream(Core::Filesystem::BinPath(file.path));
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
}