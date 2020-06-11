// Code review content development project.
// Code style follows Google C++ Style Guide.
// (https://google.github.io/styleguide/cppguide.html)

#include "chat_server.h"
#include "gtest/gtest.h"
#include "cpprest/http_client.h"
#include "chat_server_test_fixture.h"

using namespace std;
using namespace utility;
using namespace chatserver;
using namespace chatservertests;
using namespace web;
using ::concurrency::task_status;
using ::web::http::client::http_client;
using ::web::http::http_response;
using ::web::json::value;

TEST_F(ChatServerTest, Post_CreateAccount_Success) {
  ostringstream_t buf;
  // Test for success to create an account
  buf << "account" << UU("?id=")
      << "wsplab" << UU("&password=") << HashString(UU("bestkaistlab"));
  http_response response = http_client_->request(
      http::methods::POST, uri::encode_uri(buf.str())).get();
  EXPECT_EQ(response.status_code(), http::status_codes::OK);
}

// ToDo: Implement unit tests.