#version 330 core
layout (location = 0) in vec3 aPos; // 0번째 attribute가 정점의 위치

out vec4 vertexColor; // fragment shader로 넘어갈 컬러값

void main() {
  gl_Position = vec4(aPos, 1.0); // vec3를 vec4 생성자에 사용
  vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // 어두운 빨간색을 출력값으로
}