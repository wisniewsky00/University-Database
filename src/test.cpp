#include <gtest/gtest.h>
#include "student.hpp"
#include "database.hpp"

struct DatabaseTest : ::testing::Test
{
  Database db;
  Student adam;
  Student natalia;
  Student kamil;
  Student marcel;

  DatabaseTest(): adam("Adam",
          "Kowalski", 
          "ul. Dobra 14, 00-200 Warszawa",
          123456,
          "11223344567",
          Gender::Male),

          natalia("Natalia",
          "Nowak",
          "ul. Mila 3, 00-200 Warszawa",
          654321,
          "76544332211",
          Gender::Female),

          kamil("Kamil",
          "Kowalski",
          "ul. Polna 8, 00-200 Warszawa",
          149321,
          "11332244567",
          Gender::Male),

          marcel("Marcel",
          "Bogucki",
          "ul. Warszawska 19, 00-200 Warszawa",
          105305,
          "55533322266",
          Gender::Male)
  { }
};

TEST_F(DatabaseTest, DisplayEmptyDb) {

  auto content = db.show();
  auto expected = "The database is empty.\n";
  EXPECT_EQ(content, expected);
}

TEST_F(DatabaseTest, DisplayNonEmptyDb) 
 {
  db.add(adam);
  db.add(natalia);

  auto content = db.show();
  auto expected = "Adam Kowalski; ul. Dobra 14, 00-200 Warszawa; 123456; 11223344567; Male\n"
                  "Natalia Nowak; ul. Mila 3, 00-200 Warszawa; 654321; 76544332211; Female\n"; 
                  
  EXPECT_EQ(content, expected);
}

TEST_F(DatabaseTest, FindByLastName)
{
  db.add(adam);
  auto content = db.findByLastName("Kowalski");
  auto expected = "Adam Kowalski; ul. Dobra 14, 00-200 Warszawa; 123456; 11223344567; Male\n";
  EXPECT_EQ(content, expected);

  content = db.findByLastName("Nowak");
  expected = "The lastname 'Nowak' was not found in the database.\n";

  db.add(natalia);
  content = db.findByLastName("Nowak");
  expected = "Natalia Nowak; ul. Mila 3, 00-200 Warszawa; 654321; 76544332211; Female\n";
  EXPECT_EQ(content, expected);


  db.add(kamil);
  content = db.findByLastName("Kowalski");
  expected = "Adam Kowalski; ul. Dobra 14, 00-200 Warszawa; 123456; 11223344567; Male\n"
             "Kamil Kowalski; ul. Polna 8, 00-200 Warszawa; 149321; 11332244567; Male\n";

  EXPECT_EQ(content, expected);
}

TEST_F(DatabaseTest, FindyByPESEL)
{
  db.add(adam);

  auto content = db.findByPESEL("11223344567");
  auto expected = "Adam Kowalski; ul. Dobra 14, 00-200 Warszawa; 123456; 11223344567; Male\n";
  EXPECT_EQ(content, expected);

  content = db.findByPESEL("11223344568");
  expected = "Student with PESEL '11223344568' was not found in the database.\n";

}

TEST_F(DatabaseTest, SortByPESEL)
{
  db.add(adam);
  db.add(natalia);
  db.add(kamil);

  auto content = db.sortByPESEL(sortingType::ASC);
  auto expected = "Adam Kowalski; ul. Dobra 14, 00-200 Warszawa; 123456; 11223344567; Male\n"
                  "Kamil Kowalski; ul. Polna 8, 00-200 Warszawa; 149321; 11332244567; Male\n"
                  "Natalia Nowak; ul. Mila 3, 00-200 Warszawa; 654321; 76544332211; Female\n";
  EXPECT_EQ(content, expected);

  content = db.sortByPESEL(sortingType::DESC);
  expected = "Natalia Nowak; ul. Mila 3, 00-200 Warszawa; 654321; 76544332211; Female\n"
             "Kamil Kowalski; ul. Polna 8, 00-200 Warszawa; 149321; 11332244567; Male\n"
             "Adam Kowalski; ul. Dobra 14, 00-200 Warszawa; 123456; 11223344567; Male\n";
  EXPECT_EQ(content, expected);
}

