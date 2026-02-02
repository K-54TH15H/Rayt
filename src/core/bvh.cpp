#include <ryt/rtcore.hpp>
#include <algorithm>

namespace RYT
{
    static bool BoxCompare(const Hittable& a, const Hittable& b, int axisIndex)
    {
	Interval aAxisInterval = (a.bBox).AxisInterval(axisIndex);
	Interval bAxisInterval = (b.bBox).AxisInterval(axisIndex);
	return aAxisInterval.min < bAxisInterval.min;
    }
    static bool BoxXCompare(const Hittable& a, const Hittable& b){ return BoxCompare(a, b, 0); }
    static bool BoxYCompare(const Hittable& a, const Hittable& b){ return BoxCompare(a, b, 1); }
    static bool BoxZCompare(const Hittable& a, const Hittable& b){ return BoxCompare(a, b, 2); }

    Hittable* ConstructBVHTree(Hittable* hittables, size_t start, size_t end)
    {
	BVHNode root;

	int axis = RandomInt(0, 2);

	auto comparator = (axis == 0) ? BoxXCompare : (axis == 1) ? BoxYCompare : BoxZCompare;

	size_t span = end - start;

	if(span == 1)
	{
	    return hittables + start;
	}
	if(span == 2)
	{
	    root.left = hittables + start;
	    root.right = hittables + start + 1; 
	}
	else
	{
	    std::sort(hittables + start, hittables + end, comparator);

	    size_t mid = start + (span / 2);
	    root.left = ConstructBVHTree(hittables, start, mid);
	    root.right = ConstructBVHTree(hittables, mid, end); 
	}
	root.bBox = AABB(root.left->bBox, root.right->bBox);
	
	Hittable* bvhRoot = new Hittable(root);
	return bvhRoot;
    }
}
