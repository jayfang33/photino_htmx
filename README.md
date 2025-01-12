#  Warning

This project is still a demo project.

# Basic idea

You maybe like this project if 
- want to find Electron alternative
- want to write a cross platform desktop app by C / C++ 
- want to use browser as UI
- not good at frontend framework. not good at javascript.
- then, use HTMX to control web UI

# Using following project code

- The webview control:  [photino.Native](https://github.com/tryphotino/photino.Native)
- The template engine : [inja](https://github.com/pantor/inja)
- Json lib used by inja :  [nlohmann/json](https://github.com/nlohmann/json)
- The HTMX :  [htmx](https://github.com/bigskysoftware/htmx)

# How to Build


Build Environment
- wondows :  VS2022 
- macOS :  Xcode

The steps 
- git clone this project
- cd project dir
- mkdir build
- cd build
- cmake ../
- copy wwwroot folder to build folder
- run photino_htmx
 


# Basic flow

- handle URL from webview
- if url is localhost file, open file in wwwroot and send to webview
- if url is not a file, open inja template and generate html



