#include "gtest/gtest.h"
#include "../LM_OMS.h"

//class LM_OMS_Test : public :: testing :: Test {
//    LM_OMS MS_
//};

TEST(A,B){
    LM_OMS OMS;

    string order = "X,100001,S,10,1075";

    EXPECT_TRUE(OMS.execute_order(order).str()=="Cannot delete order. It has either been settled or was never placed.\n");
}

TEST(OrderPlacement, AskOrders){
    LM_OMS OMS;
    string order = "A,100001,S,10,1075";
    ASSERT_TRUE(OMS.execute_order(order).str() == "New order added for price HKD1075\n");

    order = "A,100002,S,3,1075";
    EXPECT_TRUE(OMS.execute_order(order).str() == "New order added at the end of the queue of price HKD1075\n");
}

TEST(OrderPlacement, BuyOrders){
    LM_OMS OMS;
    string order = "A,100001,B,10,1075";

    ASSERT_TRUE(OMS.execute_order(order).str() == "New order added for price HKD1075\n");

    order = "A,100002,B,3,1075";
    EXPECT_TRUE(OMS.execute_order(order).str() == "New order added at the end of the queue of price HKD1075\n");
}