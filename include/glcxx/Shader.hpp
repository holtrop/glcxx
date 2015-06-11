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

            void create(GLenum shader_type, const char * source, int length = -1);

            void create_from_file(GLenum shader_type, const char * filename);

            GLuint id() const { return m_id; }

            bool valid() const { return m_id > 0u; }

        protected:
            GLuint m_id;
    };
};

#endif
