Pod::Spec.new do |spec|
  spec.name         = "firebase-auth"
  spec.version      = "0.0.1"
  spec.summary      = "Firebase Auth wrapper for iOS/Android projects"
  spec.description  = <<-DESC
  Firebase Auth wrapper for iOS/Android projects.
  Supports following login methods:
  Apple
  Facebook
  Facebook Gaming
  Google Sign In
                        DESC
  spec.license      = { :type => "MIT", :file => "FILE_LICENSE" }
  spec.platform     = :ios
  spec.swift_version = '5.7'
  spec.ios.deployment_target = "12.0"
  spec.source       = { :git => "https://github.com/G-E-E-B-S/firebase-auth-wrapper.git", :tag => "#{spec.version}" }
  spec.source_files  = [
    "authentication/controller/controller.cpp", 
    "authentication/firebase/auth_state_listener.cpp",
    "authentication/models",
    "ios/firebase-auth/firebase-auth/*.h",
    "ios/*",
    "ios/firebase-auth/firebase-auth/*"]

  spec.public_header_files = ["ios/IosGlobals.h"]
  spec.framework = "AuthenticationServices"
  spec.static_framework = true
  spec.dependency 'GoogleSignIn'
  spec.dependency 'Firebase/Auth', '10.6.0'
  spec.dependency 'Firebase/Analytics', '10.6.0'
  spec.dependency 'FBSDKCoreKit'
  spec.dependency 'FBSDKLoginKit'
  spec.dependency 'firebase-auth-vendored', '0.0.1'
  spec.dependency 'log_wrapper', '0.0.1'

  spec.pod_target_xcconfig = {
    "HEADER_SEARCH_PATHS" => '${inherited} '+
    '"${PODS_TARGET_SRCROOT}/external/firebase/includes" ',
    "USER_HEADER_SEARCH_PATHS" => '${inherited} '+
    '"${PODS_TARGET_SRCROOT}" '+
    '"${PODS_TARGET_SRCROOT}/../log_wrapper/includes" ' +
    '"${PODS_TARGET_SRCROOT}/../jsb-helper" '
  }
end
