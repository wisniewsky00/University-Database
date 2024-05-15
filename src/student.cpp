#include "student.hpp"
Student::Student(std::string name,
                 std::string lastName,
                 std::string address,
                 int indexNumber,
                 std::string pesel,
                 Gender gender)
    : name_(name), lastName_(lastName), address_(address),
      indexNumber_(indexNumber), pesel_(pesel), gender_(gender)
{}
Student::Student(){};

std::string Student::show() const
{
    return name_ + " " 
    + lastName_ + "; " 
    + address_ + "; " 
    + std::to_string(indexNumber_) + "; " 
    + pesel_ + "; " 
    + getgender();
}

std::string Student::getgender() const
{
  return gender_ == Gender::Male ? "Male" : "Female";
}

Gender Student::getGender() const
{
  return gender_;
}

std::string Student::getLastName() const
{
  return lastName_;
}

std::string Student::getPESEL() const
{
  return pesel_;
}

int Student::getIndexNumber() const
{
  return indexNumber_;
}

std::string Student::getName() const
{
  return name_;
}

std::string Student::getAddress() const
{
  return address_;
}

bool Student::isPESELValid() const
{
  if(pesel_.length() != 11) return false;

  const int multipielrs[4] = {1, 3, 7, 9};
  int sum = 0;

  for(unsigned int i = 0; i < pesel_.length() - 1; i++)
  {
    sum += multipielrs[i % 4] * (pesel_[i] - '0');
  }

  int checkDigit;
  sum % 10 == 0 ? checkDigit = 0 : checkDigit = 10 - (sum % 10);

  if(checkDigit == pesel_[10] - '0') return true;
  else return false;
}