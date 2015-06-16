# glcxx

glcxx is a Modern C++ Interface to OpenGL Object Management.

## Features

### C++11

glcxx uses C++11 features such as initializer_list and variadic templates to
provide a user-friendly API.
For example, an OpenGL buffer can be allocated and filled with data with a
a single call:

```
auto buffer = glcxx::Buffer::create(GL_ARRAY_BUFFER, GL_STATIC_DRAW,
                                    {-1, -1, 1, -1, 1, 1, -1, 1});
```

## License

glcxx is licensed under the [MIT License](LICENSE).
