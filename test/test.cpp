#include <SDL.h>
#include GLCXX_GL_INCLUDE
#include <iostream>
#include "glcxx.hpp"

using namespace std;

#define WIDTH   800
#define HEIGHT  600

shared_ptr<glcxx::Shader> vs;
shared_ptr<glcxx::Shader> vs2;
shared_ptr<glcxx::Shader> fs;
shared_ptr<glcxx::Shader> fs2;
shared_ptr<glcxx::Program> program;
shared_ptr<glcxx::Program> program2;
shared_ptr<glcxx::Buffer> buffer;
shared_ptr<glcxx::Buffer> buffer2;
shared_ptr<glcxx::Buffer> buffer3;

bool init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    try
    {
        vs = make_shared<glcxx::Shader>();
        vs2 = make_shared<glcxx::Shader>();
        fs = make_shared<glcxx::Shader>();
        fs2 = make_shared<glcxx::Shader>();
        program = make_shared<glcxx::Program>();
        program2 = make_shared<glcxx::Program>();
        buffer = make_shared<glcxx::Buffer>();
        buffer2 = make_shared<glcxx::Buffer>();
        buffer3 = make_shared<glcxx::Buffer>();

        vs->create_from_file(GL_VERTEX_SHADER, "test/vert.glsl");
        fs->create_from_file(GL_FRAGMENT_SHADER, "test/frag.glsl");
        program->create(vs, fs,
                        "position", 0);

        vs2->create_from_file(GL_VERTEX_SHADER, "test/vert2.glsl");
        fs2->create_from_file(GL_FRAGMENT_SHADER, "test/frag2.glsl");
        program2->create(vs2, fs2,
                         "position", 0,
                         "color", 1);

        GLfloat coords[] = {
            -0.5, -0.5,
            0.5, -0.5,
            0.5, 0.5,
            -0.5, 0.5,
        };
        buffer->create(GL_ARRAY_BUFFER, GL_STATIC_DRAW, &coords, sizeof(coords));

        GLfloat coords2[] = {
            0.2, 0.2,
            0.9, 0.2,
            0.9, 0.9,
        };
        buffer2->create(GL_ARRAY_BUFFER, GL_STATIC_DRAW, &coords2, sizeof(coords2));
        GLfloat colors[] = {
            1.0, 0.1, 0.1, 1.0,
            0.1, 1.0, 0.1, 1.0,
            0.1, 0.1, 1.0, 1.0,
        };
        buffer3->create(GL_ARRAY_BUFFER, GL_STATIC_DRAW, &colors, sizeof(colors));
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

    glEnableVertexAttribArray(0);
    buffer->bind();
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
    program->use();
    GLint uniform_location = program->get_uniform_location("color");
    glUniform4f(uniform_location, 1.0, 0.6, 0.2, 1.0);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glEnableVertexAttribArray(1);
    buffer2->bind();
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
    buffer3->bind();
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), NULL);
    program2->use();
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
