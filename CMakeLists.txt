
cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 11)

if (WIN32)
    add_definitions("-DUNICODE")

    set ( WebviewInclude  "${CMAKE_SOURCE_DIR}/webview2/include"    )
    message (WebviewInclude = ${WebviewInclude} )
    include_directories (${WebviewInclude})

    set ( WebviewLib "${CMAKE_SOURCE_DIR}/webview2/x64")
    message (WebviewLib = ${WebviewLib} )
    link_directories (${WebviewLib})

    include_directories("wil")

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS ")


    add_executable(photino_htmx WIN32 

        WebviewHtmx.cpp

        Photino.h
        Photino.Windows.cpp
        Photino.Windows.DarkMode.cpp
        Photino.Windows.DarkMode.h
        Photino.Windows.ToastHandler.h

        Photino.Dialog.h
        Photino.Windows.Dialog.cpp

        Dependencies/wintoastlib.h
        Dependencies/wintoastlib.cpp

        #Exports.h
        #Exports.cpp

    )   

    target_link_libraries( photino_htmx  WebView2Loader.dll.lib)

Endif()




if (APPLE)

    add_library(mylib  

        #WebviewHtmx.cpp

        #Exports.h
        #Exports.cpp

        Photino.h
        Photino.Mac.mm
        json.hpp

        Photino.Mac.AppDelegate.h
        Photino.Mac.AppDelegate.mm

        Photino.Mac.NavigationDelegate.h
        Photino.Mac.NavigationDelegate.mm

        Photino.Mac.NSWindowBorderless.h
        Photino.Mac.NSWindowBorderless.mm

        Photino.Mac.UIDelegate.h
        Photino.Mac.UIDelegate.mm

        Photino.Mac.UrlSchemeHandler.h
        Photino.Mac.UrlSchemeHandler.mm

        Photino.Dialog.h
        Photino.Mac.Dialog.mm
    )  

Endif()