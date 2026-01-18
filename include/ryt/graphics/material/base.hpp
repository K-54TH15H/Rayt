#ifndef BASE_H
#define BASE_H

#include <ryt/graphics/color.hpp>

#include <ryt/math/ray.hpp>

namespace ryt
{
    enum MaterialType
    {
	LAMBERTIAN
    };

    class Material
    {
	private:
	    MaterialType type;

	public:
	    ~Material()
	    {

	    }

	    bool scatter()
	    {

	    }
    };
}
#endif
