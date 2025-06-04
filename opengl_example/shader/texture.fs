#version 330 core
in vec4 vertexColor;
in vec2 texCoord;
out vec4 fragColor;

uniform sampler2D tex; // 어떤 텍스처를 셰이더안에서 사용하고 싶다면 sampler2D로 선언

void main() {
    fragColor = texture(tex, texCoord); // texture함수를 사용하여 텍셀의 값을 꺼내옴
}