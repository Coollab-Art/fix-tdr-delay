#include <fix_tdr_delay/fix_tdr_delay.hpp>

namespace fix_tdr_delay {

#if defined(_WIN32)
#include <Windows.h>

static const HKEY   registry{HKEY_CURRENT_USER};
static const LPCSTR registryPath = R"(SYSTEM\CurrentControlSet\Control\GraphicsDrivers)";

static auto set_key(LPCSTR key_name, DWORD key_value)
{
    bool success{false};
    HKEY hKey;
    LONG openResult = RegCreateKeyExA(registry, registryPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, &hKey, NULL);

    if (openResult == ERROR_SUCCESS)
    {
        DWORD valueType = REG_DWORD;
        LONG setResult = RegSetValueExA(hKey, key_name, 0, valueType, reinterpret_cast<BYTE*>(&key_value), sizeof(key_value));

        if (setResult == ERROR_SUCCESS)
            success = true;

        // Don't forget to close the key after using it
        RegCloseKey(hKey);
    }

    return success;
}

auto get_key_value(LPCSTR key_name) -> DWORD
{
    HKEY  hKey;
    DWORD value{2}; // The default value when the key does not exist is 2 seconds on Windows.
    LONG  result = RegOpenKeyExA(registry, registryPath, 0, KEY_READ, &hKey);

    if (result == ERROR_SUCCESS)
    {
        DWORD valueType;
        DWORD valueData;
        DWORD valueSize = sizeof(DWORD);

        LONG queryResult = RegQueryValueExA(hKey, key_name, NULL, &valueType, reinterpret_cast<LPBYTE>(&valueData), &valueSize);

        if (queryResult == ERROR_SUCCESS && valueType == REG_DWORD)
            value = valueData;
        
        RegCloseKey(hKey);
    }
    return value;
}

auto set_tdr_delay(int delay_in_seconds) -> bool
{
    return set_key("TdrDelay", delay_in_seconds);
}

auto set_tdr_ddi_delay(int delay_in_seconds) -> bool
{
    return set_key("TdrDdiDelay", delay_in_seconds);
}

auto get_tdr_delay() -> int
{
    return get_key_value("TdrDelay");
}

auto get_tdr_ddi_delay() -> int
{
    return get_key_value("TdrDdiDelay");
}

#else

auto set_tdr_delay(int /* delay_in_seconds */) -> bool
{
    return true;
}

auto set_tdr_ddi_delay(int /* delay_in_seconds */) -> bool
{
    return true;
}

auto get_tdr_delay() -> int
{
    return 999;
}

auto get_tdr_ddi_delay() -> int
{
    return 999;
}

#endif

auto set_minimum_delay(int delay_in_seconds) -> Result
{
    bool success{true};
    bool needs_to_restart{false};
    if (get_tdr_delay() < delay_in_seconds)
    {
        bool const b = set_tdr_delay(delay_in_seconds);
        success &= b;
        needs_to_restart |= b;
    }
    if (get_tdr_ddi_delay() < delay_in_seconds)
    {
        bool const b = set_tdr_ddi_delay(delay_in_seconds);
        success &= b;
        needs_to_restart |= b;
    }
    return Result{success, needs_to_restart};
}

} // namespace fix_tdr_delay
