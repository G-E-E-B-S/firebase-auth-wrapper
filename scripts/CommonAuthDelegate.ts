import {
    FBGamingLoginSignInResponse,
    LoginStatus, LoginType
} from "./AuthDefinitions";
import { BaseAuthDelegate } from "./BaseAuthDelegate";
import IAuthDelegate, { FetchUserCallback, StringCallback } from "./interfaces/IAuthDelegate";
import { IHttpRequestSender } from "./interfaces/IHttpRequest";

const MaxInitAuthFail = 10;

export interface IPlatformAuth {
    isLoggedInApple(): boolean;
    tryInit(): void;
    isReady(): boolean;
    getUserDisplayName(): string;
    getUserPhotoUrl(): string;
    getFacebookAccessToken(): string;
    getFacebookUserId(): string;
    getToken(): string;
    fetchToken(): void;
    isAppleSignInSupported(): boolean;
    isLoggedInFB(): boolean;
    isLoggedInFBGaming(): boolean;
    isLoggedInGoogle(): boolean;
    isLoggedInAnonymous(): boolean;
    SignInAnonymously(autoLogin: boolean): void;
    SignInFacebook(autoLogin: boolean, permissions: string[]): void;
    SignInGoogle(autoLogin: boolean): void;
    SignInApple(autoLogin: boolean): void;
    SignInOnLinkFail(type: number): void;
    logOutFB(): void;
    logOutGoogle(): void;
    logOutApple(): void;
    signOut(): void;
    OnGGFirebaseTokenReceived(accessToken: string): void;
    getUserID(): string;
}

export interface IAuthListener {
    OnSuccess(): void;
    OnCancel(): void;
    OnFailure(): void;
    OnLinkAccountFail(): void;
    OnFbGamingLogin(gamingLoginToken: string): void;
}
type AuthCallback = (status: LoginStatus) => void;
// TODO: implement account merge flow.
export default class CommonAuthDelegate extends BaseAuthDelegate implements IAuthDelegate {
    private platformAuth: IPlatformAuth;
    private authInitFailCount = 0;
    private httpRequest: IHttpRequestSender;
    private fbGamingApiAddress: string;
    private fbPermissions: string[];
    protected authCallback;
    protected listener: IAuthListener;
    constructor(platformAuthImpl: IPlatformAuth, httpRequest: IHttpRequestSender, userServerAddress: string) {
        super();
        this.httpRequest = httpRequest;
        this.fbGamingApiAddress = userServerAddress;
        this.platformAuth = platformAuthImpl;
        this.initListener();
    }

    //used by native platforms only
    setListener(listener): void {
        this.initListener(listener);
    }

    private initListener(listener = {} as any) {
        listener.OnSuccess = (): void => {
            console.log("OnLoginSuccess");
            if (this.authCallback) {
                this.authCallback(LoginStatus.SUCCESS);
            }
        };
        listener.OnCancel = () => {
            console.log("OnLoginCancelled");
            if (this.authCallback) {
                this.authCallback(LoginStatus.CANCELLED);
            }
        };
        listener.OnFailure = () => {
            console.log("OnLoginError");
            if (this.authCallback) {
                this.authCallback(LoginStatus.ERROR);
            }
        };
        listener.OnLinkAccountFail = (errorCode: number) => {
            console.log("OnLoginLinkFailed");
            if (this.authCallback) {
                this.authCallback(LoginStatus.LINK_FAIL, errorCode);
            }
        };
        listener.OnFbGamingLogin = (gamingToken: string) => {
            this.onFBGamingLogin(gamingToken);
        };
        this.listener = listener;
    }
    getListener(): IAuthListener {
        return this.listener;
    }
    getPlatformId(): string {
        return this.getUserID();
    }
    getLoginProviderUserId(): Promise<string> {
        // TODO:
        return Promise.resolve("");
    }
    getLoginProviderAccessToken(): Promise<string> {
        throw new Error("Method not implemented.");
    }
    getLoginType(): LoginType {
        if (this.isLoggedInFBGaming()) {
            return LoginType.FACEBOOK_GAMING
        }
        if (this.isLoggedInFB()) {
            return LoginType.FACEBOOK;
        }
        if (this.isLoggedInApple()) {
            return LoginType.APPLE;
        }
        if (this.isLoggedInGoogle()) {
            return LoginType.GOOGLE;
        }
        if (this.isLoggedInAnonymous()) {
            return LoginType.ANONYMOUS;
        }
        return LoginType.NONE;
    }

    getUserID(): string {
        return this.platformAuth.getUserID();
    }

    fetchToken() {
        this.platformAuth.fetchToken();
    }

