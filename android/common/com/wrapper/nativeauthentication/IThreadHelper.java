package com.wrapper.nativeauthentication;

public interface IThreadHelper {
    void runOnUiThread(Runnable runnable);
    void runOnGameThread(Runnable runnable);
}