//#include "Export.h"

//#include "Windows.h"
#include "webview2.h"
#include "Exports.h"
#include "Photino.h"

using namespace std;

int CALLBACK WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
)
{

    PhotinoInitParams param = {0};

    param.StartUrl = "file://d:/index.html";
    param.Title = "hello";
    param.StartString = "<html>hello</html>";

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


    HINSTANCE _nativeTupe = NULL;
    Photino_register_win32(_nativeTupe);



    Photino* photino = Photino_ctor(&param);

    Photino_AddCustomSchemeName(photino, (wchar_t*)L"app");
    

    Photino_WaitForExit(photino);


}