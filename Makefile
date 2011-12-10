serveur : final.cpp sdlglutils.cpp librairie.cpp reseau.cpp
	g++ -Wall -v -Wextra -Os -o $@ $^ `sdl-config --libs --cflags` -lSDL_image -lGL -lGLU -Wall -Wextra -DSERVEUR

client : final.cpp sdlglutils.cpp librairie.cpp reseau.cpp
	g++ -Wall -v -Wextra -Os -o $@ $^ `sdl-config --libs --cflags` -lSDL_image -lGL -lGLU -Wall -Wextra
