#pragma once
#ifndef ARGUMENT_HPP
#define ARGUMENT_HPP

#include <string>

namespace cli {

template <class T> class Argument {
  public:
	using ret_type = T;
};

template <> class Argument<char const *> {
	std::string _name, _description;

  public:
	using ret_type = char const *;

	Argument(std::string const &name, std::string const &description) : _name{name}, _description{description} {}

	char const *get_name() const { return _name.c_str(); }
	char const *parse(char const *value) const { return value; }
};

namespace details {

template <class> struct is_argument_type : public std::false_type {};

template <class T> struct is_argument_type<Argument<T>> : public std::true_type {};

} // namespace details

} // namespace cli

#endif