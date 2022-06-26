#version 330 core

in vec3 fPos;
out vec4 FragColor;

void main() {
    FragColor = vec4(fPos.x + 0.5, 0.5, fPos.y+0.5, 1.0);
}