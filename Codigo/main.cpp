//=============================================================================
// Sample Application for GLEW, and cwc Application/Window class using freeglut
//=============================================================================

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "myApplication.h"
#include "myWindow.h"
#include <iostream>

//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

int main(void)
{
	myApplication*  pApp = new myApplication;
	myWindow* myWin = new myWindow();

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cout << "Failed to initialize GLEW!" << std::endl;
    }
    std::cout << "Using GLEW Version: " << glewGetString(GLEW_VERSION) << std::endl;

	pApp->run();
	delete pApp;
	return 0;
}

//-----------------------------------------------------------------------------

