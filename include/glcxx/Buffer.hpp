#ifndef GLCXX_BUFFER_HPP
#define GLCXX_BUFFER_HPP

#include "glcxx/gl.hpp"
#include <memory>

namespace glcxx
{
    class Buffer
    {
        public:
            Buffer();

            ~Buffer();

            void set_buffer_data(GLenum target, GLenum usage, const void * ptr, size_t size);

            GLuint id() const { return m_id; }

            void bind() const { glBindBuffer(m_target, m_id); }

            static std::shared_ptr<Buffer> create(GLenum target, GLenum usage, const void * ptr, size_t size)
            {
                std::shared_ptr<Buffer> buffer = std::make_shared<Buffer>();
                buffer->set_buffer_data(target, usage, ptr, size);
                return buffer;
            }

        protected:
            GLuint m_id;

            GLenum m_target;

            void allocate();
    };
};

#endif
