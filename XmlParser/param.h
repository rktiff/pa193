#ifndef PARAM_H
#define PARAM_H

#include <string>

class Param
{
    std::string* m_name;
    std::string* m_value;
public:
    Param();
    ~Param();

    std::string *getName() const;
    void setName(const std::string& name);

    std::string *getValue() const;
    void setValue(const std::string& value);
};

#endif // PARAM_H
