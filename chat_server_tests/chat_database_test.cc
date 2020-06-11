// Code review content development project.
// Code style follows Google C++ Style Guide.
// (https://google.github.io/styleguide/cppguide.html)

#include "gtest/gtest.h"
#include "chat_database.h"
#include "chat_message.h"

using namespace std;
using namespace utility;
using namespace chatserver;

// Fixture class for chat_database.h testing.
class ChatDatabaseTest : public ::testing::Test {
 protected:
  ChatDatabase chat_database_;
  // Delimiter in the chat message file database.
  string_t kParsingDelimeterChatDb = UU("|");

  void SetUp() override {
    const string_t chat_message_file = UU("chat_messages.txt");
    const string_t chat_room_file = UU("chat_room.txt");
    wofstream file(chat_message_file, wofstream::out | ofstream::trunc);
    file << "1583581783|kaist|a|hihi" << endl;
    file << "1583581784|wsp|a|hello" << endl;
    file << "1583581785|kaist|b|hello world" << endl;
    file << "1583581786|wsp|c|??" << endl;
    file.close();

    file.open(chat_room_file, wofstream::out | ofstream::trunc);
    file << "a" << endl;
    file << "b" << endl;
    file << "c" << endl;
    file.close();
    chat_database_.Initialize(chat_message_file, chat_room_file);
  }
};

TEST_F(ChatDatabaseTest, Initialization_success) {
  // Check initialization fails.
  EXPECT_EQ(true, chat_database_.Initialize(UU("chat_messages.txt"), UU("chat_room.txt")));
}

// ToDo: Implement unit tests.