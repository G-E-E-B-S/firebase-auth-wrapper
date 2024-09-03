import CommonAuthDelegate from "../CommonAuthDelegate";
import { IHttpRequestSender } from "../interfaces/IHttpRequest";

declare const authentication;
// TODO: implement account merge flow.
export default class AuthDelegateNative extends CommonAuthDelegate {
    constructor(firebaseAppGetter: any, httpRequest: IHttpRequestSender, userServerAddress: string) {
        super(authentication.getController(firebaseAppGetter), httpRequest, userServerAddress);
        authentication.setListener(this.getListener());
    }
}

