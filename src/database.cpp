#include "database.hpp"
#include <iostream>

bool Database::add(const Student & s)
{
    if(!isAdded_) {
        isAdded_ = true;
        return true;
    } else {
        return false;
    }
}

void Database::display() const
{
    std::cout << show();
}

std::string Database::show() const
{
    return "";
}