#ifndef KeychainHelper_h
#define KeychainHelper_h

#include <string>
#import <Foundation/Foundation.h>

class KeychainHelper {
public:
    static Boolean saveNsStringValue(NSString *key, NSString* value, NSStringEncoding valEncoding=NSUTF8StringEncoding);
    static Boolean saveStringValue(const std::string &key, const std::string &value, NSStringEncoding valEncoding=NSUTF8StringEncoding);
    static std::string getStringValue(const std::string &key, NSStringEncoding valEncoding=NSUTF8StringEncoding);
    static NSString* getNsStringValue(NSString* key, NSStringEncoding valEncoding=NSUTF8StringEncoding);
};


#endif /* KeychainHelper_h */
