#include "KeychainHelper.h"
#import <firebase_auth/firebase_auth-Swift.h>

Boolean KeychainHelper::saveNsStringValue(NSString* key, NSString* secValStr, NSStringEncoding valEncoding)
{
    return [KeychainHelperImplementation saveNsStringValueWithKey:key val:secValStr encoding:valEncoding];
}


Boolean KeychainHelper::saveStringValue(const std::string &key, const std::string &value, NSStringEncoding valEncoding)
{
    NSString *secValStr = [NSString stringWithCString:value.c_str()
                                    encoding:valEncoding];
    return KeychainHelper::saveNsStringValue([NSString stringWithUTF8String:key.c_str()], secValStr);
}

NSString* KeychainHelper::getNsStringValue(NSString* key, NSStringEncoding valEncoding)
{
//    NSData* tag = [key dataUsingEncoding:NSUTF8StringEncoding];
//    NSDictionary *getquery = @{
//       (id)kSecClass: (id)kSecClassGenericPassword,
//       (id)kSecAttrAccount: tag,
//       (id)kSecReturnAttributes: @YES,
//       (id)kSecReturnData: @YES,
//       (id)kSecMatchLimit: (id)kSecMatchLimitOne
//    };
//    CFDictionaryRef secValCF;
//    OSStatus status = SecItemCopyMatching((__bridge CFDictionaryRef)getquery,
//                                          (CFTypeRef *)&secValCF);
//    if (status != errSecSuccess) {
//        return @"";
//    }
//    else {
//        NSDictionary *secValNsDict = nil;
//        secValNsDict = (__bridge NSDictionary*)(secValCF);
//        NSString* secValNs = [[NSString alloc] initWithData:[secValNsDict objectForKey:(__bridge id)(kSecValueData)] encoding:valEncoding];
//        return secValNs;
//    }
    return @"";
}

std::string KeychainHelper::getStringValue(const std::string &key, NSStringEncoding valEncoding)
{
    NSString* secValNs = KeychainHelper::getNsStringValue([NSString stringWithUTF8String: key.c_str()], valEncoding);
    return [secValNs UTF8String];
}
