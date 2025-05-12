#include "context.h"

ContextUPtr Context::Create()
{
    auto context = ContextUPtr(new Context());
    if (!context->Init())
        return nullptr;
    return std::move(context);
}

bool Context::Init()
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
    };

    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);

    glGenBuffers(1, &m_vertexBuffer); // Buffer Object를 생성
    // 지금부터 사용할 buffer object 지정하며 버퍼 오브젝트의 용도를 지정. GL_ARRAY_BUFFER는 VBO로 사용됨을 지정.
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
     // 바인딩한 버퍼 오브젝트에 실제로 데이터를 복사
     // GL_STATIC_DRAW: GPU 버퍼에 값을 세팅하고 다시는 변경하지 않을 것임을 명시
     // GL_DYANMIC_DRAW: 값을 변경할 여지가 있음을 명시
     // GL_STREAM:DRAW: 값을 한 번 사용한 뒤 바로 버릴 예정임을 명시
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); // 0번 버텍스 어레이를 사용
    // 0번 어트리뷰트는 셰이더의 location = 0과 연결됨
    // 0번 어트리뷰트가 생긴 형태는 float값이 3개이고, (0, 3, GL_FLOAT)
    // normalizing 안해도 되고 (GL_FALSE)
    // STRIDE의 크기 설정: sizeof(float) * 3
    // offset은 0번부터 시작한다
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    

    ShaderPtr vertShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER);
    ShaderPtr fragShader = Shader::CreateFromFile("./shader/simple.fs", GL_FRAGMENT_SHADER);
    if (!vertShader || !fragShader)
        return false;
    SPDLOG_INFO("vertex shader id: {}", vertShader->Get());
    SPDLOG_INFO("fragment shader id: {}", fragShader->Get());

    m_program = Program::Create({fragShader, vertShader});
    if (!m_program)
        return false;
    SPDLOG_INFO("program id: {}", m_program->Get());

    glClearColor(0.0f, 0.1f, 0.2f, 0.0f); // 색상 설정

    return true;
}

void Context::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(m_program->Get());
    glDrawArrays(GL_TRIANGLES, 0, 3);
}