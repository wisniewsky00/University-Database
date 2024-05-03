#pragma once
#include "student.hpp"
#include <vector>

class Database {
public:
    void add(const Student & s);
    void display() const;
    std::string show() const;
    std::string findByLastName(const std::string & lastName) const;
    std::string findByPESEL(const std::string & PESEL) const;
private:
    std::vector<Student> students_;
};