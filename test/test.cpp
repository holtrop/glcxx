#include <SDL.h>
#include GLCXX_GL_INCLUDE
#include <iostream>
#include "glcxx.hpp"

using namespace std;

#define WIDTH   800
#define HEIGHT  600

shared_ptr<glcxx::Array> quad_array;
shared_ptr<glcxx::Program> quad_program;
shared_ptr<glcxx::Buffer> quad_geom_buffer;

shared_ptr<glcxx::Array> triangle_array;
shared_ptr<glcxx::Program> triangle_program;
shared_ptr<glcxx::Buffer> triangle_geom_buffer;
shared_ptr<glcxx::Buffer> triangle_color_buffer;

bool init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    try
    {
        quad_geom_buffer = glcxx::Buffer::create(GL_ARRAY_BUFFER, GL_STATIC_DRAW,
                                       {-0.5, -0.5,
                                        0.5, -0.5,
                                        0.5, 0.5,
                                        -0.5, 0.5});

        quad_array = make_shared<glcxx::Array>();

        quad_array->bind();
        glEnableVertexAttribArray(0);
        quad_geom_buffer->bind();
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

        quad_program = glcxx::Program::create(
          glcxx::Shader::create_from_file(GL_VERTEX_SHADER, "test/vert.glsl"),
          glcxx::Shader::create_from_file(GL_FRAGMENT_SHADER, "test/frag.glsl"),
          "position", 0);


        triangle_geom_buffer = glcxx::Buffer::create(GL_ARRAY_BUFFER, GL_STATIC_DRAW,
                                        {0.2, 0.2,
                                         0.9, 0.2,
                                         0.9, 0.9});
        triangle_color_buffer = glcxx::Buffer::create(GL_ARRAY_BUFFER, GL_STATIC_DRAW,
                                        {1.0, 0.1, 0.1, 1.0,
                                         0.1, 1.0, 0.1, 1.0,
                                         0.1, 0.1, 1.0, 1.0});

        triangle_array = make_shared<glcxx::Array>();

        triangle_array->bind();
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        triangle_geom_buffer->bind();
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
        triangle_color_buffer->bind();
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), NULL);

        triangle_program = glcxx::Program::create(
          glcxx::Shader::create_from_file(GL_VERTEX_SHADER, "test/vert2.glsl"),
          glcxx::Shader::create_from_file(GL_FRAGMENT_SHADER, "test/frag2.glsl"),
          "position", 0,
          "color", 1);
    }
    catch (glcxx::Error & e)
    {
        cerr << "glcxx error: " << e.what() << endl;
        return false;
    }
    return true;
}

void display(SDL_Window * window)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    quad_array->bind();
    quad_program->use();
    GLint uniform_location = quad_program->get_uniform_location("color");
    glUniform4f(uniform_location, 1.0, 0.6, 0.2, 1.0);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    triangle_array->bind();
    triangle_program->use();
    glDrawArrays(GL_TRIANGLE_FAN, 0, 3);

    SDL_GL_SwapWindow(window);
}

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf("Failed to initialize SDL!\n");
        return 1;
    }

    atexit(SDL_Quit);

    SDL_Window * window = SDL_CreateWindow(argv[0],
                                           SDL_WINDOWPOS_UNDEFINED,
                                           SDL_WINDOWPOS_UNDEFINED,
                                           WIDTH,
                                           HEIGHT,
                                           SDL_WINDOW_OPENGL);
    if (!window)
    {
        printf("Failed to create window!\n");
        SDL_Quit();
        return 2;
    }

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    if (gl_context == NULL)
    {
        cerr << "Failed to create OpenGL context" << endl;
        return 1;
    }
    SDL_GL_MakeCurrent(window, gl_context);

    if (gl3wInit())
    {
        cerr << "Failed to initialize gl3w!" << endl;
        return 1;
    }
    if (!gl3wIsSupported(3, 0))
    {
        cerr << "OpenGL 3.0 is not supported!" << endl;
        return 1;
    }

    if (!init())
    {
        return 1;
    }
    display(window);

    SDL_Event event;
    while (SDL_WaitEvent(&event))
    {
        if (event.type == SDL_QUIT)
            break;
        else if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
                break;
            if (event.key.keysym.sym == SDLK_RETURN)
                display(window);
        }
    }

    return 0;
}
