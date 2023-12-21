#include <fix_tdr_delay/fix_tdr_delay.hpp>
#include <iostream>

int main()
{
    {
        auto const backup = fix_tdr_delay::get_tdr_delay();
        std::cout << "Current TdrDelay " << backup << '\n';
        auto const success = fix_tdr_delay::set_tdr_delay(17);
        if (!success)
            std::cout << "Failed to set TdrDelay\n";
        if (fix_tdr_delay::get_tdr_delay() != 17)
            std::cout << "Failed to set TdrDelay to the correct value\n";
        fix_tdr_delay::set_tdr_delay(backup);
    }
    {
        auto const backup = fix_tdr_delay::get_tdr_ddi_delay();
        std::cout << "Current TdrDdiDelay " << backup << '\n';
        auto const success = fix_tdr_delay::set_tdr_ddi_delay(17);
        if (!success)
            std::cout << "Failed to set TdrDdiDelay\n";
        if (fix_tdr_delay::get_tdr_ddi_delay() != 17)
            std::cout << "Failed to set TdrDdiDelay to the correct value\n";
        fix_tdr_delay::set_tdr_ddi_delay(backup);
    }
}