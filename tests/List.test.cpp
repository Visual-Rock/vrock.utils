#include <gtest/gtest.h>

#include <vrock/utils/List.hpp>

#include <string>

struct Person {
    int age;
    std::string name;

    friend bool operator==(const Person& lhs, const Person& rhs)
        { return lhs.age == rhs.age && lhs.name == rhs.name; }

    friend bool operator<(const Person& a, const Person& b)
        { return a.age < b.age; }
};

TEST(ListCount, BasicAssertions) {
    auto list = vrock::utils::List<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    EXPECT_EQ(list.count(), 9);
}

TEST(ListForEach, BasicAssertions) {
    auto list = vrock::utils::List<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9 }); // 45
    int i = 0;
    list.for_each([&](int n){
        i += n;
    });
    EXPECT_EQ(i, 45);
}

TEST(ListAggregate, BasicAssertions) {
    auto list = vrock::utils::List<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    EXPECT_EQ(list.aggregate<int>([](int a, int b){ return a + b; }), 45);
}

TEST(ListLet, BasicAssertions) {
    auto list = vrock::utils::List<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    auto cplist = vrock::utils::List<int>();

    EXPECT_NE(list, cplist);
    list.let(&cplist);
    EXPECT_EQ(list, cplist);
}

TEST(ListContains, BasicAssertions) {
    auto list = vrock::utils::List<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    EXPECT_EQ(list.contains(5), true);
    EXPECT_EQ(list.contains(10), false);
}

TEST(ListAny, BasicAssertions) {
    auto list = vrock::utils::List<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    EXPECT_EQ(list.any(), true);
    EXPECT_EQ(list.any([](int i){ return i % 2; }), true);
}

TEST(ListAll, BasicAssertions) {
    auto list = vrock::utils::List<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    EXPECT_EQ(list.all([](int i){ return i > 0 && i < 10; }), true);
    EXPECT_EQ(list.all([](int i){ return i > 0 && i < 5; }), false);
}

TEST(ListSequenceEqual, BasicAssertions) {
    auto list1 = vrock::utils::List<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    auto list2 = vrock::utils::List<int>({ 1, 2, 3, 4, 5, 6, 7, 2, 9 });
    auto list3 = vrock::utils::List<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });

    EXPECT_EQ(list1.sequence_equal(list2), false);
    EXPECT_EQ(list1.sequence_equal(list3), true);
}

TEST(ListConcat, BasicAssertions) {
    auto list1 = vrock::utils::List<int>({ 10, 1, 2, 3, 4 });
    auto list2 = vrock::utils::List<int>({ 5, 6, 7, 8, 9 });
    auto list3 = vrock::utils::List<int>({ 10, 1, 2, 3, 4, 5, 6, 7, 8, 9 });

    EXPECT_EQ(list1.concat(list2), list3);
}

TEST(ListSkip, BasicAssertions) {
    auto list1 = vrock::utils::List<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    auto list2 = vrock::utils::List<int>({ 6, 7, 8, 9 });

    EXPECT_EQ(list1.skip(5), list2);
    EXPECT_EQ(list1.skip_while([](int i){ return i <= 5; }), list2);
}

TEST(ListTake, BasicAssertions) {
    auto list1 = vrock::utils::List<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    auto list2 = vrock::utils::List<int>({ 1, 2, 3, 4, 5 });

    EXPECT_EQ(list1.take(5), list2);
    EXPECT_EQ(list1.take_while([](int i){ return i <= 5; }), list2);
}

TEST(ListRevers, BasicAssertions) {
    auto list1 = vrock::utils::List<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    auto list2 = vrock::utils::List<int>({ 9, 8, 7, 6, 5, 4, 3, 2, 1 });

    EXPECT_EQ(list1.revers(), list2);
}

TEST(ListFirst, BasicAssertions) {
    auto list = vrock::utils::List<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });

    EXPECT_THROW(list.first([](int i){ return i == 10; }), std::runtime_error);
    EXPECT_EQ(list.first([](int i){ return i == 3; }), 3);
    EXPECT_EQ(list.first_or_default([](int i){ return i == 10; }, 10), 10);
    EXPECT_EQ(list.first_or_default([](int i){ return i == 3; }), 3);
}

TEST(ListLast, BasicAssertions) {
    auto list = vrock::utils::List<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });

    EXPECT_THROW(list.last([](int i){ return i == 10; }), std::runtime_error);
    EXPECT_EQ(list.last([](int i){ return i == 3; }), 3);
    EXPECT_EQ(list.last_or_default([](int i){ return i == 10; }, 10), 10);
    EXPECT_EQ(list.last_or_default([](int i){ return i == 3; }), 3);
}

TEST(ListSingle, BasicAssertions) {
    auto list = vrock::utils::List<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 9 });

    EXPECT_THROW(list.single([](int i){ return i == 10; }), std::runtime_error);
    EXPECT_THROW(list.single([](int i){ return i == 9; }), std::runtime_error);
    EXPECT_EQ(list.single([](int i){ return i == 3; }), 3);
    EXPECT_THROW(list.single_or_default([](int i){ return i == 9; }), std::runtime_error);
    EXPECT_EQ(list.single_or_default([](int i){ return i == 3; }), 3);
    EXPECT_EQ(list.single_or_default([](int i){ return i == 10; }, 10), 10);
}

