//#include "Export.h"

//#include "Windows.h"

#include <iostream>
#include <fstream>

#include "webview2.h"
//#include "Exports.h"
#include "Photino.h"

using namespace std;

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


void* WebResReqCb(AutoString url, int* outNumBytes, AutoString* outContentType)
{
    std::wstring uriString = url;

    // check is file
    *outContentType = NULL;
    if (uriString.find(L".html") != std::wstring::npos)
    {
        *outContentType = L"text/html";
    }

    if (uriString.find(L".css") != std::wstring::npos)
    {
        *outContentType = L"text/css";
    }

    if (uriString.find(L".js") != std::wstring::npos)
    {
        *outContentType = L"application/javascript";
    }

    if (uriString.find(L".ico") != std::wstring::npos)
    {
        *outContentType = L"image/x-icon";
    }

    if (uriString.find(L".wasm") != std::wstring::npos)
    {
        *outContentType = L"application/wasm";
    }

    //
    if (*outContentType == NULL)   // action
    {
    }
    else
    {
    }

    std::wstring dir = GetCurrentDllDirectory();
    std::wstring toReplace = L"http://localhost";
    std::wstring newStr = dir + L"/wwwroot";

    size_t position = uriString.find(toReplace);
    uriString.replace(position, toReplace.length(), newStr);

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



int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
)
{

    PhotinoInitParams param = {0};

    param.StartUrlWide = (wchar_t*)L"http://localhost/index.html";
    //param.Title = "hello";
    //param.StartString = "<html> <a href=\"ms-appx://test\"> link </a></html>";
    //param.StartStringWide = L"<html> <a href=\"http://localhost/index.html\"> link </a></html>";

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

    param.CustomSchemeHandler = (WebResourceRequestedCallback*) & WebResReqCb;


    //
    HINSTANCE _nativeTupe = GetModuleHandle(NULL);;
    Photino::Register(_nativeTupe);



    Photino* photino = new Photino(&param);

    photino->AddCustomSchemeName(L"http");

    photino->WaitForExit();




}