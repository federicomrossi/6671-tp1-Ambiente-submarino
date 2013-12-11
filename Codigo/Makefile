# 6671 1er c 2013

# Nombre del ejecutable.
target = 6671

# Archivo log de Valgrind.
VGLOGFILE = valgrind.out

# Flags para el Valgrind
VGFLAGS = --tool=memcheck --trace-children=yes --track-fds=yes --time-stamp=yes --num-callers=20 --error-exitcode=42 --db-attach=no --leak-check=full --leak-resolution=med --log-file=$(VGLOGFILE)




all: main
	g++  main.o lib_matematica.o scene.o object_dibujable.o object_eje_coordenado.o object_vector.o object_cube.o object_grid.o object_spiralSphere.o object_superficie.o object_superficie_agua.o object_cangrejo.o object_cangrejo_cuerpo.o object_cangrejo_pata.o object_cangrejo_pata_muslo.o object_cangrejo_pata_pierna.o object_cangrejo_pata_pie.o object_cangrejo_ojo.o object_cangrejo_pinza.o object_cangrejo_pinza_antebrazo.o object_cangrejo_pinza_brazo.o object_cangrejo_pinza_garra_superior.o object_cangrejo_pinza_garra_inferior.o object_pez.o object_pez_cuerpo.o object_pez_ojo.o object_pez_aleta_trasera.o object_pez_aleta_dorsal.o object_pez_aleta_lateral.o object_roca.o object_planta_acuatica.o object_planta_hoja_tipo01.o object_planta_hoja_tipo02.o object_planta_hoja_tipo03.o myWindow.o myApplication.o glutWindow.o glWindow.o glApplication.o -lGLEW -lGLU -lGL -lglut -lSOIL -o 6671

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

object_vector: object_vector.cpp object_vector.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_vector.cpp

object_grid: object_grid.cpp object_grid.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_grid.cpp

object_cube: object_cube.cpp object_cube.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_cube.cpp

object_spiralSphere: object_spiralSphere.cpp object_spiralSphere.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_spiralSphere.cpp




object_cangrejo: object_cangrejo.cpp object_cangrejo.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_cangrejo.cpp

object_cangrejo_cuerpo: object_cangrejo_cuerpo.cpp object_cangrejo_cuerpo.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_cangrejo_cuerpo.cpp

object_cangrejo_pata: object_cangrejo_pata.cpp object_cangrejo_pata.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_cangrejo_pata.cpp

object_cangrejo_pata_muslo: object_cangrejo_pata_muslo.cpp object_cangrejo_pata_muslo.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_cangrejo_pata_muslo.cpp

object_cangrejo_pata_pierna: object_cangrejo_pata_pierna.cpp object_cangrejo_pata_pierna.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_cangrejo_pata_pierna.cpp

object_cangrejo_pata_pie: object_cangrejo_pata_pie.cpp object_cangrejo_pata_pie.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_cangrejo_pata_pie.cpp

object_cangrejo_ojo: object_cangrejo_ojo.cpp object_cangrejo_ojo.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_cangrejo_ojo.cpp

object_cangrejo_pinza: object_cangrejo_pinza.cpp object_cangrejo_pinza.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_cangrejo_pinza.cpp

object_cangrejo_pinza_antebrazo: object_cangrejo_pinza_antebrazo.cpp object_cangrejo_pinza_antebrazo.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_cangrejo_pinza_antebrazo.cpp

object_cangrejo_pinza_brazo: object_cangrejo_pinza_brazo.cpp object_cangrejo_pinza_brazo.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_cangrejo_pinza_brazo.cpp

object_cangrejo_pinza_garra_superior: object_cangrejo_pinza_garra_superior.cpp object_cangrejo_pinza_garra_superior.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_cangrejo_pinza_garra_superior.cpp

object_cangrejo_pinza_garra_inferior: object_cangrejo_pinza_garra_inferior.cpp object_cangrejo_pinza_garra_inferior.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_cangrejo_pinza_garra_inferior.cpp



object_superficie: object_superficie.cpp object_superficie.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_superficie.cpp

object_superficie_agua: object_superficie_agua.cpp object_superficie_agua.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_superficie_agua.cpp

object_pez: object_pez.cpp object_pez.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_pez.cpp

object_pez_cuerpo: object_pez_cuerpo.cpp object_pez_cuerpo.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_pez_cuerpo.cpp

object_pez_ojo: object_pez_ojo.cpp object_pez_ojo.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_pez_ojo.cpp

object_pez_aleta_trasera: object_pez_aleta_trasera.cpp object_pez_aleta_trasera.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_pez_aleta_trasera.cpp

object_pez_aleta_dorsal: object_pez_aleta_dorsal.cpp object_pez_aleta_dorsal.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_pez_aleta_dorsal.cpp

object_pez_aleta_lateral: object_pez_aleta_lateral.cpp object_pez_aleta_lateral.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_pez_aleta_lateral.cpp

object_roca: object_roca.cpp object_roca.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_roca.cpp

object_planta_acuatica: object_planta_acuatica.cpp object_planta_acuatica.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_planta_acuatica.cpp

object_planta_hoja_tipo01: object_planta_hoja_tipo01.cpp object_planta_hoja_tipo01.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_planta_hoja_tipo01.cpp

object_planta_hoja_tipo02: object_planta_hoja_tipo02.cpp object_planta_hoja_tipo02.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_planta_hoja_tipo02.cpp


object_planta_hoja_tipo03: object_planta_hoja_tipo03.cpp object_planta_hoja_tipo03.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c object_planta_hoja_tipo03.cpp





scene: scene.cpp scene.h
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c scene.cpp

lib_matematica: lib_matematica.cpp lib_matematica.h
	g++ -c lib_matematica.cpp

main: main.cpp lib_matematica myWindow myApplication scene object_dibujable object_eje_coordenado object_vector object_cube object_grid object_spiralSphere object_superficie object_superficie_agua object_cangrejo object_cangrejo_cuerpo object_cangrejo_pata object_cangrejo_pata_muslo object_cangrejo_pata_pierna object_cangrejo_pata_pie object_cangrejo_ojo object_cangrejo_pinza object_cangrejo_pinza_antebrazo object_cangrejo_pinza_brazo object_cangrejo_pinza_garra_superior object_cangrejo_pinza_garra_inferior object_pez object_pez_cuerpo object_pez_ojo object_pez_aleta_trasera object_pez_aleta_dorsal object_pez_aleta_lateral object_roca object_planta_acuatica object_planta_hoja_tipo01 object_planta_hoja_tipo02 object_planta_hoja_tipo03
	g++ -DFREEGLUT_STATIC -DGLEW_STATIC -c main.cpp

run:
	./$(target)

valgrind:
	valgrind $(VGFLAGS) ./$(target)

clean:
	rm -rf *o main ./$(target)
