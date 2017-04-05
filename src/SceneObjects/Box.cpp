#include <cmath>
#include <assert.h>

#include "Box.h"

bool Box::intersectLocal( const ray& r, isect& i ) const
{
	// YOUR CODE HERE:
    // Add box intersection code here.
	// it currently ignores all boxes and just returns false.
	vec3f dir = r.getDirection();
	vec3f pos = r.getPosition();

	double tfar = DBL_MAX, tnear = -tfar;
	i.obj = this;

	for (int i = 0; i < 3; i++) {
		if (abs(dir[i]) < RAY_EPSILON) {
			if (pos[i] > 0.5 || pos[i] < -0.5) return false;
		}
		else {
			double t1, t2;
			t1 = (-0.5 - pos[i]) / dir[i];
			t2 = (0.5 - pos[i]) / dir[i];
			if (t1 > t2) swap(t1, t2);
			if (t1 > tnear) { 
				tnear = t1; 
			}
			if (t2 < tfar) { 
				tfar = t2; 
			}
			if (tnear > tfar || tfar < RAY_EPSILON) return false;

		}
	}
	return true;


}
