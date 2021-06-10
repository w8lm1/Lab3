#include "pch.h"
#include "../LabMain/Person.h"
#include "gtest/gtest.h"
#include <string>

TEST(PersonTest, Init) {
    Person person = Person();
    EXPECT_NO_THROW(person.GetFullName());
    EXPECT_NO_THROW(person.GetBirthDate());
    EXPECT_NO_THROW(person.GetID());
}

TEST(PersonTest, Equality) {
    Person person = Person({ 1, 1 }, "Shreder", "Oroku", "Saki", 0);
    Person person1 = Person({ 1, 1 }, "Shreder", "Oroku", "Saki", 0);
    ASSERT_TRUE(person == person1);
} 
