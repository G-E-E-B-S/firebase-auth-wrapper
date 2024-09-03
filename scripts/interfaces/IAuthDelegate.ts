import { LoginType } from "../AuthDefinitions";

export type PlatformUserDataFetchCallback = (data : any, dataItems : Array<string>) => void;
export type FetchUserCallback = (success : boolean) => void;
export type StringCallback = (value: string) => void;

export default interface IAuthDelegate {
    getUserID() : string;
    /**
     * Sometimes user id is communicated by server or firebase-auth.
     * In that case force set id (for example in instant game flow)
     * @param userId 
     */
    forceSetUserId(userId: string): void;
    fetchToken();
    getToken(): string;
    getLoginType(): LoginType;
    getLoginProviderUserId(): Promise<string>;
    getLoginProviderAccessToken(): Promise<string>;
    getPlatformId(): string;
    getFacebookUserId() : string;
    getFacebookAccessToken(): string;

    getUserPhotoUrl() : string;
    getUserDisplayName() : string;
    getPlayerSignatureAsync(callback : StringCallback);
    signInFirebase(callback: FetchUserCallback);
    signOut(): void;
}