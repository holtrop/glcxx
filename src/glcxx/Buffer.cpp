#include "glcxx/Buffer.hpp"
#include "glcxx/Error.hpp"

namespace glcxx
{
    Buffer::Buffer()
    {
        allocate();
    }

    Buffer::~Buffer()
    {
        glDeleteBuffers(1, &m_id);
    }

    void Buffer::set_buffer_data(GLenum target, GLenum usage, const void * ptr, size_t size)
    {
        m_target = target;
        bind();
        glBufferData(target, size, ptr, usage);
    }

    void Buffer::allocate()
    {
        m_id = 0u;
        glGenBuffers(1, &m_id);
        if (m_id == 0u)
        {
            throw Error("Failed to allocate an OpenGL buffer");
        }
    }
}
