#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform2.hpp> 
#include <glm/gtx/projection.hpp>

#include <iostream>
#include <fstream>

#include "myWindow.h"





/* ****************************************************************************
 * DEFINICIÓN DE LA CLASE
 * ***************************************************************************/


const char* loadShaderAsString(const char* file)
{
    std::ifstream shader_file(file, std::ifstream::in);
    std::string str((std::istreambuf_iterator<char>(shader_file)), std::istreambuf_iterator<char>());
    return str.c_str();
}


myWindow::myWindow() { }


void myWindow::OnRender(void)
{
	// Renderizamos escena
	this->scene.render(this->height, this->width);
	this->Repaint();
}


void  myWindow::OnIdle()
{
	// while(true) {
	// 	this->dra
	// }
}


// When OnInit is called, a render context (in this case GLUT-Window) 
// is already available
void  myWindow::OnInit()
{
	// Inicializamos escena
	this->scene.initialize();
}


// Resize event handler.
void myWindow::OnResize(int w, int h) 
{
	// Redimensionamos escena
	this->scene.resize(w, h);

	// Redimensionamos ventana
	this->width = w;
	this->height = h;
}


// Close event handler.
void  myWindow::OnClose(void) { }


// Mouse down event handler.
void myWindow::OnMouseDown(int button, int x, int y) { }


// Mouse up event handler.
void myWindow::OnMouseUp(int button, int x, int y) { }


// Mouse wheel event handler.
void myWindow::OnMouseWheel(int nWheelNumber, int nDirection, int x, int y) 
{
	std::cout << nWheelNumber << std::endl;
	
	// Disparamos evento
	this->scene.OnMouseWheel(nWheelNumber, nDirection, x, y);

	// Repintamos la ventana
	this->Repaint();
}


// Called when Mouse is moved (without pressing any button)
void myWindow::OnMouseMove(int x, int y)
{
	// Disparamos evento de movimiento del mouse
	this->scene.OnMouseMove(x, y);

	// Repintamos la ventana
	this->Repaint();
}


// Key down event handler.
void myWindow::OnKeyDown(int nKey, char cAscii)
{
	 // 0x1b = ESC
	if (cAscii == 27)
	{
		// Close Window
		this->Close(); 

		return;		
	}

	// Disparamos evento de tecla presionada
	this->scene.onKeyDown(nKey, cAscii);

	// Repintamos la ventana
	this->Repaint();
}


// Key up event handler.
void myWindow::OnKeyUp(int nKey, char cAscii)
{
	if (cAscii == 'o')
	{
		SetFullscreen(true);
	}
	else if (cAscii == 'l')
	{
		SetFullscreen(false);
	}

	// Disparamos evento de tecla liberada
	this->scene.onKeyUp(nKey, cAscii);
}
