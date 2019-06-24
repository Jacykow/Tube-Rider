
#include "wall.h"

namespace Models {

	Wall wall;

	Wall::Wall() {
		vertices=WallInternal::vertices;
		normals=WallInternal::normals;
		texCoords=WallInternal::texCoords;
		vertexCount=WallInternal::vertexCount;
	}

	Wall::~Wall() {
	}

	void Wall::drawSolid(bool smooth) {

		glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);


        glVertexAttribPointer(0,4,GL_FLOAT,false,0,vertices);
        glVertexAttribPointer(1,4,GL_FLOAT,false,0,normals);
        glVertexAttribPointer(2,2,GL_FLOAT,false,0,texCoords);

        glDrawArrays(GL_TRIANGLES,0,vertexCount);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);
	}

	namespace WallInternal {
			unsigned int vertexCount=6;

			float vertices[]={
				1.0f,0.0f,-1.0f,1.0f,
				-1.0f, 0.0f,1.0f,1.0f,
				-1.0f,0.0f,-1.0f,1.0f,

				1.0f,0.0f,-1.0f,1.0f,
				1.0f, 0.0f,1.0f,1.0f,
				-1.0f, 0.0f,1.0f,1.0f
			};

			float normals[]={
				-0.7071f, 0.7071f, 0.0f, 0.0f,
				0.7071f, 0.7071f, 0.0f, 0.0f,
				0.7071f, 0.7071f, 0.0f, 0.0f,

				-0.7071f, 0.7071f, 0.0f, 0.0f,
				-0.7071f, 0.7071f, 0.0f, 0.0f,
				0.7071f, 0.7071f, 0.0f, 0.0f
			};

			float texCoords[]={
				1.0f,0.0f, 0.0f,1.0f, 0.0f,0.0f,
				1.0f,0.0f, 1.0f,1.0f, 0.0f,1.0f
			};
	}
}

