#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include <ryt/math/vec3.hpp>
#include <ryt/math/ray.hpp>

namespace ryt
{
    class Material; // Forward Declaration

    class HitRecord
    {
	public:
	    Vec3 p;
	    Vec3 normal;
	    Material* mat; // This Doesn't Own the Material just points to it.
	    double t;
	    bool front_face;

	    void SetFaceNormal(const Ray& r, const Vec3& outward_normal)
	    {
		front_face = Dot(r.Direction(), outward_normal) < 0;

		normal = (front_face) ? outward_normal : -outward_normal;
	    }
    };
}

#endif
