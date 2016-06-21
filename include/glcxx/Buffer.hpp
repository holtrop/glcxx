/**
 * @file
 *
 * C++ wrapper for an OpenGL buffer object.
 */
#ifndef GLCXX_BUFFER_HPP
#define GLCXX_BUFFER_HPP

#include "glcxx/gl.hpp"
#include <memory>
#include <initializer_list>

namespace glcxx
{
    /**
     * C++ wrapper for an OpenGL buffer object.
     */
    class Buffer
    {
        public:
            /**
             * Construct and allocate an OpenGL buffer object.
             */
            Buffer();

            /**
             * Destroy the buffer object.
             */
            ~Buffer();

            /**
             * Set the buffer's data, target, and usage.
             *
             * @param target Buffer target (e.g. GL_ARRAY_BUFFER).
             * @param usage Buffer usage hint (e.g. GL_STATIC_DRAW).
             * @param ptr Pointer to data to load in buffer.
             * @param size Length of the data to load in buffer.
             */
            void set_buffer_data(GLenum target, GLenum usage, const void * ptr, size_t size);

            /**
             * Set the buffer's data, target, and usage.
             *
             * @param target Buffer target (e.g. GL_ARRAY_BUFFER).
             * @param usage Buffer usage hint (e.g. GL_STATIC_DRAW).
             * @param data Data to load in buffer.
             */
            void set_buffer_data(GLenum target, GLenum usage, std::initializer_list<GLfloat> data)
            {
                set_buffer_data(target, usage, &*data.begin(),
                                (uintptr_t)&*data.end() - (uintptr_t)&*data.begin());
            }

            /**
             * Set the buffer's data, target, and usage.
             *
             * @param target Buffer target (e.g. GL_ARRAY_BUFFER).
             * @param usage Buffer usage hint (e.g. GL_STATIC_DRAW).
             * @param data Data to load in buffer.
             */
            void set_buffer_data_d(GLenum target, GLenum usage, std::initializer_list<GLdouble> data)
            {
                set_buffer_data(target, usage, &*data.begin(),
                                (uintptr_t)&*data.end() - (uintptr_t)&*data.begin());
            }

            /**
             * Get the buffer object's ID.
             *
             * @return The buffer object's ID.
             */
            GLuint id() const { return m_id; }

            /**
             * Bind the buffer object.
             */
            void bind() const { glBindBuffer(m_target, m_id); }

            /**
             * Factory method to construct a Buffer.
             *
             * This method does not fill the buffer with any data.
             *
             * @return std::shared_ptr to the created Buffer.
             */
            static std::shared_ptr<Buffer>
            create()
            {
                return std::make_shared<Buffer>();
            }

            /**
             * Factory method to construct a Buffer and fill it with data.
             *
             * @param target Buffer target (e.g. GL_ARRAY_BUFFER).
             * @param usage Buffer usage hint (e.g. GL_STATIC_DRAW).
             * @param ptr Pointer to data to load in buffer.
             * @param size Length of the data to load in buffer.
             *
             * @return std::shared_ptr to a Buffer.
             */
            static std::shared_ptr<Buffer>
            create(GLenum target, GLenum usage, const void * ptr, size_t size)
            {
                std::shared_ptr<Buffer> buffer = std::make_shared<Buffer>();
                buffer->set_buffer_data(target, usage, ptr, size);
                return buffer;
            }

            /**
             * Factory method to construct a Buffer and fill it with data.
             *
             * @param target Buffer target (e.g. GL_ARRAY_BUFFER).
             * @param usage Buffer usage hint (e.g. GL_STATIC_DRAW).
             * @param data Data to load in buffer.
             */
            static std::shared_ptr<Buffer>
            create(GLenum target, GLenum usage,
                   std::initializer_list<GLfloat> data)
            {
                std::shared_ptr<Buffer> buffer = std::make_shared<Buffer>();
                buffer->set_buffer_data(target, usage, data);
                return buffer;
            }

            /**
             * Factory method to construct a Buffer and fill it with data.
             *
             * @param target Buffer target (e.g. GL_ARRAY_BUFFER).
             * @param usage Buffer usage hint (e.g. GL_STATIC_DRAW).
             * @param data Data to load in buffer.
             */
            static std::shared_ptr<Buffer>
            create_d(GLenum target, GLenum usage,
                     std::initializer_list<GLdouble> data)
            {
                std::shared_ptr<Buffer> buffer = std::make_shared<Buffer>();
                buffer->set_buffer_data_d(target, usage, data);
                return buffer;
            }

        protected:
            /**
             * The buffer object's ID.
             */
            GLuint m_id;

            /**
             * The target for binding the buffer.
             */
            GLenum m_target;

            /**
             * Allocate the OpenGL buffer object.
             */
            void allocate();
    };
};

#endif
