#include <ryt/rtcore.hpp>

namespace RYT {
// Context functions
void InitializeRaytracingContext(RaytracingContext *context, size_t capacity) {
  context->hittableCapacity = capacity;
  context->hittableSize = 0;
  
  // Creates an empty bounding box
  context->bBox = AABB();
  context->hittables = new Hittable[capacity];
}

void DestroyRaytracingContext(RaytracingContext *context) {
  delete[] context->hittables;
  context->hittableSize = 0;
  context->hittableCapacity = 0;

  // Destroys AABB by replacing  it with empty bounding box
  context->bBox = AABB(); 
}

Hittable *PushHittable(RaytracingContext *context, Hittable hittable) {
  if (context->hittableSize >= context->hittableCapacity)
    return nullptr;

  context->hittables[context->hittableSize] = hittable;
    
  context->bBox = AABB(context->bBox, hittable.bBox);
  return &(context->hittables[context->hittableSize++]);
}

bool HitWorld(const RaytracingContext *context, const Ray &r, Interval t,
              HitRecord &rec) {
  HitRecord tempRec;
  bool hitAnything = false;
  double closestSoFar = t.max;

  // Loop through all objects of the World
  for (size_t i = 0; i < context->hittableSize; i++) {
    if ((context->hittables[i])
            .Hit(r, Interval(t.min, closestSoFar), tempRec)) {
      hitAnything = true;
      closestSoFar = tempRec.t;
      rec = tempRec;
    }
  }

  return hitAnything;
}
} // namespace RYT
