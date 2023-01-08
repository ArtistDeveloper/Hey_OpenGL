# ExternalProject 관련 명령어 셋 추가
include(ExternalProject) # include: CMake에서 다른 기능을 사용하고 싶을 때 사용. -> ExternalProject라는 기능을 사용

# Dependency 관련 변수 설정
set(DEP_INSTALL_DIR ${PROJECT_BINARY_DIR}/install) #PROJECT_BINARY_DIR: build폴더 가리킴
set(DEP_INCLUDE_DIR ${DEP_INSTALL_DIR}/include)
set(DEP_LIB_DIR ${DEP_INSTALL_DIR}/lib)

# spdlog: fast logger library
ExternalProject_Add(
    dep_spdlog # 프로젝트를 컴파일 할 때 대표이름
    GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
    GIT_TAG "v1.x"
    GIT_SHALLOW 1 # Shallow On, OFF: 가장 최신의 것 다운.(예전 커밋목록 안나오게)
    UPDATE_COMMAND "" # 다운받은 라이브러리가 최신버전이 나왔다면, 업데이트 해주는 역할
    PATCH_COMMAND "" # 다운받은 코드에서 어떤 코드를 고칠 때 사용.

    # CMake configure를 수행하는데, Configure를 할 대 인자를 어떻게 줄 것인지 세팅 | spdlog 빌드한 결과를 주어진 변수값으로 지정
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR} 
    TEST_COMMAND ""
)
# Dependency 리스트 및 라이브러리 파일 리스트 추가
set(DEP_LIST ${DEP_LIST} dep_spdlog)
set(DEP_LIBS ${DEP_LIBS} spdlog$<$<CONFIG:Debug>:d>)

# glfw
ExternalProject_Add(
    dep_glfw
    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
    GIT_TAG "3.3.2"
    GIT_SHALLOW 1
    UPDATE_COMMAND "" PATCH_COMMAND "" TEST_COMMAND ""
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
        -DGLFW_BUILD_EXAMPLES=OFF
        -DGLFW_BUILD_TESTS=OFF
        -DGLFW_BUILD_DOCS=OFF
    )
set(DEP_LIST ${DEP_LIST} dep_glfw)
set(DEP_LIBS ${DEP_LIBS} glfw3)

# glad
ExternalProject_Add(
    dep_glad
    GIT_REPOSITORY "https://github.com/Dav1dde/glad"
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