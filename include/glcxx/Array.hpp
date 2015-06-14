#ifndef GLCXX_ARRAY_HPP
#define GLCXX_ARRAY_HPP

#include "glcxx/gl.hpp"

namespace glcxx
{
    class Array
    {
        public:
            Array();

            ~Array();

            void bind()
            {
                glBindVertexArray(m_id);
            }

            GLuint id() const { return m_id; }

        protected:
            GLuint m_id;
    };
};

#endif
