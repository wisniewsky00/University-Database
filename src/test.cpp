#include <gtest/gtest.h>
#include "student.hpp"
#include "database.hpp"

struct DatabaseTest : ::testing::Test
{
  Database db;
  Student adam;
  Student natalia;
  Student kamil;

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
          Gender::Male)
  { }
};

TEST_F(DatabaseTest, DisplayEmptyDb) {

  auto content = db.show();
  auto expected = "";
  EXPECT_EQ(content, expected);
}

TEST_F(DatabaseTest, DisplayNonEmptyDb) 
 {
  db.add(adam);
  db.add(natalia);
  // check adding the same person twice

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
  expected = "The lastname 'Nowak' was not found in the database";

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

