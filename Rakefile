require "rscons"

base_env = Rscons::Environment.new do |env|
  env["build_root"] = lambda {|args| args[:env].build_root}
  env["CPPPATH"] << "include"
  env["CPPPATH"] << "test/gl3w"
  env["CPPDEFINES"] << %[GLCXX_GL_INCLUDE="GL3/gl3w.h"]
  env["CCFLAGS"] += %w[-Wall]
  env["CXXFLAGS"] += %w[-std=gnu++11]
  env["CXXSUFFIX"] = %w[.cc .cpp]
end

task :lib do
  base_env.clone do |env|
    env.build_root = "build/lib"
    sources = Dir["src/**/*.cpp"]
    env.Library("${build_root}/lib.a", sources)
  end
end

task :test do
  base_env.clone do |env|
    env.build_root = "build/test"
    env.parse_flags!("!sdl2-config --cflags --libs")
    sources = Dir["src/**/*.cpp", "test/**/*.{cpp,c}"]
    env["LIBS"] += %w[dl GL]
    env.Program("${build_root}/testapp", sources)
  end
end

task :clean do
  Rscons.clean
end
