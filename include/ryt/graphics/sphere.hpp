#ifndef SPHERE_H
#define SPHERE_H

#include <ryt/math/interval.hpp>
#include <ryt/math/ray.hpp>
#include <ryt/math/vec3.hpp>

#include <ryt/graphics/hit_record.hpp>
#include <ryt/graphics/material.hpp>

namespace ryt
{
    class Sphere
    {
	private:
	    Vec3 center;
	    double radius;
	    Material mat;

	public:
	    Sphere(const Vec3& center, double radius, Material mat) : center(center), radius(std::fmax(0, radius)), mat(mat)
	    {}

	    bool Hit(const Ray& r, Interval t, HitRecord& rec)
	    {
		Vec3 CQ = center - r.Origin();
		auto a = r.Direction().LengthSquared();
		auto h = Dot(r.Direction(), CQ);
		auto c = CQ.LengthSquared() - radius * radius;

		auto discriminant = h*h - a*c;

		if(discriminant < 0) return false;
		
		auto sqrtd = std::sqrt(discriminant);
		
		// Get the nearest root that is in acceptable range
		auto root = (h - sqrtd) / a;

		if(!t.Surrounds(root))
		{
		    root = (h + sqrtd) / a;

		    if(!t.Surrounds(root)) return false;
		}

		// record hit then return true
		rec.t = root;
		rec.p = r.At(rec.t);

		Vec3 outward_normal = (rec.p - center) / radius;
		rec.SetFaceNormal(r, outward_normal);
		rec.mat = &mat;

		return true;
	    }

    };
}

#endif
