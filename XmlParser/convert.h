#ifndef CONVERT
#define CONVERT

#include <string>

using namespace std;

enum class ConversionResult {
    Success,
    Overflow,
    Underflow,
    Inconvertible
};

ConversionResult str2ull (unsigned long long &i, const std::string& s, int base);

ConversionResult str2d (double &i, const std::string& s);

#endif // CONVERT

