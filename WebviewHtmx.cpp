//#include "Export.h"

//#include "Windows.h"
#include "webview2.h"
//#include "Exports.h"
#include "Photino.h"

using namespace std;


//void* (*WebResourceRequestedCallback)(AutoString url, int* outNumBytes, AutoString* outContentType);

void* WebResReqCb(AutoString url, int* outNumBytes, AutoString* outContentType)
{
    return NULL;
}



int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
)
{

    PhotinoInitParams param = {0};

    //param.StartUrlWide = (wchar_t*)L"file://d:/index.html";
    //param.Title = "hello";
    param.StartString = "<html> <a href=\"http://test\"> link </a></html>";
    param.StartStringWide = L"<html> <a href=\"http://test\"> link </a></html>";

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

    photino->AddCustomSchemeName(L"cust");

    photino->WaitForExit();




}