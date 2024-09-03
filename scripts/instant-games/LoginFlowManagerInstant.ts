import { LoginType } from "../AuthDefinitions";
import { EventDispatcher } from "../EventDispatcher";
import IAuthDelegate from "../interfaces/IAuthDelegate";
import { ILoginFlowListener, ILoginFlowManager } from "../interfaces/ILoginFlowManager";

export class LoginFlowManagerInstant implements ILoginFlowManager {
    private authDelegate: IAuthDelegate;
    private dispatcher: EventDispatcher;
    private listener: ILoginFlowListener;
    constructor(authDelegate: IAuthDelegate) {
        this.dispatcher = new EventDispatcher();
        this.authDelegate = authDelegate;
    }
    login(loginType: LoginType): void {
        this.listener.onSuccess();
    }
    setListener(listener: ILoginFlowListener): void {
        this.listener = listener;
    }
    logOut(): void {
        throw new Error("Method not supported.");
    }

    getAuthDelegate(): IAuthDelegate {
        return this.authDelegate;
    }
    
    autoLogin() {
        this.listener.onSuccess();
    }

    clear() {
        // no - op        
    }

    getDispatcher(): EventDispatcher {
        return this.dispatcher;
    }
}

