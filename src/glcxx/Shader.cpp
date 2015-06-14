#include "glcxx/Shader.hpp"
#include "glcxx/Error.hpp"
#include <string>
#include <fstream>
#include <vector>

namespace glcxx
{
    Shader::Shader(GLenum shader_type)
    {
        m_shader_type = shader_type;
        allocate();
    }

    Shader::~Shader()
    {
        glDeleteShader(m_id);
    }

    void Shader::set_source(const char * source, int length)
    {
        GLint status;

        GLint lengths[1] = {length};
        glShaderSource(m_id, 1, &source, &lengths[0]);

        glCompileShader(m_id);

        glGetShaderiv(m_id, GL_COMPILE_STATUS, &status);
        if (status == GL_TRUE)
        {
            return;
        }

        std::string message = "Error compiling ";
        switch (m_shader_type)
        {
            case GL_VERTEX_SHADER:
                message += "vertex";
                break;
            case GL_FRAGMENT_SHADER:
                message += "fragment";
                break;
            default:
                message += "unknown";
                break;
        }
        message += " shader";

        GLint log_length;
        glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &log_length);
        if (log_length > 0)
        {
            char * log = new char[log_length];
            glGetShaderInfoLog(m_id, log_length, &log_length, log);
            message += "\nShader Log:\n";
            message += log;
            message += "\n";
            delete[] log;
        }
        glDeleteShader(m_id);
        throw Error(message);
    }

    void Shader::set_source_from_file(const char * filename)
    {
        std::ifstream ifs;
        ifs.open(filename);
        if (!ifs.is_open())
        {
            throw Error(std::string("Error opening ") + filename);
        }
        ifs.seekg(0, ifs.end);
        int length = ifs.tellg();
        ifs.seekg(0, ifs.beg);
        std::vector<char> file_contents(length);
        ifs.read(&file_contents[0], length);
        set_source(&file_contents[0], length);
    }

    void Shader::allocate()
    {
        m_id = glCreateShader(m_shader_type);
        if (m_id == 0u)
        {
            throw Error("Failed to allocate an OpenGL shader");
        }
    }
}
