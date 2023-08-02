// Leave off trailing semicolon to enforce function-like usage
#define ASSERT(cond, fmt) \
    do { \
        if (!(cond)) { \
            SPDLOG_ERROR("Assertion Failed ({}): {}", #cond, fmt); \
            exit(1); \
        } \
    } while (0)
