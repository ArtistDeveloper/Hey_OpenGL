#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 transform; // 값이 아무것도 전달되지 않으면, 값이 (0, 0, 0, 0)으로 초기화

out vec4 vertexColor;
out vec2 texCoord;

void main() {
    gl_Position = transform * vec4(aPos, 1.0);
    vertexColor = vec4(aColor, 1.0);
    texCoord = aTexCoord;
}