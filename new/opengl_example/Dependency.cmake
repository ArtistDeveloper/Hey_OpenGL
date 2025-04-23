# spdlog
# ExternalProject 관련 명령어 셋 추가
include(ExternalProject)

set(DEP_INSTALL_DIR ${PROJECT_BINARY_DIR}/install) # PROJECT_BINARY_DIR : build 폴더
set(DEP_INCLUDE_DIR ${DEP_INSTALL_DIR}/include)
set(DEP_LIB_DIR ${DEP_INSTALL_DIR}/lib)


ExternalProject_Add(
    dep_spdlog # 타겟의 이름
    GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
    GIT_TAG "v1.x"
    GIT_SHALLOW 1
    UPDATE_COMMAND "" # 라이브러리가 최신 업데이트가 되면 자동으로 업데이트. 원하지 않기에 비워둠
    PATCH_COMMAND "" # 다운 받은 코드에서 수정하고자 하는 것이 있으면 사용
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
    TEST_COMMAND "" # 라이브러리 대상 자동 테스트 실행 관련
)
# Dependency 리스트 및 라이브러리 파일 리스트 추가
set(DEP_LIST ${DEP_LIST} dep_spdlog) # DEP_LIST에 dep-spdlog 값 추가
set(DEP_LIBS ${DEP_LIBS} spdlog$<$<CONFIG:Debug>:d>)


# glfw
ExternalProject_Add(
    dep_glfw
    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
    GIT_TAG "3.3.3"
    GIT_SHALLOW 1
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    TEST_COMMAND ""
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
        -DGLFW_BUILD_EXAMPLES=OFF
        -DGLFW_BUILD_TESTX=OFF
        -DGLFW_BUILD_DOCS=OFF
)
set(DEP_LIST ${DEP_LIST} dep_glfw)
set(DEP_LIBS ${DEP_LIBS} glfw3)

# glad
ExternalProject_Add(
    dep_glad
    GIT_REPOSITORY "https://github.com/Dav1dde/glad.git"
    GIT_TAG "v0.1.34"
    GIT_SHALLOW 1
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
        -DGLAD_INSTALL=ON
    TEST_COMMAND ""
)
set(DEP_LIST ${DEP_LIST} dep_glad)
set(DEP_LIBS ${DEP_LIBS} glad)