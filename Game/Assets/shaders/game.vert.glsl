#version 330 core

in vec3 pos;
out vec3 fPos;


uniform mat4 viewProjection;

void main() {
    fPos = pos;
    gl_Position = viewProjection * vec4(pos, 1.0);
    
}