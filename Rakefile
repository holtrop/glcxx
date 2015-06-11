require "rscons"

task :lib do
  Rscons::Environment.new do |env|
    env["build_root"] = "build/lib"
    env.build_root = env["build_root"]
    sources = Dir["src/**/*.cpp"]
    env["CPPPATH"] << "include"
    env["CPPPATH"] << "test/gl3w"
    env["CPPDEFINES"] << %[GLCXX_GL_INCLUDE="gl3w.h"]
    env["CXXFLAGS"] += %w[-Wall -std=gnu++11]
    env.Library("${build_root}/lib.a", sources)
  end
end

task :test do
end

task :clean do
  Rscons.clean
end
