#include "SmallFish.h"
#include <cmath>
#include <glm/gtc/random.hpp>
#include <ppgso/ppgso.h>
#include <shaders/underwater_vert_glsl.h>
#include <shaders/underwater_frag_glsl.h>

// shared resources
std::unique_ptr<ppgso::Mesh> SmallFish::mesh;
std::unique_ptr<ppgso::Texture> SmallFish::texture;
std::unique_ptr<ppgso::Shader> SmallFish::shader;



SmallFish::SmallFish(float x, float y, float z, float movement_phase) {
    offset = glm::vec3(x, y, z);
    phase = movement_phase;

    if (!shader) shader = std::make_unique<ppgso::Shader>(underwater_vert_glsl, underwater_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("smallFish\\smallFish_texture.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("smallFish\\smallFish_body.obj");

    tail = std::make_unique<FishTail>();
}



bool SmallFish::update(Scene &scene, float time) {
    position = offset;
    rotation.x = glm::radians(90.0f);
    rotation.y = (abs(std::fmod(time + phase, 2.0f) - 1.0f)*2 - 1.0f) * glm::radians(10.0f);
    position.x = offset.x + std::sin(time + phase);


    generateModelMatrix();
    tail->update(scene, time + phase);
    tail->modelMatrix = modelMatrix * tail->modelMatrix;
    return true;
}


void SmallFish::render(Scene &scene) {
    shader->use();
    shader->setUniform("LightDirection", scene.lightDirection);

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    shader->setUniform("Transparency", 1);
    shader->setUniform("HasNormals", 1.0f);
    //shader->setUniform("Time", (float) glfwGetTime());

    mesh->render();

    tail->render(scene);

}


