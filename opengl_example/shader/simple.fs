#version 330 core

in vec4 vertexColor; // vs로부터 입력된 변수 (같은 변수명, 같은 타입)
out vec4 FragColor; // 최중 출력 색상

// 픽셀의 색상 변경
void main() {
    FragColor = vertexColor;
}
