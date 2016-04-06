def options(opt):
    opt.load("compiler_c compiler_cxx")

def configure(conf):
    conf.load("compiler_c compiler_cxx")
    conf.check(header_name = "stdio.h", features = "cxx cxxprogram")
    conf.env.INCLUDES += ["include"]
    conf.env.INCLUDES += ["test/gl3w"]
    conf.env.DEFINES += ['''GLCXX_GL_INCLUDE="GL3/gl3w.h"''']
    conf.env.CXXFLAGS += ["-Wall"]
    conf.env.CXXFLAGS += ["-std=gnu++11"]
    conf.check_cfg(package = "sdl2", args = "--cflags --libs")

def build(bld):
    sources = bld.path.ant_glob("src/**/*.cpp")
    bld.shlib(source = sources, target = "glcxx")

    test_sources = bld.path.ant_glob("test/**/*.cpp") + \
                   bld.path.ant_glob("test/**/*.c")
    bld.program(source = test_sources,
                target = "glcxx-test",
                use = "glcxx",
                uselib = "SDL2",
                lib = ["dl", "GL"],
                linkflags = ["-Wl,-rpath,$ORIGIN"])
