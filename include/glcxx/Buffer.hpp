#ifndef GLCXX_BUFFER_HPP
#define GLCXX_BUFFER_HPP

#include "glcxx/gl.hpp"

namespace glcxx
{
    class Buffer
    {
        public:
            Buffer();

            ~Buffer();

            void create(GLenum target, GLenum usage, const void *ptr, size_t sz);

            GLuint id() const { return m_id; }

            void bind() const { glBindBuffer(m_target, m_id); }

            bool valid() const { return m_id > 0u; }

        protected:
            GLuint m_id;

            GLenum m_target;
    };
};

#endif
