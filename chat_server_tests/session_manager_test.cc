// Code review content development project.
// Code style follows Google C++ Style Guide.
// (https://google.github.io/styleguide/cppguide.html)

#include "gtest/gtest.h"
#include "session_manager.h"

#include "session.h"

using namespace std;
using namespace chrono;
using namespace utility;
using namespace chatserver;

// Fixture class for session_manager.h testing.
class SessionManagerTest : public ::testing::Test {
 protected:
  SessionManager session_manager_;
  Session kaist_session;
  Session wsp_session;
  Session gsis_session;

  void SetUp() override {
    kaist_session = session_manager_.CreateSession(UU("kaist"));
    wsp_session = session_manager_.CreateSession(UU("wsp"));
    gsis_session = session_manager_.CreateSession(UU("gsis"));
  }
};

// ToDo: Implement unit tests.