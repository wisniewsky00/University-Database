# University-Database
## Description
The University-Database project is a C++ application designed to manage and organize university-related data through CRUD (Create, Read, Update, Delete) operations. This project simulates a database without using a real database managment system like SQL, making it a great tool for understanding basic database operations and data structures.

## Table of Contents
1. [Features](#features)
2. [Technologies Used](#technologies-used)
3. [Installation](#installation)
4. [Usage](#usage)
5. [License](#license)

## Features
- **Student records**: Storing student records with structure: Name, Last Name, Address, Index number, PESEL, Gender.
- **Add new students**: Adding new students to the database and also checking if the student already exists in the database.
- **Show database**: Display the entire database of student records
- **Search by last name**: Search for students by their last name.
- **Search by PESEL**: Search for students by their PESEL (Personal Identification Number).
- **Sort by PESEL**: Sort the student records based on their PESEL in ascending or descending order.
- **Sort by last name**: Sort the student records alphabetically by last name.
- **Delete by index number**: Delete a student record based on their index number.
- **Check validity of PESEL**: Verify if a PESEL number is valid according to predefined rules.
- **Save and read database from file**: Save the database to a file and read from the file for future use.

## Technologies Used
- **Programming Language**: C++
- **Build Systems**: CMake, Make
- **Testing**: GTest (Google Test) based on TDD (Test-Driven Development) technique
- **Version Control**: Git
- **Data Structures**: Vectors, Lambda expressions
- **IDE**: Visual Studio Code (VSCode)

## Installation
To set up the University-Database project on your local machine, follow these steps:

1. **Clone the repository**:
    ```bash
    git clone https://github.com/wisniewsky00/University-Database.git
    cd University-Database
    ```
2. **Create a build directory**:
   ```bash
   mkdir build
   cd build
   ```
3. **Generate the Makefile using CMake**:
   ```bash
   cmake ..
   ```
4. **Compile the application**:
   ```bash
   make
   ```
After completing these steps, the application will be compiled and ready to use.

## Usage
Here are some basic instructions on how to use the University-Database:

1. **Run the application**:
   ```bash
   ./student-database
   ```
   This will start the application and display a menu with the following options:
    ```
    University Database Menu
    1. Add new student
    2. Show database
    3. Search by last name
    4. Search by PESEL
    5. Sort by PESEL
    6. Sort by last name
    7. Delete by index number
    8. Save database to file
    9. Read database from file
    0. Exit
    Enter your choice:
    ```
2. **Run the tests**:
   ```bash
   ./student-database-ut
   ```
3. **Preparing for tests**:
    - To ensure all tests pass, you need to create an empty file called 'emptyFile' in the 'build' directory. This is required for the test called "ReadDbFromFile" which checks if the file is empty.
        ```bash
        touch build/emptyFile
        ```
    - The test "SaveDbToFile" saves the database to a file named "Database1" in the `build` directory. Make sure this file does not already exist before running the test, or delete it if it was previously created.
       ```bash
       # Example to run the specific test
       ./student-database-ut --gtest_filter=DatabaseTest.SaveDbToFile
   
       # Ensure the file does not exist before running the test
       cd build
       rm Database1
       ```
    - Make sure to delete or rename files created during the tests to avoid conflicts.

By following these steps, you can run the application and tests successfully, ensuring that the environment is correctly set up for all test cases. 

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
