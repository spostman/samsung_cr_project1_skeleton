// Code review content development project.
// Code style follows Google C++ Style Guide.
// (https://google.github.io/styleguide/cppguide.html)

#include "session_manager.h"

#include <chrono>
#include <future>

#include "cpprest/asyncrt_utils.h"
#include "spdlog/spdlog.h"

using namespace std;
using chrono::system_clock;
using chrono::duration;
using ::utility::conversions::to_utf8string;
using ::utility::string_t;
using ::spdlog::info;

namespace chatserver {

  // Session alive time (second).
  const time_t kSessionAliveTime = 30;
  // Length of session id.
  const size_t kSessionLength = 32;
  // Period to check session expire (second).
  const time_t kSessionCheckInterval = 1;
  // Session seed.
  const string_t kSessionValue = UU(
      "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

  SessionManager::SessionManager()
      : rand_(std::random_device{}()),
        session_generator_(0, kSessionValue.size() - 1) {
  }

  SessionManager::~SessionManager() {
  }

  bool SessionManager::IsExistSessionId(string_t session_id) {
    // ToDo: Implement to check whether the given session id exists in session_.
    return false;
  }

  Session SessionManager::CreateSession(string_t user_id) {
    // ToDo: Implement to create session id of the given user id.
    Session session;
    return session;
  }

  bool SessionManager::DeleteSession(string_t session_id) {
    // ToDo: Implement to delete the given session id.
    return false;
  }

  bool SessionManager::RenewLastActivityTime(string_t session_id) {
    // ToDo: Implement to renew last_activity_time of the given session id.
    // ToDo: Set last_activity_time to the current time.
    return false;
  }

  const string_t SessionManager::GenerateSessionId() {
    // ToDo: Return random session id using kSessionValue and kSessionLength.
    // ToDo: The session ID must be a unique value.
    // ToDo: Use random function of rand_, session_generator_.
    return UU("");
  }

  bool SessionManager::GetUserIDFromSessionId(string_t session_id, 
                                              string_t* out_user_id) {
    // ToDo: Save user id of the given session id into out_user_id. 
    // ToDo: If it fails return false.
    return false;
  }

  void SessionManager::RunSessionExpireThread() {
    // ToDo: Run a thread to remove expired session.
    // ToDo: If a session's last_activity_time is over kSessionAliveTime from
    // ToDo: the current time, delete the session.
    // ToDo: Run this the above logic every kSessionCheckInterval.
  }

} // namespace chatserver
