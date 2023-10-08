# ComputerGraphics
For course work for a class at Grand Canyon University

## Building instructions.

Requirements:
1. Requires OpenGL
2. GLU
3. GLUT

The above need to be installed on the system, and their packages discoverable by cmake.

This repository uses `cmake` to build the project. 
There is a `buildme.sh` script that cleans the build directory.
It then automatically runs cmake and make.

1. Make sure the working directory is the root of the repository.
2. Run buildme.sh `bash buildme.sh`
3. This will have created a build directory. The executable is called `OpenGLTest` in the build directory.
4. To run, `cd build` and then `./OpenGLTest`
