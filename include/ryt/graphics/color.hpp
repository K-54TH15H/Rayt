#ifndef COLOR_H
#define COLOR_H

#include <ryt/math/vec3.hpp>
#include <ryt/math/interval.hpp>

#include <iostream>


namespace ryt
{
    using color = vec3; // alias for rt::vec3 as color as an context - might need to modify
    
    inline void write_color(std::ostream& os, const color& pixel_color)
    {
	auto r = pixel_color.x;
	auto g = pixel_color.y;
	auto b = pixel_color.z;
	
	static const Interval intensity(0.000, 0.999);

	int rb = int(256 * intensity.clamp(r));
	int gb = int(256 * intensity.clamp(g));
	int bb = int(256 * intensity.clamp(b));

	os << rb << ' ' << gb << ' ' << bb << std::endl;
    }
}

#endif
