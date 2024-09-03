import CommonAuthDelegate from "../CommonAuthDelegate";
import { CommonLoginFlowManager } from "../CommonLoginFlowManager";
import { IAnalyticsHelper } from "../interfaces/IAnalyticsHelper";
import { ISessionHelper } from "../interfaces/ISessionHelper";

let isReLogin = false;


export class LoginFlowManagerNative extends CommonLoginFlowManager {
    constructor(analyticsHelper: IAnalyticsHelper, authDelegate: CommonAuthDelegate, sessionHelper: ISessionHelper, fbPermissions: string[]) {
        super(analyticsHelper, authDelegate, sessionHelper, fbPermissions);
    }
}

