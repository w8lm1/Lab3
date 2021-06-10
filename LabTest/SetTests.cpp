#include "pch.h"
#include "../LabMain/Set.h"
#include "../LabMain/Person.h"
#include "../LabMain/BinaryTree.h"
#include <string>
#include "gtest/gtest.h"



using namespace std;

int MapCheck1(int a) {
    return a * 3;
}
string MapCheckString1(string a) {
    return a + " aboba";
}
bool IsEven1(int a) {
    return a % 2 == 0;
}
int ReduceCheck1(int a, int b) {
    return a + b;
}

TEST(SetTest, Init) {
    Set<int> set = Set<int>();
    EXPECT_ANY_THROW(set.Delete(0));
    EXPECT_ANY_THROW(set.Contains((int)nullptr));
    EXPECT_ANY_THROW(set.Contains(1));
    set.Add(0);
    set.Add(1);
    set.Add(2);
    set.Add(3);
    set.Add(4);

    Set<int> set1 = Set<int>({ 0, 1, 2, 3, 4 });
    ASSERT_TRUE(set.IsSubSet(set1));
}

TEST(SetTest, Add_Delete) {
    Set<int> set = Set<int>();
    set.Add(0);
    set.Add(1);
    set.Add(2);
    set.Add(3);
    set.Delete(0);
    set.Delete(3);
    ASSERT_TRUE(set.Contains(2));
    ASSERT_FALSE(set.Contains(3));

    Set<int> set1 = Set<int>({ 0, 1, 2, 3, 4 });
    ASSERT_TRUE(set1.IsSubSet(set));
}

TEST(SetTest, SubSet) {
    Set<int> set = Set<int>({ 2, 4 });
    Set<int> set1 = Set<int>({ 0, 1, 2, 3, 4 });
    ASSERT_TRUE(set1.IsSubSet(set));


    Set<Person> people = Set<Person>({ Person({1, 01}, "Oleg", "Mid", "Punk", time(nullptr)),
                                      Person({1, 02}, "Lul", "Papa", "Go", time(nullptr)),
                                      Person({1, 03}, "Lol", "Lul", "Kek", time(nullptr)),
                                      Person({1, 04}, "UwU", "Ok", "No", time(nullptr)) });
    Set<Person> people1 = Set<Person>({ Person({1, 01}, "Oleg", "Mid", "Punk", time(nullptr)),
                                      Person({1, 04}, "UwU", "Ok", "No", time(nullptr)) });
    ASSERT_TRUE(people.IsSubSet(people1));
} 

TEST(SetTest, Map) {
    Set<int> set = Set<int>({ -4, -3, -2, 0 });
    Set<int> mapSet = set.MapSet(MapCheck1);
    ASSERT_TRUE(mapSet.IsEqual(Set<int>({ -12, -9, -6, 0 })));

    Set<string> setString = Set<string>({ "", "0" });
    Set<string> mapSetString = setString.MapSet(MapCheckString1);
    ASSERT_TRUE(mapSetString.IsEqual(Set<string>({ " aboba", "0 aboba" })));
}

TEST(SetTest, Where) {
    Set<int> set = Set<int>({ -4, -3, -2, 0 });
    Set<int> mapSet = set.WhereSet(IsEven1);
    ASSERT_TRUE(mapSet.IsEqual(Set<int>({ -4, -2, 0 })));
}

TEST(SetTest, Reduce) {
    Set<int> set = Set<int>({ -4, -3, -2, 0 });
    int reduce = set.ReduceSet(ReduceCheck1, 0);
    ASSERT_EQ(reduce, -9);
}

TEST(SetTest, Inersection) {
    Set<int> set = Set<int>({ 1, 2, 3, 4, 5 });
    Set<int> set1 = Set<int>({ 4, 5, 6, 7, 8 });
    Set<int> intersection = set & set1;
    ASSERT_TRUE(intersection.IsSubSet(Set<int>({ 4, 5 })));
}

TEST(SetTest, Union) {
    Set<int> set = Set<int>({ 1, 2, 3, 4, 5 });
    Set<int> set1 = Set<int>({ 4, 5, 6, 7, 8 });
    Set<int> uni = set | set1;
    ASSERT_TRUE(uni.IsSubSet(Set<int>({ 1, 2, 3, 4, 5, 6, 7, 8 })));
}

TEST(SetTest, Substraction) {
    Set<int> set = Set<int>({ 1, 2, 3, 4, 5 });
    Set<int> set1 = Set<int>({ 4, 5, 6, 7, 8 });
    Set<int> sub = set - set1;
    ASSERT_TRUE(sub.IsSubSet(Set<int>({ 1, 2, 3 })));
}

TEST(SetTest, EqualTest) {
    Set<int> set = Set<int>({ 1, 2, 3, 4, 5 });
    Set<int> set1 = Set<int>(set);
    ASSERT_TRUE(set1 == set);
}