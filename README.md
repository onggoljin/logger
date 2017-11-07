# logger

## simple log sample:

```cpp
#include "logger.hpp"
int main()
{
    logger::activate_console_logger();
    LOGI("very simple log.");
}
```

output:

```
[2017-11-07 17:45:47] [info   ] [main.cpp(5)] very simple log.
```

## file logger

```cpp
#include "logger.hpp"
int main()
{
    logger::activate_file_logger("/your/path/log.txt");
    LOGI("it is file logger %3d%s", 42, "('-')");
}
```

## buffer logger

```cpp
#include "logger.hpp"
int main()
{
    logger::activate_buffer_logger();
    LOGD("it is buffer logger!");
    std::cout << logger::get_buffer_log();
}
```

output:

```
[2017-11-07 17:45:47] [debug  ] [main.cpp(5)] it is buffer logger!
```

## log types

```cpp
#include "logger.hpp"
int main()
{
    LOGD("debug %d", 42);
    LOGI("info %d %d", 42, 43);
    LOGE("error");
    LOGW("warning");
}
```
