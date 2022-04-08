#include "shape/aarect.h"

bool xy_rect::hit(const ray &r, double t_min, double t_max, hit_record &rec) const {
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
    auto outward_normal = vec(0, 0, 1);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mp;
    rec.p = r.at(t);
    return true;
}