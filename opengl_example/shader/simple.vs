#version 330 core
// location = 0은 VAO attribute 0번을 의미. attribute 개수가 2개 이상일 때 명확하게 알 수 있으므로 추후에 다시 공부
layout (location = 0) in vec3 aPos;

// 모든 정점마다 개별적으로 실행될 함수
// 정점의 위치 설정
// normalizing된 좌표계 사용
void main() {
  gl_Position = vec4(aPos, 1.0);
}