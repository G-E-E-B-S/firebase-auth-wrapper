Pod::Spec.new do |spec|
  spec.name         = "firebase-auth-vendored"
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
  spec.ios.deployment_target = "12.0"
  spec.source       = { :git => "https://github.com/G-E-E-B-S/firebase-auth-wrapper.git", :tag => "#{spec.version}" }
  spec.vendored_frameworks = ['external/libs/ios/xcframeworks/firebase_auth.xcframework']
  spec.module_name = "firebase_auth_vendored"
  spec.static_framework = true
end
