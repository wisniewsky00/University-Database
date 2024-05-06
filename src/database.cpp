#include "database.hpp"
#include <iostream>

void Database::add(const Student & s)
{
    for(auto && student : students_)
    {
        if (student.getPESEL() == s.getPESEL()){
            std::cout << "Student with PESEL '" + s.getPESEL() + "' is already in the database";
        }; 
    }
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
    std::string result = "";
    for(auto && student : students_){
        if (lastName == student.getLastName()) result += student.show() + '\n';
    }
    return result.empty() ? "The lastname '" + lastName + "' was not found in the database.\n" : result;  
}

std::string Database::findByPESEL(const std::string & PESEL) const
{
    for(auto && student : students_){
        if(PESEL == student.getPESEL()) return student.show() + '\n';
    }
    return "Student with PESEL '" + PESEL + "' was not found in the database.\n";
}