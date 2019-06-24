
#ifndef WALL_H
#define WALL_H

//Cube model made out of triangles
//Contains arrays:
//vertices - vertex positions in homogenous coordinates
//normals - vertex normals in homogenous coordinates
//texCoords - texturing coordinates
//colors - vertex colors (rgba)
//Culling GL_CW
//TBN friendly

#include "model.h"

namespace Models {
	namespace WallInternal {
		extern float vertices[];
		extern float normals[];
		extern float texCoords[];
		extern unsigned int vertexCount;
	}

	class Wall: public Model {
		public:
			Wall();
			virtual ~Wall();
			virtual void drawSolid(bool smooth=false);
	};

	extern Wall wall;
}




#endif
