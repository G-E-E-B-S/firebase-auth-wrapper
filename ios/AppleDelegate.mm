#import "authentication/AppleDelegate.h"
#import "IosGlobals.h"
#import "KeychainHelper.h"
#import "SecurityHelper.h"
#import <Firebase/Firebase.h>
#import <AuthenticationServices/AuthenticationServices.h>


namespace AplDelegate {
    authentication::TokenNonceCallback s_authCallback;
}

AppleDelegate::AppleDelegate() {
    
}

bool AppleDelegate::IsSupported() {
    if (@available(iOS 13.0, *)) {
        return true;
    } else {
        return false;
    }
}

void AppleDelegate::OnSignIn(authentication::LoginState loginState,
                              const std::string &token,
                              const std::string &nonce,
                              const std::string &errorMSg,
                              int errorCode)
{
    AplDelegate::s_authCallback(loginState,
                               token,
                               nonce,
                               errorMSg,
                               errorCode);
}

void AppleDelegate::SignIn(bool autoSignIn, authentication::TokenNonceCallback callback)
{
    AplDelegate::s_authCallback = callback;
    if (@available(iOS 13.0, *)) {
        NSString* nonceNs = SecurityHelper::generateRandomNonce(32);
        KeychainHelper::saveNsStringValue([IosGlobals appleSignInNonceKeychainKey], nonceNs);
        ASAuthorizationAppleIDProvider *appleIDProvider = [[ASAuthorizationAppleIDProvider alloc] init];
        ASAuthorizationAppleIDRequest *request = [appleIDProvider createRequest];
        request.requestedScopes = @[ASAuthorizationScopeFullName, ASAuthorizationScopeEmail];
        request.nonce = SecurityHelper::getStringBySha256HashingString(nonceNs);
        ASAuthorizationController *authorizationController =
            [[ASAuthorizationController alloc] initWithAuthorizationRequests:@[request]];
        authorizationController.delegate = [IosGlobals getDelegate];
        authorizationController.presentationContextProvider = [IosGlobals getPresentationContext];
        [authorizationController performRequests];
    } else {
        // NOTE: Use IsSupported() check before showing the apple signin ui
        return;
    }
}
void AppleDelegate::CheckAndGetAuthToken(authentication::AuthTokenCheckCallback callback)
{
    if (@available(iOS 13.0, *)) {
        ASAuthorizationAppleIDProvider *appleIDProvider = [[ASAuthorizationAppleIDProvider alloc] init];
        NSString *appleIdNs = KeychainHelper::getNsStringValue([IosGlobals appleIdentifierKeychainKey]);
        [appleIDProvider getCredentialStateForUserID:appleIdNs completion:^(ASAuthorizationAppleIDProviderCredentialState credentialState, NSError * _Nullable error) {
            if (credentialState == ASAuthorizationAppleIDProviderCredentialAuthorized) {
                NSLog(@"AppleID cred state authorized");
                NSString *tokenNs = KeychainHelper::getNsStringValue([IosGlobals appleTokenKeychainKey]);
                callback([tokenNs UTF8String], this->GetNonce());
                return;
            } else if (credentialState == ASAuthorizationAppleIDProviderCredentialNotFound) {
                NSLog(@"AppleID cred state not found");
            } else if (credentialState == ASAuthorizationAppleIDProviderCredentialRevoked) {
                NSLog(@"AppleID cred state not found");
            } else {
                NSLog(@"AppleID cred state: %ld", credentialState);
            }
            callback("", "");
        }];
    } else {
        callback("", "");
    }
}

const std::string AppleDelegate::GetAuthToken()
{
    NSString *tokenNs = KeychainHelper::getNsStringValue([IosGlobals appleTokenKeychainKey]);
    return [tokenNs UTF8String];
}

const std::string AppleDelegate::GetNonce()
{
    NSString *nonceNs = KeychainHelper::getNsStringValue([IosGlobals appleSignInNonceKeychainKey]);
    return [nonceNs UTF8String];
}

bool AppleDelegate::HasLoggedIn()
{
    return this->GetAuthToken().size() > 0;
}

void AppleDelegate::LogOut()
{
    NSError *signOutError;
    BOOL status = [[FIRAuth auth] signOut:&signOutError];
    if (!status) {
      NSLog(@"Error signing out Apple: %@", signOutError);
      return;
    }
    KeychainHelper::saveNsStringValue([IosGlobals appleTokenKeychainKey], @"");
    KeychainHelper::saveNsStringValue([IosGlobals appleSignInNonceKeychainKey], @"");
}

