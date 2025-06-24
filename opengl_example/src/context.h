#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "common.h"
#include "shader.h"
#include "buffer.h"
#include "program.h"
#include "vertex_layout.h"
#include "texture.h"

// 프로그램이 완전 종료가 되기 직전 메모리를 한 번에 정리하는게 좋음
// 이를 위해 Context 클래스에서 한 번에 묶어 관리
CLASS_PTR(Context)
class Context
{
public:
    static ContextUPtr Create();
    void Render();
    void ProcessInput(GLFWwindow* window);

private:
    Context() {}
    bool Init();
    ProgramUPtr m_program;

    VertexLayoutUPtr m_vertexLayout;
    BufferUPtr m_vertexBuffer;
    BufferUPtr m_indexBuffer;
    TextureUPtr m_texture;
    TextureUPtr m_texture2;

    // camera parameter
    glm::vec3 m_cameraPos{glm::vec3(0.0f, 0.0f, 3.0f)};
    // cameraTarget이 아니라, Front 표현을 사용했다.
    // Camera가 바라보는 방향을 결정할 때 두 가지 방법이 있다.
    // 1. Target: 카메라가 특정한 방향을 바라보고 있다.
    // 2. Front: 이 방향으로 바라보고 있다.
    glm::vec3 m_cameraFront{glm::vec3(0.0f, 0.0f, -1.0f)}; // 카메라가 z축으로 3만큼 떨어져있는 상황에서 -1을 바라보고 있다
    glm::vec3 m_cameraUp{glm::vec3(0.0f, 1.0f, 0.0f)};
};

#endif // __CONTEXT_H__