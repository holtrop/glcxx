#include "glcxx/Buffer.hpp"
#include "glcxx/Error.hpp"

namespace glcxx
{
    Buffer::Buffer()
    {
        m_id = 0u;
    }

    Buffer::~Buffer()
    {
        if (m_id > 0u)
        {
            glDeleteBuffers(1, &m_id);
        }
    }

    void Buffer::create(GLenum target, GLenum usage, const void * ptr, size_t size)
    {
        m_target = target;
        glGenBuffers(1, &m_id);
        if (m_id == 0u)
        {
            throw Error("Failed to allocate an OpenGL buffer");
        }
        bind();
        glBufferData(target, size, ptr, usage);
    }
}
