#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include <ryt/math/vec3.hpp>

namespace ryt
{

    class Hit_Record
    {
	public:
	    vec3 p;
	    vec3 normal;
	    double t;
    };
}

#endif
