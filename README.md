# fix_tdr_delay

On Windows, there is a rule that says that if your program makes on operation on the GPU (like running a compute shader or a draw call) that takes more than X seconds, Windows will kill your program. By default this delay is set to 2 seconds, which can be very limiting for applications that make heavy use of the GPU. A much more sensible default would be something like 60 seconds. This can be changed with this library:

```cpp
#include <fix_tdr_delay/fix_tdr_delay.hpp>

int main()
{
    auto const result = fix_tdr_delay::set_minimum_delay(60);
    if(!result.has_succeeded)
        // Display an error message
    if(result.needs_to_restart)
        // Prompt the user to restart their computer
}
```

Note that for the changes to take effect, the user needs to restart their computer.

More precisely, what `set_minimum_delay()` does is change the `TdrDelay` and `TdrDdiDelay` registry keys on Windows. For more information, you can [read this article](https://helpx.adobe.com/substance-3d-painter/technical-support/technical-issues/gpu-issues/gpu-drivers-crash-with-long-computations-tdr-crash.html).

You can also get and set the values of the individual keys with `get_tdr_delay()`, `set_tdr_delay()`, `get_tdr_ddi_delay()` and `set_tdr_ddi_delay()`.

## Including

To add this library to your project, simply add these two lines to your *CMakeLists.txt*:
```cmake
add_subdirectory(path/to/fix_tdr_delay)
target_link_libraries(${PROJECT_NAME} PRIVATE fix_tdr_delay::fix_tdr_delay)
```

Then include it as:
```cpp
#include <fix_tdr_delay/fix_tdr_delay.hpp>
```

## Running the tests

Simply use "tests/CMakeLists.txt" to generate a project, then run it.<br/>
If you are using VSCode and the CMake extension, this project already contains a *.vscode/settings.json* that will use the right CMakeLists.txt automatically.
