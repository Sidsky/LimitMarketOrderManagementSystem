#include "gtest/gtest.h"
#include "../LMOMS.h"

TEST(OrderPlacement, AskOrders) {
    LM_OMS OMS;
    string order = "A,100001,S,10,1075";
    ASSERT_TRUE(OMS.execute_order(order).str() == "New order added for price HKD1075\n");

    order = "A,100002,S,3,1075";
    EXPECT_TRUE(OMS.execute_order(order).str() == "New order added at the end of the queue of price HKD1075\n");
}

TEST(OrderPlacement, BuyOrders) {
    LM_OMS OMS;
    string order = "A,100001,B,10,1075";

    ASSERT_TRUE(OMS.execute_order(order).str() == "New order added for price HKD1075\n");

    order = "A,100002,B,3,1075";
    EXPECT_TRUE(OMS.execute_order(order).str() == "New order added at the end of the queue of price HKD1075\n");
}

class LM_OMS_Test : public :: testing :: Test {
protected:
    void SetUp() override { // Setting up order book as per the example in the question
        MS_.execute_order("A,100001,S,5,110");
        MS_.execute_order("A,100002,S,10,110");
        MS_.execute_order("A,100003,S,3,105");
        MS_.execute_order("A,100004,S,7,105");
        MS_.execute_order("A,100005,B,4,100");
        MS_.execute_order("A,100006,B,6,100");
        MS_.execute_order("A,100007,B,10,90");
        MS_.execute_order("A,100008,B,2,90");
        MS_.execute_order("A,100009,B,3,90");
    }
    LM_OMS MS_;
};

TEST_F(LM_OMS_Test, AggresiceOrders) {
    string actual = MS_.execute_order("A,100010,B,4,105").str();
    string expected = "3 share(s) sold at 105 HKD\n1 share(s) sold at 105 HKD\n";

    ASSERT_TRUE(actual == expected);

    actual = MS_.execute_order("A,100011,S,23,80").str();
    expected = "4 share(s) sold at 100 HKD\n6 share(s) sold at 100 HKD\n10 share(s) sold at 90 HKD\n2 share(s) sold at 90 HKD\n1 share(s) sold at 90 HKD\n";
    ASSERT_TRUE(actual == expected);

    actual = MS_.execute_order("A,100012,B,8,107").str();
    expected = "6 share(s) sold at 105 HKD\nNew order added for price HKD107\n";
    ASSERT_TRUE(actual == expected);
}

TEST (Deletion, EmptyDelete) {
    LM_OMS OMS;
    string order = "X,100001,B,10,1075";
    ASSERT_TRUE(OMS.execute_order(order).str() == "Cannot delete order. It has either been settled or was never placed\n");
}

TEST (Deletion, PartialDelete) {
    LM_OMS OMS;
    string order = "A,100001,S,10,1075";
    OMS.execute_order(order);

    order = "A,100002,B,4,1090";
    OMS.execute_order(order);

    order = "X,100001,S,10,1075";
    ASSERT_TRUE(OMS.execute_order(order).str() == "Partial ordered has already been fulfilled. Remaining 6 share(s) returned\n");
}

TEST (Deletion, SeccessfullDelete) {
    LM_OMS OMS;
    string order = "A,100001,S,10,1075";
    OMS.execute_order(order);

    order = "X,100001,S,10,1075";
    ASSERT_TRUE(OMS.execute_order(order).str() == "Delete successful. All share(s) returned\n");
}
