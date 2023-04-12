#pragma once
#ifndef OPTION_HPP
#define OPTION_HPP

#include <string>

namespace cli {

template <class T> class Option {
	using ret_type = T;
};

template <> class Option<char const *> {
	std::string _name, _description;
	char const *_default_value;

  public:
	using ret_type = char const *;

	Option(std::string const &name, std::string const &description, char const *default_value)
	    : _name{name}, _description{description}, _default_value{default_value} {}

	std::string get_name() const { return _name; }
	char const *parse(char const *value) const { return value; }
	char const *get_default_value() const { return _default_value; }
};

template <> class Option<bool> {
	std::string _name, _description;
	bool _default_value;

  public:
	using ret_type = bool;

	Option(std::string const &name, std::string const &description, bool default_value = false)
	    : _name{name}, _description{description}, _default_value{default_value} {}

	std::string get_name() const { return _name; }
	bool parse(char const *value) const { return value; }
	bool get_default_value() const { return _default_value; }
};

namespace details {

template <class> struct is_option_type : public std::false_type {};

template <class T> struct is_option_type<Option<T>> : public std::true_type {};

} // namespace details

} // namespace cli

#endif