#ifndef GLCXX_SHADER_HPP
#define GLCXX_SHADER_HPP

#include "glcxx/gl.hpp"
#include <memory>

namespace glcxx
{
    class Shader
    {
        public:
            Shader(GLenum shader_type);

            ~Shader();

            void set_source(const char * source, int length = -1);

            void set_source_from_file(const char * filename);

            GLuint id() const { return m_id; }

            static std::shared_ptr<Shader> create(GLenum shader_type, const char * source, int length = -1)
            {
                std::shared_ptr<Shader> shader = std::make_shared<Shader>(shader_type);
                shader->set_source(source, length);
                return shader;
            }

            static std::shared_ptr<Shader> create_from_file(GLenum shader_type, const char * filename)
            {
                std::shared_ptr<Shader> shader = std::make_shared<Shader>(shader_type);
                shader->set_source_from_file(filename);
                return shader;
            }

        protected:
            GLuint m_id;

            GLenum m_shader_type;

            void allocate();
    };
};

#endif
