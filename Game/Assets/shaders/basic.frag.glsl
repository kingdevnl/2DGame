#version 330 core

in vec3 fPos;
in vec3 fColor;
in vec2 fTexCoord;
in float fTexID;

out vec4 FragColor;
uniform sampler2D samplers[16];

void main() {
    int index = int(fTexID);
    
    
//    FragColor = texture(samplers[index], fTexCoord);
    
    FragColor = vec4(fColor, 1.0) + texture(samplers[index], fTexCoord);
    
}