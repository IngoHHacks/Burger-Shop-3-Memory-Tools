#ifndef MEMREAD_UTILS_H
#define MEMREAD_UTILS_H

#include <atomic>
#include <windows.h>
#include <gdiplus.h>
#include <mutex>
#include <thread>
#include <list>
#include <vector>
#include <functional>
#include <unordered_map>
#include <ntstatus.h>
#include <tlhelp32.h>
#include <fstream>
#include <iostream>
#include <filesystem>

struct Node {
public:
    DWORD prev;
    DWORD next;
    DWORD content;
};

class Utils {
public:
    static uintptr_t GetModuleBaseAddress(DWORD procId, const char *modName);

#ifdef _WIN64
    static bool GetWow64ThreadContext(HANDLE hThread, WOW64_CONTEXT &context);

    static bool SetWow64ThreadContext(HANDLE hThread, WOW64_CONTEXT &context);
#endif

    static bool ReadBufferToProcessMemory(HANDLE processHandle, DWORD address, LPVOID buffer, SIZE_T size);

    static bool WriteBufferToProcessMemory(HANDLE processHandle, DWORD address, LPCVOID buffer, SIZE_T size);

    static std::list<Node> TraverseAndCollectNodes(HANDLE hProcess, DWORD startAddress);

    static bool TryFindFood(HANDLE hProcess, DWORD startAddress, int depth, int width, std::list<std::string> &path);

    static bool IsSentinelNode(HANDLE hProcess, DWORD address, const Node &node);

    static void GetItems(std::list<Node> nodeList, HANDLE hProcess);

    static void RecursivePrint(DWORD address, int depth, int items);

    static Gdiplus::Image *GetImageFromPath(std::wstring path);
};

#endif //MEMREAD_UTILS_H
