# glcxx

glcxx is a Modern C++ Interface for OpenGL Object Management.

It provides an object-oriented interface for the following OpenGL objects:

- Array (VAO)
- Buffer (VBO)
- Shader
- Program
- Texture

glcxx is not an OpenGL loading library. It does not provide window or OpenGL
context creation.
Other libraries such as GL3W, GLEW, SDL, Qt, GTK, etc... can be used in
conjunction with glcxx.

## Features

### Modern C++11 API

glcxx uses modern C++11 features such as initializer_list and variadic
templates to provide a user-friendly API.
For example, an OpenGL buffer can be allocated and filled with data with a
a single call:

```
auto buffer = glcxx::Buffer::create(GL_ARRAY_BUFFER, GL_STATIC_DRAW,
                                    {-1, -1, 1, -1, 1, 1, -1, 1});
```

## Documentation

[https://holtrop.github.io/glcxx/doxygen/annotated.html](https://holtrop.github.io/glcxx/doxygen/annotated.html)

## Integrating onto a Project

glcxx can be imported into an OpenGL project as a subdirectory and built along
with the project. The top-level `include` directory needs to be added to the
C++ include path, and the *.cpp sources under the `src` directory need to be
compiled and linked with the project.

glcxx headers need access to an OpenGL header. The integrating project should
define the macro `GLCXX_GL_INCLUDE` to a string naming the include file to use.

## License

glcxx is licensed under the [MIT License](LICENSE).
