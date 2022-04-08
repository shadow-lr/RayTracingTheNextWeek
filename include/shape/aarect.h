#pragma once

#include "geometry/hittable.h"
#include "rtweekend.h"

class xy_rect : public hittable {
public:
    xy_rect() {}

    xy_rect(double x0_, double x1_, double y0_, double y1_, double k_, shared_ptr<material> mat)
            : x0(x0_), x1(x1_), y0(y0_), y1(y1_), k(k_) {}

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;

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
