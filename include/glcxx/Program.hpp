/**
 * @file
 *
 * C++ wrapper for an OpenGL program object.
 */
#ifndef GLCXX_PROGRAM_HPP
#define GLCXX_PROGRAM_HPP

#include <initializer_list>
#include <memory>
#include "glcxx/Shader.hpp"

namespace glcxx
{
    /**
     * C++ wrapper for an OpenGL program object.
     */
    class Program
    {
        public:
            /**
             * Create and allocate an OpenGL program object.
             */
            Program();

            /**
             * Destroy the program object.
             */
            ~Program();

            /**
             * Get the program object's ID.
             *
             * @return The program object's ID.
             */
            GLuint id() const { return m_id; }

            /**
             * Use the program.
             */
            void use() const { glUseProgram(m_id); }

            /**
             * Utility method to attach shaders and link the program.
             *
             * This method automatically invokes attach_shader() for each
             * shader given and then invokes link() to link the program.
             *
             * @param shaders
             *   A std::unique_ptr<Shader>, std::shared_ptr<Shader>, or
             *   const Shader &.
             */
            template <typename... Shaders>
            void build(Shaders... shaders)
            {
                _build(shaders...);
            }

            /**
             * Attach a shader to the program.
             *
             * @param shader The shader to attach.
             */
            void attach_shader(const Shader & shader) const
            {
                glAttachShader(m_id, shader.id());
            }

            /**
             * Attach a shader to the program.
             *
             * @param shader The shader to attach.
             */
            void attach_shader(std::unique_ptr<Shader> shader) const
            {
                glAttachShader(m_id, shader->id());
            }

            /**
             * Attach a shader to the program.
             *
             * @param shader The shader to attach.
             */
            void attach_shader(std::shared_ptr<Shader> shader) const
            {
                glAttachShader(m_id, shader->id());
            }

            /**
             * Link the program.
             */
            void link() const;

            /**
             * Get the index of a uniform variable in the program.
             *
             * @param uniform_name Name of the uniform variable.
             *
             * @return Index of the uniform variable.
             */
            GLint get_uniform_location(const char * uniform_name)
            {
                return glGetUniformLocation(m_id, uniform_name);
            }

            /**
             * Factory method to construct a Program object.
             *
             * @param args
             *   The arguments given are passed to the constructed Program's
             *   build() method.
             *
             * @return std::shared_ptr to a Buffer.
             */
            template <typename... Args>
            static std::shared_ptr<Program>
            create(Args... args)
            {
                std::shared_ptr<Program> program = std::make_shared<Program>();
                program->build(args...);
                return program;
            }

        protected:
            /**
             * The program object's ID.
             */
            GLuint m_id;

            /**
             * Allocate an OpenGL program object.
             */
            void allocate();

            /**
             * Internal helper to build().
             */
            void _build() const
            {
                link();
            }

            /**
             * Internal helper to build().
             */
            template <typename... Shaders>
            void _build(const Shader & shader, Shaders... args) const
            {
                attach_shader(shader);
                _build(args...);
            }

            /**
             * Internal helper to build().
             */
            template <typename... Shaders>
            void _build(std::unique_ptr<Shader> shader, Shaders... args) const
            {
                attach_shader(shader);
                _build(args...);
            }

            /**
             * Internal helper to build().
             */
            template <typename... Shaders>
            void _build(std::shared_ptr<Shader> shader, Shaders... args) const
            {
                attach_shader(shader);
                _build(args...);
            }

            /**
             * Internal helper to build().
             */
            template <typename... Shaders>
            void _build(const char * attribute_name, GLuint index, Shaders... args) const
            {
                glBindAttribLocation(m_id, index, attribute_name);
                _build(args...);
            }
    };
};

#endif
