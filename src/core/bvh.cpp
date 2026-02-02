#include <ryt/rtcore.hpp>
#include <algorithm>

namespace RYT
{
    BVHNode ConstructBVHTree(Hittable* hittables, size_t start, size_t end)
    {
	BVHNode root;

	int axis = RandomInt(0, 2);
	
	auto comparator = (axis == 0) ? BoxXCompare : (axis == 1) ? BoxYCompare : BoxZCompare;

	size_t span = end - start;

	if(span == 1)
	{
	    root.left = hittables + start; 
	    root.right = hittables + start;
	}
	else if(span == 2)
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
	return root;
    }
}
