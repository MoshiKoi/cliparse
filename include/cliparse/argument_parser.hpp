#pragma once
#ifndef ARGUMENTPARSER_HPP
#define ARGUMENTPARSER_HPP

#include <cstring>
#include <functional>
#include <vector>

#include <tuple>

#include "argument.hpp"
#include "option.hpp"

// namespace cli {

// template <class... Args> class ArgumentParser {
// 	std::tuple<Args...> _args;

// 	template <class T> void visit(Argument<T> arg) {}
// 	template <class T> void visit(Option<T> arg) {}

//   public:
// 	ArgumentParser(std::tuple<Args...> args) : ArgumentParser{args, std::make_index_sequence<sizeof...(Args)>{}} {}

// 	template <size_t... Idx> ArgumentParser(std::tuple<Args...> args, std::index_sequence<Idx...> seq) : _args{args} {}

// 	auto parse(int argc, char const *const *argv) {
		
// 	}
// };

// } // namespace cli

#endif