// Code review content development project.
// Code style follows Google C++ Style Guide.
// (https://google.github.io/styleguide/cppguide.html)

#include "chat_client.h"

#include <cstdlib>
#include <stdio.h>

#include "chat_client_test_fixture.h"
#include "gtest/gtest.h"

using namespace std;
using namespace utility;
using namespace chatclient;

TEST_F(ChatClientTest, SignupTest_Success) {
  FILE *f1 = nullptr;
  // Signup success.
  // Mimic user's keyboard input.
  // Enter the contents of the file in C++ standard input.
  EXPECT_EQ(0, fopen_s(&f1, "test_input.txt", "w"));
  fputs("signup\n", f1);
  fputs("test\n", f1);
  fputs("12345678\n", f1);
  fputs("12345678\n", f1);
  fputs("exit\n", f1);
  fclose(f1);
  freopen_s(&f1, "test_input.txt", "r", stdin);
  chat_client_ = GetChatClient();
  string_t standard_output = GetStandardOutputFromChatClient(chat_client_);
  fclose(f1);
  EXPECT_NE(string_t::npos, standard_output.find(UU("Success to signup")));
}

// ToDo: Implement unit tests.