# logger

simple log sample:

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
