#include "sample/perlin.h"

perlin::perlin() {
    ranfloat = new double[point_count];
    for (int i = 0; i < point_count; ++i)
        ranfloat[i] = random_double();

    perm_x = perlin_generate_perm();
    perm_y = perlin_generate_perm();
    perm_z = perlin_generate_perm();
}

double perlin::noise(const point3 &p) const {

    auto u = p.x() - std::floor(p.x());
    auto v = p.y() - std::floor(p.y());
    auto w = p.z() - std::floor(p.z());

    // SovMach bands
    // Hermite cubic to round off the interpolation
    u = u * u * (3 - 2 * u);
    v = v * v * (3 - 2 * v);
    w = w * w * (3 - 2 * w);

    auto i = static_cast<int>(std::floor(p.x()));
    auto j = static_cast<int>(std::floor(p.y()));
    auto k = static_cast<int>(std::floor(p.z()));

    double c[2][2][2];

    for (int di = 0; di < 2; ++di) {
        for (int dj = 0; dj < 2; ++dj) {
            for (int dk = 0; dk < 2; ++dk) {
                c[di][dj][dk] = ranfloat[perm_x[(i + di) & 255] ^
                                         perm_y[(j + dj) & 255] ^
                                         perm_z[(k + dk) & 255]];
            }
        }
    }

    return trilinear_interp(c, u, v, w);
}

double perlin::turb(const point3& p, int depth/* = 7*/) const {
    auto accum = 0.0;
    auto temp_p = p;
    auto weight = 1.0;

    for (int i = 0; i < depth; i++) {
        accum += weight*noise(temp_p);
        weight *= 0.5;
        temp_p *= 2;
    }

    return std::fabs(accum);
}

perlin::~perlin() {
    delete[] ranfloat;
    delete[] perm_x;
    delete[] perm_y;
    delete[] perm_z;
}


int *perlin::perlin_generate_perm() {
    auto p = new int[point_count];

    for (int i = 0; i < perlin::point_count; ++i)
        p[i] = i;

    permute(p, point_count);

    return p;
}

// Perlin with trilienear interpolation
double perlin::trilinear_interp(double c[2][2][2], double u, double v, double w) {
    auto accum = 0.0;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 2; ++k)
                accum += (i * u + (1 - i) * (1 - u)) *
                         (j * v + (1 - j) * (1 - v)) *
                         (k * w + (1 - k) * (1 - w)) *
                         c[i][j][k];
    return accum;
}

// 洗牌算法
void perlin::permute(int *p, int n) {
    for (int i = n - 1; i > 0; --i) {
        int target = random_int(0, i);
        std::swap(p[i], p[target]);
    }
}