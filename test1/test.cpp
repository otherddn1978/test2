#include "gtest/gtest.h"

TEST (TESTS1, test1)
{
    ASSERT_TRUE (1==1);
}

TEST (TESTS1, test2)
{
    ASSERT_TRUE (1!=2);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}