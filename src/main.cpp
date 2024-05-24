#include "student.hpp"
#include "database.hpp"
#include <iostream>
///////////////////////////////////////////////////////////
void printMenu();
void addStudent(Database & db);
int countDigit(long long n);
int getIndexNumber(int flag);
std::string getPESEL();
sortingType getSortType();
void getFirstLastName(std::string & firstName, std::string & Lastname);
///////////////////////////////////////////////////////////
int main(){
    Database db;
    int choice, indexNumber;
    std::string lastName, PESEL, fileName;
    sortingType type;

    do{
        printMenu();
        std::cin >> choice;
        
        switch(choice){
            case 0: break;
            case 1:
                addStudent(db);
                break;
            case 2:
                std::cout << std::endl;
                db.display();
                std::cout << std::endl;
                break;
            case 3:
                std::cout << "\nEnter a last name to search: ";
                std::cin >> lastName;
                std::cout << "\n" << db.findByLastName(lastName) << std::endl;
                break;
            case 4:
                PESEL = getPESEL();
                std::cout << "\n" << db.findByPESEL(PESEL) << std::endl;
                break;
            case 5:
                type = getSortType();
                std::cout << "\n" << db.sortByPESEL(type) << std::endl;
                break;
            case 6:
                std::cout << "\n" << db.sortByLastName() << std::endl;
                break;
            case 7:
                indexNumber = getIndexNumber(1);
                std::cout << "\n" << db.deleteByIndexNumber(indexNumber) << std::endl;
                break;
            case 8:
                std::cout << "\nEnter filename to save database: ";
                std::cin >> fileName;
                std::cout << "\n" << db.saveToFile(fileName) << std::endl;
                break;
            case 9:
                std::cout << "\nEnter filename to read database from: ";
                std::cin >> fileName;
                std::cout << "\n" << db.readFromFile(fileName) << std::endl;
                break;
            default:
                std::cout << "\nInvalid choice. Please try again.\n" << std::endl;
                break;          
        }

    }while(choice != 0);

}
////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////
void addStudent(Database & db){
    Student student;
    std::string firstName, lastName, address, pesel, gen;
    Gender gender;
    int indexNumber;

    getFirstLastName(firstName, lastName);

    std::cout << "Enter address: ";
    std::getline(std::cin, address);

    indexNumber = getIndexNumber(0);
    pesel = getPESEL();
   
    if(pesel.at(9) % 2) gender = Gender::Male;
    else gender = Gender::Female;

    Student newStudent(firstName, lastName, address, indexNumber, pesel, gender);
    if(db.add(newStudent)) std::cout << "\nStudent added successfully.\n" << std::endl;
}   
////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////
int getIndexNumber(int flag){

    int indexNumber;
    std::string index;
    bool success;

    if(flag){
        getline(std::cin, index);
    }

    do{
        success = true;
        std::cout << "Enter index number: ";
        getline(std::cin, index);

        for(unsigned int i = 0; i < index.length(); i++){
            if(index[i] < 48 || index[i] > 57) {
                std::cout << "Invalid characters entered! Allowed characters are numbers (0-9). Please try again" << std::endl;
                success = false;
                break;
            }
        }

        if (success) {
           indexNumber = std::stoi(index);
           if(countDigit(indexNumber) != 6){
                std::cout << "The index number must consist of 6 digits! Please try again." << std::endl;
                success = false;
            } 
        }

    } while(!success);

    return indexNumber;
}
////////////////////////////////////////////////////////////////////////////////////////
std::string getPESEL(){

    Student student;
    std::string pesel;
    bool success;


    do{
        success = true;
        std::cout << "Enter PESEL: ";
        getline(std::cin, pesel);

        for(unsigned int i = 0; i < pesel.length(); i++){
            if(pesel[i] < 48 || pesel[i] > 57) {
                std::cout << "Invalid characters entered! Allowed characters are numbers (0-9). Please try again" << std::endl;
                success = false;
                break;
            }
        }

        if(success) {
            if(pesel.length() != 11){
                std::cout << "The PESEL must consist of 11 digits!\n";
                success = false; 
            } 
        }

        if(success){
            student.setPESEL(pesel);
            if(!student.isPESELValid()){
                std::cout << "The pesel number given is incorrect! Please try again." << std::endl;
                success = false;
            }  
        }

    } while(!success);

    return pesel;
}
////////////////////////////////////////////////////////////////////////////////////////
sortingType getSortType(){

    sortingType type;
    std::string sortType;

    do{
        std::cout << "\nEnter a sort type (ASC or DESC): ";
        std::cin >> sortType;
        if(sortType == "ASC") {
            type = sortingType::ASC;
            break;
        } else if(sortType == "DESC") {
            type = sortingType::DESC;
            break;    
        } else std::cout << "The sort type given is incorrect! Please try again." << std::endl;

        } while(true);

    return type;
}
////////////////////////////////////////////////////////////////////////////////////////
void getFirstLastName(std::string & firstName, std::string & Lastname){
    
    
    bool success;
    getline(std::cin, firstName);

    do{
        success = true;

        std::cout << "\nEnter first name: ";
        getline(std::cin, firstName);

        for(unsigned int i = 0; i < firstName.length(); i++){
            if((firstName[i] >= 'A' && firstName[i] <= 'Z') || (firstName[i] >= 'a' && firstName[i] <= 'z'));
            else {
                std::cout << "Invalid characters entered! Allowed characters are letters (A-Z). Please try again" << std::endl;
                success = false;
                break;
            }
        }

        if(success){
            std::cout << "Enter last name: ";
            getline(std::cin, Lastname);

            for(unsigned int i = 0; i < Lastname.length(); i++){
                if((Lastname[i] >= 'A' && Lastname[i] <= 'Z') || (Lastname[i] >= 'a' && Lastname[i] <= 'z'));
                else {
                    std::cout << "Invalid characters entered! Allowed characters are letters (A-Z). Please try again" << std::endl;
                    success = false;
                    break;
                }
            }   
        }
    } while(!success);
}