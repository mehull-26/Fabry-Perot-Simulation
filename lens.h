#pragma once

#include "simulation.h"
#include "ray.h"

double intersect(ray& r, double R, vec3 center)
{
	vec3 oc = center - r.origin();
	auto a = r.direction().length_squared();
	auto h = dot(r.direction(), oc);
	auto c = oc.length_squared() - R * R;

	auto discriminant = h * h - a * c;
	if (discriminant < 0)
	{
		if (DEV)
		{
			std::cout << "\n---DEV: No intersectiong of ray (" << r.origin() << ") with direction vector (" << r.direction() << ") with lens sphere.---\n\n";
			return 0;
		}
	}
	auto sqrtd = std::sqrt(discriminant);

	// Choose the root according to the ROC.
	double root;
	if (R > 0)
		root = (h - sqrtd) / a;
	else
		root = (h + sqrtd) / a;

	return root;
}

ray snellsLaw(const ray& I, const double mu, vec3 N, const double t)
{
	// ensure normal always pointing out
	if (dot(N, I.direction()) > 0)
	{
		N = -1 * N;
	}

	// ensure acute angle
	N = unit_vector(N);
	double cosi = -dot(N, I.direction());

	// mu = n1/n2
	// handling TIR
	double TIR = mu * mu * (1 - cosi * cosi);
	if (TIR > 1)
	{
		if (DEV)
			std::cout << "\n---DEV: TIR of ray starting at (" << I.origin() << ") with direction vector (" << I.direction() << ")---\n\n";
		return ray(I.origin() + t * I.direction(), vec3(I.direction().x(), -1 * I.direction().y(), 0));
	}

	double cost = std::sqrt(1 - mu * mu * (1 - cosi * cosi));
	vec3 dirT = mu * I.direction() + (mu * cosi - cost) * N;
	ray T = ray(I.origin() + t * I.direction(), dirT);

	return T;
}


// Note: follow sign conventions used in Optics while filling up every data
class lens 
{
private:
	float R1, R2;
	vec3 center;
	double aperature;
	double thickness;
	double RI;
	double path_length;

public:
	lens(float R1, float R2, double thickness, double RI) : R1(R1), R2(R2), thickness(thickness), RI(RI), center(vec3()), aperature(INT_MAX), path_length(0) {}
	
	void set_center(vec3 ctr) { center  = ctr; }
	void set_aperature(double aptr) { aperature = aptr; }

	float r1() { return R1; }
	float r2() { return R2; }
	vec3 lensCenter() { return center; }
	double lensAperature() { return aperature; }
	double lensThickness() { return thickness; }
	double mu() { return RI; }
	double pathLength() { return path_length; }

	ray refract(ray& I, double n1)
	{
		vec3 C1, C2;
		if ( R1 > 0 )
			C1 = vec3(center.x() + (R1 - thickness/2), center.y(), center.z());
		else
			C1 = vec3(center.x() + (R1 + thickness / 2), center.y(), center.z());

		double intersection1_t = intersect(I, R1, C1);
		// no need to fix the direction of normal here, snellsLaw function manages that
		vec3 normal1 = I.origin() + I.direction() * intersection1_t - C1;
		ray r1 = snellsLaw(I, n1 / RI, normal1, intersection1_t);

		if (R2 > 0)
			C2 = vec3(center.x() + (R2 - thickness / 2), center.y(), center.z());
		else
			C2 = vec3(center.x() + (R2 + thickness / 2), center.y(), center.z());
		double intersection2_t = intersect(r1, R2, C2);
		vec3 normal2 = r1.origin() + r1.direction() * intersection2_t - C2;
		ray r2 = snellsLaw(r1, RI/n1, normal2, intersection2_t);

		// path length travelled inside lens
		path_length = ((r1.origin() + r1.direction() * intersection2_t) - (I.origin() + I.direction() * intersection1_t)).length();

		// return final refracted ray
		return r2;
	}
};

