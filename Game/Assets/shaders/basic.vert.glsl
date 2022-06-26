#version 330 core

in vec3 pos;
in vec3 color;
in vec2 texCoord;
in float texID;
out vec3 fPos;
out vec3 fColor;
out vec2 fTexCoord;
out float fTexID;

uniform mat4 viewProjection;

void main() {
    fPos = pos;
    fColor = color;
    fTexCoord = texCoord;
    fTexID = texID;
    gl_Position = viewProjection * vec4(pos, 1.0);

}