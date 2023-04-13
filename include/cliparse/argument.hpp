#pragma once
#ifndef ARGUMENT_HPP
#define ARGUMENT_HPP

#include "common.hpp"

namespace cli {

template <class T> class Argument {
	std::string _name, _description;

  public:
	using ret_type = T;

	Argument(std::string const &name, std::string const &description) : _name{name}, _description{description} {}

	char const *get_name() const { return _name.c_str(); }
	T parse(char const *value) const { return argument_parse<T>(value); }
};

namespace details {

template <class> struct is_argument_type : public std::false_type {};

template <class T> struct is_argument_type<Argument<T>> : public std::true_type {};

} // namespace details

} // namespace cli

#endif