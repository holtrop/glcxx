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

            void bind_attribute(const char * name, GLuint index) const
            {
                glBindAttribLocation(m_id, index, name);
            }

            template <typename... Args>
            void bind_attributes(const char * name, GLuint index, Args... args) const
            {
                bind_attribute(name, index);
                bind_attributes(args...);
            }

        protected:
            void allocate();

            void _create() const;

            template <typename T, typename... Shaders>
            void _create(T shader, Shaders... args) const
            {
                attach_shader(shader);
                _create(args...);
            }

            GLuint m_id;
    };
};

#endif
