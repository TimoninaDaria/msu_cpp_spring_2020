#pragma once
#include <string>
#include <iostream>

bool isInteger(const std::string & s)
{
    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

    char * p;
    strtol(s.c_str(), &p, 10);

    return (*p == 0);
}

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
    static constexpr char Separator = ' ';
    std::ostream& out_;
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
    template <class... ArgsT>
    Error process(bool val, ArgsT... args)
    {
        if(val)
            out_ << "true"<< Separator;
        else
            out_ << "false" << Separator;
        process(std::forward<ArgsT>(args)...);
        return Error::NoError;
    }

    template <class... ArgsT>
    Error process(uint64_t val, ArgsT... args)
    {
        out_ << val << Separator;
        process(std::forward<ArgsT>(args)...);
        return Error::NoError;
    }
    Error process(uint64_t val)
    {
        out_ << val << Separator;
        return Error::NoError;
    }
    Error process(bool val)
    {
        if(val)
            out_ << "true" << Separator;
        else
            out_ << "false" << Separator;
        return Error::NoError;
    }
};

class Deserializer
{
    std::istream& in_;
    static constexpr char Separator = ' ';

public:
    explicit Deserializer(std::istream& in)
        : in_(in)
    {
    }

    template <class T>
    Error load(T& object)
    {
        return object.deserialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args)
    {
        return process(args...);
    }

private:
    template <class... ArgsT>
    Error process(bool& val, ArgsT&&... args)
    {
        std::string text;
        in_ >> text;
        if (text == "true")
            val = true;
        else if (text == "false")
            val = false;
        else
            return Error::CorruptedArchive;

        process(std::forward<ArgsT>(args)...);
        return Error::NoError;
    }

    template <class... ArgsT>
    Error process(uint64_t& val, ArgsT&&... args)
    {

        std::string text;
        in_ >> text;
        if (isInteger(text))
            val = std::stoi(text);
        else
            return Error::CorruptedArchive;

        process(std::forward<ArgsT>(args)...);
        return Error::NoError;
    }

    Error process(uint64_t& val)
    {
        std::string text;
        in_ >> text;
        if (isInteger(text))
            val = std::stoi(text);
        else
            return Error::CorruptedArchive;
        return Error::NoError;
    }

    Error process(bool& val)
    {
        std::string text;
        in_ >> text;
        if (text == "true")
            val = true;
        else if (text == "false")
            val = false;
        else
            return Error::CorruptedArchive;
        return Error::NoError;
    }

};
