
#include "Photino.h"

#include <Cocoa/Cocoa.h>


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
    param.StartString = "<html>hello</html>";
    //param.StartStringWide = L"<html>hello</html>";

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

    param.Size = sizeof(param);

   

    Photino* photino = new Photino(&param);

    photino->WaitForExit();

 
    
    return 0;
}
