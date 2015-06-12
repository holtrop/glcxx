#ifndef GLCXX_PROGRAM_HPP
#define GLCXX_PROGRAM_HPP

#include <initializer_list>
#include <memory>
#include "glcxx/Shader.hpp"

namespace glcxx
{
    class Program
    {
        public:
            Program();

            ~Program();

            GLuint id() const { return m_id; }

            void use() const { glUseProgram(m_id); }

            bool valid() const { return m_id > 0u; }

            template <typename... Shaders>
            void create(Shaders... shaders)
            {
                allocate();
                _create(shaders...);
            }

            void attach_shader(const Shader & shader) const
            {
                glAttachShader(m_id, shader.id());
            }

            void attach_shader(std::unique_ptr<Shader> shader) const
            {
                glAttachShader(m_id, shader->id());
            }

            void attach_shader(std::shared_ptr<Shader> shader) const
            {
                glAttachShader(m_id, shader->id());
            }

            GLint get_uniform_location(const char * uniform_name)
            {
                return glGetUniformLocation(m_id, uniform_name);
            }

        protected:
            void allocate();

            void _create() const;

            template <typename... Shaders>
            void _create(const Shader & shader, Shaders... args) const
            {
                attach_shader(shader);
                _create(args...);
            }

            template <typename... Shaders>
            void _create(std::unique_ptr<Shader> shader, Shaders... args) const
            {
                attach_shader(shader);
                _create(args...);
            }

            template <typename... Shaders>
            void _create(std::shared_ptr<Shader> shader, Shaders... args) const
            {
                attach_shader(shader);
                _create(args...);
            }

            template <typename... Shaders>
            void _create(const char * attribute_name, GLuint index, Shaders... args) const
            {
                glBindAttribLocation(m_id, index, attribute_name);
                _create(args...);
            }

            GLuint m_id;
    };
};

#endif
