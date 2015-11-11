#include "param.h"

Param::Param()
    : m_name(NULL), m_value(NULL)
{
}

Param::~Param()
{
    delete m_name;
    delete m_value;
}

std::string *Param::getName() const
{
    return m_name;
}

void Param::setName(const std::string& name)
{
    m_name = new std::string(name);
}

std::string *Param::getValue() const
{
    return m_value;
}

void Param::setValue(const std::string& value)
{
    m_value = new std::string(value);
}


