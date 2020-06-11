// Code review content development project.
// Code style follows Google C++ Style Guide.
// (https://google.github.io/styleguide/cppguide.html)

#include "chat_client.h"

#include "spdlog/spdlog.h"

using namespace std;
using ::chatserver::ChatMessage;
using ::web::uri;
using ::web::http::methods;
using ::web::http::http_response;
using ::web::http::status_code;
using ::web::http::status_codes;
using ::web::json::value;
using ::web::json::array;
using ::utility::string_t;
using ::utility::ostringstream_t;
using ::utility::conversions::to_string_t;
using ::spdlog::error;

namespace chatclient {

  ChatClient::ChatClient(const string_t chat_server_url)
      : current_client_status_(kBeforeLogin),
        chat_server_url_(chat_server_url) {
    http_requester_ = make_unique<HttpRequester>(
        web::http::uri_builder(chat_server_url).to_uri().to_string());
    chat_client_view_ = make_unique<ChatClientView>();
  }

  void ChatClient::RunChatClient() {
    while (true) {
      string_t method;
      if (session_id_.empty() && current_client_status_ == kBeforeLogin) {
        // Services before login: login, signup
        if(!BeforeLogin()) {
          break;
        }
      } else if (!session_id_.empty() && 
                 current_client_status_ == kAfterLogin) {
        // Services after login.
        // 1) get room list, 2) join chat room, 3) create chat room, 4) logout
        if(!AfterLogin()) {
          break;
        }
      } else if (!session_id_.empty() &&
                 !current_chat_room_.empty() && 
                 current_client_status_ == kInChatRoom) {
        // Enter a chat room.
        InChatRoom();
      } else {
        error("Invalid client status: {}", current_client_status_);
        break;
      }
    }
  }

  bool ChatClient::BeforeLogin() {
    const string_t method = chat_client_view_->
        GetUserInput(UU("Enter method name (login, signup, exit): "));

    if (method == UU("signup")) {
      SignUp();
    } else if (method == UU("login")) {
      Login();
    } else if (method == UU("exit")) {
      return false;
    } else {
      ostringstream_t buf;
      buf << method << " not understood.";
      chat_client_view_->DisplayMessage(buf.str());
    }
    return true;
  }

  bool ChatClient::AfterLogin() {
    const string_t method = chat_client_view_->
        GetUserInput(
            UU("Enter method name (join, room_list, room_create, logout, exit): "));

    if (method == UU("room_list")) {
      if (DisplayChatRoomList() == status_codes::Forbidden) {
        ClearUserInformation();
      }
    } else if (method == UU("join")) {
      JoinChatRoom();
    } else if (method == UU("logout")) {
      Logout();
    } else if (method == UU("room_create")) {
      const status_code response_code = CreateChatRoom();
      if (response_code == status_codes::Forbidden) {
        ClearUserInformation();
      } else if (response_code == status_codes::BadRequest) {
        return true;
      }
    } else if (method == UU("exit")) {
      return false;
    } else {
      ostringstream_t buf;
      buf << method << " not understood.";
      chat_client_view_->DisplayMessage(buf.str());
    }
    return true;
  }

  void ChatClient::InChatRoom() {
    chat_room_ = make_unique<ChatRoom>(chat_server_url_,
                                       session_id_,
                                       current_chat_room_);
    chat_room_->RunChatRoom();
    current_client_status_ = kAfterLogin;
  }

  void ChatClient::SignUp() const {
    // User input: ID, password, password once more
    const string_t id = 
        chat_client_view_->GetUserInput(UU("Enter id: "));
    const string_t password =
        chat_client_view_->GetUserInput(UU("Enter password: "));
    const string_t password_again =
        chat_client_view_->GetUserInput(UU("Enter the password once more: "));

    // Check password matching
    if (password != password_again) {
      chat_client_view_->DisplayMessage(UU("Password not matching."));
      return;
    }

    // Check password length
    if (password.size() < 8) {
      chat_client_view_->
          DisplayMessage(UU("Password must be at least 8 characters."));
      return;
    }

    // Make request URL
    ostringstream_t http_request_url;
    http_request_url << "account" << UU("?id=") << id << UU("&password=")
                     << http_requester_->HashString(password);

    // Make HTTP request
    if (http_requester_->MakeHttpRequest(methods::POST, 
                                         http_request_url.str())) {

      chat_client_view_->
          DisplayMessage(UU("Success to signup."));
    }
  }

  void ChatClient::Login() {
    // ToDo: Implement login API.
  }

  status_code ChatClient::DisplayChatRoomList() const {
    // ToDo: Implement display chat room list API.
    return status_codes::BadRequest;
  }

  status_code ChatClient::CreateChatRoom() const {
    // ToDo: Implement create chat room list API.
    return status_codes::BadRequest;
  }

  void ChatClient::JoinChatRoom() {
    // ToDo: Implement join chat room list API.
  }

  void ChatClient::Logout() {
    // ToDo: Implement logout API.
  }

  void ChatClient::ClearUserInformation() {
    session_id_.clear();
    user_id_.clear();
    current_chat_room_.clear();
    current_client_status_ = kBeforeLogin;
  }

} // namespace chatclient