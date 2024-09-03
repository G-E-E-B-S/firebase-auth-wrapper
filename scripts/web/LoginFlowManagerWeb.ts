import { CommonLoginFlowManager } from "../CommonLoginFlowManager";
import { IAnalyticsHelper } from "../interfaces/IAnalyticsHelper";
import { ISessionHelper } from "../interfaces/ISessionHelper";
import AuthDelegateWeb from "./AuthDelegateWeb";

let isReLogin = false;

export default class LoginFlowManagerWeb extends CommonLoginFlowManager {
    constructor(analyticsHelper: IAnalyticsHelper, authDelegate: AuthDelegateWeb, sessionHelper: ISessionHelper, fbPermissions: string[]) {
        super(analyticsHelper, authDelegate, sessionHelper, fbPermissions);
    }
}
