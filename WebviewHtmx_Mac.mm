
#include "Photino.h"

#include <iostream>
#include <fstream>
#include <string>


#include "WebReqHandle.h"




void* WebResReqCb(AutoString url, int* outNumBytes, AutoString* outContentType)
{
    // 
    WebReqHandle rq = WebReqHandle();
    rq.setUrl(url);



    //content type
    #ifdef __APPLE__
    int len = rq.contentType_.length();
    char* tmp = new char[len+1];
    memcpy(tmp, rq.contentType_.c_str(), len);
    tmp[len] = 0;
    *outContentType = tmp;
    #endif


    
    //data
    uint8_t* data = new uint8_t[rq.fileSize_];
    rq.file_.read(reinterpret_cast<char*>(data), rq.fileSize_);

    *outNumBytes = rq.fileSize_;


    return data;
    
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

    param.StartUrl = "ms-appx://localhost/index.html";
    //param.Title = "hello";

    //param.StartStringWide = L"<html>hello</html>";
    //param.StartString = "<html> <a href=\"app://\"> link </a></html>";
    //param.StartStringWide = L"<html> <a href=\"app://   \"> link </a></html>";

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

    param.CustomSchemeNames[0] = "ms-appx";
    param.Size = sizeof(param);

   

    Photino* photino = new Photino(&param);

    //photino->AddCustomSchemeName("file");

    photino->WaitForExit();

 
    
    return 0;
}
