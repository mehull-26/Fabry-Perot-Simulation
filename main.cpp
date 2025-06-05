#include "simulation.h"
#include "lens.h"

int main()
{
	vec3 normal = vec3(0, 1, 0);
	ray i = ray(vec3(-50, 1, 0), vec3(1, 0, 0));

	lens l1(10.0f, -10.0f, 0.5, 1.5);
	ray r = l1.refract(i, 1);

	std::cout << r.origin() << "\n" << r.direction();

	double focal_t = -1 * r.origin().y() / r.direction().y();
	vec3 focalPoint = r.origin() + focal_t * r.direction();
	
	std::cout << "\n\n" << focal_t;
	std::cout << "\n\nfocal Point: (" << focalPoint << ")\n\n";
	return 0;
}