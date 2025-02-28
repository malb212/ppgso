//
// Created by Hoxtilicious on 05.12.2021.
//


#include <glm/gtc/random.hpp>
#include "dolphin.h"
#include <windows.h>

#include <shaders/underwater_vert_glsl.h>
#include <shaders/underwater_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Dolphin::mesh;
std::unique_ptr<ppgso::Texture> Dolphin::texture;
std::unique_ptr<ppgso::Shader> Dolphin::shader;
float base = 2.0f;
//float x = 0.0f;


Dolphin::Dolphin() {
    // Set random scale speed and rotation
    //scale *= glm::linearRand(.1f, .3f);
    //speed = {glm::linearRand(-2.0f, 2.0f), glm::linearRand(-5.0f, -10.0f), 0.0f};
    rotation = {0, 0, 0};
    rotMomentum = {0, 0, 0};

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(underwater_vert_glsl, underwater_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("dolphin\\10014_dolphin_v1_Diffuse.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("dolphin\\10014_dolphin_v2_max2011_it2.obj");
}

bool Dolphin::update(Scene &scene, float dt) {
    // Count time alive
    //age += dt;

    // Animate position according to time
    position += speed * dt;
    rotation += rotMomentum * dt;
    jump(scene);
    // Delete when alive longer than 10s or out of visibility
    //if (age > 10.0f || position.y < -10) return false;

    // Collide with scene
    //for (auto &obj : scene.objects) {
    // Ignore self in scene
    //if (obj.get() == this) continue;

    // We only need to collide with asteroids and projectiles, ignore other objects
    //auto asteroid = dynamic_cast<Island*>(obj.get()); // dynamic_pointer_cast<Island>(obj);
    //auto projectile = dynamic_cast<Projectile*>(obj.get()); //dynamic_pointer_cast<Projectile>(obj);
    //if (!asteroid && !projectile) continue;

    // When colliding with other asteroids make sure the object is older than .5s
    // This prevents excessive collisions when asteroids explode.
    //if (asteroid && age < 0.5f) continue;

    // Compare distance to approximate size of the asteroid estimated from scale.
    //if (distance(position, obj->position) < (obj->scale.y + scale.y) * 0.7f) {
    //  int pieces = 3;
//
    //  // Too small to split into pieces
    //  if (scale.y < 0.5) pieces = 0;
//
    //  // The projectile will be destroyed
    //  if (projectile) projectile->destroy();
//
    //  // Generate smaller asteroids
    //  explode(scene, (obj->position + position) / 2.0f, (obj->scale + scale) / 2.0f, pieces);
//
    // Destroy self
    //return false;
    //}
    //}

    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return true;
}

void Dolphin::jump(Scene &scene){
    clock_t t;
    t = clock();
    //float s = glm::linearRand(7.0f, 20.0f);
    float step = 0.02f;
    //Motion

    position.x = r * sin(t/1000.0f);
    position.y = 5* sin(t/300.0f);
    position.z = r * cos(t/1000.0f);

  //  double r = position.x*position.x + position.z*position.z;
  //  std::cout << r <<std::endl;
    //base fluctuating between 2.0f and 4.0f
    if ((position.y >= 0) && (base <= 4.0f)) {
        rotation.x = -M_PI / base;
        base += step;
    }
    else if ((position.y < 0) && (base >= 2.0f)){
        rotation.x = -M_PI / base;
        base-=step;
    }
  //  rotation.y = -cos(t/1000.0f)*2.87f;

    rotation.z = M_PI_2 + t/1000.0f;
    //x += step2;
    //rotation.z += cos(t/1000.0f) / 60.0f;
    std::cout << t << std::endl;
}

void Dolphin::render(Scene &scene) {
    shader->use();
    shader->setUniform("LightDirection", scene.lightDirection);

    //glm::vec3 ambientLight(1, 0.5, 0.5);
    //shader->setUniform("AmbientLight", ambientLight);
    //float light_ambient[] = {1.0f, 1.0f, 1.0f, 1.0f };
    //float mat_ambient[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    //glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    //glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);

    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    shader->setUniform("Transparency", 1);
    mesh->render();
}

void Dolphin::onClick(Scene &scene) {
    std::cout << "Dolphin clicked!" << std::endl;
    age = 10000;
}

