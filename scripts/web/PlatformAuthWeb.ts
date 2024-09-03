import { LoginType } from "../AuthDefinitions";
import { IAuthListener, IPlatformAuth } from "../CommonAuthDelegate";

declare var firebase;
declare var FB;
export interface IUserData {
    uid: string,
    isAnonymous: boolean,
}
export class PlatformAuthWeb implements IPlatformAuth {
    private listener: IAuthListener;
    private authService: any = firebase.auth();
    private currentUser: IUserData;
    private loggedInType: any;
    constructor() {
        const type = localStorage.getItem('logged_in_type');
        if (type) {
            this.loggedInType = Number(type);
        } else {
            this.loggedInType = LoginType.ANONYMOUS;
        }
    }
    setListener(listener: IAuthListener) {
        this.listener = listener;
    }
    isLoggedInApple(): boolean {
        return false;
    }
    tryInit(): void {
        throw new Error("Method not implemented.");
    }
    isReady(): boolean {
        throw new Error("Method not implemented.");
    }
    getUserDisplayName(): string {
        return "";
    }
    getUserPhotoUrl(): string {
        return "";
    }
    getFacebookAccessToken(): string {
        throw new Error('Get Facebook Access Token');
    }
    getFacebookUserId(): string {
        return "";
    }
    getToken(): string {
        return "";
    }
    fetchToken() {
        return this.getToken();
    }
    isAppleSignInSupported(): boolean {
        return false;
    }
    isLoggedInFB(): boolean {
        return this.loggedInType === LoginType.FACEBOOK;
    }
    isLoggedInFBGaming(): boolean {
        return this.loggedInType === LoginType.FACEBOOK_GAMING;
    }
    isLoggedInGoogle(): boolean {
        return this.loggedInType === LoginType.GOOGLE;
    }
    isLoggedInAnonymous(): boolean {
        return this.loggedInType === LoginType.ANONYMOUS;
    }
    SignInAnonymously(autoLogin: boolean): void {
        if (!autoLogin) {
            this.setLoginType(null);
            this.authService
                .signInAnonymously().then(() => {
                    const user = this.authService.currentUser;
                    this.setCurrentUser(user);
                    this.setLoginType(LoginType.ANONYMOUS);
                    console.log("LoginFlow: Anonymous signin success");
                    this.listener.OnSuccess();
                }).catch((error) => {
                    console.log("LoginFlow: Anonymous signin failed");
                    this.listener.OnFailure();
                });
        } else {
            console.log("LoginFlow: Anonymous autologin");
            this.autoLoginFromFirebaseAuth();
        }
    }
    SignInFacebook(autoLogin: boolean, permissions: string[]): void {
        if (!autoLogin) {
            this.setLoginType(null);
            FB.login((response) => {
                console.log('LoginFlow: Facebook login call');
                if (response) {
                    if (response.status === 'connected') {
                        const accessToken = response.authResponse.accessToken;
                        this.listener.OnFbGamingLogin(accessToken);
                    } else {
                        this.listener.OnFailure();
                    }
                } else {
                    this.listener.OnFailure();
                }
            }, { scope: permissions.join() });
        } else {
            console.log("LoginFlow: Facebook autologin");
            this.autoLoginFromFirebaseAuth();
        }
    }
    SignInGoogle(autoLogin: boolean): void {
        if (!autoLogin) {
            this.setLoginType(null);
            var provider = new firebase.auth.GoogleAuthProvider();
            provider.setCustomParameters({
                prompt: 'select_account'
            });
            this.authService.currentUser.linkWithPopup(provider).then((result) => {
                this.setCurrentUser(result.user);
                this.setLoginType(LoginType.GOOGLE);
                console.log('LoginFlow: Google login with firebase sigin success');
                this.listener.OnSuccess();
            }).catch(error => {
                const errorCode = error.code
                console.log('LoginFlow: Google login with firebase sigin failed ', errorCode);
                if (errorCode === 'auth/provider-already-linked' ||
                    errorCode === 'auth/credential-already-in-use' ||
                    errorCode === 'auth/email-already-in-use') {
                    this.credentialFromLinkError = error.credential;
                    this.listener.OnLinkAccountFail();
                } else {
                    this.listener.OnFailure();
                }
            });
        } else {
            console.log("LoginFlow: Google autologin");
            this.autoLoginFromFirebaseAuth();
        }
    }
    SignInApple(autoLogin: boolean): void {
        throw new Error("Method not implemented.");
    }
    SignInOnLinkFail(type: number): void {
        this.authService.signInWithCredential(this.credentialFromLinkError).then((result) => {
            this.setCurrentUser(result.user);
            this.setLoginType(type);
            console.log('LoginFlow: Firebase link signin success');
            this.listener.OnSuccess();
        }).catch((error) => {
            console.log("LoginFlow: Firebase link signin failed");
            this.listener.OnFailure();
        })
    }
    logOutFB(): void {
        FB.logout((response) => {
            console.log('LoginFlow: Facebook logout success');
        });
    }
    logOutGoogle(): void {
    }
    logOutApple(): void {
        throw new Error("Method not implemented.");
    }
    signOut(): void {
        this.setLoginType(null);
        this.authService.signOut().then(() => {
            console.log('LoginFlow: Firebase logout success');
        }).catch(err => {
            console.log('LoginFlow: Firebase logout failed');
        })
    }
    OnGGFirebaseTokenReceived(accessToken: string): void {
        this.authService.signInWithCustomToken(accessToken).then((userCredential) => {
            this.setCurrentUser(userCredential.user);
            this.setLoginType(LoginType.FACEBOOK);
            this.listener.OnSuccess();
            console.log('LoginFlow: Firebase success login after fb login');
        }).catch(err => {
            console.log('LoginFlow: Firebase failure login after fb login');
        });
    }
    getUserID(): string {
        return this.currentUser ? this.currentUser.uid : "";
    }
    private setCurrentUser(user) {
        this.currentUser = {
            uid: user.uid,
            isAnonymous: user.isAnonymous
        }
        return;
    }
    private setLoginType(loginType) {
        this.loggedInType = loginType;
        if (loginType) {
            localStorage.setItem('logged_in_type', this.loggedInType.toString());
        } else localStorage.removeItem('logged_in_type');
    }
    private autoLoginFromFirebaseAuth() {
        const unsubscribe = this.authService.onAuthStateChanged((user) => {
            if (user) {
                this.setCurrentUser(user);
                this.listener.OnSuccess();
            } else {
                console.error('FirebaseAuthError: No user found for autologin');
            }
            unsubscribe();
        })
    }

    private credentialFromLinkError: any;
}