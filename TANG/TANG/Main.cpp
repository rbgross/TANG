/***************************************************************************************************
* Main.cpp
*
* Placeholder.
***************************************************************************************************/

#include "TangHeader.h"

/***************************************************************************************************
* main function
*
* Placeholder.
***************************************************************************************************/
int main( int argc, char* argv[] ) {	
	Renderer* renderer = new Renderer();
	while ( renderer->windowOpen() ) {
		renderer->draw();
	}
	delete renderer;
}