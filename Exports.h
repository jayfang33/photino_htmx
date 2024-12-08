#pragma once

#include "Photino.Dialog.h"

extern "C"
{

#ifdef _WIN32
    void Photino_register_win32(HINSTANCE hInstance);
    HWND Photino_getHwnd_win32(Photino* instance);
    void Photino_setWebView2RuntimePath_win32(Photino* instance, AutoString webView2RuntimePath);

#elif __APPLE__
    EXPORTED void Photino_register_mac();
#endif

    Photino* Photino_ctor(PhotinoInitParams* initParams);   
    void Photino_dtor(Photino* instance);
    void Photino_Center(Photino* instance);
    void Photino_ClearBrowserAutoFill(Photino* instance);
    void Photino_Close(Photino* instance);

    void Photino_GetTransparentEnabled(Photino* instance, bool* enabled);
    void Photino_GetContextMenuEnabled(Photino* instance, bool* enabled);
    void Photino_GetDevToolsEnabled(Photino* instance, bool* enabled);
    void Photino_GetFullScreen(Photino* instance, bool* fullScreen);
    void Photino_GetGrantBrowserPermissions(Photino* instance, bool* grant);

    AutoString Photino_GetUserAgent(Photino* instance);
    void Photino_GetMediaAutoplayEnabled(Photino* instance, bool* enabled);
    void Photino_GetFileSystemAccessEnabled(Photino* instance, bool* enabled);

    void Photino_GetWebSecurityEnabled(Photino* instance, bool* enabled);
    void Photino_GetJavascriptClipboardAccessEnabled(Photino* instance, bool* enabled);
    void Photino_GetMediaStreamEnabled(Photino* instance, bool* enabled);
    void Photino_GetSmoothScrollingEnabled(Photino* instance, bool* enabled);
    void Photino_GetMaximized(Photino* instance, bool* isMaximized);
    void Photino_GetMinimized(Photino* instance, bool* isMinimized);
    void Photino_GetIgnoreCertificateErrorsEnabled(Photino* instance, bool *disabled);

    void Photino_GetPosition(Photino* instance, int* x, int* y);
    void Photino_GetResizable(Photino* instance, bool* resizable);
    unsigned int Photino_GetScreenDpi(Photino* instance);
    void Photino_GetSize(Photino* instance, int* width, int* height);
    void Photino_GetTitle(Photino* instance, AutoString* title);
    void Photino_GetTopmost(Photino* instance, bool* topmost);
    void Photino_GetZoom(Photino* instance, int* zoom);

    void Photino_NavigateToString(Photino* instance, AutoString content);
    void Photino_NavigateToUrl(Photino* instance, AutoString url);
    void Photino_Restore(Photino* instance);
    void Photino_SendWebMessage(Photino* instance, AutoString message);
    void Photino_SetTransparentEnabled(Photino* instance, bool enabled);
    void Photino_SetContextMenuEnabled(Photino* instance, bool enabled);
    void Photino_SetDevToolsEnabled(Photino* instance, bool enabled);
    void Photino_SetFullScreen(Photino* instance, bool fullScreen);
    void Photino_SetIconFile(Photino* instance, AutoString filename);
    void Photino_SetMaximized(Photino* instance, bool maximized);
    void Photino_SetMaxSize(Photino* instance, int width, int height);
    void Photino_SetMinimized(Photino* instance, bool minimized);
    void Photino_SetMinSize(Photino* instance, int width, int height);
    void Photino_SetPosition(Photino* instance, int x, int y);
    void Photino_SetResizable(Photino* instance, bool resizable);
    void Photino_SetSize(Photino* instance, int width, int height);
    void Photino_SetTitle(Photino* instance, AutoString title);
    void Photino_SetTopmost(Photino* instance, bool topmost);
    void Photino_SetZoom(Photino* instance, int zoom);
    
    void Photino_ShowNotification(Photino* instance, AutoString title, AutoString body);
    void Photino_WaitForExit(Photino* instance);

    AutoString* Photino_ShowOpenFile(Photino* inst, AutoString title, AutoString defaultPath, bool multiSelect, AutoString* filters, int filterCount, int* resultCount);
    AutoString* Photino_ShowOpenFolder(Photino* inst, AutoString title, AutoString defaultPath, bool multiSelect, int* resultCount);
    AutoString Photino_ShowSaveFile(Photino* inst, AutoString title, AutoString defaultPath, AutoString* filters, int filterCount);
    DialogResult Photino_ShowMessage(Photino* inst, AutoString title, AutoString text, DialogButtons buttons, DialogIcon icon);

    void Photino_AddCustomSchemeName(Photino* instance, AutoString scheme);
    void Photino_GetAllMonitors(Photino* instance, GetAllMonitorsCallback callback);
    void Photino_SetClosingCallback(Photino* instance, ClosingCallback callback);
    void Photino_SetFocusInCallback(Photino* instance, FocusInCallback callback);
    void Photino_SetFocusOutCallback(Photino* instance, FocusOutCallback callback);

    void Photino_SetMovedCallback(Photino* instance, MovedCallback callback);
    void Photino_SetResizedCallback(Photino* instance, ResizedCallback callback);
    void Photino_Invoke(Photino* instance, ACTION callback);

}