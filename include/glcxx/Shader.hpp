#ifndef GLCXX_SHADER_HPP
#define GLCXX_SHADER_HPP

#include "glcxx/gl.hpp"
#include <memory>

namespace glcxx
{
    /**
     * C++ wrapper for an OpenGL shader object.
     */
    class Shader
    {
        public:
            /**
             * Create and allocate an OpenGL shader object.
             *
             * @param shader_type OpenGL shader type (e.g. GL_VERTEX_SHADER).
             */
            Shader(GLenum shader_type);

            /**
             * Destroy the shader object.
             */
            ~Shader();

            /**
             * Load shader source from memory.
             *
             * @param source Pointer to the shader source.
             * @param length
             *   Length of the shader source. If unspecified, the shader source
             *   must be NULL-terminated.
             */
            void set_source(const char * source, int length = -1);

            /**
             * Load shader source from a file.
             *
             * @param filename Name of the file to load.
             */
            void set_source_from_file(const char * filename);

            /**
             * Get the shader object's ID.
             *
             * @return The shader object's ID.
             */
            GLuint id() const { return m_id; }

            /**
             * Factory method to construct a Shader object.
             *
             * @param shader_type OpenGL shader type (e.g. GL_VERTEX_SHADER).
             * @param source Pointer to the shader source.
             * @param length
             *   Length of the shader source. If unspecified, the shader source
             *   must be NULL-terminated.
             */
            static std::shared_ptr<Shader>
            create(GLenum shader_type, const char * source, int length = -1)
            {
                std::shared_ptr<Shader> shader = std::make_shared<Shader>(shader_type);
                shader->set_source(source, length);
                return shader;
            }

            /**
             * Factory method to construct a Shader object.
             *
             * @param shader_type OpenGL shader type (e.g. GL_VERTEX_SHADER).
             * @param filename Name of the file to load.
             */
            static std::shared_ptr<Shader>
            create_from_file(GLenum shader_type, const char * filename)
            {
                std::shared_ptr<Shader> shader = std::make_shared<Shader>(shader_type);
                shader->set_source_from_file(filename);
                return shader;
            }

        protected:
            /**
             * The shader object's ID.
             */
            GLuint m_id;

            /**
             * The OpenGL shader type.
             */
            GLenum m_shader_type;

            /**
             * Allocate the OpenGL shader object.
             */
            void allocate();
    };
};

#endif
