// Code review content development project.
// Code style follows Google C++ Style Guide.
// (https://google.github.io/styleguide/cppguide.html)

#include "chat_server.h"

#include "cpprest/json.h"
#include "cpprest/uri.h"
#include "spdlog/spdlog.h"

using namespace std;
using ::web::uri;
using ::web::http::methods;
using ::web::http::http_request;
using ::web::http::status_codes;
using ::web::http::experimental::listener::http_listener;
using ::web::json::value;
using ::utility::string_t;
using ::utility::conversions::to_utf8string;
using ::pplx::task;
using ::spdlog::info;
using ::spdlog::warn;
using ::spdlog::error;

namespace chatserver {

  ChatServer::ChatServer(ChatDatabase* chat_database, 
                         AccountDatabase* account_database, 
                         SessionManager* session_manager)
                         : chat_database_(chat_database),
                           account_database_(account_database),
                           session_manager_(session_manager) {
  }

  bool ChatServer::Initialize(string_t server_url) {
    if (chat_database_ == nullptr || 
        account_database_ == nullptr || 
        session_manager_ == nullptr) {
      error("chat_database, account_database, or session_manager is nullptr.");
      return false;
    }
    session_manager_->RunSessionExpireThread();

    // HTTP request listener from cpprestsdk.
    listener_ = http_listener(server_url);  

    // Set HTTP request methods.
    listener_.support(methods::GET,
                      bind(&ChatServer::HandleGet, this, placeholders::_1));
    listener_.support(methods::PUT,
                      bind(&ChatServer::HandlePut, this, placeholders::_1));
    listener_.support(methods::POST,
                      bind(&ChatServer::HandlePost, this, placeholders::_1));
    listener_.support(methods::DEL,
                      bind(&ChatServer::HandleDelete, this, placeholders::_1));
    return true;
  }

  task<void> ChatServer::OpenServer() {
    return listener_.open();
  }

  task<void> ChatServer::CloseServer() {
    return listener_.close();
  }

  void ChatServer::HandleGet(const http_request& message) {
    // Path of HTTP request URL.
    // path[n] means the name of the nth path in HTTP request URL.
    vector<string_t> url_paths = uri::split_path(
        uri::decode(message.relative_uri().path()));
    
    // Query string of HTTP request URL.
    // Format: map<string_t, string_t> = <query name, query value>
    map<string_t, string_t> url_queries = uri::split_query(
        uri::decode(message.relative_uri().query()));

    if (url_paths.empty()) {
      message.reply(status_codes::NotFound);
      return;
    }

    if (!IsValidSession(url_queries)) {
      message.reply(status_codes::Forbidden,
                    UU("Not a valid session ID"));
      return;
    }

    // ToDo: Add get chat message and get chat room list API service.

    // No matching HTTP request.
    warn("No matching HTTP request");
    message.reply(status_codes::NotFound);
  }

  void ChatServer::ProcessGetChatMessageRequest(
      const http_request& message,
      const map<string_t, string_t>& url_queries) {
    const auto chat_room_it = url_queries.find(UU("chat_room"));
    // ToDo: Implement chat message request. The Http response must have chat
    // ToDO: messages of the given chat room.
  }

  void ChatServer::ProcessGetChatRoomRequest(const http_request& message) {
    // ToDo: Implement get chat room API. The Http response must have chat
    // ToDO: room list.
  }

  void ChatServer::HandlePost(const http_request& message) {
    // Path of HTTP request URL.
    // path[n] means the name of the nth path in HTTP request URL.
    vector<string_t> url_paths = uri::split_path(
        uri::decode(message.relative_uri().path()));

    // Query string of HTTP request URL.
    // Format: map<string_t, string_t> = <query name, query value>
    map<string_t, string_t> url_queries = uri::split_query(
        uri::decode(message.relative_uri().query()));

    if (url_paths.empty()) {
      message.reply(status_codes::NotFound);
      return;
    }

    // Signup API is implemented as a sample.
    // API service without session ID.
    const string_t first_request_url_path = url_paths[0];
    if (first_request_url_path == UU("account")) {
      ProcessPostSignUpRequest(message, url_queries);
      return;
    }

    // ToDo: Add login API service.

    if (!IsValidSession(url_queries)) {
      message.reply(status_codes::Forbidden,
                    UU("Not a valid session ID"));
      return;
    }

    // ToDo: Add chat message input and chat room create API service.

    // No matching HTTP request.
    warn("No matching HTTP request");
    message.reply(status_codes::NotFound);
  }

