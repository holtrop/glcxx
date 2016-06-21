/**
 * @file
 *
 * C++ wrapper for an OpenGL texture object.
 */
#ifndef GLCXX_TEXTURE_HPP
#define GLCXX_TEXTURE_HPP

#include "glcxx/gl.hpp"
#include <memory>

namespace glcxx
{
    /**
     * C++ wrapper for an OpenGL texture object.
     */
    class Texture
    {
        public:
            /**
             * Construct and allocate an OpenGL texture object.
             */
            Texture();

            /**
             * Destroy the texture object.
             */
            ~Texture();

            /**
             * Get the texture object's ID.
             *
             * @return The texture object's ID.
             */
            GLuint id() const { return m_id; }

            /**
             * Bind the texture object.
             */
            void bind(GLenum target) const { glBindTexture(target, m_id); }

            /**
             * Factory method to construct a Texture.
             *
             * @return std::shared_ptr to the created Texture.
             */
            static std::shared_ptr<Texture>
            create()
            {
                return std::make_shared<Texture>();
            }

            /**
             * Return the lowest power-of-2 integer greater than or equal to n.
             *
             * @param n Minimum bound for return value.
             *
             * @return Lowest power-of-2 integer greater than or equal to n.
             */
            static uint32_t next_power_of_2(uint32_t n);

        protected:
            /**
             * The texture object's ID.
             */
            GLuint m_id;

            /**
             * Allocate the OpenGL texture object.
             */
            void allocate();
    };
};

#endif
