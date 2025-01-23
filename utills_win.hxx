/**
 * Utills_win.hxx "WindowsAPI Utility"
 * Functions and classes by @author David "Rétro" Siřait.
 * This file contains various reusable functions and classes.
 * This is not meant to be executed directly.
 *
 * You can freely edit this file
 * Contact me via discord @dwsz56
 *
 * Do not run or compile. Use it by importing.
 * Requires C++23 (-std=c++23)
 *
 * Compile: clang++ -std=c++23 -o <file> <file>.cpp -O3 -Wall -pedantic -pthread -mwindows -lgdi32 -luser32 -lws2_32 -W#warnings
 * -W#warnings and -mwindows are optional
 */
#pragma once

#include "Includes.hxx"

#pragma comment(lib, "ws2_32.lib") // Link Winsock library

/* Namespace containing all utility functions */
namespace WinAPI {
    // --------------------- Terminal utils ---------------------
    namespace CMD {

        /**
         * Retrieves the terminal size (columns and rows).
         * @return A tuple containing the number of columns and rows in the terminal.
         */
        TP::TINT GetTerminalSize() {
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

            if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
                int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
                int rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
                return {columns, rows};
            }
            return {0, 0}; // Return (0, 0) if unable to get the size
        }

        /**
         * Clears the terminal screen.
         */
        void ClearTerminal() {
            system("cls");
        }

        /**
         * Moves the cursor to the specified position in the terminal (X, Y).
         * @param x The horizontal position (column).
         * @param y The vertical position (row).
         */
        void MoveCursor(int x, int y) {
            COORD coord = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        }

