/*******************************************************************************
* FocusObject.cpp
*
* Placeholder.
*******************************************************************************/

/* INCLUDES */
#include "TangHeader.h"

/***************************************************************************************************
* FocusObject function
*
* Placeholder.
***************************************************************************************************/
FocusObject::FocusObject( Renderer* renderer ) {
	this->renderer = renderer;
	this->mesh = new Mesh( "C:\\Users\\Ryan\\Game Tests\\SphereTest.obj" );
	this->position = glm::vec3();
	this->color = glm::vec3();
}

/***************************************************************************************************
* ~FocusObject function
*
* Placeholder.
***************************************************************************************************/
FocusObject::~FocusObject( void ) {
	delete this->mesh;
}

/***************************************************************************************************
* setPosition function
*
* Placeholder.
***************************************************************************************************/
void FocusObject::setPosition( glm::vec3 position ) {
	this->position = position;
}

/***************************************************************************************************
* setColor function
*
* Placeholder.
***************************************************************************************************/
void FocusObject::setColor( glm::vec3 color ) {
	this->color = color;
}

/***************************************************************************************************
* update function
*
* Placeholder.
***************************************************************************************************/
void FocusObject::update( void ) {
	
}

/***************************************************************************************************
* draw function
*
* Placeholder.
***************************************************************************************************/
void FocusObject::draw( void ) {
	// Calculate and apply the cube model transformation
	glm::mat4 model = glm::translate( this->renderer->environment->getModel(), this->position );
	this->renderer->setModel( model );
	this->renderer->setDiffCol( this->color );
	this->mesh->draw();
}