TEST(ListSelect, BasicAssertions) {
    auto list = vrock::utils::List<std::pair<int, int>>({ 
        { 1, 4 }, { 2, 6 }, { 3, 7 },
        { 4, 4 }, { 5, 6 }, { 6, 7 },
        { 7, 4 }, { 8, 6 }, { 9, 7 },
    });
    auto res = vrock::utils::List<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });

    EXPECT_EQ(list.select<int>([](std::pair<int, int> i) { return i.first; }), res);
}

TEST(ListWhere, BasicAssertions) {
    auto list = vrock::utils::List<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    auto res = vrock::utils::List<int>({ 1, 3, 5, 7, 9 });
    EXPECT_EQ(list.where([](int i){ return i % 2; }), res);
}

TEST(ListJoin, BasicAssertions) {
    auto list1 = vrock::utils::List<std::pair<int, int>>({ 
        { 1, 4 }, { 2, 6 }, { 3, 7 },
        { 4, 4 }, { 5, 6 }, { 6, 7 },
        { 7, 4 }, { 8, 6 }, { 9, 7 },
    });
    auto list2 = vrock::utils::List<std::pair<int, std::string>>({ 
        { 1, "4" }, { 2, "6" }, { 3, "7" },
        { 4, "4" }, { 5, "6" }, { 6, "7" },
        { 7, "4" }, { 8, "6" }, { 9, "7" },
    });
    auto res = list1.join<std::pair<int, std::string>, std::pair<int, std::string>>(
        list2,
        [](auto a, auto b){ return a.first == b.first; },
        [](auto a, auto b){ return std::pair<int, std::string>(a.second, b.second);}
    );
    auto exp = vrock::utils::List<std::pair<int, std::string>>({ 
        { 4, "4" }, { 6, "6" }, { 7, "7" },
        { 4, "4" }, { 6, "6" }, { 7, "7" },
        { 4, "4" }, { 6, "6" }, { 7, "7" },
    });
    
    EXPECT_EQ(res, exp);
}

TEST(ListGroupBy, BasicAssertions) {
    auto list = vrock::utils::List<Person>({
        { 23, "John" },
        { 22, "James" },
        { 38, "William" },
        { 22, "Amelia" },
        { 38, "Emma" }
    });

    auto exp = std::map<int, vrock::utils::List<Person>>();
    exp[22] = vrock::utils::List<Person>(std::vector<Person>({ { 22, "James" }, { 22, "Amelia" } }));
    exp[23] = vrock::utils::List<Person>(std::vector<Person>({ { 23, "John" } }));
    exp[38] = vrock::utils::List<Person>(std::vector<Person>({ { 38, "William" }, { 38, "Emma" } }));

    auto res = list.group_by(&Person::age);

    EXPECT_EQ(res[22], exp[22]);
    EXPECT_EQ(res[23], exp[23]);
    EXPECT_EQ(res[38], exp[38]);
}

TEST(ListOrderBy, BasicAssertions) {
    auto list = vrock::utils::List<int>({ 9, 2, 6, 3, 5, 8, 4, 7, 1 });
    auto exp = vrock::utils::List<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });

    list.order_by([](int a, int b){ return a < b; });

    EXPECT_EQ(list, exp);
}

TEST(ListDistinct, BasicAssertions) {
    auto list = vrock::utils::List<int>({ 1, 1, 2, 2, 2, 3, 4, 4 });
    auto exp = vrock::utils::List<int>({ 1, 2, 3, 4 });

    EXPECT_EQ(list.distinct(), exp);
}

TEST(ListUnion, BasicAssertions) {
    auto list1 = vrock::utils::List<int>({ 1, 5, 6, 9 });
    auto list2 = vrock::utils::List<int>({ 4, 5, 7, 11 });

    auto exp = vrock::utils::List<int>({ 1,5,6,9,4,7,11 });

    EXPECT_EQ(list1.union_list(list2), exp);
}

TEST(ListIntersect, BasicAssertions) {
    auto list1 = vrock::utils::List<int>({ 1, 5, 6, 9 });
    auto list2 = vrock::utils::List<int>({ 4, 5, 7, 11 });
    auto exp = vrock::utils::List<int>({ 5 });

    EXPECT_EQ(list1.intersect(list2), exp);
}

TEST(ListExcept, BasicAssertions) {
    auto list1 = vrock::utils::List<int>({ 1, 5, 6, 9 });
    auto list2 = vrock::utils::List<int>({ 4, 5, 7, 11 });
    auto exp = vrock::utils::List<int>({ 1, 6, 9 });

    EXPECT_EQ(list1.except(list2), exp);
}

TEST(ListTo, BasicAssertions) {
    auto list = vrock::utils::List<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    
    auto expv = std::vector<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    auto expd = std::deque<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    auto expf = std::forward_list<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    auto expl = std::list<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });

    EXPECT_EQ(list.to_vector(), expv);
    EXPECT_EQ(list.to_deque(), expd);
    EXPECT_EQ(list.to_forward_list(), expf);
    EXPECT_EQ(list.to_list(), expl);
}

TEST(ListSelectMany, BasicAssertions) {
    auto l1 = vrock::utils::List<vrock::utils::List<int>>();
    l1.push_back(vrock::utils::List<int>({ 1, 2, 3 }));
    l1.push_back(vrock::utils::List<int>({ 4, 5, 6 }));
    l1.push_back(vrock::utils::List<int>({ 7, 8, 9 }));

    auto l2 = vrock::utils::List<std::vector<int>>({
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 }
    });
    auto exp = vrock::utils::List<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });

    EXPECT_EQ(vrock::utils::select_many(l1), exp);
    EXPECT_EQ(vrock::utils::select_many(l2), exp);
}