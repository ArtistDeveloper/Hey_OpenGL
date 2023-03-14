cmake_minimum_required(VERSION 3.14)

# set: 변수세팅 
set(PROJECT_NAME opengl_project) # PROJECT_NAME에다가 cmake_project_example 세팅 
set(CMAKE_CXX_STANDARD 17)

set(WINDOW_NAME "OpenGL Example")
set(WINDOW_WIDTH 960)
set(WINDOW_HEIGHT 540)

project(${PROJECT_NAME}) # 이 아래부터 이런 프로젝트 이름의 세팅을 할 것이다.
add_executable(${PROJECT_NAME} # 이 프로젝트 이름의 실행파일을 만들 것인데, 그 뒤에 붙어있는 모든 소스파일을 다 컴파일해서 실행파일을 만들겠다. 
    src/main.cpp 
    src/common.cpp src/common.h
    src/shader.cpp src/shader.h
    src/program.cpp src/program.h
    ) 

include(Dependency.cmake)


# 우리 프로젝트에 include / lib 관련 옵션 추가 # 라이브러리를 다운 받은 다음 우리 프로젝트에서 사용하겠다. # 실행 파일이름이 타겟
target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR}) # 헤더파일 위치 연결
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR}) # lib위치 path연결
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS}) # 실제로 어떤 라이브러리 사용할지 설정

# #define 해주는 역할. 이것을 소스코드 안쪽이 아니라, 바깥쪽에서 가능하도록 만드는 것임 
target_compile_definitions(${PROJECT_NAME} PUBLIC
    WINDOW_NAME="${WINDOW_NAME}"
    WINDOW_WIDTH=${WINDOW_WIDTH}
    WINDOW_HEIGHT=${WINDOW_HEIGHT}
    )

# Dependency들이 먼저 build 될 수 있게 관계 설정
add_dependencies(${PROJECT_NAME} ${DEP_LIST})