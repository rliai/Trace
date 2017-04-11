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
	vec3f transparency = vec3f(1, 1, 1) - kt;
	IA = scene->getAmbient();
	IA = vec3f(IA[0] * ka[0]*transparency[0], IA[1] * ka[1]*transparency[1], IA[2] * ka[2]*transparency[2]);
	result = ke + IA;
	vec3f interp = r.at(i.t);
	vec3f sum, dir2;
	vec3f dir1 = -r.getDirection().normalize();
	vec3f n = i.N.normalize();
	for (list<Light*>::const_iterator j = scene->beginLights(); j != scene->endLights(); j++) {
		dir2 = (*j)->getDirection(interp).normalize();
		double theta = n.dot(dir2);
	
		double alpha = theta - n.dot(dir1);
		if (theta < 0) theta = 0;
		if (alpha < 0) alpha = 0;
		vec3f light = kd*theta + ks*pow(alpha, shininess*128.0);
		vec3f atten = ((*j)->distanceAttenuation(interp))*((*j)->shadowAttenuation(interp));
		light = vec3f(light[0] * atten[0], light[1] * atten[1], light[2] * atten[2]);
		sum = sum + light;
	}
	result = result + sum;
	return result;
}
