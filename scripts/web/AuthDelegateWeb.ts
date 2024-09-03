import CommonAuthDelegate from "../CommonAuthDelegate";
import { IHttpRequestSender } from "../interfaces/IHttpRequest";
import { PlatformAuthWeb } from "./PlatformAuthWeb";

export default class AuthDelegateWeb extends CommonAuthDelegate {
    constructor(httpRequest: IHttpRequestSender, userServerAddress: string) {
        //TODO: Handle arguments null check with error popup
        const authService = new PlatformAuthWeb();
        super(authService, httpRequest, userServerAddress);
        authService.setListener(this.getListener());
    }
}
