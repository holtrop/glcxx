#include "glcxx/Program.hpp"
#include "glcxx/Error.hpp"
#include <string>

namespace glcxx
{
    Program::Program()
    {
        m_id = 0u;
    }

    Program::~Program()
    {
        if (m_id > 0u)
        {
            glDeleteProgram(m_id);
        }
    }

    void Program::allocate()
    {
        m_id = glCreateProgram();
        if (m_id == 0u)
        {
            throw Error("Failed to allocate an OpenGL program");
        }
    }

    void Program::_create() const
    {
        glLinkProgram(m_id);

        GLint link_status;
        glGetProgramiv(m_id, GL_LINK_STATUS, &link_status);
        if (link_status != GL_TRUE)
        {
            std::string message = "Failed to link program";
            GLint log_length = 0;
            glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &log_length);
            if (log_length > 0)
            {
                char *log = new char[log_length];
                glGetProgramInfoLog(m_id, log_length, &log_length, log);
                message += "\n";
                message += log;
                message += "\n";
                delete[] log;
            }
            throw Error(message);
        }
    }
}
