#include <string.h>
#include<iostream>
#include <sstream>

enum class Error
{
	NoError,
	CorruptedArchive,
	IncorrectType
};
template <class T1, class T2>
struct IsSame
{
	static constexpr bool value = false;
};

template <class T>
struct IsSame<T, T>
{
	static constexpr bool value = true;
};

class Serializer
{
	std::ostream &out_;
	static constexpr char Separator = ' ';

public:
	explicit Serializer(std::ostream& out)
		: out_(out)
	{
	}

	template <class T>
	Error save(T& object)
	{
		return object.serialize(*this);
	}

	template <class... ArgsT>
	Error operator()(ArgsT... args)
	{
		return process(args...);
	}

private:

	template<class T>
	Error process(T value) {
		if (IsSame<bool, decltype(value)>::value) {
			out_ << (value ? "true" : "false") << Separator;
			return Error::NoError;
		}
		else if (IsSame<uint64_t, decltype(value)>::value) {
			out_ << value << Separator;
			return Error::NoError;
		}
		else {
			return Error::IncorrectType;
		}
	}

	template <class T, class... ArgsT>
	Error process(T value, ArgsT... args) {
		if (IsSame<bool, decltype(value)>::value) {
			out_ << (value ? "true" : "false") << Separator;
		}
		else if (IsSame<uint64_t, decltype(value)>::value) {
			out_ << value << Separator;
		}
		else {
			return Error::IncorrectType;
		}
		return process(args...);
	}
};

class Deserializer
{
	std::istream &in_;
	static constexpr char Separator = ' ';

	static bool isNumber(const std::string &str) {
		for (auto ch : str) {
			if ((ch < 48) || (ch > 57)) {
				return false;
			}
			return true;
		}
	}

public:
	explicit Deserializer(std::istream& in)
		: in_(in)
	{
	}

	template <class T>
	Error load(T& object)
	{
		return object.serialize(*this);
	}

	template <class... ArgsT>
	Error operator()(ArgsT&... args)
	{
		return process(args...);
	}

private:

	template<class T>
	Error process(T &value) {

		std::string str;
		std::stringstream str_stream;
		uint64_t temp;
		if (IsSame<bool&, decltype(value)>::value) {
			in_ >> str;
			if (str == "true") {
				value = true;
				return Error::NoError;
			}
			else if (str == "false") {
				value = false;
				return Error::NoError;
			}
			else {
				return Error::CorruptedArchive;
			}
		}
		else if (IsSame<uint64_t&, decltype(value)>::value) {
			in_ >> str;
			if (isNumber(str)) {
				str_stream << str << Separator;
				str_stream >> temp;
				value = temp;
				return Error::NoError;
			}
			else {
				return Error::CorruptedArchive;
			}
		}
		else {
			return Error::IncorrectType;
		}
	}

	template <class T, class... ArgsT>
	Error process(T &value, ArgsT&... args) {
		std::string str;
		std::stringstream str_stream;
		uint64_t temp;
		if (IsSame<bool&, decltype(value)>::value) {
			in_ >> str;
			if (str == "true") {
				value = true;
				return process(args...);
			}
			else if (str == "false") {
				value = false;
				return process(args...);
			}
			else {
				return Error::CorruptedArchive;
			}
		}
		else if (IsSame<uint64_t&, decltype(value)>::value) {
			in_ >> str;
			if (isNumber(str)) {
				str_stream << str << Separator;
				str_stream >> temp;
				value = temp;
				return process(args...);
			}
			else {
				return Error::CorruptedArchive;
			}
		}
		else {
			return Error::IncorrectType;
		}
		return process(args...);
	}
};
