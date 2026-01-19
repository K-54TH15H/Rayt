#ifndef BASE_H
#define BASE_H

#include <ryt/graphics/color.hpp>
#include <ryt/graphics/hit_record.hpp>
#include <ryt/math/ray.hpp>


namespace ryt
{
    enum MaterialType
    {
	LAMBERTIAN,
	METAL
    };

    class Lambertian
    {
	private:
	    Color albedo;

	public:
	    Lambertian(const Color& albedo) : albedo(albedo) {}

	    bool Scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const
	    {
		Vec3 scatter_direction = rec.normal + RandomUnitVector();

		if(scatter_direction.NearZero()) scatter_direction = rec.normal;

		scattered = Ray(rec.p, scatter_direction);
		attenuation = albedo;

		return true;
	    }
    };

    class Metal
    {
	private:
	    Color albedo;
	    double fuzz;

	public:
	    Metal(const Color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz) {}

	    bool Scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const 
	    {
		Vec3 reflected = Reflect(r_in.Direction(), rec.normal);
		reflected = (UnitVector(reflected)) + (fuzz * RandomUnitVector());

		scattered = Ray(rec.p, reflected);
		attenuation = albedo;

		return (Dot(scattered.Direction(), rec.normal) > 0);
	    }
    };

    class Material
    {
	private:
	    MaterialType type;

	    union data 
	    {
		Lambertian lambertian;
		Metal metal;

		data() {}
		~data() {}

	    } Data;

	public:

	    Material(const Lambertian lambertian) : type(LAMBERTIAN)
	    {
		Data.lambertian = lambertian;
	    }

	    Material(const Metal metal) : type(METAL)
	    {
		Data.metal = metal;
	    }

	    ~Material()
	    {
		switch(type)
		{
		    case LAMBERTIAN:
			(Data.lambertian).~Lambertian();
			break;
		    
		    case METAL:
			(Data.metal).~Metal();
			break;
		}
	    }

	    bool Scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const 
	    {
		switch(type)
		{
		    case LAMBERTIAN:
			return Data.lambertian.Scatter(r_in, rec, attenuation, scattered);

		    case METAL:
			return Data.metal.Scatter(r_in, rec, attenuation, scattered);

		    default:
			return false;
		}
	    }
    };
}

#endif
