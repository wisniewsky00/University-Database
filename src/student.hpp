#pragma once
#include <string>

enum class Gender {
    Male,
    Female
};


class Student{
public:
    Student(std::string name,
            std::string lastName,
            std::string address,
            int indexNumber,
            std::string pesel,
            Gender gender);
    Student();
    std::string show() const;
    std::string getLastName() const;
    std::string getPESEL() const;
    Gender getGender() const;
    std::string getName() const;
    std::string getAddress() const;
    int getIndexNumber() const;
    bool isPESELValid() const;

private:
    std::string name_;
    std::string lastName_;
    std::string address_;
    int indexNumber_;
    std::string pesel_;
    Gender gender_;
    std::string getgender() const;
};