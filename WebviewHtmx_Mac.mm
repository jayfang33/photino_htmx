
#include "Photino.h"

#include <iostream>
#include <fstream>
#include <string>
#include <Cocoa/Cocoa.h>

#include <mach-o/dyld.h>

std::string GetCurrentDllDirectory()
{
    char path[1024];
    uint32_t size = sizeof(path);
    _NSGetExecutablePath(path, &size);
    std::string str = path;
    
    size_t found = str.find_last_of("/\\");
    return str.substr(0, found);
}


void* WebResReqCb(AutoString url, int* outNumBytes, AutoString* outContentType)
{
    std::string uriString = url;

    // check is file
    *outContentType = NULL;
    if (uriString.find(".html") != std::string::npos)
    {
        *outContentType = "text/html";
    }

    if (uriString.find(".css") != std::string::npos)
    {
        *outContentType = "text/css";
    }

    if (uriString.find(".js") != std::string::npos)
    {
        *outContentType = "application/javascript";
    }

    if (uriString.find(".ico") != std::string::npos)
    {
        *outContentType = "image/x-icon";
    }

    if (uriString.find(".wasm") != std::string::npos)
    {
        *outContentType = "application/wasm";
    }

    //
    if (*outContentType == NULL)   // action
    {
    }
    else
    {
    }

    std::string dir = GetCurrentDllDirectory();

    printf("dir: %s\n", dir.c_str());

    std::string toReplace = "ms-appx://localhost";
    std::string newStr = dir + "/wwwroot";

    size_t position = uriString.find(toReplace);
    uriString.replace(position, toReplace.length(), newStr);

    printf("uriString: %s\n", uriString.c_str());

    std::ifstream file(uriString, std::ios::binary | std::ios::ate);
    int fileSize = file.tellg();

    //check hasBOM
    file.seekg(0, std::ios::beg);
    bool hasBOM = FALSE;
    uint8_t bom[3] = { 0 };
    file.read((char*)bom, 3);
    if (bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF)
    {
        hasBOM = TRUE;
        fileSize -= 3;
    }
    else
    {
        file.seekg(0, std::ios::beg);
    }

    uint8_t* buf = new uint8_t[fileSize];
    file.read(reinterpret_cast<char*>(buf), fileSize);

    *outNumBytes = fileSize;

    return buf;
    
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
