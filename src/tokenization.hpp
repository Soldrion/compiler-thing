#pragma once
#include <string>
#include <vector>
#include <optional>
enum class TokenType {
    _exit,
    int_lit,
    semi
};

struct Token {
    TokenType type;
    int line;
    std::optional<std::string> value {};
};


class Tokenizer {
public:
    inline explicit Tokenizer(const std::string src)
        : m_src(std::move(src))
    {
    }

    inline std::vector<Token> tokenize() {
        std::vector<Token> tokens;
        std::string buf;

        while (peek().has_value()) {
            if (std::isalpha(peek().value())) {
                buf.push_back(consume());
                while (peek().has_value() && std::isalnum(peek().value())) {
                    buf.push_back(consume());
                }
                if (buf == "exit") {
                    tokens.push_back({.type =  TokenType::_exit});
                    buf.clear();
                    continue;
                } else {
                    std::cerr << "Failed to read token 'exit'" << std::endl;
                    exit(EXIT_FAILURE);
                }
            } else if (std::isdigit(peek().value())) {
                buf.push_back(consume());
                while (peek().has_value() && std::isdigit(peek().value())) {
                    buf.push_back(consume());
                }
                tokens.push_back({.type= TokenType::int_lit, .value = buf});
                buf.clear();
                continue;
            }else if (peek().value() == ';') {
                buf.push_back(consume());
                continue;
        } else if (std::isspace(peek().value())) {
            buf.push_back(consume());
            continue;
        } else {
            std::cerr << "something messed up bro idk" << std::endl;
            exit(EXIT_FAILURE);
        }
        }
        m_index = 0;
        return tokens;
    }

private:
    [[nodiscard]] std::optional<char> peek(int ahead = 1) const {
        if (m_index +ahead >= m_src.length()) {
            return {};
        } else {
            return m_src.at(m_index);
        }
    }

    char consume() {
        return m_src.at(m_index++);
    }


    const std::string m_src;

    int m_index = 0;
};