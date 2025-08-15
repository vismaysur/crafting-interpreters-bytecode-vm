#include "scanner.h"
#include <stdbool.h>
#include <string.h>

Scanner scanner;

void initScanner(const char *source) {
  scanner.start = source;
  scanner.current = source;
  scanner.line = 1;
}

static bool isAtEnd() { return *scanner.current == '\0'; }

static Token makeToken(TokenType type) {
  Token token;
  token.type = type;
  token.start = scanner.start;
  token.line = scanner.line;
  token.length = (int)(scanner.current - scanner.start);
  return token;
}

static Token errorToken(const char *source) {
  Token token;
  token.type = TOKEN_ERROR;
  token.start = source;
  token.length = (int)(strlen(source));
  token.line = scanner.line;
  return token;
}

static char advance() {
  scanner.current++;
  return scanner.current[-1];
}

static bool match(char expected) {
  if (isAtEnd())
    return false;

  if (*scanner.current != expected)
    return false;

  scanner.current++;
  return true;
}

static char peek() { return *scanner.current; }

static char peekNext() {
  if (isAtEnd())
    return '\0';
  return scanner.current[1];
}

static void skipWhitespace() {
  for (;;) {
    char c = peek();
    switch (c) {
    case ' ':
    case '\r':
    case '\t':
      advance();
      break;
    case '\n':
      scanner.line++;
      advance();
      break;
    case '/':
      if (peekNext() == '/') {
        while (peek() != '\n' && !isAtEnd())
          advance();
      } else {
        return;
      }
      break;
    default:
      return;
    }
  }
}

Token string() {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n')
      scanner.line++;
    advance();
  }

  if (isAtEnd())
    return errorToken("Unterminated string.");

  advance();

  return makeToken(TOKEN_STRING);
}

static bool isDigit(char c) { return (c >= '0' && c <= '9'); }

static bool isAlpha(char c) {
  return ('a' <= c && c <= 'z' || 'A' <= c && c <= 'Z' || c == '_');
}

static Token number() {
  while (isDigit(peek()))
    advance();

  if (peek() == '.' && isDigit(peekNext())) {
    advance();
    while (isDigit(peek()))
      advance();
  }

  return makeToken(TOKEN_NUMBER);
}

TokenType checkKeyword(int start, const char *rest, TokenType type) {
  int restLength = strlen(rest);

  if ((scanner.current - scanner.start) == (start + restLength) &&
      memcmp(scanner.start + start, rest, restLength) == 0) {
    return type;
  }

  return TOKEN_IDENTIFIER;
}

TokenType identifierType() {
  switch (scanner.start[0]) {
  case 'a':
    return checkKeyword(1, "nd", TOKEN_AND);
  case 'c':
    return checkKeyword(1, "lass", TOKEN_CLASS);
  case 'e':
    return checkKeyword(1, "lse", TOKEN_ELSE);
  case 'f':
    if (scanner.current - scanner.start > 1) {
      switch (scanner.start[1]) {
      case 'a':
        return checkKeyword(2, "lse", TOKEN_FALSE);
      case 'o':
        return checkKeyword(2, "r", TOKEN_FOR);
      case 'u':
        return checkKeyword(2, "n", TOKEN_FUN);
      }
    }
    break;
  case 'i':
    return checkKeyword(1, "f", TOKEN_IF);
  case 'n':
    return checkKeyword(1, "il", TOKEN_NIL);
  case 'o':
    return checkKeyword(1, "r", TOKEN_OR);
  case 'p':
    return checkKeyword(1, "rint", TOKEN_PRINT);
  case 'r':
    return checkKeyword(1, "eturn", TOKEN_RETURN);
  case 's':
    return checkKeyword(1, "uper", TOKEN_SUPER);
  case 't':
    if (scanner.current - scanner.start > 1) {
      switch (scanner.start[1]) {
      case 'h':
        return checkKeyword(2, "is", TOKEN_THIS);
      case 'r':
        return checkKeyword(2, "ue", TOKEN_TRUE);
      }
    }
    break;
  case 'v':
    return checkKeyword(1, "ar", TOKEN_VAR);
  case 'w':
    return checkKeyword(1, "hile", TOKEN_WHILE);
  }

  return TOKEN_IDENTIFIER;
}

Token identifier() {
  while (isAlpha(peek()) || isDigit(peek()))
    advance();
  return makeToken(identifierType());
}

Token scanToken() {
  skipWhitespace();

  scanner.start = scanner.current;

  if (isAtEnd())
    return makeToken(TOKEN_EOF);

  char c = advance();

  if (isAlpha(c))
    return identifier();

  if (isDigit(c))
    return number();

  switch (c) {
  case '(':
    return makeToken(TOKEN_LEFT_PAREN);
  case ')':
    return makeToken(TOKEN_RIGHT_PAREN);
  case '{':
    return makeToken(TOKEN_LEFT_BRACE);
  case '}':
    return makeToken(TOKEN_RIGHT_BRACE);
  case ';':
    return makeToken(TOKEN_SEMICOLON);
  case ',':
    return makeToken(TOKEN_COMMA);
  case '-':
    return makeToken(TOKEN_MINUS);
  case '+':
    return makeToken(TOKEN_PLUS);
  case '/':
    return makeToken(TOKEN_SLASH);
  case '*':
    return makeToken(TOKEN_STAR);
  case '!':
    return (match('=') ? makeToken(TOKEN_BANG_EQUAL) : makeToken(TOKEN_BANG));
  case '=':
    return (match('=') ? makeToken(TOKEN_EQUAL_EQUAL) : makeToken(TOKEN_EQUAL));
  case '>':
    return (match('=') ? makeToken(TOKEN_GREATER_EQUAL)
                       : makeToken(TOKEN_GREATER));
  case '<':
    return (match('=') ? makeToken(TOKEN_LESS_EQUAL) : makeToken(TOKEN_LESS));
  case '"':
    return string();
  }

  return errorToken("Unexpected character.");
}
