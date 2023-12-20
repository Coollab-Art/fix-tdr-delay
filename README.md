# fix_tdr_delay

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
