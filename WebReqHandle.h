#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "inja.hpp"

#if defined(__APPLE__)
#include <Cocoa/Cocoa.h>
#include <mach-o/dyld.h>
#endif

#ifdef _WIN32
#include "Windows.h"
#endif

#if defined(__APPLE__)

    std::wstring GetCurrentDllDirectory()
    {
        char path[1024];
        uint32_t size = sizeof(path);
        _NSGetExecutablePath(path, &size);
        std::string str = path;
        
        
        size_t found = str.find_last_of("/\\");


        return  std::wstring(str.begin(), str.begin() + found);
    }
#endif

#ifdef _WIN32

    std::wstring GetCurrentDllDirectory()
    {
        // Buffer to store the path of the DLL directory
        std::vector<wchar_t> buffer(MAX_PATH);

        // Get the full path of the executable or DLL that is currently being executed
        DWORD result = GetModuleFileNameW(NULL, buffer.data(), static_cast<DWORD>(buffer.size()));

        if (result == 0)
        {
            // Error handling if the path cannot be retrieved
            std::wcerr << L"Error getting the module file name" << std::endl;
            return L"";
        }

        // Remove the file name from the full path to get the directory
        std::wstring filePath(buffer.begin(), buffer.begin() + result);
        size_t pos = filePath.find_last_of(L"\\/");
        if (pos != std::wstring::npos)
        {
            return filePath.substr(0, pos);
        }

        return L"";
    }
#endif //  




class WebReqHandle
{
public:

    WebReqHandle():
    fileSize_(0)
    {
        scheme_local_ = L"ms-appx://localhost";
    }
    
    void setUrl(std::wstring url)
    {
        url_ = url;
        process();
    }
    void setUrl(std::string url)
    {
        url_ = std::wstring(url.begin(), url.end());
        process();
    }

    void process()
    {
        if (url_.find(L".html") != std::wstring::npos)
        {
            contentType_ = "text/html";
        }
        if (url_.find(L".css") != std::wstring::npos)
        {
            contentType_ = "text/css";
        }
        if (url_.find(L".js") != std::wstring::npos)
        {
            contentType_ = "application/javascript";
        }
        if (url_.find(L".ico") != std::wstring::npos)
        {
            contentType_ = "image/x-icon";
        }
        if (url_.find(L".wasm") != std::wstring::npos)
        {
            contentType_ = "application/wasm";
        }
        
        if (contentType_.length() != 0 )
        {
            process_file();
        }
        else
        {
            process_action();
        }

    }

    void process_file()
    {
        std::wstring dir = GetCurrentDllDirectory();

        std::wstring wwwroot_path = dir + L"/wwwroot";
        printf("wwwroot: %ls\n", wwwroot_path.c_str());

        size_t position = url_.find(scheme_local_);
        if (position == std::wstring::npos)
        {
            return;
        }
        url_.replace(position, scheme_local_.length(), wwwroot_path);

        //
        std::string url_str(url_.begin(), url_.end());
        //std::ifstream file(url_str, std::ios::binary | std::ios::ate);

        file_.open(url_str, std::ios::binary | std::ios::ate);

       

        fileSize_ = file_.tellg();
        printf("wwwroot full: %s , file size = %zd \n", url_str.c_str() ,fileSize_  );

        //check hasBOM
        file_.seekg(0, std::ios::beg);
        bool hasBOM = FALSE;
        uint8_t bom[3] = { 0 };
        file_.read((char*)bom, 3);
        if (bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF)
        {
            hasBOM = TRUE;
            fileSize_ -= 3;
        }
        else
        {
            file_.seekg(0, std::ios::beg);
        }

        //buf_ = new uint8_t[fileSize_];
        //file.read(reinterpret_cast<char*>(buf_), fileSize_);
    }

    void process_action()
    {
        printf("process_action\n");




    }


    std::wstring scheme_local_;

    std::wstring url_;
    std::string contentType_;

    std::ifstream file_;
    //uint8_t* buf_ ;
    size_t fileSize_;
};