#ifndef SecurityHelper_h
#define SecurityHelper_h

#include <string>
#import <Foundation/Foundation.h>

class SecurityHelper {
public:
    static NSString* generateRandomNonce(const int length);
    static NSString* getStringBySha256HashingString(NSString* inputNS);
};

#endif /* SecurityHelper_h */
