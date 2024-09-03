#ifndef USER_INFO_H
#define USER_INFO_H

#include <string>
namespace authentication
{
    class UserInfo {
    private:
        std::string _userID;
    public:
        const std::string& getUserID() {
            return _userID;
        }
        void setUserID(const std::string& userID) {
            _userID = userID;
        }
    };
}

#endif // USER_INFO_H
