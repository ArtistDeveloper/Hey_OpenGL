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
    // 사각형의 코너 포인트 4개
    float vertices[] = 
    {
         0.5f,  0.5f, 0.0f, // top right : 0
         0.5f, -0.5f, 0.0f, // bottom right : 1
        -0.5f, -0.5f, 0.0f, // bottom left : 2
        -0.5f,  0.5f, 0.0f, // top left : 3
    };

    uint32_t indices[] = // note that we start from 0!
    { 
        0, 1, 3, // first triangle
        1, 2, 3, // second triangle
    };

    // VAO 생성 : 무조건 buffer object만들기 전에 생성
    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);

    // VBO 생성
    m_vertexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW,
                                            vertices, sizeof(float) * 12);

    // VAO attribute setting : 
    glEnableVertexAttribArray(0); // 0번 arrtribute 사용
    // 0번 arrtibute는 값이 3개고, float값이고, normalizing 할 필요없고, stride의 크기 설정하고, offset은 0부터 시작한다.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0); 

    // EBO : 어차피 인덱스는 정수값이 들어올 것이라고 알고 있으니까, 따로 VAO 세팅을 할 필요가 없다.
    m_indexBuffer = Buffer::CreateWithData(GL_ELEMENT_ARRAY_BUFFER, 
                                           GL_STATIC_DRAW, indices, sizeof(uint32_t) * 6);

    ShaderPtr vertShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER);
    ShaderPtr fragShader = Shader::CreateFromFile("./shader/simple.fs", GL_FRAGMENT_SHADER);
    if (!vertShader || !fragShader) // 초기화 실패할 때 nullptr반환 받은 것으로 예외처리
        return false;
    SPDLOG_INFO("vertex shader id: {}", vertShader->Get());
    SPDLOG_INFO("fragment shader id: {}", fragShader->Get());

    m_program = Program::Create({fragShader, vertShader});
    if (!m_program)
        return false;
    SPDLOG_INFO("program id: {}", m_program->Get());

    glClearColor(0.0f, 0.1f, 0.2f, 0.0f); // 화면을 지울 때 무슨 색으로 지울까를 설정.

    return true;
}

void Context::Render()
{
    // 실제로 프레임버퍼를 clear하는 함수. GL_COLOR_BUFFER_BIT: 화면에 보이는 색상 버퍼를 의미.
    // 색상이 들어갈 화면을 지운다.
    glClear(GL_COLOR_BUFFER_BIT);

    m_program->Use();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // incides가 uint이므로 uint로 설정
}