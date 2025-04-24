#include "common.h"
#include <fstream>
#include <sstream>

std::optional<std::string> LoadTextFile(const std::string& filename) {
    // cpp 스타일의 파일 로딩
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        SPDLOG_ERROR("failed to open file: {}", filename);
        return {}; // optional 반환 타입에서 {}를 보내면 아무것도 없는 값을 반환할 수 있다.
    }
    std::stringstream text;
    text << fin.rdbuf();
    return text.str();
}