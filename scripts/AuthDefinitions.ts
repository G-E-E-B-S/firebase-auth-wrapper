export enum LoginStatus {
    SUCCESS= 0,
    CANCELLED,
    ERROR,
    LINK_FAIL
}

export interface  INativeLoginListener {
    onFacebookSelected(autoLogin?: boolean): void;
    onGoogleSelected(autoLogin?: boolean): void;
    onAppleSelected(autoLogin?: boolean): void;
    onGuestSelected(autoLogin? : boolean): void;
}

export enum LoginTypeStr {
    NONE = "none",
    ANONYMOUS = "anonymous",
    FACEBOOK = "facebook",
    FACEBOOK_GAMING = "facebook_gaming",
    GOOGLE = "google",
    GUEST = "guest",
    APPLE = "apple"
}
export enum LoginType {
    NONE,
    ANONYMOUS,
    FACEBOOK,
    FACEBOOK_GAMING,
    GOOGLE,
    APPLE,
}

export const LoginTypeToStr = [
    LoginTypeStr.NONE,
    LoginTypeStr.ANONYMOUS,
    LoginTypeStr.FACEBOOK,
    LoginTypeStr.FACEBOOK_GAMING,
    LoginTypeStr.GOOGLE,
    LoginTypeStr.APPLE
];

export type LoginSuccessCallback = () => void;
export enum LoginEvents {
    LOGIN_SUCCESS = "login_success"
}
export interface SignInGGRequest {
    ggToken: string;
    userIdToConnectTo?: string;
}
export interface InstantFBGamingLoginSignInRequest {
    igUserId: string,
    appScopedUserId: string,
}

export interface SignInIGGGRequest {
    signature: string;
    igPlayerId: string;
    ggId: string;
    name: string;
    email: string;
}

export interface GGProfileResponse {
    name: string;
    id: string;
    email: string;
}
export interface NativeFBGamingLoginSignInResponse {
    error?: SignInGGError,
    data? : {
        userRecord: string,
        accessToken: string,
    }
}
export interface FBGamingLoginSignInResponse {
    error?: SignInGGError,
    data? : {
        userId: string,
        accessToken: string,
    }
}
export interface SignInGGResponse {
    firebaseToken: string;
    error?: SignInGGError;
    mergeInfo?: AccountMergeInfo;
}

export interface AccountMergeInfo {
    account1: UserAccountData;
    account2: UserAccountData;
    mergedData;
}

export interface UserAccountData {
    userId: string;
    userData;
}

export interface MergeSigninGGRequest extends MergeSigninRequestBase {
    ggToken: string;
}

export interface MergeSigninIGGGRequest extends MergeSigninRequestBase {
    ggId: string;
    igSignature: string;
    igPlayerId: string;
}

export interface MergeSigninRequestBase {
    userId1: string;
    userId2: string;
    mergeOption: MergeOption;
}

export enum MergeOption {
    FIRST_USER = 1,
    SECOND_USER = 2,
    BOTH = 3
}

export enum SignInGGError {
    GG_TOKEN_ERROR = "gg_token_failed",
    FIREBASE_TOKEN_ERROR = "firebase_token_failed",
    USER_CREATION_ERROR = "user_creation_failed",
    PROVIDER_UPDATE_ERROR = "provider_updation_failed",
    USER_GET_ERROR = "user_getting_failed",
    FAILED = "failed",
    IG_SIGNATURE_INVALID = "ig_signature_invalid",
    MERGE_ERROR = "merge_failed"
}

export const GRAPH_API_ADDRESS = "https://graph.fb.gg/v12.0/";
export type MergeOptionChosenCallback = (option: MergeOption) => void;
export type MergeOptionsCallback = (mergeInfo: AccountMergeInfo, selectionCallback: MergeOptionChosenCallback) => void;
