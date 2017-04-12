#include <cmath>

#include "light.h"

double DirectionalLight::distanceAttenuation( const vec3f& P ) const
{
	// distance to light is infinite, so f(di) goes to 0.  Return 1.
	return 1.0;
}


vec3f DirectionalLight::shadowAttenuation( const vec3f& P ) const
{
	isect i;
	vec3f dir = getDirection(P);	
	vec3f curPoint = P;	
	vec3f c = getColor(P);
	ray r = ray(curPoint, dir);
	if (scene->intersect(r, i))
	{
		
		if (i.getMaterial().kt.iszero()) return vec3f(0, 0, 0);
		curPoint = r.at(i.t);
		r = ray(curPoint, dir);
		c = prod(c, i.getMaterial().kt);
	}
	return c;
}

vec3f DirectionalLight::getColor( const vec3f& P ) const
{
	// Color doesn't depend on P 
	return color;
}

vec3f DirectionalLight::getDirection( const vec3f& P ) const
{
	return -orientation;
}

double PointLight::distanceAttenuation( const vec3f& P ) const
{
	double d = (P - position).length();
	
	double result = 1/ (m_const_coeff + m_linear_coeff * d + m_quadratic_coeff * d * d);
	if (result < 1) return result;
	return 1.0;
}

vec3f PointLight::getColor( const vec3f& P ) const
{
	// Color doesn't depend on P 
	return color;
}

vec3f PointLight::getDirection( const vec3f& P ) const
{
	return (position - P).normalize();
}


vec3f PointLight::shadowAttenuation(const vec3f& P) const
{
	isect i;
	vec3f dir = getDirection(P);
	vec3f curPoint = P;
	vec3f c = getColor(P);
	ray r = ray(curPoint, dir);
	while (scene->intersect(r, i))
	{

		if (i.getMaterial().kt.iszero()) return vec3f(0, 0, 0);
		curPoint = r.at(i.t);
		r = ray(curPoint, dir);
		c = prod(c, i.getMaterial().kt);
	}
	return c;
}


void PointLight::setDistanceAttenuation(const double constant,
	const double linear, const double quadratic)
{
	m_const_coeff = constant;
	m_linear_coeff = linear;
	m_quadratic_coeff = quadratic;
}




