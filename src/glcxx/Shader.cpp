#include "glcxx/Shader.hpp"
#include "glcxx/Error.hpp"
#include <string>
#include <fstream>
#include <vector>

namespace glcxx
{
    Shader::Shader()
    {
        m_id = 0u;
    }

    Shader::~Shader()
    {
        if (m_id > 0u)
        {
            glDeleteShader(m_id);
        }
    }

    void Shader::create(GLenum shader_type, const char * source, int length)
    {
        GLint status;

        m_id = glCreateShader(shader_type);
        if (m_id == 0u)
        {
            throw Error("Failed to allocate an OpenGL shader");
        }

        GLint lengths[1] = {length};
        glShaderSource(m_id, 1, &source, &lengths[0]);

        glCompileShader(m_id);

        glGetShaderiv(m_id, GL_COMPILE_STATUS, &status);
        if (status == GL_TRUE)
        {
            return;
        }

        std::string message = "Error compiling ";
        switch (shader_type)
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

    void Shader::create_from_file(GLenum shader_type, const char * filename)
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
        create(shader_type, &file_contents[0], length);
    }
}
