export class BaseAuthDelegate {
    protected forcedUserId = "";
    forceSetUserId(userId: string): void {
        this.forcedUserId = userId;
    }
}