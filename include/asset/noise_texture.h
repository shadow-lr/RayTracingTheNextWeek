#pragma once

#include "texture.h"
#include "sample/perlin.h"

class noise_texture : public texture {
public:
    noise_texture() = default;

    virtual color value(double u, double v, const point3 &p) const override {
        return color(1, 1, 1) * noise.noise(p);
    }

public:
    perlin noise;
};