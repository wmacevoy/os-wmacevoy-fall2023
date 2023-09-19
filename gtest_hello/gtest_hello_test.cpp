#include "gtest/gtest.h"

#include "gtest_hello.h"

TEST(GREET,ME)
{
  std::string who = "me";

  std::string expect = "hello, me";
  std::string result = greet(who);

  ASSERT_EQ(expect,result);
}