#ifndef GLCXX_ERROR_HPP
#define GLCXX_ERROR_HPP

#include <stdexcept>

namespace glcxx
{

    class Error : public std::runtime_error
    {
        public:
            Error(const std::string & msg) : std::runtime_error(msg)
            {
            };
    };

};

#endif
