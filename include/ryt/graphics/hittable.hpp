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
			(data.sphere).~Sphere(); // Calling Destructor Call Explicitly
		}
	    }

	public:
	    GeometryType type;

	    union
	    {
		Sphere sphere;

	    } data;
	    
	    ~Hittable()
	    {
		destroy();
	    }

    };
}

#endif
