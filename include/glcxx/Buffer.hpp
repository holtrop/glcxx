#ifndef GLCXX_BUFFER_HPP
#define GLCXX_BUFFER_HPP

#include "glcxx/gl.hpp"
#include <memory>
#include <initializer_list>

namespace glcxx
{
    class Buffer
    {
        public:
            Buffer();

            ~Buffer();

            void set_buffer_data(GLenum target, GLenum usage, const void * ptr, size_t size);

            void set_buffer_data(GLenum target, GLenum usage, std::initializer_list<GLfloat> data)
            {
                set_buffer_data(target, usage, &*data.begin(),
                                (uintptr_t)&*data.end() - (uintptr_t)&*data.begin());
            }

            void set_buffer_data_d(GLenum target, GLenum usage, std::initializer_list<GLdouble> data)
            {
                set_buffer_data(target, usage, &*data.begin(),
                                (uintptr_t)&*data.end() - (uintptr_t)&*data.begin());
            }

            GLuint id() const { return m_id; }

            void bind() const { glBindBuffer(m_target, m_id); }

            static std::shared_ptr<Buffer> create(GLenum target, GLenum usage, const void * ptr, size_t size)
            {
                std::shared_ptr<Buffer> buffer = std::make_shared<Buffer>();
                buffer->set_buffer_data(target, usage, ptr, size);
                return buffer;
            }

            static std::shared_ptr<Buffer> create(GLenum target, GLenum usage,
                                                  std::initializer_list<GLfloat> data)
            {
                std::shared_ptr<Buffer> buffer = std::make_shared<Buffer>();
                buffer->set_buffer_data(target, usage, data);
                return buffer;
            }

            static std::shared_ptr<Buffer> create_d(GLenum target, GLenum usage,
                                                    std::initializer_list<GLdouble> data)
            {
                std::shared_ptr<Buffer> buffer = std::make_shared<Buffer>();
                buffer->set_buffer_data_d(target, usage, data);
                return buffer;
            }

        protected:
            GLuint m_id;

            GLenum m_target;

            void allocate();
    };
};

#endif
