import { INativeLoginListener, LoginEvents, LoginStatus, LoginType, LoginTypeStr, LoginTypeToStr } from "./AuthDefinitions";
import CommonAuthDelegate from "./CommonAuthDelegate";
import { EventDispatcher } from "./EventDispatcher";
import { IAnalyticsHelper } from "./interfaces/IAnalyticsHelper";
import IAuthDelegate from "./interfaces/IAuthDelegate";
import { ILoginFlowListener, ILoginFlowManager } from "./interfaces/ILoginFlowManager";
import { ISessionHelper } from "./interfaces/ISessionHelper";

let isReLogin = false;

export class CommonLoginFlowManager implements ILoginFlowManager, INativeLoginListener {
    protected authDelegate: CommonAuthDelegate;
    protected sessionHelper: ISessionHelper;
    protected listener: ILoginFlowListener;
    protected dispatcher: EventDispatcher;
    private fbPermissions: string[];
    protected analyticsHelper: IAnalyticsHelper;
    constructor(analyticsHelper: IAnalyticsHelper, authDelegate: CommonAuthDelegate, sessionHelper: ISessionHelper, fbPermissions: string[]) {
        this.dispatcher = new EventDispatcher();
        this.authDelegate = authDelegate;
        this.analyticsHelper = analyticsHelper;
        this.sessionHelper = sessionHelper;
        this.fbPermissions = fbPermissions;
    }
    setListener(listener: ILoginFlowListener): void {
        this.listener = listener;
    }
    logOut(): void {
        this.sessionHelper.onLogOut();
        this.authDelegate.signOut()
    }
    getAuthDelegate(): IAuthDelegate {
        return this.authDelegate;
    }

    getDispatcher(): EventDispatcher {
        return this.dispatcher;
    }
    autoLogin(fallbackToGuest: boolean) {
        console.log("LoginFlow: forceAutoLogin start");
        if (isReLogin && this.authDelegate.isLoggedInAnyPlatform()) {
            if (this.listener) {
                this.listener.onSuccess();
            } else {
                console.error("LoginFlow: autoLogin: isRelogin listener is null");
            }
            return;
        }
        // NOTE: This will autologin to guest if not loggedin before
        console.log("LoginFlow: LoginFlow firebase setup done");
        if (this.isLoggedIn()) {
            const loginType = this.authDelegate.getLoginType();
            if (this.canAutoFbLogin()) {
                this.onFacebookSelected(this.isLoginTypeFacebook(loginType));
            } else if (this.canAutoGoogleLogin()) {
                this.onGoogleSelected(loginType == LoginType.GOOGLE);
            } else if (this.canAutoAppleLogin()) {
                this.onAppleSelected();
            } else {
                this.onGuestSelected(loginType == LoginType.ANONYMOUS);
            }
        } else {
            if (fallbackToGuest) {
                this.onGuestSelected(false);
            } else {
                if (this.listener) {
                    this.listener.onFailure(LoginType.ANONYMOUS, null, null);
                } else {
                    console.error("LoginFlow: autoLogin: no guest fallback listener is null");
                }
            }
        }
    }
    login(loginType: LoginType) {
        if (loginType == LoginType.FACEBOOK || loginType == LoginType.FACEBOOK_GAMING) {
            this.onFacebookSelected(false)
        } else if (loginType == LoginType.GOOGLE) {
            this.onGoogleSelected(false);
        } else if (loginType == LoginType.APPLE) {
            this.onAppleSelected();
        } else if (loginType == LoginType.ANONYMOUS) {
            this.onGuestSelected(false);
        }
    }

    clear() {
        this.listener = null;
        console.log("LoginFlowManagerNative::clear");
    }

    private canAutoFbLogin() {
        if (this.sessionHelper.getLoginType() == LoginTypeStr.FACEBOOK) {
            return true;
        }
        return this.authDelegate.isLoggedInFB();
    }

    private canAutoGoogleLogin() {
        if (this.sessionHelper.getLoginType() == LoginTypeStr.GOOGLE) {
            return true;
        }
        return this.authDelegate.isLoggedInGoogle();
    }
    private canAutoAppleLogin() {
        if (this.sessionHelper.getLoginType() == LoginTypeStr.APPLE) {
            return true;
        }
        return this.authDelegate.isLoggedInApple();
    }
    private isLoginTypeFacebook(loginType: LoginType): boolean {
        return loginType == LoginType.FACEBOOK || loginType == LoginType.FACEBOOK_GAMING
    }

    onGuestSelected(autoLogin : boolean) {
        autoLogin = autoLogin || false;
        console.log("LoginFlow: onGuestSelected");
        this.showLoginProgress(true);
        if (this.authDelegate.isLoggedInAnonymous()) {
            console.log("LoginFlow: onGuestSelected User already logged in as anon, move forward")
            setTimeout(() => {
                // NOTE: This is to avoid race condition in receiving LOGIN_SUCCESS event
                this.onAnonymousLogin(LoginStatus.SUCCESS, null);
            }, 10);
        } else {
            this.authDelegate.SignInAnonymously(autoLogin, this.onAnonymousLogin.bind(this));
        }
        this.analyticsHelper.logCustomEvent("login_guest_confirm_callback");
    }

