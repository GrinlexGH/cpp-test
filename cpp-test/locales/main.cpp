// #include <iostream>
// #include <iomanip>
// #include <format>
// #include <print>
// #include <string>
// #include <chrono>
// #include <cassert>

// void TestLocaleDependentWideFuncs() {
//     std::time_t t = std::time(nullptr);
//     std::tm tm {};
//     #ifdef _WIN32
//         assert(localtime_s(&tm, &t) == 0);
//     #else
//         assert(localtime_r(&t, &tm) == 0);
//     #endif
//     std::wcout << std::endl << std::put_time(&tm, L"%c %A");

//     std::wcout << std::endl << std::showbase << std::put_money(125.45) << std::noshowbase << std::endl;
// }

// void TestWideEncoding() {
//     std::wcout.exceptions(std::ios_base::badbit | std::ios_base::failbit);
//     std::cin.exceptions(std::ios_base::badbit | std::ios_base::failbit);

//     std::wcout << L"TestWideEncoding():\n";

//     const wchar_t ch[] = {0x044F, 0};//L"я";
//     for (int i = 0; ch[i] != 0; ++i) {
//         std::wcout << std::format(L"Byte {}: {:#06x}\n", i, int(ch[i]));
//     }
//     std::wcout << std::format(L"Character: {}\n", ch);

//     TestLocaleDependentWideFuncs();

//     std::wstring string;
//     std::wcout << L"\nEnter string: ";
//     std::wcin >> string;
//     for (std::size_t i = 0, size = string.size(); i <= size; ++i) {
//         std::wcout << std::format(L"Byte {}: {:#06x}\n", i, int(string[i]));
//     }
//     std::wcout << std::format(L"Entered string: {}\n", string);

//     std::wcout << L'\n' << std::endl;
// }

// void TestNarrowEncoding() {
//     std::cout.exceptions(std::ios_base::badbit | std::ios_base::failbit);
//     std::cin.exceptions(std::ios_base::badbit | std::ios_base::failbit);

//     std::cout << "TestNarrowEncoding():\n";

//     const char* ch = "я";
//     for (int i = 0; ch[i] != 0; ++i) {
//         std::cout << std::format("Byte {}: {:#04x}\n", i, int(static_cast<unsigned char>(ch[i])));
//     }
//     std::cout << std::format("Character: {}\n", ch);

//     std::string string;
//     std::cout << "\nEnter string: ";
//     std::cin >> string;
//     for (std::size_t i = 0, size = string.size(); i <= size; ++i) {
//         std::cout << std::format("Byte {}: {:#04x}\n", i, int(static_cast<unsigned char>(string[i])));
//     }
//     std::cout << std::format("Entered string: {}\n", string);

//     std::cout << '\n' << std::endl;
// }

// #ifdef _WIN32
// #include <io.h>
// #include <fcntl.h>
// #include <windows.h>

// std::wstring Widen(const std::string_view narrowStr) {
//     if (narrowStr.empty()) {
//         return {};
//     }

//     const int len = MultiByteToWideChar(
//         CP_UTF8, 0,
//         narrowStr.data(), static_cast<int>(narrowStr.size()),
//         nullptr, 0
//     );

//     std::wstring out(len, 0);
//     MultiByteToWideChar(
//         CP_UTF8, 0,
//         narrowStr.data(), static_cast<int>(narrowStr.size()),
//         out.data(), len
//     );

//     return out;
// }
// #endif

// int main() {
//     std::cout.exceptions(std::ios_base::badbit | std::ios_base::failbit);
//     std::wcout.exceptions(std::ios_base::badbit | std::ios_base::failbit);


//     std::println("===== Source file encoding test ====================================");
//     const char* ch = "я";
//     for (int i = 0; ch[i] != 0; ++i) {
//         std::cout << std::format("Byte {}: {:#04x}\n", i, static_cast<int>((static_cast<unsigned char>(ch[i]))));
//     }
//     std::cout << std::format("Character: {}\n\n", ch);


//     std::println("===== Console encoding test ========================================");
//     std::println(
//         "{:13} = [Numero Sign]\n"
//         "{:13} = [Cyrillic Small Letter Soft Sign]\n"
//         "{:13} = [Superscript Latin Small Letter N]\n"
//         "{:13} = [Latin Small Letter U With Diaeresis]:\n",
//         "CP866",
//         "Windows-1251",
//         "CP437",
//         "UTF-8"
//     );
//     std::cout << "-----> \xFC <-----\n\n";


//     std::println("===== Source file encoding to console encoding =====================");
//     std::cout << "Привет, мир!\n\n";


//     std::println("===== Console translates stdout text from global encoding ==========");
//     std::println("Console will try to translate these characters from UTF-8 to console default encoding:");

//     std::locale::global(std::locale(".utf8"));
//     std::cout << "Я срал в окно 💀\n\n";

//     std::println("Console will try to translate these characters from cp437 to console default encoding:");
//     std::locale::global(std::locale(".437"));
//     std::cout << "\xF0 \xA5 \xAE\n\n";

//     std::println(
//         "Console will try to translate these characters from windows default encoding (windows 1251 in russian windows) "
//         "to console default encoding (cp866 in russian windows):");
//     std::locale::global(std::locale(""));
//     std::cout << "\xDF \xF1\xF0\xE0\xEB \xE2 \xEE\xEA\xED\xEE 💀\n\n";


//     std::println("===== C time locale test ===========================================");
//     std::locale::global(std::locale("Japanese_Japan.utf8"));
//     std::cout.imbue(std::locale("Russian_Russia.1251"));

//     UINT outputCP = GetConsoleOutputCP();
//     UINT inputCP = GetConsoleCP();

//     SetConsoleOutputCP(CP_UTF8);
//     SetConsoleCP(CP_UTF8);

