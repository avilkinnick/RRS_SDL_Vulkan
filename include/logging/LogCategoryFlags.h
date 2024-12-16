#ifndef LOGGING_LOG_CATEGORY_FLAGS_H
#define LOGGING_LOG_CATEGORY_FLAGS_H

enum class LogCategoryFlags : int
{
    error = 0x01,
    warning = 0x02,
    info = 0x04,
    message = 0x08,
    debug = 0x10,
    all = 0x20 - 1
};

inline constexpr LogCategoryFlags operator&(LogCategoryFlags flag1, LogCategoryFlags flag2)
{
    return static_cast<LogCategoryFlags>(static_cast<int>(flag1) & static_cast<int>(flag2));
}

inline constexpr LogCategoryFlags operator|(LogCategoryFlags flag1, LogCategoryFlags flag2)
{
    return static_cast<LogCategoryFlags>(static_cast<int>(flag1) | static_cast<int>(flag2));
}

inline constexpr LogCategoryFlags operator^(LogCategoryFlags flag1, LogCategoryFlags flag2)
{
    return static_cast<LogCategoryFlags>(static_cast<int>(flag1) ^ static_cast<int>(flag2));
}

inline constexpr LogCategoryFlags operator~(LogCategoryFlags flag)
{
    return static_cast<LogCategoryFlags>(~static_cast<int>(flag));
}

inline LogCategoryFlags& operator&=(LogCategoryFlags& flag1, LogCategoryFlags flag2)
{
    flag1 = flag1 & flag2;
    return flag1;
};

inline LogCategoryFlags& operator|=(LogCategoryFlags& flag1, LogCategoryFlags flag2)
{
    flag1 = flag1 | flag2;
    return flag1;
};

inline LogCategoryFlags& operator^=(LogCategoryFlags& flag1, LogCategoryFlags flag2)
{
    flag1 = flag1 ^ flag2;
    return flag1;
};

#endif // LOGGING_LOG_CATEGORY_FLAGS_H
