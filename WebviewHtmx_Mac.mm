
#include "Photino.h"

#include <Cocoa/Cocoa.h>


void* WebResReqCb(AutoString url, int* outNumBytes, AutoString* outContentType)
{
    printf("WebResReqCb: %s\n", url);


    char *a = "<html> <a href=\"/from_cb\"> link </a></html>";

//char *a = "123123";

    char *buf  = new char[strlen(a) + 1];

    strcpy(buf, a);

    *outNumBytes =  strlen(a);
    *outContentType = "text/html";

    printf("WebResReqCb 2: %s\n", url);


    return (void*)buf;
}

int main(int argc, char *argv[]) {

    // // Create the application
    // NSApplication *app = [NSApplication sharedApplication];
    // [app setActivationPolicy:NSApplicationActivationPolicyRegular];
    // [app activateIgnoringOtherApps:YES];

    // // Create the main window
    // NSRect frame = NSMakeRect(0, 0, 800, 600);
    // NSUInteger style = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable;
    // NSWindow *window = [[NSWindow alloc] initWithContentRect:frame styleMask:style backing:NSBackingStoreBuffered defer:NO];
    // [window setTitle:@"Photino Window"];
    // [window makeKeyAndOrderFront:nil];

    // // Create the webview
    // WKWebViewConfiguration *configuration = [[WKWebViewConfiguration alloc] init];
    // WKWebView *webview = [[WKWebView alloc] initWithFrame:frame configuration:configuration];
    // [window setContentView:webview];

    // // Load the HTML content
    // NSString *html = @"<html><body><h1>Hello, world!</h1></body></html>";
    // [webview loadHTMLString:html baseURL:nil];

    // // Run the application
    // [app run];

    // // Clean up
    // [webview release];
    // [window release];
    // [app release];

    // return 0;


     Photino::Register();


  


    PhotinoInitParams param = {0};

    //param.StartUrlWide = (wchar_t*)L"file://d:/index.html";
    //param.Title = "hello";

    //param.StartStringWide = L"<html>hello</html>";
    param.StartString = "<html> <a href=\"app://\"> link </a></html>";
    param.StartStringWide = L"<html> <a href=\"app://\"> link </a></html>";

    param.MaxWidth = 4096;
    param.MaxHeight = 4096;

    param.MinWidth = 800;
    param.MinHeight = 600;

    param.CenterOnInitialize = true;

    param.Zoom= 100;
    param.Width= 1024;
    param.Height = 768;


    param.Resizable = true;
    param.DevToolsEnabled = true;

    param.CustomSchemeHandler = (WebResourceRequestedCallback*) & WebResReqCb;

    param.CustomSchemeNames[0] = "app";
    param.Size = sizeof(param);

   

    Photino* photino = new Photino(&param);

    //photino->AddCustomSchemeName("file");

    photino->WaitForExit();

 
    
    return 0;
}
