import Foundation
@objc public class KeychainHelperImplementation: NSObject {
    @objc static public func saveNsStringValue(key: String, val: String, encoding: UInt) -> Bool {
        return SecItemAdd([kSecValueData: val.data(using: String.Encoding(rawValue: encoding))!,
                    kSecClass: kSecClassGenericPassword,
                  kSecAttrAccount: key.data(using: .utf8)!] as NSDictionary, nil) == errSecSuccess;
    }
}
