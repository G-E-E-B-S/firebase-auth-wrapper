import { AccountMergeInfo, FBGamingLoginSignInResponse, GGProfileResponse, InstantFBGamingLoginSignInRequest, LoginType } from "../AuthDefinitions";
import { BaseAuthDelegate } from "../BaseAuthDelegate";
import IAuthDelegate, { FetchUserCallback, StringCallback } from "../interfaces/IAuthDelegate";
import { IErrorLogger } from "../interfaces/IErrorLogger";
import { IHttpRequestSender } from "../interfaces/IHttpRequest";

export default class AuthDelegateInstant extends BaseAuthDelegate implements IAuthDelegate {
    private token = "";
    private accountMergeInfo: AccountMergeInfo = null;
    private fbGamingApiAddress = "";
    private requestSender: IHttpRequestSender;
    private errorLogger: IErrorLogger;
    private appScopedUserId: string;
    constructor(requestSender: IHttpRequestSender,  fbGamingApiAddress: string, errorLogger: IErrorLogger) {
        super();
        this.fbGamingApiAddress = fbGamingApiAddress;
        this.requestSender = requestSender;
        this.errorLogger = errorLogger;
    }
    getLoginProviderUserId(): Promise<string> {
        return this.getGGID();
    }
    getLoginProviderAccessToken(): Promise<string> {
        return this.getSignedPlayerInfoAsync().then(result => {
            return result.getSignature();
        })
    }
    signOut(): void {
        // No-op
    }
    getLoginType(): LoginType {
        return LoginType.FACEBOOK_GAMING;
    }

    getPlayerSignatureAsync(callback: StringCallback) {
        callback("");
    }

    fetchToken() {
        this.getPlayerSignatureAsync(() => {
            // no-op
        });
    }

    getToken(): string {
        return this.token;
    }

    getUserID() {
        if (this.forcedUserId) {
            return this.forcedUserId;
        }
        return "fb_" + this.getPlayerID();
    }
    getPlatformId(): string {
        return this.getPlayerID();
    }

    getUserDisplayName() {
        if (typeof FBInstant === 'undefined') {
            return "";
        }

        if (FBInstant.getSupportedAPIs().indexOf("player.getName") === -1) {
            return "";
        }

        try {
            return FBInstant.player.getName();
        } catch (e) {
            return "";
        }
    }
    
    getUserPhotoUrl() {
        if (typeof FBInstant === 'undefined') {
            return "";
        }

        if (FBInstant.getSupportedAPIs().indexOf("player.getPhoto") === -1) {
            return "";
        }

        try {
            return FBInstant.player.getPhoto();
        } catch (e) {
            return "";
        }
    }

    getFacebookUserId() : string {
        return this.getPlayerID();
    }

    getFacebookAccessToken(): string {
        return "";
    }
    isLoggedInFBGaming(): boolean {
        return true;
    }

    isLoggedInFB(): boolean {
        return false;
    }

    isLoggedInGoogle(): boolean {
        return false;
    }

    isLoggedInApple(): boolean {
        return false;
    }

    isLoggedInAnonymous(): boolean {
        return false;
    }
    /**
     * Sign into gaming login on instant first.
     * @param callback
     */
    signInFirebase(callback: FetchUserCallback) {
        const authCallback = (success: boolean, data: FBGamingLoginSignInResponse) => {
            if (!success || !data || (data && data.error)) {
                this.errorLogger.logError("sigin_ig_gg_firebase error", (data? data.error: null));
                callback(false);
                return;
            }
            callback(true);
        }
        // NOTE: used for getting API failure data
        // can be removed after getting data.
        this.getGamingLoginPayload().then((request) => {
            const address = this.fbGamingApiAddress + "/signin_gaming_login_on_instant";
            this.requestSender.sendPostRequest(address, JSON.stringify(request), authCallback)
        })
    }
    /**
     * You can directly get instant game info. Then call your backend to do the signing and
     * user fetch
     * @returns InstantFBGamingLoginSignInRequest app scoped id and player id for user.
     */
    async getGamingLoginPayload(): Promise<InstantFBGamingLoginSignInRequest> {
        const appScopedUserId = await this.getGGID();
        const request: InstantFBGamingLoginSignInRequest = {
            igUserId: this.getPlayerID(),
            appScopedUserId,
        }
        return request
    }

    getAccountMergeInfo(): AccountMergeInfo {
        return this.accountMergeInfo;
    }

    clearAccountMergeInfo() {
        this.accountMergeInfo = null;
    }
    private getPlayerID() {
        if (typeof FBInstant === 'undefined') {
            return "";
        }

        if (FBInstant.getSupportedAPIs().indexOf("player.getID") === -1) {
            return null;
        }

        try {
            return FBInstant.player.getID();
        } catch (e) {
            this.errorLogger.logError("player.getID error", e);
            return "";
        }
    }
    private getGGID(): Promise<string> {
        if (this.appScopedUserId) {
            return Promise.resolve(this.appScopedUserId);
        }
        if (typeof FBInstant === 'undefined') {
            return Promise.resolve("");
        }
        try {
            //@ts-ignore
            return FBInstant.player.getASIDAsync().then((val) => {
                this.appScopedUserId = val;
                return val;
            }).catch((error) => {
				return error;
            });
        } catch (e) {
            this.errorLogger.logError("player.getASIDAsync error", e)
            return Promise.reject("Api error");
        }
    }

    private getProfile(): Promise<GGProfileResponse> {
        if (typeof FBInstant === 'undefined') {
            return Promise.resolve(null);
        }
        try {
            //@ts-ignore
            return FBInstant.graphApi.requestAsync('/me?fields=email,name').then(val => {
                return val;
            }).catch((error) => {
				return error;
            });
        } catch (e) {
            this.errorLogger.logError("getProfile error", e);
            return Promise.reject("Api error");
        }
    }
    private getSignedPlayerInfoAsync(): Promise<FBInstant.SignedPlayerInfo> {
        if (typeof FBInstant === 'undefined') {
            return Promise.resolve(null);
        }
        if (FBInstant.getSupportedAPIs().indexOf("player.getSignedPlayerInfoAsync") === -1) {
            return Promise.reject("Api not supported");
        }
        try {
            return FBInstant.player.getSignedPlayerInfoAsync().then((result) => {
                return result;
            }).catch((error) => {
				return error;
            });
        } catch (e) {
            return Promise.reject("Api error");
        }
    }

}

// NOTE: This is to make this available to main.js
//@ts-ignore
window.AuthDelegateInstant = AuthDelegateInstant;
