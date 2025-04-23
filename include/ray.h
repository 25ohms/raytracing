#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
  private:
    point3 o;
    vec3 d;
  public:
    ray() {}
    ray(const point3 &origin, const vec3 &direction) : o{origin}, d{direction} {}
    const point3 &origin() const { return this->o; }
    const vec3 &direction() const { return this->d; }

    point3 at(double t) const {
      return o + (t * d);
    }
};

#endif

