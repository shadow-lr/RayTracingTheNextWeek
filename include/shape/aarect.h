#pragma once

#include "geometry/hittable.h"
#include "rtweekend.h"

class xy_rect : public hittable {
public:
    xy_rect() {}

    xy_rect(double x0_, double x1_, double y0_, double y1_, double k_, shared_ptr<material> mat)
            : x0(x0_), x1(x1_), y0(y0_), y1(y1_), k(k_), mp(mat) {}

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override{
        auto t = (k - r.orig.z()) / r.direction().z();

        if (t < t_min || t > t_max)
            return false;

        // hit point
        double hit_x = r.origin().x() + t * r.direction().x();
        double hit_y = r.origin().y() + t * r.direction().y();

        if (hit_x < x0 || hit_x > x1 || hit_y < y0 || hit_y > y1)
            return false;

        rec.u = (hit_x - x0) / (x1 - x0);
        rec.v = (hit_y - y0) / (y1 - y0);
        rec.t = t;
        // todo: may cause some error(z )
        auto outward_normal = vec3(0, 0, 1);
        rec.set_face_normal(r, outward_normal);
        rec.mat_ptr = mp;
        rec.p = r.at(t);
        return true;
    }

    virtual bool bounding_box(double time0, double time1, aabb &output_box) const override {
        // The bounding box must have non-zero width in each dimension, so pad the Z
        // dimension a small amount.

        output_box = aabb(point3(x0, y0, k - 0.0001), point3(x1, y1, k + 0.0001));
        return true;
    }

public:
    shared_ptr<material> mp;
    // z = k
    double x0{}, x1{}, y0{}, y1{}, k{};
};