  void ChatServer::ProcessPostSignUpRequest(
      const http_request& message,
      const map<string_t, string_t>& url_queries) {
    const auto id_it = url_queries.find(UU("id"));
    const auto password_it = url_queries.find(UU("password"));
    if (id_it == url_queries.end() ||
      password_it == url_queries.end()) {
      message.reply(status_codes::BadRequest,
          UU("Account information absence"));
      return;
    }
    const string_t id = id_it->second;
    const string_t password = password_it->second;

    const int signup_result = 
        account_database_->SignUp(id, password);
    if (signup_result == AccountDatabase::kAuthSuccess) {
      message.reply(status_codes::OK);
      return;
    } else if (signup_result == AccountDatabase::kProhibitedCharInID) {
      message.reply(status_codes::BadRequest,
                    UU("Prohibited character in ID"));
      return;
    } else if (signup_result == AccountDatabase::kProhibitedCharInPassword) {
      message.reply(status_codes::BadRequest,
                    UU("Prohibited character in password"));
      return;
    } else if (signup_result == AccountDatabase::kDuplicateID) {
      message.reply(status_codes::BadRequest, 
                    UU("Duplicated ID"));
      return;
    } else if (signup_result == AccountDatabase::kAccountWriteError) {
      message.reply(status_codes::BadRequest,
                    UU("Account write error in file DB"));
      return;
    }
  }

  void ChatServer::ProcessPostLoginRequest(
      const http_request& message, 
      const map<string_t, string_t>& url_queries) {
    const auto id_it = url_queries.find(UU("id"));
    const auto password_it = url_queries.find(UU("password"));
    const auto nonce_it = url_queries.find(UU("nonce"));
    // ToDo: Implement login API.
  }

  void ChatServer::ProcessPostInputChatMessageRequest(
      const http_request& message, 
      const map<string_t, string_t>& url_queries) {
    const auto chat_message_it = url_queries.find(UU("chat_message"));
    const auto chat_room_it = url_queries.find(UU("chat_room"));
    // ToDo: Implement API to save chat message into the server.
  }

  void ChatServer::ProcessCreateChatRoomRequest(
      const http_request& message,
      const map<string_t, string_t>& url_queries) {
    const auto chat_room_it = url_queries.find(UU("chat_room"));
    // ToDo: Implement API to create the given chat room.
  }

  void ChatServer::HandleDelete(const http_request& message) {
    // Path of HTTP request URL.
    // path[n] means the name of the nth path in HTTP request URL.
    vector<string_t> url_paths = uri::split_path(
        uri::decode(message.relative_uri().path()));

    // Query string of HTTP request URL.
    // Format: map<string_t, string_t> = <query name, query value>
    map<string_t, string_t> url_queries = uri::split_query(
        uri::decode(message.relative_uri().query()));

    if (!IsValidSession(url_queries)) {
      message.reply(status_codes::Forbidden,
                    UU("Not a valid session ID"));
      return;
    }
    // ToDo: Add logout API service.

    // No matching HTTP request.
    warn("No matching HTTP request");
    message.reply(status_codes::NotFound);
  }

  void ChatServer::ProcessDeleteLogoutRequest(
      const http_request& message, 
      const map<string_t, string_t>& url_queries) {
    const auto session_id_it = url_queries.find(UU("session_id"));
    // ToDo: Implement logout API.
  }

  void ChatServer::HandlePut(const http_request& message) {
    // No matching HTTP request.
    warn("No matching HTTP request");
    message.reply(status_codes::NotFound);
  }

  bool ChatServer::IsValidSession(
      const map<string_t, string_t>& url_queries) {
    const auto session_id_it = url_queries.find(UU("session_id"));
    // ToDo: Implement to check the given session Id is valid.
    return false;
  }

} // namespace chatserver
