#include "database.hpp"
#include <iostream>

void Database::add(const Student & s)
{
    students_.push_back(s);
}

void Database::display() const
{
    std::cout << show();
}

std::string Database::show() const
{
    std::string result = "";
    for(auto && student : students_){
        result += student.show() + '\n';
    }
    return result;
}

std::string Database::findByLastName(const std::string & lastName) const
{
    for(auto && student : students_){
        if (lastName == student.getLastName()) return student.show();
    }
    return "The lastname '" + lastName + "' was not found in the database";
}