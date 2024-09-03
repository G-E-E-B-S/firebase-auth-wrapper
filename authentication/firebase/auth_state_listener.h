#ifndef AUTHENTICATION_AUTH_STATE_LISTENER_H
#define AUTHENTICATION_AUTH_STATE_LISTENER_H

#include "firebase/auth.h"

namespace authentication {
	class AuthStateListener : public firebase::auth::AuthStateListener {
	public:
		void OnAuthStateChanged(firebase::auth::Auth* auth) override;
	};	
} // authentication

#endif //AUTHENTICATION_AUTH_STATE_LISTENER_H
		