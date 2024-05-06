#pragma once
#include "student.hpp"
#include <vector>
#include <algorithm>

enum class sortingType {
    ASC,
    DESC
};

class Database {
public:
    void add(const Student & s);
    void display() const;
    std::string show() const;
    std::string findByLastName(const std::string & lastName) const;
    std::string findByPESEL(const std::string & PESEL) const;
    std::string sortByPESEL(const sortingType & s) const;
    std::string sortByLastName() const;
private:
    std::vector<Student> students_;
};