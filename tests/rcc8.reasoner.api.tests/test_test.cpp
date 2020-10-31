#include "gtest/gtest.h"

TEST (HelloWorld1, Assert_Null_Succeed)
    {
    ASSERT_EQ (1, 0);
    }

TEST (HelloWorld2, Assert_Null_Fail)
    {
    ASSERT_EQ (1, 1);
    }