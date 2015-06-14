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

            template <typename... Shaders>
            void build(Shaders... shaders)
            {
                allocate();
                _build(shaders...);
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

            void link() const;

            GLint get_uniform_location(const char * uniform_name)
            {
                return glGetUniformLocation(m_id, uniform_name);
            }

            template <typename... Args>
            static std::shared_ptr<Program> create(Args... args)
            {
                std::shared_ptr<Program> program = std::make_shared<Program>();
                program->build(args...);
                return program;
            }

        protected:
            GLuint m_id;

            void allocate();

            void _build() const
            {
                link();
            }

            template <typename... Shaders>
            void _build(const Shader & shader, Shaders... args) const
            {
                attach_shader(shader);
                _build(args...);
            }

            template <typename... Shaders>
            void _build(std::unique_ptr<Shader> shader, Shaders... args) const
            {
                attach_shader(shader);
                _build(args...);
            }

            template <typename... Shaders>
            void _build(std::shared_ptr<Shader> shader, Shaders... args) const
            {
                attach_shader(shader);
                _build(args...);
            }

            template <typename... Shaders>
            void _build(const char * attribute_name, GLuint index, Shaders... args) const
            {
                glBindAttribLocation(m_id, index, attribute_name);
                _build(args...);
            }
    };
};

#endif
