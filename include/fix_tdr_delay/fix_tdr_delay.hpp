#pragma once

namespace fix_tdr_delay {

struct Result {
    /// True iff the values of TdrDelay and TdrDdiDelay are now greater or equal to the minimum requested.
    bool has_succeeded{};
    /// True iff something has actually changed and the computer needs to restart for the changes to take effect.
    bool needs_to_restart{};
};

/// Sets the TdrDelay and TdrDdiDelay to the requested value, or does nothing if they were already greater or equal to the minimum requested.
auto set_minimum_delay(int delay_in_seconds) -> Result;

// Returns true iff the delay has been successfully set.
auto set_tdr_delay(int delay_in_seconds) -> bool;
// Returns true iff the delay has been successfully set.
auto set_tdr_ddi_delay(int delay_in_seconds) -> bool;

auto get_tdr_delay() -> int;
auto get_tdr_ddi_delay() -> int;

} // namespace fix_tdr_delay