    getToken(): string {
        return this.platformAuth.getToken();
    }

    getFacebookUserId(): string {
        return this.platformAuth.getFacebookUserId();
    }

    getFacebookAccessToken(): string {
        return this.platformAuth.getFacebookAccessToken();
    }
    getUserPhotoUrl(): string {
        return this.platformAuth.getUserPhotoUrl();
    }

    getUserDisplayName(): string {
        return this.platformAuth.getUserDisplayName();
    }

    isAuthReady() {
        if (!this.platformAuth) {
            return false;
        }
        return this.platformAuth.isReady();
    }

    tryAuthInit() {
        if (this.authInitFailCount >= MaxInitAuthFail) {
            return;
        }
        if (!this.platformAuth.isReady()) {
            this.platformAuth.tryInit();
        }
        if (!this.platformAuth.isReady()) {
            this.authInitFailCount++;
        }
    }

    isLoggedInAnonymous(): boolean {
        return this.platformAuth.isLoggedInAnonymous();
    }

    isLoggedInGoogle(): boolean {
        return this.platformAuth.isLoggedInGoogle();
    }
    isLoggedInFBGaming(): boolean {
        return this.platformAuth.isLoggedInFBGaming();
    }
    isLoggedInFB(): boolean {
        return this.platformAuth.isLoggedInFB();
    }

    isAppleSignInSupported(): boolean {
        return this.platformAuth.isAppleSignInSupported();
    }

    isLoggedInApple(): boolean {
        return this.platformAuth.isLoggedInApple();
    }

    isLoggedInAnyPlatform(): boolean {
        return this.getLoginType() != LoginType.NONE;
    }

    SignInAnonymously(autoLogin: boolean, callback: AuthCallback) {
        this.authCallback = callback;
        this.platformAuth.SignInAnonymously(autoLogin);
    }

    SignInFacebook(autoLogin: boolean, permissions: string[], callback: AuthCallback) {
        this.fbPermissions = permissions;
        this.authCallback = callback;
        this.platformAuth.SignInFacebook(autoLogin, permissions);
    }

    SignInGoogle(autoLogin: boolean, callback: AuthCallback) {
        this.authCallback = callback;
        this.platformAuth.SignInGoogle(autoLogin);
    }

    SignInApple(autoLogin: boolean, callback: AuthCallback) {
        this.authCallback = callback;
        this.platformAuth.SignInApple(autoLogin);
    }

    SignInOnLinkFail(type: number) {
        this.platformAuth.SignInOnLinkFail(type);
    }

    logOutGoogle(): void {
        this.platformAuth.logOutGoogle();
    }

    logOutFB(): void {
        this.platformAuth.logOutFB();
    }

    logOutApple() {
        this.platformAuth.logOutApple();
    }

    signInFirebase(callback: FetchUserCallback) {
        callback(true);
    }

    getPlayerSignatureAsync(callback: StringCallback) {
        callback(this.getToken());
    }

    signOut(): void {
        const loginType = this.getLoginType();
        if (loginType == LoginType.FACEBOOK || loginType == LoginType.FACEBOOK_GAMING) {
            this.platformAuth.logOutFB();
        } else if (loginType == LoginType.GOOGLE) {
            this.platformAuth.logOutGoogle();
        } else if (loginType == LoginType.APPLE) {
            this.platformAuth.logOutApple();
        }
        this.platformAuth.signOut();
    }
    protected onFBGamingLogin(gamingLoginToken: string) {
        console.log("AuthDelegate gg token:", gamingLoginToken);
        const address = this.getAddress();
        const payload = JSON.stringify({
            gamingLoginToken,
            userId: this.getUserID(),
        });
        this.httpRequest.sendPostRequest(address, payload, (success: boolean, response: FBGamingLoginSignInResponse) => {
            // TODO: implement merge
            if (success) {
                if (response.data && response.data.accessToken) {
                    this.platformAuth.OnGGFirebaseTokenReceived(response.data.accessToken);
                    return;
                }
                console.error("Got success but improper format in response %s", JSON.stringify(response));
            }
            if (response && response.error) {
                console.log("LoginFlow: AuthDelegateNative signin gg error:", response.error);
            }
            if (this.authCallback) {
                this.authCallback(LoginStatus.ERROR);
            }
        });
        return;
    }
    private getAddress(): string {
        if (this.getUserID()) {
            return this.fbGamingApiAddress + "/link_and_signin_gaming_login_on_native";
        }
        return this.fbGamingApiAddress + "/signin_gaming_login_on_native";
    }

	private isInstantGame(): boolean {
		//@ts-ignore
		if (typeof FBInstant === 'undefined') {
			return false;
		}
		return true;
	}    
}