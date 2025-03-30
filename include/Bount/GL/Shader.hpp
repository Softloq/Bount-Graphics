#ifndef BOUNT_GL_SHADER_HPP
#define BOUNT_GL_SHADER_HPP

#include "Bount/GL/Lib-Macro.hpp"
#include <GL/glew.h>
#include <initializer_list>

namespace Bount::GL::Shader
{
struct File { String path; };

enum class Type { Vert, Geom, Frag, Tese, Tesc, Comp};

class Source
{
    Type _type;
    String _source;

public:
    BOUNT_GL_API Source(Type type, const String& source);
    BOUNT_GL_API Source(Type type, const File& file);

    BOUNT_GL_API Type getType() const;
    BOUNT_GL_API GLenum getGLType() const;
    BOUNT_GL_API const String& getContent() const;
};

class Program
{
    GLuint _glProgram;

public:
    BOUNT_GL_API Program(const std::initializer_list<Source>& shaders);

    BOUNT_GL_API void use();
};
}

#endif