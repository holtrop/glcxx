#include "glcxx/Array.hpp"
#include "glcxx/Error.hpp"

namespace glcxx
{
    Array::Array()
    {
        m_id = 0u;

        glGenVertexArrays(1, &m_id);

        if (m_id == 0u)
        {
            throw Error("Failed to allocate an OpenGL array");
        }
    }

    Array::~Array()
    {
        glDeleteVertexArrays(1, &m_id);
    }
}
