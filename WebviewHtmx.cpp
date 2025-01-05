//#include "Export.h"

//#include "Windows.h"

#include <iostream>
#include <fstream>

#include "webview2.h"
//#include "Exports.h"
#include "Photino.h"

#include <string>
#include "WebReqHandle.h"


void* WebResReqCb(AutoString url, int* outNumBytes, AutoString* outContentType)
{
    //for windows , http://localhost  ->  ms-appx://localhost 

    std::wstring  scheme_local = L"http://localhost";
    std::wstring  url_appx = url;

    size_t position = url_appx.find(scheme_local);

    //check if url has scheme_local
    if (position == std::wstring::npos)
    {
        return nullptr;
    }
    url_appx.replace(position, scheme_local.length(), L"ms-appx://localhost");

    // 
    WebReqHandle rq = WebReqHandle();
    rq.setUrl(url_appx);
    
    // convert rq.contentType_ to wide string
    std::wstring wstr = std::wstring(rq.contentType_.begin(), rq.contentType_.end());
    size_t len = rq.contentType_.length();

    wchar_t* tmp = new wchar_t[len+1];
    memcpy(tmp, wstr.c_str(), len);
    tmp[len] = 0;
    *outContentType = tmp;

    //data
    if (rq.fileSize_ == 0)
    {
        *outNumBytes = 0;
        return nullptr;
    }
    uint8_t* data = new uint8_t[rq.fileSize_];
    rq.file_.read(reinterpret_cast<char*>(data), rq.fileSize_);

    *outNumBytes = rq.fileSize_;

    return data;
    
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

    param.CustomSchemeHandler = (WebResourceRequestedCallback*) &WebResReqCb;


    //
    HINSTANCE _nativeTupe = GetModuleHandle(NULL);;
    Photino::Register(_nativeTupe);



    Photino* photino = new Photino(&param);

    photino->AddCustomSchemeName(L"http");
    photino->AddCustomSchemeName(L"ms-appx");

    photino->WaitForExit();




}