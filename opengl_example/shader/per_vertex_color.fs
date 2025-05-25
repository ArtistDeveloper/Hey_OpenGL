#version 330 core
in vec4 vertexColor;
out vec4 fragColor;

void main() {
    fragColor = vertexColor; // 색깔을 최종적으로 프레임 버퍼에 넣음
}