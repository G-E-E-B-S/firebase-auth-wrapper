#include "auth_state_listener.h"
#include "logger/log.h"

namespace authentication {
    void AuthStateListener::OnAuthStateChanged(firebase::auth::Auth* auth)
    {
        firebase::auth::User* user = auth->current_user();
        if (user != nullptr) {
            // User is signed in
            logger::log("OnAuthStateChanged: signed_in %s\n", user->uid().c_str());
        } else {
            // User is signed out
            logger::log("OnAuthStateChanged: signed_out\n");
        }
    // ...
    }
} // authentication
