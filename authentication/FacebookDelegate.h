#ifndef FacebookDelegate_h
#define FacebookDelegate_h

#include <string>
#include <vector>
#include "controller/login_delegate.h"

class FacebookDelegate
{
public:
    FacebookDelegate();
    void FetchAuthToken(authentication::TokenCallback, const std::vector<std::string> permissions);
    const std::string GetAuthToken(bool checkValidity);
    void FetchUserName();
    const std::string GetUserName();
    const bool IsTokenActive();
    void LogOut();
private:
    bool _enableFriendsPermission;
};

#endif /* FacebookDelegate_h */
