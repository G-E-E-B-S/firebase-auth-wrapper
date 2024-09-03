#ifndef IosGlobals_h
#define IosGlobals_h

#import <Foundation/Foundation.h>
#import <AuthenticationServices/AuthenticationServices.h>

@interface IosGlobals: NSObject
+ (void)setDelegate:(id<ASAuthorizationControllerDelegate>) delegate API_AVAILABLE(ios(13.0));
+ (id<ASAuthorizationControllerDelegate>)getDelegate API_AVAILABLE(ios(13.0));
+ (void)setPresentationContext:(id <ASAuthorizationControllerPresentationContextProviding>) presentationContext API_AVAILABLE(ios(13.0));
+(id <ASAuthorizationControllerPresentationContextProviding>)getPresentationContext API_AVAILABLE(ios(13.0));
+ (NSString*) appleTokenKeychainKey;
+ (NSString*) appleSignInNonceKeychainKey;
+ (NSString*) appleIdentifierKeychainKey;
@end

#endif /* IosGlobals_h */
