#ifndef GLCXX_SHADER_HPP
#define GLCXX_SHADER_HPP

#include "glcxx/gl.hpp"

namespace glcxx
{
    class Shader
    {
        public:
            Shader();

            ~Shader();

            void create(GLenum shaderType, const char *source);

            GLuint id() const { return m_id; }

            bool valid() const { return m_id > 0u; }

        protected:
            GLuint m_id;
    };
};

#endif
