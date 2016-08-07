
#pragma once

#include <string>

const std::string singleLineComment = "//.*";
const std::string multiLineComment = "[/][*][^]*?[*][/]";
const std::string charLiteral = "'(\\\\'|[^'])*?'";        // '(\\'|[^'])*?'
const std::string stringLiteral = "\"(\\\\\"|[^\"])*?\"";  // "(\\"|[^"])*?"

const std::string comments = "(" + singleLineComment + ")|(" + multiLineComment + ")";
const std::string literals = "(" + charLiteral + ")|(" + stringLiteral + ")";

const std::string lineContinuation = "\\\\\\n"; // \\\n
const std::string directiveLine = "^( |\t|\v)*#.*$";

const std::string space = "[ \t\v\n\r]+";
const std::string spaceOrEmpty = "[ \t\v\n\r]*";

const std::string simplexOperator = "[(){}\\[\\],~?]";      // (){}[],~?
const std::string combinableOperator = "[*&<>+-/%|!=.:]";
