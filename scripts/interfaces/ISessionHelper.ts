import { LoginTypeStr } from "../AuthDefinitions";

export interface ISessionHelper {
    getLoginType(): LoginTypeStr;
    saveLoginType(loginType: LoginTypeStr);
    onLogOut(): void;
}