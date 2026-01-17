#include <cstdlib>

namespace ryt
{
    inline double random_double()
    {
	// returns radom in [0, 1)
	return std::rand() / (RAND_MAX + 1.0);
    }

    inline double random_double(double min, double max)
    {
	// returns random in [min, max)
	return min + ((max - min) * random_double());
    }
}
