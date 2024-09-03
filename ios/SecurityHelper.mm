#import "SecurityHelper.h"
#import <firebase_auth/firebase_auth-Swift.h>

NSString* SecurityHelper::generateRandomNonce(const int length)
{
    return [SecurityHelperImplementation generateRandomNonceWithLength:length];
}


NSString* SecurityHelper::getStringBySha256HashingString(NSString* inputNS) {
    return [SecurityHelperImplementation getStringBySha256HashingString:inputNS];
}

