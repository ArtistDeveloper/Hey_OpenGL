#ifndef __COMMON_H__
#define __COMMON_H__

#include <memory>
#include <string>
#include <optional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

/*
매크로 함수의 형태 => 매크로이름(매개변수)
매개변수로 클래스 이름을 받으면 매개변수의 내용으로 클래스 이름이 선언된다.
using을 통해 alias. (typedef의 c++버전)
define function을 여러 줄로 사용하고 싶으면 문장 끝을 '\'로 이어준다.
##: 사이를 붙여주는 역할 ex) ShaderUPtr, ShaderWPtr 
*/

#define CLASS_PTR(klassName) \
class klassName; \
using klassName ## UPtr = std::unique_ptr<klassName>; \
using klassName ## Ptr = std::shared_ptr<klassName>; \
using klassName ## WPtr = std::weak_ptr<klassName>;

std::optional<std::string> LoadTextFile(const std::string& filename);

#endif // __COMMON_H__