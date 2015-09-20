
#pragma once

#include <string>
#include <vector>

std::vector<std::string> Split(std::string string, std::string separator);
std::string Join(std::vector<std::string> vector, std::string separator);

void Replace(std::string& string, std::string oldValue, std::string newValue);
std::string GetReplaced(std::string string, std::string oldValue, std::string newValue);

void ToLower(std::string& string);
void ToUpper(std::string& string);
