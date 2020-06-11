// Code review content development project.
// Code style follows Google C++ Style Guide.
// (https://google.github.io/styleguide/cppguide.html)

#include "gtest/gtest.h"
#include "account_database.h"
#include "chat_database.h"

using namespace std;
using namespace utility;
using namespace chatserver;
using ::utility::conversions::to_utf8string;

// fixture class for testing
class AccountDatabaseTest : public ::testing::Test {
 protected:
  AccountDatabase account_database_;
  ChatDatabase chat_database_;

  // Delimiter between id and password in a file database.
  string_t kParsingDelimeterAccount = UU(",");
  // Delimiter in the chat message file database.
  string_t kParsingDelimeterChatDb = UU("|");
  // Length of nonce.
  const size_t kNonceLength = 10;
  // Nonce seed.
  const string_t kNonceValue = UU(
      "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

  void SetUp() override {
    const string_t file_name = UU("accounts.txt");
    wofstream file(file_name, wofstream::out | ofstream::trunc);
    file << "kaist" << "," << HashString(UU("12345678")) << endl;
    file << "wsp" << "," << HashString(UU("abcdefgh")) << endl;
    file << "gsis" << "," << HashString(UU("!@#$%^&*")) << endl;
    file.close();
    EXPECT_EQ(true, account_database_.Initialize(file_name));
  }

  string_t HashLoginPassword(string_t password, string_t nonce) const {
    return HashString(HashString(password) + nonce);
  }

  string_t HashString(utility::string_t string) const {
    return conversions::to_string_t(
      std::to_string(std::hash<utility::string_t>{}(string)));
  }

  string_t GenerateNonce() const {
    std::random_device device;
    std::mt19937 generator(device());
    const std::uniform_int_distribution<int>
        distribution(0, kNonceValue.size() - 1);
    string_t result;
    for (size_t i = 0; i < 10; i++) {
      result += kNonceValue.at(distribution(generator));
    }
    return result;
  }
};

TEST_F(AccountDatabaseTest, Initialization_Fail) {
  // Fail to initialization with file does not exist.
  EXPECT_EQ(false, account_database_.Initialize(UU("abcdedef.txt")));
}

// ToDo: Implement unit tests.