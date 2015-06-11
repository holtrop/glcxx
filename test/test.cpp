#include <SDL.h>
#include GLCXX_GL_INCLUDE
#include <iostream>
#include "glcxx.hpp"

using namespace std;

#define WIDTH   800
#define HEIGHT  600

shared_ptr<glcxx::Shader> vs;
shared_ptr<glcxx::Shader> fs;
shared_ptr<glcxx::Program> program;

bool init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    try
    {
        vs->create_from_file(GL_VERTEX_SHADER, "test/vert.glsl");
        fs->create_from_file(GL_FRAGMENT_SHADER, "test/frag.glsl");
        program->create(vs, fs);
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

    SDL_GL_CreateContext(window);

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
