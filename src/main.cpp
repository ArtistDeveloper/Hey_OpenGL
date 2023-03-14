#include "common.h"
#include "shader.h"

// #include <spdlog/spdlog.h>
// #include <glad/glad.h>
// #include <GLFW/glfw3.h>


void OnFramebufferSizeChange(GLFWwindow* window, int width, int height)
{
    SPDLOG_INFO("framebuffer size changed: ({} x {})", width, height);
    glViewport(0, 0, width, height); // OpenGL이 그림을 그릴 화면의 위치 및 크기 설정.
}

void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    SPDLOG_INFO("Key: {}, scancode: {}, action: {}, mods: {}{}{}",
    key, scancode,
    action == GLFW_PRESS ? "Pressed" :
    action == GLFW_RELEASE ? "Released" :
    action == GLFW_REPEAT ? "Repeat" : "Unknown",
    mods & GLFW_MOD_CONTROL ? "C" : "-",
    mods & GLFW_MOD_SHIFT ? "S" : "-",
    mods & GLFW_MOD_ALT ? "A" : "-" );

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }    
}

int main(int argc, const char** argv)
{
    SPDLOG_INFO("Start Program");
    
    // glfw 라이브러리 초기화, 실패하면 에러 출력후 종료, glfwInit 함수가 라이브러리 초기화해주는 역할
    SPDLOG_INFO("Initialize glfw");
    if (!glfwInit()) {
        const char* description = nullptr;
        glfwGetError(&description);
        SPDLOG_ERROR("failed to initialize glfw: {}", description);
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw 윈도우 생성, 실패하면 에러 출력후 종료
    SPDLOG_INFO("Create glfw window");
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);
    if (!window) {  
        SPDLOG_ERROR("failed to create glfw window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // 여기까지 하면 OpenGL Context 세팅 완료.

    // glad를 활용한 OpenGL 함수 로딩
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        SPDLOG_ERROR("failed to initialize glad");
        glfwTerminate();
        return -1;
    }
    // 위에까지 완료되면 GL함수 사용가능.
    const GLubyte* glVersion = glGetString(GL_VERSION);
    SPDLOG_INFO("OpenGL context version: {}", (const char*)glVersion); 

    auto vertexShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER);
    auto fragmentShader = Shader::CreateFromFile("./shader/simple.fs", GL_FRAGMENT_SHADER);
    SPDLOG_INFO("vertex shader id: {}", vertexShader->Get());
    SPDLOG_INFO("fragment shader id: {}", fragmentShader->Get());

    // glContext와 openGL 로딩이 된 후에 콜백을 glfw쪽에서 호출 될 수 있도록 만들어 주어야 함.
    OnFramebufferSizeChange(window, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChange);
    glfwSetKeyCallback(window, OnKeyEvent);

    // glfw 루프 실행, 윈도우 close 버튼을 누르면 정상 종료
    SPDLOG_INFO("Start main loop");
    while (!glfwWindowShouldClose(window)) {
        // 창은 기본적으로 1/60초 마다 그려지게 되는데, 그 이벤트들을 모아놨다가 실행. 어쨌든 이벤트를 기다리는 코드
        glfwPollEvents(); // 윈도우와 관렫뇐 다양한 이벤트들이 있을텐데, 그것들을 수집하는 역할을 하는 함수이다.
        glClearColor(0.0f, 0.1f, 0.2f, 0.0f); // 화면을 지울 때 무슨 색으로 지울까를 설정.
        glClear(GL_COLOR_BUFFER_BIT); // 실제로 프레임버퍼를 clear하는 함수. GL_COLOR_BUFFER_BIT: 화면에 보이는 색상 버퍼를 의미. 색상이 들어갈 화면을 지운다.
        glfwSwapBuffers(window); // front, back buffer 번갈아가며 그림.(double buffering이라고도 함.)
    }
    

    glfwTerminate();

    return 0;
}