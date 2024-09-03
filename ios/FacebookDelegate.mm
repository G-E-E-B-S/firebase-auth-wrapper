#import "authentication/FacebookDelegate.h"
#import <FBSDKLoginKit/FBSDKLoginKit-Swift.h>
#import <FBSDKCoreKit/FBSDKGraphRequest.h>
#import <FBSDKCoreKit/FBSDKGraphRequestConnecting.h>

namespace {
    FBSDKLoginManager *s_sharedLoginManager = nullptr;
    NSString* userName = @"";
    bool nameFetchSuccess = false;
}

FacebookDelegate::FacebookDelegate() {
    s_sharedLoginManager = [[FBSDKLoginManager alloc] init];
}

void FacebookDelegate::FetchUserName()
{
    if (nameFetchSuccess == false) {
        auto token = [FBSDKAccessToken currentAccessToken];
          if (token) {
            FBSDKGraphRequest *request = [[FBSDKGraphRequest alloc]
              initWithGraphPath:@"/me"
                  parameters:{}
                  HTTPMethod:@"GET"];
              [request startWithCompletion:^(id<FBSDKGraphRequestConnecting> connection, id result, NSError *error) {
                  // Insert your code here
                  NSDictionary* resultDict = (NSDictionary*)result;
                  userName = [resultDict objectForKey:@"name"];
                  nameFetchSuccess = true;
              }];
          }
    }
}

void FacebookDelegate::FetchAuthToken(authentication::TokenCallback callback, const std::vector<std::string> permissions)
{
    auto handler = ^(FBSDKLoginManagerLoginResult *result, NSError *error) {
        if (error) {
            NSLog(@"Process error");
            callback(authentication::LoginState::ERROR,
                     "",
                     [error.localizedDescription UTF8String],
                     (int)error.code);
        } else if (result.isCancelled) {
            NSLog(@"Cancelled");
            callback(authentication::LoginState::CANCELLED,
                     "",
                     "cancelled",
                     -1);
        } else {
//             NSLog(@"Logged in");
            callback(authentication::LoginState::SUCCESS,
                     [result.token.tokenString UTF8String],
                     "",
                     0);
        }
    };
    auto token = [FBSDKAccessToken currentAccessToken];
    if (token && [token isDataAccessExpired]) {
        [s_sharedLoginManager reauthorizeDataAccess: [UIApplication sharedApplication].keyWindow.rootViewController handler:handler];
        return;
    }
    NSMutableArray* params = [[NSMutableArray alloc] init]; 
    for (auto idx = 0; idx < permissions.size(); idx++) {
        [params addObject:[NSString stringWithUTF8String:permissions[idx].c_str()]];
    }
    [s_sharedLoginManager
     logInWithPermissions: params
     fromViewController:nil
     handler:handler];
}

const std::string FacebookDelegate::GetAuthToken(bool checkValidity)
{
    auto token = [FBSDKAccessToken currentAccessToken];
    if (token == nil) {
        return "";
    }
    auto tokenStr = [[token tokenString] UTF8String];
    if (!checkValidity) {
        return tokenStr;
    }
    if (![token isExpired] && ![token isDataAccessExpired]) {
        return tokenStr;
    }
    return "";
}

const std::string FacebookDelegate::GetUserName()
{
    std::string userNameStr = [userName UTF8String];
    return userNameStr;
}

const bool FacebookDelegate::IsTokenActive()
{
    return [FBSDKAccessToken isCurrentAccessTokenActive];
}

void FacebookDelegate::LogOut()
{
    [s_sharedLoginManager logOut];
}
