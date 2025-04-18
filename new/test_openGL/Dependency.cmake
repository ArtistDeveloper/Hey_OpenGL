# ExternalProject 관련 명령어 셋 추가
include(ExternalProject)

set(DEP_INSTALL_DIR ${PROJECT_BINARY_DIR}/install) # PROJECT_BINARY_DIR : build 폴더
set(DEP_INCLUDE_DIR ${DEP_INSTALL_DIR}/include)
set(DEP_LIB_DIR ${DEP_INSTALL_DIR}/lib)


ExternalProject_Add(
    dep-spdlog # 타겟의 이름
    GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
    GIT_TAG "v1.x"
    GIT_SHALLOW 1
    UPDATE_COMMAND "" # 라이브러리가 최신 업데이트가 되면 자동으로 업데이트. 원하지 않기에 비워둠
    PATCH_COMMAND "" # 다운 받은 코드에서 수정하고자 하는 것이 있으면 사용
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
    TEST_COMMAND "" # 라이브러리 대상 자동 테스트 실행 관련
)

# Dependency 리스트 및 라이브러리 파일 리스트 추가
set(DEP_LIST ${DEP_LIST} dep-spdlog) # DEP_LIST에 dep-spdlog 값 추가
set(DEP_LIBS ${DEP_LIBS} spdlog$<$<CONFIG:Debug>:d>)
