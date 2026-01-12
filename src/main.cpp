#include <iostream>

int main()
{
    int img_w = 256;
    int img_h = 256;

    // The Below block of code renders the image
    std::cout << "P3" << std::endl << img_w << ' ' << img_h << std::endl << 255 << std::endl;

    for(int i = 0; i < img_h; i++)
    {
	std::clog << '\r';
	std::clog << std::string(25, ' ') << '\r';
	std::clog << "Progress : " << ((((double)i)/(img_h-1)) * 100) << '%';

	for(int j = 0; j < img_w; j++)
	{
	    auto r = double(i) / (img_w - 1);
	    auto g = double(j) / (img_h - 1);
	    auto b  = 0.0;

	    int ir = int(255.999 * r);
	    int ig = int(255.999 * g);
	    int ib = int(255.999 * b);

	    std::cout << ir << ' ' << ig << ' ' << ib << std::endl;
	}
    }

    std::clog << std::endl << "Render Complete" << std::endl;

    return 0;
}
