# 6671 1er c 2013

all: main
	g++  main.o scene.o object_dibujable.o object_eje_coordenado.o object_cube.o object_grid.o object_spiralSphere.o object_cangrejo_pata.o object_cangrejo_pata_muslo.o myWindow.o myApplication.o glutWindow.o glWindow.o glApplication.o -lGLEW -lGLU -lGL -lglut -o 6671

glApplication: glApplication.cpp glApplication.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c glApplication.cpp

glWindow: glWindow.cpp glWindow.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c glWindow.cpp

glutWindow: glutWindow.cpp glutWindow.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c glutWindow.cpp
	
myApplication: myApplication.cpp myApplication.h glApplication
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c myApplication.cpp

myWindow: myWindow.cpp myWindow.h glutWindow glWindow
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c myWindow.cpp

object_dibujable: object_dibujable.cpp object_dibujable.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_dibujable.cpp

object_eje_coordenado: object_eje_coordenado.cpp object_eje_coordenado.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_eje_coordenado.cpp

object_grid: object_grid.cpp object_grid.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_grid.cpp

object_cube: object_cube.cpp object_cube.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_cube.cpp

object_spiralSphere: object_spiralSphere.cpp object_spiralSphere.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_spiralSphere.cpp

object_cangrejo_pata: object_cangrejo_pata.cpp object_cangrejo_pata.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_cangrejo_pata.cpp

object_cangrejo_pata_muslo: object_cangrejo_pata_muslo.cpp object_cangrejo_pata_muslo.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_cangrejo_pata_muslo.cpp

scene: scene.cpp scene.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c scene.cpp

main: main.cpp myWindow myApplication scene object_dibujable object_eje_coordenado object_cube object_grid object_spiralSphere object_cangrejo_pata object_cangrejo_pata_muslo
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c main.cpp

run:
	./6671

clean:
	rm -rf *o main ./6671
