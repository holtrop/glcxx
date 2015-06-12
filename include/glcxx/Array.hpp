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

            void create();

            void bind()
            {
                glBindVertexArray(m_id);
            }

            GLuint id() const { return m_id; }

            bool valid() const { return m_id > 0u; }

        protected:
            GLuint m_id;
    };
};

#endif
