// Code review content development project.
// Code style follows Google C++ Style Guide.
// (https://google.github.io/styleguide/cppguide.html)

#include "chat_database.h"

#include "cpprest/asyncrt_utils.h"
#include "spdlog/spdlog.h"

namespace chatserver {

  using namespace std;
  using ::utility::conversions::to_utf8string;
  using ::utility::string_t;
  using ::spdlog::error;

  // Delimiter in the chat message file database.
  const string_t kParsingDelimiter = UU("|");

  bool ChatDatabase::Initialize(string_t chat_message_file,
                                string_t chat_room_file) {
    chat_message_file_ = chat_message_file;
    chat_room_file_ = chat_room_file;

    // ToDo: Use the below commented code. We comment on the code because of the
    // ToDo: execution of skeleton code.
    /*
    if (!ReadChatMessagesFromFileDatabase(chat_message_file_)) {
      error("Error to open chat message file: {}",
            to_utf8string(chat_message_file_));
      return false;
    }

    if (!ReadChatRoomFromFileDatabase(chat_room_file_)) {
      error("Error to open chat room file: {}", 
            to_utf8string(chat_room_file_));
      return false;
    }*/
    return true;
  }

  bool ChatDatabase::StoreChatMessage(const ChatMessage& message) {
    // ToDo: Check if the given message has delimiter.
    // ToDo: Save the given message into chat message file DB.
    // ToDo: Save the given message into chat_messages_
    return false;
  }

  const vector<ChatMessage>* ChatDatabase::GetAllChatMessages(
      string_t chat_room) {
    // ToDo: Return chat message of the given chat room.
    return nullptr;
  }

  bool ChatDatabase::CreateChatRoom(string_t chat_room) {
    // ToDo: Check if the given chat_room name is correct.
    // ToDo: Check if the given chat_room name is duplicate.
    // ToDo: Save the given chat_room into chat room file DB.
    // ToDo: Save the given chat_room into chat_rooms_.
    return false;
  }

  bool ChatDatabase::IsExistChatRoom(string_t chat_room) const {
    // ToDo: The given chat_room exist in chat_rooms_.
    return false;
  }

  const vector<string_t>* ChatDatabase::GetChatRoomList() const{
    // ToDo: Implement to return chat room list.
    return nullptr;
  }

  bool ChatDatabase::ReadChatMessagesFromFileDatabase(
      string_t chat_message_file) {
    // ToDo: Implement saving the given chat message DB file into
    // ToDo: chat_messages_.
    return false;
  }

  bool ChatDatabase::ReadChatRoomFromFileDatabase(string_t chat_room_file) {
    // ToDo: Implement saving the given chat room DB file into chat_rooms_.
    return false;
  }

} // namespace chatserver
