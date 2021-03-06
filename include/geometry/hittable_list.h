#pragma once

#include "hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

/* hitable_list是所有能够被光线撞击的物体的列表集合*/
class hittable_list : public hittable {
public:
    hittable_list() {}

    hittable_list(shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }

    void add(shared_ptr<hittable> object) { objects.push_back(object); }

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;

    virtual bool bounding_box(double time0, double time1, aabb &output_box) const override;

public:
    std::vector<shared_ptr<hittable>> objects;
};