TEST_F(DatabaseTest, SortByLastName)
{
  db.add(adam);
  db.add(kamil);
  db.add(natalia);

  auto content = db.sortByLastName();
  auto expected = "Adam Kowalski; ul. Dobra 14, 00-200 Warszawa; 123456; 11223344567; Male\n"
                  "Kamil Kowalski; ul. Polna 8, 00-200 Warszawa; 149321; 11332244567; Male\n"
                  "Natalia Nowak; ul. Mila 3, 00-200 Warszawa; 654321; 76544332211; Female\n";
  EXPECT_EQ(content, expected);

  db.add(marcel);

  content = db.sortByLastName();
  expected = "Marcel Bogucki; ul. Warszawska 19, 00-200 Warszawa; 105305; 55533322266; Male\n"
             "Adam Kowalski; ul. Dobra 14, 00-200 Warszawa; 123456; 11223344567; Male\n"
             "Kamil Kowalski; ul. Polna 8, 00-200 Warszawa; 149321; 11332244567; Male\n"
             "Natalia Nowak; ul. Mila 3, 00-200 Warszawa; 654321; 76544332211; Female\n";
  EXPECT_EQ(content, expected);
}

TEST_F(DatabaseTest, DeleteByIndexNumber)
{
  db.add(adam);
  db.add(kamil);
  db.add(natalia);

  auto content = db.deleteByIndexNumber(123456);
  auto expected = "Student with index number '123456' was deleted from database.\n";

  content = db.show();
  expected = "Kamil Kowalski; ul. Polna 8, 00-200 Warszawa; 149321; 11332244567; Male\n"
             "Natalia Nowak; ul. Mila 3, 00-200 Warszawa; 654321; 76544332211; Female\n";
  EXPECT_EQ(content, expected);

  content = db.deleteByIndexNumber(123456);
  expected = "Student with index number '123456' was not found in the database.\n";
  EXPECT_EQ(content, expected);
}

TEST_F(DatabaseTest, ValidatePESEL)
{
  Student marta("Marta", "Janowska", 
                "ul. Sucha 1, 00-200 Warszawa", 140012, 
                "12345678901", Gender::Female);

  auto content = marta.isPESELValid();
  auto expected = false;
  EXPECT_EQ(content, expected);

  Student rafal("Rafal", "Dobry",
                "ul Lesna 21, 00-200 Warszawa", 567102,
                "55030101230", Gender::Male);
  
  content = rafal.isPESELValid();
  expected = true;
  EXPECT_EQ(content, expected);
}

TEST_F(DatabaseTest, SaveDbToFile)
{
  auto content = db.saveToFile("Database0");
  auto expected = "Database is empty.\n";

  db.add(adam);
  db.add(kamil);
  db.add(natalia);

  content = db.saveToFile("Database1");
  expected = "File 'Database1' was successfully created.\n";
  EXPECT_EQ(content, expected);

  content = db.saveToFile("Database1");
  expected = "File 'Database1' already exists.\n";;
  EXPECT_EQ(content, expected);
}

TEST_F(DatabaseTest, ReadDbFromFile)
{
  auto content = db.readFromFile("WrongFileName");
  auto expected = "Failed to open file 'WrongFileName' for reading\n";
  EXPECT_EQ(content, expected);

  content = db.readFromFile("emptyFile");
  expected = "File 'emptyFile' is empty.\n";
  EXPECT_EQ(content, expected);

  content = db.readFromFile("Database1");
  expected = "Database was successfully read from 'Database1' file.\n";
  EXPECT_EQ(content, expected);

  content = db.show();
  expected = "Adam Kowalski; ul. Dobra 14, 00-200 Warszawa; 123456; 11223344567; Male\n"
             "Kamil Kowalski; ul. Polna 8, 00-200 Warszawa; 149321; 11332244567; Male\n"
             "Natalia Nowak; ul. Mila 3, 00-200 Warszawa; 654321; 76544332211; Female\n";
  EXPECT_EQ(content, expected);
}

