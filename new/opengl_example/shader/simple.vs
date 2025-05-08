#version 330 core
layout (location = 0) in vec3 aPos;

// 모든 정점마다 개별적으로 실행될 함수
void main() {
  gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
}