    private onAnonymousLogin(status: LoginStatus, errorCode?) {
        console.log("login status: ", status);
        if (status == LoginStatus.SUCCESS) {
            this.analyticsHelper.setSignupMethod(LoginTypeStr.GUEST);
            console.log("analytics set sigup method:");
            this.analyticsHelper.logCustomEvent("login_guest_success");
            console.log("analytics log custom event");
            this.onLoginSuccess();
            console.log("LoginFlow: onAnonymousLogin() success");
        } else {
            this.showLoginProgress(false);
            if (this.listener) {
                this.listener.onFailure(LoginType.ANONYMOUS,  this.onGuestSelected.bind(this), null);
            } else {
                console.error("LoginFlow: onAnonymousLogin: listener is null %s", errorCode);
            }
            this.analyticsHelper.logCustomEvent("login_guest_failed");
            console.log("LoginFlow: onAnonymousLogin() failed");
        }
    }

    onFacebookSelected(autoLogin: boolean) {
        autoLogin = autoLogin || false;
        console.log("onFacebookSelected");
        this.showLoginProgress(true);
        this.authDelegate.SignInFacebook(autoLogin,
            this.fbPermissions,
            this.onPlatformLogin.bind(this, LoginType.FACEBOOK, this.onFacebookSelected.bind(this)));
        this.analyticsHelper.logCustomEvent("login_facebook_callback");
    }

    onGoogleSelected(autoLogin?: boolean) {
        autoLogin = autoLogin || false;
        this.showLoginProgress(true);
        this.authDelegate.SignInGoogle(autoLogin,
            this.onPlatformLogin.bind(this, LoginType.GOOGLE, this.onGoogleSelected.bind(this)));
        this.analyticsHelper.logCustomEvent("login_google_callback");
    }

    onAppleSelected() {
        console.log("onAppleSelected autoLogin");
        const autoLogin = this.authDelegate.isLoggedInApple();
        this.showLoginProgress(true);
        this.authDelegate.SignInApple(autoLogin,
            this.onPlatformLogin.bind(this, LoginType.APPLE, this.onAppleSelected.bind(this)));
        this.analyticsHelper.logCustomEvent("login_apple_callback");
    }

    private onPlatformLogin(loginType: LoginType, buttonSelectCallback: (autoLogin?: boolean) => void, status: LoginStatus, errorCode) {
        console.log("LoginFlow: onPlatformLogin: err: %s", JSON.stringify(errorCode));
        if (status == LoginStatus.LINK_FAIL) {
            this.logOutOtherPlatforms(loginType);
            this.authDelegate.SignInOnLinkFail(loginType);
            return;
        }
        const loginStr = LoginTypeToStr[loginType];
        if (status == LoginStatus.SUCCESS) {
            this.finishPlatformLogin(loginType);
        } else if (status == LoginStatus.CANCELLED) {
            this.showLoginProgress(false);
            this.sessionHelper.onLogOut();
            if (this.listener) {
                this.listener.onCancel();
            } else {
                console.error("LoginFlow: onPlatformLogin: onCancel listener is null");
            }
            this.analyticsHelper.logCustomEvent("login_" + loginStr + "_cancel");
            console.log("Login cancelled");
        } else {
            if (loginType == LoginType.FACEBOOK) {
                this.authDelegate.logOutFB();  // NOTE: This is required to initiate fb platform turn on flow, if it is off
            }
            this.showLoginProgress(false);
            if (this.listener) {
                this.listener.onFailure(loginType, buttonSelectCallback, this.onGuestSelected.bind(this));
            } else {
                console.error("LoginFlow: onPlatformLogin: onFailure listener is null");
            }
            this.analyticsHelper.logCustomEvent("login_" + loginStr + "_failed");
            console.log("Login failed");
        }
    }

    private logOutOtherPlatforms(currentLoginType: LoginType) {
        if (currentLoginType != LoginType.GOOGLE && this.authDelegate.isLoggedInGoogle()) {
            this.authDelegate.logOutGoogle();
        }
        if (!this.isLoginTypeFacebook(currentLoginType) && this.authDelegate.isLoggedInFB()) {
            this.authDelegate.logOutFB();
        }
        if (currentLoginType != LoginType.APPLE && this.authDelegate.isLoggedInApple()) {
            this.authDelegate.logOutApple();
        }
    }

    private finishPlatformLogin(loginType: LoginType) {
        const loginStr = LoginTypeToStr[loginType];
        this.sessionHelper.saveLoginType(loginStr as LoginTypeStr);
        console.log("finishPlatformLogin:", loginType);
        this.logOutOtherPlatforms(loginType);
        this.analyticsHelper.setSignupMethod(loginStr);
        this.analyticsHelper.logCustomEvent("login_" + loginStr + "_success");
        console.log("finishPlatformLogin getuser");
        this.onLoginSuccess();
    }

    private isLoggedIn(): boolean {
        if (this.sessionHelper.getLoginType() != LoginTypeStr.NONE) {
            return true;
        }
        return this.authDelegate.getLoginType() != LoginType.NONE;
    }

    private showLoginProgress(isShow: boolean) {
        if (this.listener) {
            this.listener.onProgress(isShow);
        } else {
            console.error("LoginFlow: showLoginProgress: listener is null");
        }
    }

    private onLoginSuccess() {
        isReLogin = true;
        if (this.listener) {
            this.listener.onSuccess();
        } else {
            console.error("LoginFlow: onLoginSuccess: listener is null");
        }
        this.dispatcher.emit(LoginEvents.LOGIN_SUCCESS);
    }
}