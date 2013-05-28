/*******************************************************************************
* Mesh.cpp
*
* Placeholder.
*******************************************************************************/

/* INCLUDES */
#include "TangHeader.h"

/***************************************************************************************************
* Mesh function
*
* Placeholder.
***************************************************************************************************/
Mesh::Mesh( std::string fileName ) {
	// Create Vertex Array Object
	glGenVertexArrays( 1, &this->vao );
	glBindVertexArray( this->vao );

	// Load the model from a file
	this->loadModel( fileName );

	// Create a Vertex Buffer Object and copy the vertex data to it
	glGenBuffers( 1, &this->vbo );
	glBindBuffer( GL_ARRAY_BUFFER, this->vbo );
	glBufferData( GL_ARRAY_BUFFER, this->meshData.size() * sizeof( float ), this->meshData.data(), GL_STATIC_DRAW );

	// Create an element array
	glGenBuffers( 1, &this->ebo );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->ebo );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, this->elements.size() * sizeof( float ), this->elements.data(), GL_STATIC_DRAW );

	// Specify layout of mesh data
	glEnableVertexAttribArray( ATTRIB_POSITION );
	glVertexAttribPointer( ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( float ), 0 );
	glEnableVertexAttribArray( ATTRIB_NORMAL );
	glVertexAttribPointer( ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( float ), (void*)( 3 * sizeof( float ) ) );

	// Unbind buffers
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, NULL );
	glBindBuffer( GL_ARRAY_BUFFER, NULL );
	glBindVertexArray( NULL );
}

/***************************************************************************************************
* ~Mesh function
*
* Placeholder.
***************************************************************************************************/
Mesh::~Mesh( void ) {
	glDeleteBuffers( 1, &this->ebo );
	glDeleteBuffers( 1, &this->vbo );
	glDeleteVertexArrays( 1, &this->vao );
}

/***************************************************************************************************
* update function
*
* Placeholder.
***************************************************************************************************/
void Mesh::update( void ) {

}

/***************************************************************************************************
* draw function
*
* Placeholder.
***************************************************************************************************/
void Mesh::draw( void ) {
	// Bind this vertex array
	glBindVertexArray( this->vao );

	// Draw the mesh
	glDrawElements( GL_TRIANGLES, this->elements.size(), GL_UNSIGNED_INT, this->elements.data() );
}


/***************************************************************************************************
* loadModel function
*
* Placeholder.
***************************************************************************************************/
void Mesh::loadModel( std::string fileName ) {
	std::ifstream in( fileName.c_str() );
	if ( !in ) {
		std::cerr << "Unable to open " << fileName << ".";
		return;
	}

	std::string line;
	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec3 > normals;
	std::vector< glm::vec2 > texCoords;

	while ( getline( in, line ) ) {
		std::istringstream s( line );
		std::string token;
		s >> token;

		if ( token == "v" ) {
			glm::vec3 v;
			s >> v.x >> v.y >> v.z;
			vertices.push_back( v );
		} else if ( token == "vn" ) {
			glm::vec3 v;
			s >> v.x >> v.y >> v.z;
			normals.push_back( v );
		} else if ( token == "vt" ) {
			glm::vec2 v;
			s >> v.x >> v.y;
			texCoords.push_back( v );
		} else if ( token == "f" ) {
			unsigned int v, t, n;
			int pos;
			for ( unsigned int i = 0; i < 3; i++ ) {
				s >> v;
				pos = s.tellg();
				s.seekg( pos + 1 );
				s >> t;
				pos = s.tellg();
				s.seekg( pos + 1 );
				s >> n;
				pos = s.tellg();
				s.seekg( pos + 1 );
				this->meshData.push_back( vertices[ v - 1 ].x );
				this->meshData.push_back( vertices[ v - 1 ].y );
				this->meshData.push_back( vertices[ v - 1 ].z );
				this->meshData.push_back( normals[ n - 1 ].x );
				this->meshData.push_back( normals[ n - 1 ].y );
				this->meshData.push_back( normals[ n - 1 ].z );
				this->elements.push_back( this->elements.size() );
			}
		}
	}

	this->meshData.shrink_to_fit();
	this->elements.shrink_to_fit();
}