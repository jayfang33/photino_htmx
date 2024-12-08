
cmake_minimum_required(VERSION 3.8)

add_definitions("-DUNICODE")

set ( WebviewInclude  "${CMAKE_SOURCE_DIR}/webview2/include"    )
message (WebviewInclude = ${WebviewInclude} )
include_directories (${WebviewInclude})

set ( WebviewLib "${CMAKE_SOURCE_DIR}/webview2/x64")
message (WebviewLib = ${WebviewLib} )
link_directories (${WebviewLib})

include_directories("wil")

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

    Exports.h
    Exports.cpp

)   


target_link_libraries( photino_htmx  WebView2Loader.dll.lib)