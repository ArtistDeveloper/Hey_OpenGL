#include "common.h"
#include "shader.h"
#include <spdlog/spdlog.h>
#include <glad/glad.h> // glfw.h 이전에 glad를 추가해야 한다
#include <GLFW/glfw3.h>

void OnFramebufferSizeChange(GLFWwindow *window, int width, int height)
{
    SPDLOG_INFO("framebuffer size change: ({} x {})", width, height);
    glViewport(0, 0, width, height); // OpenGL이 그림을 그릴 화면의 위치와 범위를 지정
}

// mods: modifier
void OnKeyEvent(GLFWwindow *window,
                int key, int scancode, int action, int mods)
{
    SPDLOG_INFO("Key: {}, scancode: {}, action: {}, mods: {}{}{}",
                key, scancode,
                action == GLFW_PRESS     ? "Pressed"
                : action == GLFW_RELEASE ? "Release"
                : action == GLFW_REPEAT  ? "Repeat"
                                         : "Unknown",
                mods & GLFW_MOD_CONTROL ? "C" : "-",
                mods & GLFW_MOD_SHIFT ? "S" : "-",
                mods & GLFW_MOD_ALT ? "A" : "-");

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(int argc, const char **argv)
{
    SPDLOG_INFO("Start program");

    // glfw 라이브러리 초기화, 실패하면 에러 출력 후 종료
    SPDLOG_INFO("Initialize glfw");
    if (!glfwInit())
    {
        const char *descrption = nullptr;
        glfwGetError(&descrption);
        SPDLOG_ERROR("failed to initialize glfw: {}", descrption);
    }

    // 윈도우 컨텍스트 버전 힌트
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw 윈도우 생성, 실패하면 에러 출력 후 종료
    SPDLOG_INFO("Create glfw window");
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);
    if (!window)
    {
        SPDLOG_ERROR("failed to create glfw window");
        glfwTerminate();
        return -1;
    }
    // 어떤 윈도우에 대해 그림을 그리라고 세팅하는게 따로 없다
    // 만들어져있는 대상 컨텍스트에 대해 실행하라는 것을 가정하고 만들어진 것
    // OpenGL이 만들어졌을 당시에는 윈도우를 여러 개 띄울 필요가 없었기 때문
    // 지금은 여러 개의 윈도우가 동시에 OpenGL Function을 이용할 수 있기 때문에
    // glfwCreateWindow 함수를 통해 window를 만들 때 생성된 컨텍스트를 사용하겠다고 명시적으로 호출
    glfwMakeContextCurrent(window);

    // glad를 활용한 OpenGL 함수 로딩
    // gladLoadGLLoader: OpenGL 함수를 로드하는 역할
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        SPDLOG_ERROR("failed to initialize glad");
        glfwTerminate();
        return -1;
    }
    // OpenGL 함수 로딩이 되었는지 확인하기 위한 gl함수 호출 테스트
    auto glVersion = glGetString(GL_VERSION);
    SPDLOG_INFO("OpenGL context version: {}", reinterpret_cast<const char *>(glVersion));

    // auto vertexShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER);
    // auto fragmentShader = Shader::CreateFromFile("./shader/simple.fs", GL_FRAGMENT_SHADER);
    // SPDLOG_INFO("vertex shader id: {}", vertexShader->Get());
    // SPDLOG_INFO("fragment shader id: {}", fragmentShader->Get());

    // 윈도우 생성 직후 프레임버퍼 변경 이벤트가 발생하지 않으므로, 첫 호출은 수동으로
    OnFramebufferSizeChange(window, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChange);
    glfwSetKeyCallback(window, OnKeyEvent);

    // glfw 루프 실행, 윈도우 close 버튼을 누르면 정상 종료
    SPDLOG_INFO("Start main loop");
    while (!glfwWindowShouldClose(window))
    {
        // Frame의 입력 및 출력 이벤트를 처리
        // 이벤트가 발생하였는지 확인하고 윈도우 상태를 업데이트.
        // 이벤트를 처리하면 해당 이벤트와 관련된 콜백을 호출한다
        glfwPollEvents();
        glClearColor(0.0f, 0.1f, 0.2f, 0.0f); // 색상 설정
        // 실제로 프레임버퍼 클리어하는 함수
        // 여기선 색상 버퍼를 클리어 하겠다는 의미. (한 번만 세팅해도 됨)
        glClear(GL_COLOR_BUFFER_BIT);
        // 프레임 버퍼 2개를 준비 (더블버퍼링)
        // back buffer에 그림을 그리고, front와 back을 바꿔치기 한다. 이 과정을 계속 반복
        // front buffer에만 그림을 그리면 그림이 그려지는 과정이 노출되는데 이를 방지
        glfwSwapBuffers(window);
    }
    glfwTerminate();

    return 0;
}