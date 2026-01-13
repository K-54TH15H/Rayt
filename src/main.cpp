#include <iostream>

#include <rayt/graphics/color.hpp>
#include <rayt/math/vec3.hpp>

int main()
{
    int img_w = 256;
    int img_h = 256;

    // The Below block of code renders the image
    std::cout << "P3" << std::endl << img_w << ' ' << img_h << std::endl << 255 << std::endl;

    for(int i = 0; i < img_h; i++)
    {
	// clear up line
	std::clog << '\r' << std::string(25, ' ') << '\r';
	// write progress
	std::clog << "Progress : " << ((((double)i)/(img_h-1)) * 100) << '%';

	for(int j = 0; j < img_w; j++)
	{
	    auto pixel_color = ryt::color(double(j)/(img_w-1), double(i)/(img_h-1), 0);
	    write_color(std::cout, pixel_color);
	}
    }

    std::clog << std::endl << "Render Complete" << std::endl;

    return 0;
}
