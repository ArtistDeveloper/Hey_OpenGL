#include "common.h"
#include <fstream>
#include <sstream>

std::optional<std::string> LoadTextFile(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        SPDLOG_ERROR("failed to open file: {}", filename);
        return {}; // Optional type의 아무것도 없는 경우에는 {}로 반환.
    }
    std::stringstream text;
    text << fin.rdbuf(); // 파일을 여는데 성공했다면 파일 내용을 stringstream에 다 넣는다.
    return text.str(); // 내용을 다 str으로 바꾼 뒤 반환.
}