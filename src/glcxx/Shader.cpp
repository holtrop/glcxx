#include "glcxx/Shader.hpp"
#include "glcxx/Error.hpp"
#include <string>

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

    void Shader::create(GLenum shaderType, const char *source)
    {
        GLint status;

        m_id = glCreateShader(shaderType);
        if (m_id == 0u)
        {
            throw Error("Failed to allocate an OpenGL shader");
        }

        glShaderSource(m_id, 1, &source, NULL);

        glCompileShader(m_id);

        glGetShaderiv(m_id, GL_COMPILE_STATUS, &status);
        if (status == GL_TRUE)
        {
            return;
        }

        std::string message = "Error compiling ";
        switch (shaderType)
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
}
