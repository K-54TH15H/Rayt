
// math
#include <ryt/math/vec3.hpp>
#include <ryt/math/ray.hpp>

// graphics
#include <ryt/graphics/color.hpp>
#include <ryt/graphics/hittable.hpp>
#include <ryt/graphics/hit_record.hpp>
#include <ryt/graphics/sphere.hpp>
#include <ryt/graphics/rtcontext.hpp>
#include <ryt/graphics/material.hpp>

// utils
#include <ryt/utils/camera.hpp>

int main()
{
    ryt::RaytracingContext world;
    ryt::InitializeRaytracingContext(&world, 16);
    
    ryt::Lambertian material_ground(ryt::Color(0.8, 0.8, 0.0));
    ryt::Lambertian material_center(ryt::Color(0.7, 0.1, 0.2));
    ryt::Metal metal_left(ryt::Color(0.8, 0.8, 0.8), 0.0);
    ryt::Metal metal_right(ryt::Color(0.8, 0.6, 0.2), 1.0);

    
    ryt::PushHittable(&world, ryt::Sphere(ryt::Vec3(0, 0, -1.2), 0.5, material_center));
    ryt::PushHittable(&world, ryt::Sphere(ryt::Vec3(0, -100.5, -1), 100, material_ground));
    ryt::PushHittable(&world, ryt::Sphere(ryt::Vec3(-1, 0, -1), 0.5, metal_left));
    ryt::PushHittable(&world, ryt::Sphere(ryt::Vec3(1, 0, -1.0), 0.5, metal_right));

    ryt::Camera cam;

    cam.Render(&world);

    ryt::DestroyRaytracingContext(&world);

    return 0;
}
