import { IAnalyticsHelper } from "./interfaces/IAnalyticsHelper";
import { IHttpRequestSender } from "./interfaces/IHttpRequest";
import { ILoginFlowManager } from "./interfaces/ILoginFlowManager";
import { ISessionHelper } from "./interfaces/ISessionHelper";
import AuthDelegateNative from "./native/AuthDelegateNative";
import { LoginFlowManagerNative } from "./native/LoginFlowManagerNative";

export type AuthPlatform = "ig" | "web" | "native";
export interface ILoginGameHelper {
    getPlatform(): AuthPlatform;
    getFirebaseAppGetter(): any;
}
export class LoginFlowManager {
    static init(
        helper: ILoginGameHelper,
        analyticsHelper: IAnalyticsHelper,
        sessionHelper: ISessionHelper,
        httpRequestSender: IHttpRequestSender,
        userServerAddress: string,
        permissions: string[]) {
        const firebaseAppGetter = helper.getFirebaseAppGetter();
        switch (helper.getPlatform()) {
            case "ig":
                this.initForIG();
                break;
            case "web":
                this.initForWeb();
                break;
            case "native":
                this.initForNative(firebaseAppGetter, analyticsHelper, sessionHelper, httpRequestSender, userServerAddress, permissions);
                break;
            default:
                console.error("LoginFlowManager::init - unknown platform");
        }
    }

    static getManager(): ILoginFlowManager {
        return LoginFlowManager.manager;
    }
    private static initForIG() {
    }
    private static initForNative(
        firebaseAppGetter: any,
        analyticsHelper: IAnalyticsHelper,
        sessionHelper: ISessionHelper,
        httpRequestSender: IHttpRequestSender,
        userServerAddress: string,
        permissions: string[]) {
        const delegate = new AuthDelegateNative(firebaseAppGetter, httpRequestSender, userServerAddress);
        this.manager = new LoginFlowManagerNative(analyticsHelper, delegate, sessionHelper, permissions)
    }
    private static initForWeb() {
    }

    private static manager: ILoginFlowManager;
}
