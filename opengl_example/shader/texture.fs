#version 330 core
in vec4 vertexColor;
in vec2 texCoord;
out vec4 fragColor;

uniform sampler2D tex; // 어떤 텍스처를 셰이더안에서 사용하고 싶다면 sampler2D로 선언
uniform sampler2D tex2;

void main() {
    // texture 함수를 사용하여 텍셀의 값을 꺼내옴
    // fragColor = texture(tex, texCoord) + texture(tex2, texCoord); // 더하는 방식의 블렌딩 되겠지.
    fragColor = texture(tex, texCoord) * 0.8 + texture(tex2, texCoord) * 0.2; // 비율 값을 통한 블렌딩
}