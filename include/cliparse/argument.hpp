#pragma once
#ifndef ARGUMENT_HPP
#define ARGUMENT_HPP

#include <charconv>
#include <exception>
#include <string>
#include <string_view>
#include <system_error>

namespace cli {

class ArgumentException : public std::exception {};

template <class T> class Argument;

template <> class Argument<char const *> {
	std::string _name, _description;

  public:
	using ret_type = char const *;

	Argument(std::string const &name, std::string const &description) : _name{name}, _description{description} {}

	char const *get_name() const { return _name.c_str(); }
	char const *parse(char const *value) const { return value; }
};

template <class T>
concept from_chars_convertible =
    requires(const char *first, const char *last, T value) { std::from_chars(first, last, value); };

#define IntegerParsingArgument(T)                                                                                      \
	template <> class Argument<T> {                                                                                    \
		std::string _name, _description;                                                                               \
                                                                                                                       \
	  public:                                                                                                          \
		using ret_type = T;                                                                                            \
                                                                                                                       \
		Argument(std::string const &name, std::string const &description) : _name{name}, _description{description} {}  \
                                                                                                                       \
		char const *get_name() const {                                                                                 \
			return _name.c_str();                                                                                      \
		}                                                                                                              \
		T parse(char const *value) const {                                                                             \
			T result;                                                                                                  \
			std::string_view view{value};                                                                              \
			auto const [_, ec] = std::from_chars(view.data(), view.data() + view.size(), result);                      \
			if (ec != std::errc())                                                                                     \
				throw ArgumentException{};                                                                             \
			return result;                                                                                             \
		}                                                                                                              \
	};

IntegerParsingArgument(int);
IntegerParsingArgument(long);
IntegerParsingArgument(long long);
IntegerParsingArgument(float);
IntegerParsingArgument(double);

#undef IntegerParsingArgument

namespace details {

template <class> struct is_argument_type : public std::false_type {};

template <class T> struct is_argument_type<Argument<T>> : public std::true_type {};

} // namespace details

} // namespace cli

#endif