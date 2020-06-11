// Code review content development project.
// Code style follows Google C++ Style Guide.
// (https://google.github.io/styleguide/cppguide.html)

#include "chat_room.h"

#include <future>

#include "spdlog/spdlog.h"

using namespace std;
using ::chatserver::ChatMessage;
using ::web::http::methods;
using ::web::http::http_response;
using ::web::http::status_codes;
using ::web::json::value;
using ::web::json::array;
using ::utility::string_t;
using ::utility::ostringstream_t;
using ::spdlog::error;
using chrono::duration;

namespace chatclient {

  // Maximum number of chat messages to be displayed on the screen.
  const time_t kMaxDisplayChatMessages = 5;
  // Line number to receive chat message input.
  const time_t kInputLine = 10;
  // Polling interval to make chat message request to the server.
  const duration<int> kPollingInterval = std::chrono::seconds(1);

  ChatRoom::ChatRoom(string_t chat_server_url,
                     string_t session_id, 
                     string_t current_chat_room)
                     : session_id_(session_id),
                       current_chat_room_(current_chat_room) {
    http_requester_ = make_unique<HttpRequester>(
        web::http::uri_builder(chat_server_url).to_uri().to_string());
    // ToDo: Use chat_room_view to get a user input and display messages.
    chat_room_view_ = make_unique<ChatRoomView>();
  }

  ChatRoom::~ChatRoom() {
    run_display_thread_ = false;
  }

  void ChatRoom::RunChatRoom() {
    chat_room_view_->ClearConsole();
    chat_room_view_->SetCursorPosition(0, kInputLine);
    run_display_thread_ = true;
    // Run polling thread to receive chat messages from the chat server.
    // Getting return value is necessary to run async thread
    // but the value is not used.
    async_thread_result_ = async(launch::async, 
                                 &ChatRoom::PollingChatMessageFromServer, this);
    // Run receiving chat messages from the user through C++ Standard input.
    ProcessChatMessageInput();
  }

  void ChatRoom::PollingChatMessageFromServer() {
    while (run_display_thread_) {
      // ToDo: Implement polling chat message from server.
      // ToDo: If there are new chat messages display the cha messages to the
      // ToDo: console screen using GetChatMessagesFromServer().
      
      this_thread::sleep_for(kPollingInterval);
    }
  }

  void ChatRoom::ProcessChatMessageInput() {
    while (true) {
      // ToDo: Implement that getting chat message by user console input.
      // ToDo: Send the chat message to the server using
      // ToDo: StoreChatMessagesToServer().
      string_t chat_message;

      if (StoreChatMessagesToServer(chat_message)) {
        chat_room_view_->
            DisplayChatMessages(display_chat_message_, 
                                current_chat_room_, 
                                kMaxDisplayChatMessages);
      }
    }
  }

  bool ChatRoom::GetChatMessagesFromServer(
      vector<ChatMessage>& chat_messages) const {
    // ToDo: Implement that getting chat message by the chat server.
    // ToDo: Save the chat message into chat_messages.
    return false;
  }

  bool ChatRoom::StoreChatMessagesToServer(const string_t chat_message) const {
    // ToDo: Send the chat_message to chat server.
    return false;
  }

} // namespace chatclient