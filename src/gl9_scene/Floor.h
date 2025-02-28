#pragma once
#include <memory>

#include <ppgso/ppgso.h>

#include "scene.h"
#include "object.h"


class Floor final {
private:
    // Static resources (Shared between instances)
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> texCoords;
    std::vector<GLuint> mesh;

    GLuint vao{}, vbo{}, tbo{}, ibo{};
    glm::mat4 modelMatrix{1.0f};

public:
    glm::vec3 position{0, 0, 0};
    glm::vec3 rotation{0, 0, 0};
    glm::vec3 scale{1, 1, 1};

    Floor();

    ~Floor();

    static float getDisplacement(float x, float z);

    bool update(Scene &scene, float time);

    bool render(Scene &scene);

};