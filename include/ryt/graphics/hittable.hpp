#ifndef HITTABLE_H
#define HITTABLE_H

#include <ryt/math/ray.hpp>
#include <ryt/graphics/sphere.hpp>

namespace ryt
{
    // Tag for Geometry type
    enum GeometryType
    {
	SPHERE
    };

    class Hittable
    {
	private:

	    void destroy()
	    {
		switch(type)
		{
		    case SPHERE:
			(Data.sphere).~Sphere(); // Calling Destructor Call Explicitly
		}
	    }

	    bool hit_data(const ray& r, double ray_tmin, double ray_tmax, Hit_Record& rec)
	    {
		switch(type)
		{
		    case SPHERE:
			return (Data.sphere).hit(r, ray_tmin, ray_tmax, rec);
		}
	    }

	public:
	    GeometryType type;

	    union data
	    {
		Sphere sphere;
	
		// default constructors get destroyed placeholder constructors and destrcutors
		// manually handled via class constructors and destrcutors
		data() {}
		~data() {}

	    } Data;
	    
	    ~Hittable()
	    {
		destroy();
	    }
	    
	    bool hit(const ray& r, double ray_tmin, double ray_tmax, Hit_Record& rec)
	    {
		return hit_data(r, ray_tmin, ray_tmax, rec);
	    }
    };
}

#endif
