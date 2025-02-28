#version 330
// The inputs will be fed by the vertex buffer objects
layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 TexCoord;
layout(location = 2) in vec3 Normal;

// Matrices as program attributes
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

// This will be passed to the fragment shader
out vec2 texCoord;

// Normal to pass to the fragment shader
out vec4 normal;
out vec3 localNormal;
out vec4 worldPosition;


void main() {
  // Copy the input to the fragment shader
  texCoord = TexCoord;

  // Normal in world coordinates
  normal = normalize(ModelMatrix * vec4(Normal, 0.0f));
  localNormal = Normal;

  // Calculate the final position on screen
  worldPosition = ModelMatrix * vec4(Position, 1.0);
  gl_Position = ProjectionMatrix * ViewMatrix * worldPosition;
}
