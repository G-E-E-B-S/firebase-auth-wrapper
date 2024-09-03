export type EventParams = { [index: string]: any };
export interface IAnalyticsHelper {
    logCustomEvent(eventName: string, params?: EventParams);
    setSignupMethod(method: string);
}