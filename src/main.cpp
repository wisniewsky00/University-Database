#include "student.hpp"
#include "database.hpp"
#include <iostream>
///////////////////////////////////////////////////////////
void printMenu();
void addStudent(Database & db);
int countDigit(long long n);
///////////////////////////////////////////////////////////
int main(){
    Database db;
    int choice;
    std::string lastName, PESEL;

    do{
        printMenu();
        std::cin >> choice;
        
        switch(choice){
            case 1:
                addStudent(db);
                break;
            case 2:
                std::cout << std::endl;
                db.display();
                std::cout << std::endl;
                break;
            case 3:
                std::cout << "\nEnter a last name to search for: ";
                std::cin >> lastName;
                std::cout << "\n" << db.findByLastName(lastName) << std::endl;
                break;
            case 4:
                std::cout << "\nEnter a PESEL to search for: ";
                std::cin >> PESEL;
                std::cout << "\n" << db.findByPESEL(PESEL) << std::endl;
                break;
        }

    }while(choice != 0);

}
///////////////////////////////////////////////////////////
void printMenu(){

    std::cout << "University Database Menu\n"
    << "1. Add new student\n"
    << "2. Show database\n"
    << "3. Search by last name\n"
    << "4. Search by PESEL\n"
    << "5. Sort by PESEL\n"
    << "6. Sort by last name\n"
    << "7. Delete by index number\n"
    << "8. Save database to file\n"
    << "9. Read database from file\n"
    << "0. Exit\n"
    << "Enter your choice: ";
}
///////////////////////////////////////////////////////////
void addStudent(Database & db){
    Student student;
    std::string firstName, lastName, address, pesel, gen;
    Gender gender;
    int indexNumber;

    std::cout << "\nEnter first name: ";
    std::cin >> firstName;
    std::cout << "Enter last name: ";
    std::cin >> lastName;
    std::cout << "Enter address: ";
    std::getline(std::cin, address);
    std::getline(std::cin, address);

    do{
        std::cout << "Enter index number: ";
        std::cin >> indexNumber;
        if(countDigit(indexNumber) != 6){
            std::cout << "The index number must consist of 6 digits! Please try again." << std::endl;
        } else break;

    } while(true);

    do{
       std::cout << "Enter PESEL: ";
       std::cin >> pesel;
       student.setPESEL(pesel);
       if(student.isPESELValid()) break;
       else{
          std::cout << "The pesel number given is incorrect! Please try again." << std::endl;
       }
    } while(true);
    
    do{
       std::cout << "Enter gender (Male or Female): ";
       std::cin >> gen;
       if(gen == "Male"){
            gender = Gender::Male;
            break;
       }
       else if(gen == "Female"){
            gender = Gender::Female;
            break;
       }
       else{
            std::cout << "The gender name given is incorrect! Please try again." << std::endl;
       }
    } while(true);

    Student newStudent(firstName, lastName, address, indexNumber, pesel, gender);
    if(db.add(newStudent)) std::cout << "\nStudent added successfully.\n" << std::endl;
}   
///////////////////////////////////////////////////////////
int countDigit(long long n)
{
    if (n == 0)
        return 1;
    int count = 0;
    while (n != 0) {
        n = n / 10;
        ++count;
    }
    return count;
}
///////////////////////////////////////////////////////////