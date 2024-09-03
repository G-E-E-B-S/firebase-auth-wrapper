import { FBGamingLoginSignInResponse } from "../AuthDefinitions";

export interface IHttpRequestSender {
    sendGetRequest(address: string, callback: (success: boolean, data: FBGamingLoginSignInResponse) => void, objForQueryParams? : any, objForB64Payload? : any): void;
    sendPostRequest(address: string, mergeReqStr: string, callback: (success: boolean, data: FBGamingLoginSignInResponse) => void): void;
}