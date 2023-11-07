 
project:
	g++ -I include/ src/*.cpp -o Program1 -D PART1BUILD -lGL -lGLEW -lglfw -lglut -lGLU -lSOIL -ldl 
	g++ -I include/ src/*.cpp -o Program2 -D PART2BUILD -lGL -lGLEW -lglfw -lglut -lGLU -lSOIL -ldl 
