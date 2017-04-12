#include "ray.h"
#include "material.h"
#include "light.h"

// Apply the phong model to this point on the surface of the object, returning
// the color of that point.
vec3f Material::shade( Scene *scene, const ray& r, const isect& i ) const
{
	// YOUR CODE HERE

	// For now, this method just returns the diffuse color of the object.
	// This gives a single matte color for every distinct surface in the
	// scene, and that's it.  Simple, but enough to get you started.
	// (It's also inconsistent with the phong model...)

	// Your mission is to fill in this method with the rest of the phong
	// shading model, including the contributions of all the light sources.
    // You will need to call both distanceAttenuation() and shadowAttenuation()
    // somewhere in your code in order to compute shadows and light falloff.
	vec3f result, IA;
	IA = scene->getAmbient();
	IA = vec3f(IA[0] * ka[0], IA[1] * ka[1], IA[2] * ka[2]);
	result = ke + IA;
	vec3f interp = r.at(i.t);
	vec3f sum, dir2;
	vec3f dir1 = -r.getDirection();
	vec3f n = i.N;
	for (list<Light*>::const_iterator j = scene->beginLights(); j != scene->endLights(); j++) {
		dir2 = (*j)->getDirection(interp);
		double theta = n.dot(dir2);
		vec3f rm = (2 * theta * n - dir2).normalize();
		double alpha = rm.dot(dir1);

		
		if (theta < 0) theta = 0;
		if (alpha < 0) alpha = 0;
		vec3f light = kd*theta + ks*pow(alpha, shininess*128);
		vec3f atten = ((*j)->distanceAttenuation(interp))*((*j)->shadowAttenuation(interp + i.N*RAY_EPSILON));
		light = vec3f(light[0] * atten[0], light[1] * atten[1], light[2] * atten[2]);
		light = prod(light, (*j)->getColor(interp));
		
		sum = sum + light;
	}
	result = result + sum;
	
	return result;
}
