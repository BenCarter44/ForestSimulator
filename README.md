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

1. First Clone the git repository
    - this can be found at https://github.com/BenRobotics101/ComputerGraphics
    - or in linux can be cloned by running
        `git clone git clone https://github.com/BenRobotics101/ComputerGraphics.git`
    - you can run `git checkout main` to make sure you are in the main branch. 
2. Make sure the working directory is the root of the repository.
3. Run buildme.sh `bash buildme.sh`
4. This will have created a build directory. The executable is called `OpenGLTest` in the build directory.
5. To run, `cd build` and then `./OpenGLTest`
