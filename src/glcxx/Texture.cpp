#include "glcxx/Texture.hpp"
#include "glcxx/Error.hpp"

namespace glcxx
{
    Texture::Texture()
    {
        allocate();
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_id);
    }

    void Texture::allocate()
    {
        m_id = 0u;
        glGenTextures(1, &m_id);
        if (m_id == 0u)
        {
            throw Error("Failed to allocate an OpenGL texture");
        }
    }

    uint32_t Texture::next_power_of_2(uint32_t n)
    {
        n--;
        n |= n >> 1u;
        n |= n >> 2u;
        n |= n >> 4u;
        n |= n >> 8u;
        n |= n >> 16u;
        n++;
        return n;
    }
}
