
#pragma once

#include <string>
#include <vector>

std::vector<std::string> Split(std::string string, std::string separator);
std::string Join(std::vector<std::string> vector, std::string separator);

void Replace(std::string& string, std::string oldValue, std::string newValue);
std::string GetReplaced(std::string string, std::string oldValue, std::string newValue);

void ToLower(std::string& string);
void ToUpper(std::string& string);
bool CaseInsensitiveCompare(std::string string1, std::string string2);

bool StartsWith(const std::string& string, const std::string& pattern);
bool EndsWith(const std::string& string, const std::string& pattern);
