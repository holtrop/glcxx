/**
 * @file
 *
 * Include module for the main OpenGL header.
 * The user can define the GLCXX_GL_INCLUDE macro to the name of the include
 * file to use for OpenGL to override the default OpenGL header name.
 */
#ifndef GLCXX_GL_HPP
#define GLCXX_GL_HPP

#ifdef GLCXX_GL_INCLUDE
#include GLCXX_GL_INCLUDE
#else
#include "GL/gl.h"
#endif

#endif
