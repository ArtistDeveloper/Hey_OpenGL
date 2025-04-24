// __COMMON_H__가 존재하지 않으면 include 될 때 내용을 복사시키고
// 정의되어 있다면 다른 곳에서 선언하지 않음
// 함수 중복 선언 컴파일 에러를 방지하기 위함
// 윈도우 프로그래밍에선 #pragma once를 많이 쓴다.
#ifndef __COMMON_H__
#define __COMMON_H__ // define 이름은 중복되면 안된다.

#include <memory>
#include <string>
#include <optional>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <spdlog/spdlog.h>

// optional: 어떤 값이 있거나 없는 경우를 포인터없이 표현 가능
// 만약 TextFile이 없었을 때 빈 문자열을 return 하도록 하면 TextFild이 존재하지만 안에 내용이 없을 때의 경우를
// 커버하지 못한다. 그러므로 C에서는 포인터를 사용해서 string*을 return하도록 만든다.
// 내용이 있다면 동적할당된 포인터가 있을 것이고, 내용이 없다면 null 포인터를 return 하도록.
// 그러나 이 방식은 수동으로 메모리를 해제해주어야 하는 단점이 있다. 그래서 동적할당을 안전하게 해제하는 방법이 필요한데,
// 이를 optional로 가능하다. 값이 들어있으면 string을 꺼낼 수 있고, 없다면 못 꺼내는 형태가 된다.
std::optional<std::string> LoadTextFile(const std::string& filename);

#endif // __COMMON_H__