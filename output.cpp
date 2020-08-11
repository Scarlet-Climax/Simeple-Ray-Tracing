#include <bits/stdc++.h>
using namespace std;

#include "camera.h"
#include "hitable.h"
#include "ray.h"
#include "vec3.h"
// #define DAY

vec3 color(const ray &r, hitable_list world, int depth) {
    hit_record rec;
    if (world.hit(r, 0.001, MAXFLOAT, rec)) {
        ray scattered;
        vec3 attenuation;
        if (depth < 50) {
            if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
                return attenuation * color(scattered, world, depth + 1);
            else
                return attenuation;
        } else
            return vec3(0, 0, 0);
    } else {
#ifdef DAY
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 * (unit_direction.y() + 1);
        return (1.0 - t) * vec3(1, 1, 1) + t * vec3(.5, .7, 1);
#else
        // vec3 unit_direction = unit_vector(r.direction());
        // float t = 0.5 * (unit_direction.y() + 1);
        return vec3(0, 0, 0);
#endif
    }
}

vector<hitable *> random_scene_day() {
    vector<hitable *> world;
    world.push_back(new sphere({0, -1000, 0}, 1000, new lambertian({.5, .5, .5})));
    for (int a = -11; a < 11; a++)
        for (int b = -11; b < 11; b++) {
            float choose = random_float();
            float radius = .1 * random_float() + .1;
            vec3 center(a + .9 * random_float(), radius, b + .9 * random_float());
            if ((center - vec3{4, .2, 0}).length() > .9) {
                if (choose < .8)
                    world.push_back(new sphere(center, radius, new lambertian({random_float() * random_float(), random_float() * random_float(), random_float() * random_float()})));
                else if (choose < .95)
                    world.push_back(new sphere(center, radius, new metal({.5 * (1.0 + random_float()), .5 * (1.0 + random_float()), .5 * (1.0 + random_float())})));
                else
                    world.push_back(new sphere(center, radius, new dielectric(1.5)));
            }
        }
    world.push_back(new sphere({0, 1, 0}, 1, new dielectric(1.5)));
    world.push_back(new sphere({-4, 1, 0}, 1, new lambertian({.4, .2, .1})));
    world.push_back(new sphere({4, 1, 0}, 1, new metal({.7, .6, .5}, 0)));
    return world;
}

vector<hitable *> random_scene_night() {
    vector<hitable *> world;
    world.push_back(new sphere({0, -1000, 0}, 1000, new lambertian({.5, .5, .5})));
    for (int a = -11; a < 11; a++)
        for (int b = -11; b < 11; b++) {
            float choose = random_float();
            float radius = .15 * random_float() + .1;
            vec3 center(a + .9 * random_float(), radius, b + .9 * random_float());
            if ((center - vec3{0, 1, 0}).length() > 1 + radius &&
                (center - vec3{-4, 1, .5}).length() > 1 + radius &&
                (center - vec3{0, 1, -3}).length() > 1 + radius) {
                if (choose < .8)
                    world.push_back(new sphere(center, radius, new light({random_float(), random_float(), random_float()})));
                else if (choose < .9)
                    world.push_back(new sphere(center, radius, new metal({.5 * (1.0 + random_float()), .5 * (1.0 + random_float()), .5 * (1.0 + random_float())})));
                else
                    world.push_back(new sphere(center, radius, new dielectric(1.5)));
            }
        }
    world.push_back(new sphere({0, 1, 0}, 1, new dielectric(1.5)));
    world.push_back(new sphere({-4, 1, .5}, 1, new light({.8, .0, 0})));
    world.push_back(new sphere({0, 1, -3}, 1, new metal({.7, .6, .5}, 0)));
    return world;
}

int main() {
    int nx = 2000;
    int ny = 1000;
    int ns = 100;
    cout << "P3\n"
         << nx << ' ' << ny << "\n255\n";
    // hitable_list world({
    //     new sphere(vec3(0, 0, -1), 0.5, new light({.1, .2, .5})),
    //     new sphere(vec3(0, -100.5, -1), 100, new light({.8, .8, 0})),
    //     new sphere(vec3(1, 0, -1), .5, new metal({.8, .6, .2})),
    //     new sphere(vec3(-1, 0, -1), .5, new dielectric(1.5)),
    //     new sphere(vec3(-1, 0, -1), -.25, new dielectric(1.5)),
    // });
    // float R = cos(M_PI / 4);
    hitable_list world = random_scene_night();
    // hitable_list world({
    //     new sphere(vec3(-R, 0, -1), R, new lambertian({0, 0, 1})),
    //     new sphere(vec3(R, 0, -1), R, new lambertian({1, 0, 0})),
    // });
    vec3 lookfrom(13, 4, 3);
    vec3 lookat(0, 0, 0);
    float dist_to_focus = 10.0;
    float aperture = 0.1;
    camera cam(lookfrom, lookat, vec3(0, 1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus);
    for (int j = ny - 1; j >= 0; j--)
        for (int i = 0; i < nx; i++) {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++) {  //Antialiasing
                float u = float(i + random_float()) / float(nx);
                float v = float(j + random_float()) / float(ny);
                // float b = 0.2;
                ray r = cam.get_ray(u, v);
                // vec3 p = r.point_at_parameter(2);
                col += color(r, world, 0);
            }
            col /= float(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            // vec3 col = color(r);
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            cout << ir << ' ' << ig << ' ' << ib << "\n";
        }
    return 0;
}