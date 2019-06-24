#ifndef DRONE_H
#define DRONE_H

#include "model.h"

namespace Models {
	namespace DroneInternal {
		extern float vertices[];
		//extern float normals[];
		extern float vertexNormals[];
		extern float texCoords[];
		//extern float colors[];
		extern unsigned int vertexCount;
	}

	class Drone: public Model {
		public:
			Drone();
			virtual ~Drone();
			virtual void drawSolid(bool smooth=true);
	};

	extern Drone drone;

}

#endif
