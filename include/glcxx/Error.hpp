/**
 * @file
 *
 * C++ exceptions for glcxx.
 */
#ifndef GLCXX_ERROR_HPP
#define GLCXX_ERROR_HPP

#include <stdexcept>

namespace glcxx
{
    /**
     * Exception class for glcxx errors.
     *
     * An instance of this class might be thrown if an OpenGL object cannot
     * be allocated or another glcxx error condition arises.
     */
    class Error : public std::runtime_error
    {
        public:
            /**
             * Construct an Error instance.
             *
             * @param msg The exception message.
             */
            Error(const std::string & msg) : std::runtime_error(msg)
            {
            };
    };
};

#endif
