#import "IosGlobals.h"
#import <AuthenticationServices/AuthenticationServices.h>

@implementation IosGlobals

static id<ASAuthorizationControllerDelegate> delegate;
static id <ASAuthorizationControllerPresentationContextProviding> presentationContext;

+ (void)setDelegate:(id<ASAuthorizationControllerDelegate>) value API_AVAILABLE(ios(13.0)){
    delegate = value;
};
+ (id<ASAuthorizationControllerDelegate>)getDelegate API_AVAILABLE(ios(13.0)) {
    return delegate;
};
+ (void)setPresentationContext:(id <ASAuthorizationControllerPresentationContextProviding>) value API_AVAILABLE(ios(13.0)) {
    presentationContext = value;
};
+(id <ASAuthorizationControllerPresentationContextProviding>)getPresentationContext API_AVAILABLE(ios(13.0)) {
    return presentationContext;
};
+ (NSString*) appleTokenKeychainKey {
    return  @"appleAuthToken";
}
+ (NSString*) appleSignInNonceKeychainKey  {
    return @"appleNonce";
}
+ (NSString*) appleIdentifierKeychainKey  {
    return @"appleIdentifier";
}

@end