        /**
         * Changes the text color in the terminal.
         * @param color The color code (0-15) for the text.
         */
        void SetTextColor(int color) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
        }

        /**
         * Sets the background color in the terminal.
         * @param color The color code (0-15) for the background.
         */
        void SetBackgroundColor(int color) {
            int textColor = 15; // White text color by default
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (color << 4) | textColor);
        }

        /**
         * Prints text in the terminal without moving the cursor to a new line.
         * @param text The text to print.
         */
        void PrintInline(const TP::STR& text) {
            std::cout << text;
            std::cout.flush();
        }

        /**
         * Prints a formatted string with the current time.
         * @param text The text to print.
         */
        void PrintWithTimestamp(const TP::STR& text) {
            time_t now = time(0);
            struct tm tstruct;
            char buf[80];
            tstruct = *localtime(&now);
            strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
            std::cout << "[" << buf << "] " << text << std::endl;
        }

        /**
         * Waits for the user to press a key before continuing.
         */
        void WaitForKeyPress() {
            std::cout << "Press any key to continue...";
            _getch();
        }

        /**
         * Displays a progress bar in the terminal.
         * @param progress The current progress (0-100).
         */
        void ShowProgressBar(int progress) {
            const int barWidth = 50;
            std::cout << "[";
            int pos = barWidth * progress / 100;
            for (int i = 0; i < barWidth; ++i) {
                if (i < pos) std::cout << "=";
                else if (i == pos) std::cout << ">";
                else std::cout << " ";
            }
            std::cout << "] " << progress << "%\r";
            std::cout.flush();
        }

        /**
         * Pauses execution for the specified amount of seconds.
         * @param seconds The number of seconds to pause.
         */
        void PauseFor(int seconds) {
            std::this_thread::sleep_for(std::chrono::seconds(seconds));
        }

        /**
         * Prompts the user for input and returns the response.
         * @param prompt The prompt to display.
         * @return The user's input as a string.
         */
        TP::STR GetInput(const TP::STR& prompt) {
            std::cout << prompt;
            TP::STR input;
            std::getline(std::cin, input);
            return input;
        }

        /**
         * Changes the terminal's title.
         * @param title The new title to set for the terminal.
         */
        void SetTerminalTitle(const TP::STR& title) {
            SetConsoleTitle(title.c_str());
        }

        /**
         * Enables or disables the terminal cursor.
         * @param visible If true, shows the cursor; if false, hides the cursor.
         */
        void SetCursorVisibility(bool visible) {
            CONSOLE_CURSOR_INFO cursorInfo;
            GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
            cursorInfo.bVisible = visible;
            SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        }
    }

    // --------------------- Display and screen utils ---------------------
    namespace SCR{
        /**
         * Gets the screen resolution.
         * @return A tuple containing the screen width and height.
         */
        TP::TINT GetScreenResolution() {
            int width = GetSystemMetrics(SM_CXSCREEN);
            int height = GetSystemMetrics(SM_CYSCREEN);
            return {width, height};
        }

        /**
         * Gets the native screen resolution and scaling factor.
         * @return A tuple containing the native width, height, and scaling factor.
         */
        std::tuple<int, int, float> GetScreenInfo() {
            HDC screen = GetDC(NULL); // Get the screen device context

            // Get the physical pixels (native resolution)
            int nativeWidth = GetDeviceCaps(screen, DESKTOPHORZRES);
            int nativeHeight = GetDeviceCaps(screen, DESKTOPVERTRES);

            // Get the logical resolution (scaled resolution)
            int scaledWidth = GetSystemMetrics(SM_CXSCREEN);
            int scaledHeight = GetSystemMetrics(SM_CYSCREEN);

            // Calculate the scaling factor
            float scalingFactor = static_cast<float>(nativeWidth) / scaledWidth;

            ReleaseDC(NULL, screen); // Release the device context

            return {nativeWidth, nativeHeight, scalingFactor};
        }

        /**
         * Captures a screenshot and saves it as a BMP file.
         * @param file_path - The path to save the screenshot.
         */
        void CaptureScreenshot(const TP::STR& file_path) {
            int screen_width = GetSystemMetrics(SM_CXSCREEN);
            int screen_height = GetSystemMetrics(SM_CYSCREEN);

            HDC hdc = GetDC(NULL);
            HDC memDC = CreateCompatibleDC(hdc);
            HBITMAP hBitmap = CreateCompatibleBitmap(hdc, screen_width, screen_height);
            SelectObject(memDC, hBitmap);

            BitBlt(memDC, 0, 0, screen_width, screen_height, hdc, 0, 0, SRCCOPY);

            DeleteObject(hBitmap);
            DeleteDC(memDC);
            ReleaseDC(NULL, hdc);
        }
    }

    // --------------------- File and drive utils ---------------------
    namespace FND{
        /**
         * Lists all logical drives in the system.
         * @return A vector of strings containing the drive letters (e.g., "C:\").
         */
        TP::VSTR GetDrives() {
            char drive_letters[256];
            DWORD size = GetLogicalDriveStringsA(sizeof(drive_letters), drive_letters);

            TP::VSTR drives;
            char* drive = drive_letters;
            while (*drive) {
                drives.emplace_back(drive);
                drive += strlen(drive) + 1;
            }
            return drives;
        }

        /**
         * Checks if a file exists at the specified path.
         * @param file_path - The path to the file.
         * @return True if the file exists; otherwise, false.
         */
        bool FileExists(const TP::STR& file_path) {
            DWORD file_attributes = GetFileAttributesA(file_path.c_str());
            return (file_attributes != INVALID_FILE_ATTRIBUTES &&
                    !(file_attributes & FILE_ATTRIBUTE_DIRECTORY));
        }
    }

    // --------------------- Networking utils ---------------------
    namespace NET {

        /**
         * Retrieves the local IP address (IPv6).
         * @return The local IPv6 address as a string.
         */
        TP::STR GetLocalIPv6Address() {
            WSADATA wsaData;
            WSAStartup(MAKEWORD(2, 2), &wsaData);

            char hostname[256];
            gethostname(hostname, sizeof(hostname));

            addrinfo hints = {}, *info;
            hints.ai_family = AF_INET6;
            getaddrinfo(hostname, NULL, &hints, &info);

            sockaddr_in6* addr = reinterpret_cast<sockaddr_in6*>(info->ai_addr);
            TP::STR ip = inet_ntop(AF_INET6, &addr->sin6_addr, new char[INET6_ADDRSTRLEN], INET6_ADDRSTRLEN);

            freeaddrinfo(info);
            WSACleanup();
            return ip;
        }

        /**
         * Retrieves the public IP address of the machine using an external service.
         * @return The public IP address as a string.
         */
        TP::STR GetPublicIPAddress() {
            using namespace std::chrono;

            // This function needs to access an external service (e.g., through a web API)
            // Implementation of HTTP client can be done via libraries like cURL, Boost.Beast, etc.

            // For illustration, here we assume that an external API or a simple request to a public service will return the public IP
            TP::STR public_ip = "203.0.113.0"; // Replace with actual call to public IP service
            return public_ip;
        }

        /**
         * Converts an IP address to a long integer (for comparison or storage).
         * @param ip The IP address as a string.
         * @return The IP address as a long integer.
         */
        long IPToLong(const TP::STR& ip) {
            sockaddr_in sa;
            inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr));
            return ntohl(sa.sin_addr.s_addr);
        }

        /**
         * Converts a long integer back to an IP address.
         * @param ipLong The long integer representing an IP address.
         * @return The IP address as a string.
         */
        TP::STR LongToIP(long ipLong) {
            sockaddr_in sa;
            sa.sin_family = AF_INET;
            sa.sin_addr.s_addr = htonl(ipLong);
            char ipStr[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(sa.sin_addr), ipStr, sizeof(ipStr));
            return std::string(ipStr);
        }

        /**
         * Checks if a port is open on a remote host.
         * @param host The host to check (e.g., "192.168.1.1").
         * @param port The port number to check.
         * @return True if the port is open, otherwise false.
         */
        bool IsPortOpen(const TP::STR& host, int port) {
            SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            addr.sin_addr.s_addr = inet_addr(host.c_str());

            int result = connect(sock, (sockaddr*)&addr, sizeof(addr));
            closesocket(sock);

            return result == 0; // If connect succeeds, the port is open
        }

        /**
         * Retrieves the hostname of the machine.
         * @return The hostname as a string.
         */
        TP::STR GetHostname() {
            char hostname[256];
            gethostname(hostname, sizeof(hostname));
            return TP::STR(hostname);
        }

        /**
         * Resolves a hostname to an IP address.
         * @param hostname The hostname to resolve (e.g., "www.example.com").
         * @return The resolved IP address as a string.
         */
        TP::STR ResolveHostnameToIP(const TP::STR& hostname) {
            addrinfo hints = {}, *info;
            hints.ai_family = AF_INET;
            getaddrinfo(hostname.c_str(), NULL, &hints, &info);

            sockaddr_in* addr = reinterpret_cast<sockaddr_in*>(info->ai_addr);
            TP::STR ip = inet_ntoa(addr->sin_addr);

            freeaddrinfo(info);
            return ip;
        }

        /**
         * Pings a remote host to check if it's reachable.
         * @param host The host to ping (e.g., "google.com").
         * @return True if the host is reachable, otherwise false.
         */
        bool Ping(const TP::STR& host) {
            DWORD result = system(("ping -n 1 " + host).c_str());
            return result == 0; // If the command exits successfully, the host is reachable
        }
    }

    // --------------------- Notification ---------------------
    namespace Notif {
        /**
         * Show a tray icon with a tooltip.
         * @param tooltip - Tooltip to display when hovering over the icon.
         */
        void ShowTrayIcon(const TP::STR& tooltip) {
            NOTIFYICONDATA nid = { sizeof(NOTIFYICONDATA) };
            nid.hWnd = NULL;
            nid.uFlags = NIF_ICON | NIF_TIP;
            nid.hIcon = LoadIcon(NULL, IDI_INFORMATION);
            strncpy_s(nid.szTip, tooltip.c_str(), sizeof(nid.szTip));
            Shell_NotifyIcon(NIM_ADD, &nid);
        }

        /**
         * Remove the tray icon.
         */
        void RemoveTrayIcon() {
            NOTIFYICONDATA nid = { sizeof(NOTIFYICONDATA) };
            nid.hWnd = NULL;
            Shell_NotifyIcon(NIM_DELETE, &nid);
        }

        /**
         * Display a motivational message box.
         * @param title : Title of box popup
         * @param message : Anything to say
         */
        void ShowMessageBox(const std::string& title, const std::string& message) {
            MessageBox(NULL, message.c_str(), title.c_str(), MB_OK | MB_ICONINFORMATION);
        }
    }

    // --------------------- Time ---------------------
    namespace Time {
        /**
         * Get current system time in "HH:mm:ss" format.
         * @return Formatted time as a string.
         */
        TP::STR GetCurrentTime() {
            SYSTEMTIME st;
            GetSystemTime(&st);
            char buffer[9];
            snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d", st.wHour, st.wMinute, st.wSecond);
            return TP::STR(buffer);
        }
    }

    // --------------------- System ---------------------
    namespace System {
        /**
         * Get the machine name.
         * @return Machine name as a string.
         */
        TP::STR GetMachineName() {
            char buffer[MAX_COMPUTERNAME_LENGTH + 1];
            DWORD size = sizeof(buffer);
            if (GetComputerNameA(buffer, &size)) {
                return TP::STR(buffer);
            }
            return "Unknown Machine";
        }

        /**
         * Retrieves the current username.
         * @return A string containing the current logged-in username.
         */
        TP::STR GetUsername() {
            char username[UNLEN + 1];
            DWORD username_len = UNLEN + 1;

            if (GetUserNameA(username, &username_len)) {
                return TP::STR(username);
            }
            return "Unknown User";
        }
    }

    // --------------------- Process ---------------------
    namespace Process {
        /**
         * Lists all running processes.
         * @return A vector of strings containing the names of all running processes.
         */
        TP::VSTR GetRunningProcesses() {
            TP::VSTR processes;
            HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
            PROCESSENTRY32 process_entry;
            process_entry.dwSize = sizeof(PROCESSENTRY32);

            if (Process32First(snapshot, &process_entry)) {
                do {
                    processes.emplace_back(process_entry.szExeFile);
                } while (Process32Next(snapshot, &process_entry));
            }
            CloseHandle(snapshot);
            return processes;
        }

        /**
         * Retrieves memory usage information.
         * @return A string with the total and used virtual memory in MB.
         */
        TP::STR GetMemoryUsage() {
            MEMORYSTATUSEX memInfo;
            memInfo.dwLength = sizeof(MEMORYSTATUSEX);
            GlobalMemoryStatusEx(&memInfo);

            DWORDLONG total_virtual_mem = memInfo.ullTotalPageFile;
            DWORDLONG used_virtual_mem = memInfo.ullTotalPageFile - memInfo.ullAvailPageFile;

            return "Total Virtual Memory: " + std::to_string(total_virtual_mem / (1024 * 1024)) + " MB\n" +
                "Used Virtual Memory: " + std::to_string(used_virtual_mem / (1024 * 1024)) + " MB";
        }

        /**
         * Check if a specific process is running.
         * @param processName - Name of the process to check (e.g., "notepad.exe").
         * @return True if the process is running, false otherwise.
         */
        bool IsProcessRunning(const TP::STR& processName) {
            PROCESSENTRY32 pe32;
            HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
            if (hProcessSnap == INVALID_HANDLE_VALUE) {
                return false;
            }

            pe32.dwSize = sizeof(PROCESSENTRY32);
            if (!Process32First(hProcessSnap, &pe32)) {
                CloseHandle(hProcessSnap);
                return false;
            }

            do {
                if (processName == pe32.szExeFile) {
                    CloseHandle(hProcessSnap);
                    return true;
                }
            } while (Process32Next(hProcessSnap, &pe32));

            CloseHandle(hProcessSnap);
            return false;
        }
    }

    // --------------------- Audio ---------------------
    namespace Audio {
        /**
         * Play a sound from a WAV file.
         * @param filename - Path to the WAV file.
         */
        void PlaySoundFromFile(const TP::STR& filename) {
            PlaySoundA(filename.c_str(), NULL, SND_FILENAME | SND_ASYNC);
        }
    }

    // --------------------- Cmd ---------------------
    namespace Cmd {
        /**
         * Run a command in the Command Prompt.
         * @param command - The command to execute.
         */
        void RunCommand(const TP::STR& command) {
            system(command.c_str());
        }
    }

    // --------------------- Power management ---------------------
    namespace Power {
        /**
         * Displays Power Status
         */
        void CheckPowerStatus() {
            SYSTEM_POWER_STATUS sps;
            if (GetSystemPowerStatus(&sps)) {
                std::cout << "Battery Life Percentage: " << static_cast<int>(sps.BatteryLifePercent) << "%\n";
                std::cout << "AC Line Status: " << (sps.ACLineStatus ? "Plugged in" : "On battery") << "\n";
            } else {
                std::cout << "Failed to retrieve power status.\n";
            }
        }
    }
}