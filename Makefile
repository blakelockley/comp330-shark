main: *.cpp *.h
	g++ -std=c++98 *.cpp -framework GLUT -framework OpenGL -o main -Wno-deprecated
