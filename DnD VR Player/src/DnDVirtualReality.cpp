// DnDVirtualReality.cpp : Defines the entry point for the application.
//

#include "DnDVirtualReality.h"

using namespace std;

Engine* Engine::engine = 0;

static int CALLBACK BrowseFolderCallback(
    HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
    if (uMsg == BFFM_INITIALIZED) {
        LPCTSTR path = reinterpret_cast<LPCTSTR>(lpData);
        ::SendMessage(hwnd, BFFM_SETSELECTION, true, (LPARAM)path);
    }
    return 0;
}

std::string BrowseFolder(std::string saved_path)
{
    TCHAR path[MAX_PATH];

    const char* path_param = saved_path.c_str();

    BROWSEINFO bi = { 0 };
    bi.lpszTitle = ("Choose the project folder:");
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    bi.lpfn = BrowseFolderCallback;
    bi.lParam = (LPARAM)path_param;

    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

    if (pidl != 0)
    {
        //get the name of the folder and put it in path
        SHGetPathFromIDList(pidl, path);

        //free memory used
        IMalloc* imalloc = 0;
        if (SUCCEEDED(SHGetMalloc(&imalloc)))
        {
            imalloc->Free(pidl);
            imalloc->Release();
        }

        return path;
    }

    return "";
}

int main(int argc, char *argv[])
{
    string path = BrowseFolder("");
    std::replace(path.begin(), path.end(), '\\', '/');
    if(!path.empty()){
        Engine* engine = Engine::getInstance();
        engine->setPackageFile(path);
        engine->run(argc, argv);

        return 0;
    }
    return 1;
}
