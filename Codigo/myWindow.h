#pragma once

#include "glutWindow.h"
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 

#include "scene.h"





/* ****************************************************************************
 * DECLARACIÓN DE LA CLASE
 * ***************************************************************************/


class myWindow : public cwc::glutWindow
{

private:

	Scene scene; // Escena

public:

	myWindow();

	virtual void OnRender(void);

	virtual void OnIdle();

	// When OnInit is called, a render context (in this case GLUT-Window) 
	// is already available.
	virtual void OnInit();

	// Resize event handler.
	virtual void OnResize(int w, int h);

	// Close event handler.
	virtual void OnClose(void);
	
	// Mouse down event handler.
	virtual void OnMouseDown(int button, int x, int y);
	
	// Mouse up event handler.
	virtual void OnMouseUp(int button, int x, int y);

	// Called when Mouse is moved (without pressing any button)
	virtual void OnMouseMove(int x, int y);
	
	// Mouse wheel event handler.
	virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y);

	// Key down event handler.
	virtual void OnKeyDown(int nKey, char cAscii);

	// Key up event handler.
	virtual void OnKeyUp(int nKey, char cAscii);
};
