#include <ryt/rtcore.hpp>

namespace RYT {
Hittable::Hittable() { type = NONE; }

Hittable::Hittable(Sphere s) {
  type = SPHERE;
  data.sphere = s;
  bBox = s.boundingBox();
}

Hittable::Hittable(BVHNode bvh)
{
    type = BVH_NODE;
    data.bvh = bvh;
    bBox = bvh.bBox;
}

Hittable::~Hittable() {
  switch (type) {
  case SPHERE:
    ((data.sphere)).~Sphere(); // Calling Destructor Call Explicitly
    break;

  default: // None
    break;
  }
}

bool Hittable::Hit(const Ray &r, Interval t, HitRecord &rec) {
  if(!bBox.Hit(r, t)) return false;

  switch (type) {
      case SPHERE:
	  return ((data.sphere)).Hit(r, t, rec);

      case BVH_NODE: {
			 bool hitLeft = data.bvh.left->Hit(r, t, rec);

			 // If hitLeft care only about right-hits closer than left hit
			 Interval rightInterval = hitLeft ? Interval(t.min, rec.t) : t;
			 bool hitRight = data.bvh.right->Hit(r, rightInterval, rec);

			 return hitLeft || hitRight;
		     }
      default: // Hit None
		     return false;
  }
}

} // namespace RYT
