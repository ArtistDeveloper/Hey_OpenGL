cmake_minimum_required(VERSION 3.17)

set(PROJECT_NAME opengl_example)
set(CMAKE_CXX_STANDARD 17)

set(WINDOW_NAME "OpenGL Example")
set(WINDOW_WIDTH 960)
set(WINDOW_HEIGHT 540)

project(${PROJECT_NAME})
add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/common.cpp src/common.h
    src/shader.cpp src/shader.h
    src/program.cpp src/program.h
    src/context.cpp src/context.h
    src/buffer.cpp src/buffer.h
    src/vertex_layout.cpp src/vertex_layout.h
)

include(Dependency.cmake)

# 우리 프로젝트에 include / lib 관련 옵션 추가
target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR}) # 타겟에서 헤더파일을 찾기 위해 사용하는 폴더를 지정하는 커맨드
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS}) # 실제로 어떤 라이브러리를 사용할지를 지정
# 즉, target_link_libraries는 install/lib/"spdlogd".lib 라이브러리 파일을 가지고 오게 된다.
# target_link_libraries 지정할 때는 .lib 빼고 지정하면 된다

target_compile_definitions(${PROJECT_NAME} PUBLIC
    WINDOW_NAME="${WINDOW_NAME}"
    WINDOW_WIDTH=${WINDOW_WIDTH}
    WINDOW_HEIGHT=${WINDOW_HEIGHT}
)

# Dependency 들이 먼저 build 될 수 있게 관계 설정
# 프로젝트 컴파일을 하기 전에, DEP_LIST안에 들어가있는 타겟들을 모두 컴파일 한 다음에 우리 프로젝트를 컴파일 하라
# 지정안하면 병렬로 빌드가 되어 문제가 생길 여지가 있음
add_dependencies(${PROJECT_NAME} ${DEP_LIST})