#pragma once

#include "texture.h"
#include "sample/perlin.h"

class noise_texture : public texture {
public:
    noise_texture() = default;
    noise_texture(double sc) : scale(sc) {}

    virtual color value(double u, double v, const point3 &p) const override {
//        return color(1, 1, 1) * noise.noise(p);
        return color(1, 1, 1) * noise.turb(scale * p);
    }

public:
    perlin noise;
    double scale = 1.0;
};