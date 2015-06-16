#ifndef GLCXX_ARRAY_HPP
#define GLCXX_ARRAY_HPP

#include "glcxx/gl.hpp"

namespace glcxx
{
    /**
     * C++ wrapper for an OpenGL vertex array object.
     */
    class Array
    {
        public:
            /**
             * Create and allocate an OpenGL vertex array object.
             */
            Array();

            /**
             * Destroy the vertex array object.
             */
            ~Array();

            /**
             * Bind the vertex array object.
             */
            void bind()
            {
                glBindVertexArray(m_id);
            }

            /**
             * Get the vertex array object's ID.
             *
             * @return The buffer ID.
             */
            GLuint id() const { return m_id; }

        protected:
            /**
             * The vertex array object's ID.
             */
            GLuint m_id;
    };
};

#endif
