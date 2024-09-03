import { LoginType } from "../AuthDefinitions";
import { EventDispatcher } from "../EventDispatcher";
import IAuthDelegate from "./IAuthDelegate";
export type RetryHandler = (autoLogin?: boolean) => void;
export interface ILoginFlowListener {
    onSuccess(): void;
    onFailure(loginType: LoginType,  retryHandler: RetryHandler, alternativeHandler: RetryHandler): void;
    onProgress(showSpinner: boolean): void;
    onCancel(): void;
}
export interface ILoginFlowManager {
    getAuthDelegate(): IAuthDelegate;
    /**
     * Event dispatcher to listen to login events.
     */
    getDispatcher(): EventDispatcher;
    setListener(listener: ILoginFlowListener): void;
    /**
     * Initiate automatic login flow.
     * @param fallbackToGuest do guest login if auto login doesn't work?
     */
    autoLogin(fallbackToGuest: boolean);
    login(loginType: LoginType);

    clear(): void;
    logOut(): void;
}

