#include "database.hpp"
#include <iostream>
#include <fstream>

bool Database::add(const Student & s)
{
    for(auto && student : students_)
    {
        if (student.getPESEL() == s.getPESEL()){
            std::cout << "\nStudent with PESEL '" + s.getPESEL() + "' is already in the database.\n";
            return false;
        };

        if(student.getIndexNumber() == s.getIndexNumber()){
            std::cout << "\nStudent with index number '" + std::to_string(s.getIndexNumber()) + "' is already in the database.\n\n";
            return false;
        } 
    }
    students_.push_back(s);
    return true;
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
    if(result == "") return "The database is empty.\n";
    else return result;
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
    if(PESEL.length() != 11) return "The PESEL must consist of 11 digits!\n";

    for(auto && student : students_){
        if(PESEL == student.getPESEL()) return student.show() + '\n';
    }
    return "Student with PESEL '" + PESEL + "' was not found in the database.\n";
}

std::string Database::sortByPESEL(const sortingType & s)
{
    std::vector<Student> sortedStudents = students_;  
    std::string result = "";

    if(s == sortingType::ASC){
        std::sort(sortedStudents.begin(), sortedStudents.end(), [](const Student & a, const Student & b)
        {
           return a.getPESEL() < b.getPESEL();
        });

        for(auto && student : sortedStudents) result += student.show() + '\n';
    }
    else{
        std::sort(sortedStudents.begin(), sortedStudents.end(), [](const Student & a, const Student & b)
        {
           return a.getPESEL() > b.getPESEL();
        });

        for(auto && student : sortedStudents) result += student.show() + '\n';

    }
    return result;
}

std::string Database::sortByLastName()
{
    std::vector<Student> sortedStudents = students_;  
    std::string result = "";
    
    sort(sortedStudents.begin(), sortedStudents.end(), [](Student &a, Student &b)
    {
        return a.getLastName() < b.getLastName();
    });

    for(auto && student : sortedStudents) result += student.show() + '\n';
    return result;
}

std::string Database::deleteByIndexNumber(const int & indexNumber)
{
    for(size_t i = 0; i < students_.size(); i++){
        if(students_[i].getIndexNumber() == indexNumber){
            students_.erase(students_.begin() + i);
            return "Student with index number '" + std::to_string(indexNumber) + "' was deleted from database.\n";
        }
    }
    return "Student with index number '" + std::to_string(indexNumber) + "' was not found in the database.\n";
}

std::string Database::saveToFile(const std::string & fileName)
{
    if(students_.empty()) return "Database is empty.\n";

    std::ifstream file;
    file.open(fileName);

    if (file) {
        file.close();
        return "File '" + fileName + "' already exists.\n";
    }
    file.close();

    std::ofstream outputFile(fileName, std::ios::out | std::ios::binary);
    if (!outputFile) return "Failed to open file '" + fileName + "' for writing\n";

    size_t numStudents = students_.size();
    outputFile.write((char*) &numStudents, sizeof(numStudents));

    std::string name, lastName, address, pesel;
    int indexNumber, genderValue;
    Gender gender;

    for(auto && student : students_) {
        name = student.getName() + ';';
        outputFile.write(name.c_str(), name.size());

        lastName = student.getLastName() + ';';
        outputFile.write(lastName.c_str(), lastName.size());

        address = student.getAddress() + ';';
        outputFile.write(address.c_str(), address.size());

        pesel = student.getPESEL() + ';';
        outputFile.write(pesel.c_str(), pesel.size());

        indexNumber = student.getIndexNumber();
        outputFile.write((char*) &indexNumber, sizeof(indexNumber));

        gender = student.getGender();
        genderValue = static_cast<int>(gender);
        outputFile.write((char*) &genderValue, sizeof(genderValue));
    }
    outputFile.close();
    return "File '" + fileName + "' was successfully created.\n";
    
}

std::string Database::readFromFile(const std::string & fileName)
{
    std::ifstream inputFile(fileName, std::ios::in | std::ios::binary);
    if (!inputFile) {
        return "Failed to open file '" + fileName + "' for reading\n";
    }

    if(!students_.empty()){
        return "Current database is not empty.\n";
    }

    inputFile.seekg(0, std::ios::end);
    if (inputFile.tellg() == 0) {
        inputFile.close();
        return "File '" + fileName + "' is empty.\n";
    }

    inputFile.seekg(0, std::ios::beg);

    size_t numStudents = 0;
    inputFile.read((char*) &numStudents, sizeof(numStudents));

    std::string name, lastName, address, pesel;
    int indexNumber, genderValue;
    Gender gender;

    for(unsigned int i = 0; i < numStudents; i++){

        std::getline(inputFile, name, ';');
        std::getline(inputFile, lastName, ';');
        std::getline(inputFile, address, ';');
        std::getline(inputFile, pesel, ';');

        inputFile.read((char*) &indexNumber, sizeof(indexNumber));
        inputFile.read((char*) &genderValue, sizeof(genderValue));
        gender = static_cast<Gender>(genderValue);

        Student student(name, lastName, address, indexNumber, pesel, gender);
        students_.push_back(student);
    }

    inputFile.close();
    return "Database was successfully read from '" + fileName + "' file";
}