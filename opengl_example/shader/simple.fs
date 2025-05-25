#version 330 core

uniform vec4 color;
out vec4 fragColor; // 최중 출력 색상

// 픽셀의 색상 변경
void main() {
    fragColor = color;
}
