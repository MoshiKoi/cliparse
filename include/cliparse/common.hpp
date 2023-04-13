#pragma once
#ifndef COMMON_HPP
#define COMMON_HPP

#include <charconv>
#include <exception>
#include <string_view>
#include <system_error>
#include <type_traits>

namespace cli {

class ArgumentException : public std::exception {};

template <class T> T argument_parse(char const *);

template <class T>
	requires std::is_constructible_v<T, char const *>
T argument_parse(char const * value) {
	return T{value};
}

template <class T>
	requires std::is_integral_v<T> || std::is_floating_point_v<T>
inline T
argument_parse(char const *value) {
	int result;
	std::string_view view{value};
	auto [_, ec] = std::from_chars(view.data(), view.data() + view.size(), result);
	if (ec != std::errc())
		throw ArgumentException{};
	return result;
}

}

#endif