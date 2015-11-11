#include <limits.h>
#include <algorithm>
#include <math.h>

#include "convert.h"

ConversionResult str2ull (unsigned long long &i, const std::string& s, int base = 0)
{
    const char* ss = s.c_str();
    char *end;
    unsigned long long l;
    errno = 0;
    l = strtoull(ss, &end, base);
    if (errno == ERANGE && l == ULONG_LONG_MAX) {
        return ConversionResult::Overflow;
    }
    if (errno == ERANGE && l == 0) {
        return ConversionResult::Underflow;
    }
    if (*ss == '\0' || *end != '\0') {
        return ConversionResult::Inconvertible;
    }
    i = l;
    return ConversionResult::Success;
}

ConversionResult str2d (double &d, const std::string& s)
{
    // replace , by . and remove spaces
    std::string mutstr = s;
    std::replace( mutstr.begin(), mutstr.end(), ',', '.');
    std::remove_if(mutstr.begin(), mutstr.end(), ::isspace);

    const char* ss = mutstr.c_str();
    char *end;
    long double ld;
    errno = 0;
    ld = strtod(ss, &end);
    if ((errno == ERANGE && ld == HUGE_VALL) || ld > HUGE_VAL) {
        return ConversionResult::Overflow;
    }
    if (errno == ERANGE && ld == 0) {
        return ConversionResult::Underflow;
    }
    if (*ss == '\0' || *end != '\0') {
        return ConversionResult::Inconvertible;
    }
    d = ld;

    return ConversionResult::Success;
}