//     std::time_t t = std::time(nullptr);
//     std::tm tm {};

//     #ifdef _WIN32
//     if (localtime_s(&tm, &t) == 0) {
//     #else
//     if (localtime_r(&t, &tm) == 0) {
//     #endif
//         std::cout << std::put_time(&tm, "%c %A\n");     // encoding utf8, language russian
//         std::cout << std::showbase << std::put_money(125.45) << std::noshowbase << "\n\n";  // encoding 1251, language Russian
//     } else {
//         std::cerr << "localtime_s failed\n";
//     }

//     SetConsoleOutputCP(outputCP);
//     SetConsoleCP(inputCP);


//     std::println("===== std::format locale test ======================================");
//     auto now = std::chrono::system_clock::now();
//     std::chrono::year_month_day ymd = floor<std::chrono::days>(now);

//     std::locale::global(std::locale(".utf8"));
//     std::println("Only in UTF-8:");
//     std::cout << std::format(std::locale("Russian_Russia.866"), "{:L%B}\n", ymd);
//     std::cout << std::format(std::locale("Russian_Russia.1251"), "{:L%B}\n", ymd);
//     std::cout << std::format(std::locale("Russian_Russia.437"), "{:L%B}\n", ymd);
//     std::cout << std::format(std::locale("Japanese_Japan.866"), "{:L%B}\n", ymd);
//     std::cout << std::format(std::locale("Japanese_Japan.1251"), "{:L%B}\n", ymd);
//     std::cout << std::format(std::locale("Japanese_Japan.437"), "{:L%B}\n\n", ymd);


//     std::println("===== std::println test ============================================");
//     std::println("𝓼𝓽𝓭::𝓹𝓻𝓲𝓷𝓽𝓵𝓷 умеет 输出 どんな κείμενο en UTF-8 🖋️📜🌏\n");


//     try {
//         // setlocale(LC_ALL, "Russian_Russia.utf8");
//         //wprintf_s(L"wprintf: �??fuck\n");
//         //wchar_t ws[10];
//         //wscanf_s(L"%ls", ws, (unsigned)_countof(ws));
//         //for (int i = 0; ws[i] != 0; ++i) {
//         //    std::wcout << std::format(L"Byte {}: {:#06x}\n", i, int(ws[i]));
//         //}

//         // std::wcout << L"\n";

//         // std::vector glocs{
//         //     "English_United Kingdom.437", "English_United Kingdom.1251", "English_United Kingdom.utf8",
//         // };
//         // std::vector locs{
//         //     "Russian_Russia.437", "Russian_Russia.1251", "Russian_Russia.utf8",
//         // };

//         // for (auto lg : glocs) {
//         //     std::locale::global(std::locale(lg));
//         //     for(auto lcout : locs) {
//         //         std::cout.imbue(std::locale(lcout));
//         //         std::cout << std::format("\nglobal: {} cout: {}", (lg), (lcout));
//         //         try {
//         //             TestLocaleDependentNarrowFuncs();
//         //         } catch(...) {
//         //             std::cout.clear();
//         //             std::cout << "\nbadbit\n";
//         //         }
//         //     }
//         // }

//         // std::cout << "\n\n";

//         // for (auto lg : glocs) {
//         //     std::locale::global(std::locale(lg));
//         //     for(auto lcout : locs) {
//         //         std::wcout.imbue(std::locale(lcout));
//         //         std::wcout << std::format(L"\nglobal: {} wcout: {}", Widen(lg), Widen(lcout));
//         //         try {
//         //             TestLocaleDependentWideFuncs();
//         //         } catch(...) {
//         //             std::wcout.clear();
//         //             std::wcout << "\nbadbit\n";
//         //         }
//         //     }
//         // }

//         // std::locale::global(std::locale("Russian_Russia.utf8"));

//         // const char* locGlob = "Russian_Russia.utf8";
//         // std::locale::global(std::locale(locGlob));

//         // const char* loc = "Russian_Russia.utf8";
//         // std::cout.imbue(std::locale(loc));
//         // std::cin.imbue(std::locale(loc));
//         // TestNarrowEncoding();

//         // std::wcout.imbue(std::locale(loc));
//         // std::wcin.imbue(std::locale(loc));

//         // std::cout << "\xF0 \xA5 \xAE\n";
//         // std::cout << "🥀\n";

//         // _setmode(_fileno(stdout), _O_U16TEXT);
//         // _setmode(_fileno(stderr), _O_U16TEXT);
//         // _setmode(_fileno(stdin), _O_U16TEXT);

//         // TestWideEncoding();

//         // https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/setmode?view=msvc-170
//         // Use of a narrow print function on a Unicode mode stream triggers an assert.
//         // _setmode(_fileno(stdout), _O_U16TEXT);
//         // _setmode(_fileno(stderr), _O_U16TEXT);
//         // _setmode(_fileno(stdin), _O_U16TEXT);
//         // TestWideEncoding();
//         // TestNarrowEncoding();
//     } catch (const std::exception& e) {
//         std::wcout << "Exception caught: " << e.what() << std::endl;
//         // MessageBoxW(NULL, Widen(e.what()).c_str(), L"", MB_OK);
//     }
//     // system("pause");
//     // SetConsoleOutputCP(866);
//     // SetConsoleCP(866);
// }

#include <stdio.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>

#define SZ 256

int main(void)
{
    int _ = _setmode(_fileno(stdin), _O_U16TEXT);
    _ = _setmode(_fileno(stdout), _O_U16TEXT);

    TCHAR input[SZ] = { 0 };

    _tprintf(L"Введите текст: ");
    fgetws(input, SZ, stdin); input[wcslen(input) - 1] = 0;
    _tprintf(L"Введенны текст: %s", input);

    return 0;
}
