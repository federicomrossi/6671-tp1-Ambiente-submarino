README
=======

AUTOR:	Federico M. Rossi
EMAIL:	federicomrossi@gmail.com
AÑO:	2014

GITHUB: https://github.com/federicomrossi/6671-tp1-Ambiente-submarino



Descripción
-----------

Version 1.0 del simulador de un ambiente submarino en OpenGL.


COMPILACIÓN
-----------

Para compilar la aplicación, posiciónese en el directorio raíz del programa desde la terminal y ejecute el siguiente comando:

	$ make

Una vez compilado, se habrá generado en dicho directorio el archivo ejecutable ./6671.
Puede realizarse una limpieza de los archivos producto de la compilación ejecutando el siguiente comando:

	$ make clean

Tenga en cuenta que al hacer esto se eliminarán todos los archivos objetos y el ejecutable generado, por lo que, en caso de desear ejecutar el simulador, deberá volver a compilar la aplicación.


EJECUTAR EL SIMULADOR
-----------

Para ejecutar el simulador, una vez compilado y estando posicionado en el directorio raiz del programa con la terminal, ejecute la siguiente directiva:

	$ make run

Una forma alternativa de ejecutar el simulador es simplemente correr el ejecutable con nombre "6671".



TECLAS DE DESPLAZAMIENTO
-----------

El simulador posee un conjunto de teclas que permiten el desplazamiento
de la cámara a través de la escena. Podrá notar el usuario que al realizar
un movimiento, la cámara se trasladará de posición con un minúsculo efecto
de inercia, lo que provee un andar suave por el medio.
Las teclas son:

	A: Movimiento hacia la izquierda;
	S: Movimiento hacia atras;
	D: Movimiento hacia la derecha;
	W: Movimiento hacia adelante;
	I: Movimiento hacia arriba;
	K: Movimiento hacia abajo;
	+: Giro hacia la derecha;
	-: Giro hacia la izquierda;


TECLAS GENERALES
-----------

Existen además teclas de propósito genera, a saber:

	P: Detiene la simulación, impidiendo además desplazarse por la escena;
	O: Cambiar a pantalla completa;
	L: Restaurar tamaño inicial de la pantalla;
