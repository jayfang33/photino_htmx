
#include "Photino.h"

#include <Cocoa/Cocoa.h>


int main(int argc, char *argv[]) {
    @autoreleasepool {
        // Create the application instance
        NSApplication *app = [NSApplication sharedApplication];
        
        // Create the main window
        NSRect frame = NSMakeRect(0, 0, 800, 600);
        NSUInteger style = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable;
        NSWindow *window = [[NSWindow alloc] initWithContentRect:frame styleMask:style backing:NSBackingStoreBuffered defer:NO];
        [window setTitle:@"Photino Window"];
        [window makeKeyAndOrderFront:nil];
        
        // // Initialize Photino
        // Photino* photino = new Photino("Photino Window", nullptr);
        // photino->SetSize(800, 600);
        // photino->SetPosition(0, 0);
        // photino->SetTopmost(false);
        // photino->SetResizable(true);
        // photino->SetContextMenuEnabled(true);
        // photino->SetDevToolsEnabled(true);
        // photino->SetTitle("Photino Window");
        // photino->Load("https://www.example.com");
        
        // Run the application
        [app run];
        
        // Clean up
        delete photino;
    }
    return 0;
}
