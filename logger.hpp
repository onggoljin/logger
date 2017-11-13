//
//  logger.hpp
//  logger
//
//  Created by NamJunHyeon on 2017. 11. 7..
//

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <cstdarg>
#include <sstream>

template <typename dummy> class logger_static_base
{
    
protected:
    
    static bool m_is_enable_console_logger;
    static bool m_is_enable_file_logger;
    static bool m_is_enable_buffer_logger;
    static std::ofstream m_file;
    static std::string m_buffer_log;
    
};

template <typename dummy> bool logger_static_base<dummy>::m_is_enable_console_logger = false;
template <typename dummy> bool logger_static_base<dummy>::m_is_enable_file_logger = false;
template <typename dummy> bool logger_static_base<dummy>::m_is_enable_buffer_logger = false;
template <typename dummy> std::ofstream logger_static_base<dummy>::m_file;
template <typename dummy> std::string logger_static_base<dummy>::m_buffer_log;

class logger : public logger_static_base<void>
{
    
public:
    
    enum class type { console, file, buffer };
    enum class level { info, error, debug, warning };
    
    logger() = delete;
    
    static void activate_console_logger() { enable_logger(logger::type::console); }
    static void inactivate_console_logger() { disable_logger(logger::type::console); }
    
    static void activate_buffer_logger() { enable_logger(logger::type::buffer); }
    static void inactivate_buffer_logger() { disable_logger(logger::type::buffer); }
    
    static bool activate_file_logger(const std::string& path)
    {
        enable_logger(logger::type::file);
        
        if ( m_file.is_open() )
            m_file.close();
        
        m_file.open(path);
        
        return m_file.is_open();
    }
    
    static void inactivate_file_logger()
    {
        disable_logger(logger::type::file);
        
        if ( m_file.is_open() )
            m_file.close();
    }
    
    
    static const std::string& get_buffer_log() { return m_buffer_log; }
    
    static void log(logger::level level, const char* file, int line, const char* format, ...)
    {
        static char msg[4096];
        va_list args;
        va_start (args, format );
        vsnprintf(msg, 4096, format, args);
        
        std::string level_str;
        switch (level)
        {
            case logger::level::info:
            {
                level_str = "[info   ]";
                break;
            }
            case logger::level::error:
            {
                level_str = "[error  ]";
                break;
            }
            case logger::level::debug:
            {
                level_str = "[debug  ]";
                break;
            }
            case logger::level::warning:
            {
                level_str = "[warning]";
                break;
            }
        }
        
        const auto slash = std::strrchr(file, '/');
        if (slash) file = slash + 1;
#ifdef _WIN32
        slash = strrchr(file, '\\');
        if (slash) file = slash + 1;
#endif
        
        std::string output = current_data_time() + " " + level_str + " [" + file + "(" + std::to_string(line) + ")] " + msg;
        if ( m_is_enable_console_logger ) std::cout << output << "\n";
        if ( m_is_enable_buffer_logger ) m_buffer_log += (output + "\n");
        if ( m_is_enable_file_logger )
        {
            m_file << output << "\n";
            m_file.flush();
        }
    }
    
private:
    
    static const std::string current_data_time()
    {
        time_t now = time(0);
        struct tm tstruct;
        char buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "[%Y-%m-%d %X]", &tstruct);
        
        return buf;
    }
    
    static void enable_logger(logger::type type)
    {
        set_logger_state(type, true);
    }
    
    static void disable_logger(logger::type type)
    {
        set_logger_state(type, false);
    }
    
    static void set_logger_state(logger::type type, bool enabled)
    {
        switch ( type)
        {
            case logger::type::console:
            {
                m_is_enable_console_logger = enabled;
                break;
            }
            case logger::type::file:
            {
                m_is_enable_file_logger = enabled;
                break;
            }
            case logger::type::buffer:
            {
                m_is_enable_buffer_logger = enabled;
                break;
            }
                
            default: break;
        }
    }
    
};

#define LOGI(expr, ...) logger::log(logger::level::info, __FILE__, __LINE__, expr, ##__VA_ARGS__);
#define LOGD(expr, ...) logger::log(logger::level::debug, __FILE__, __LINE__, expr, ##__VA_ARGS__);
#define LOGE(expr, ...) logger::log(logger::level::error, __FILE__, __LINE__, expr, ##__VA_ARGS__);
#define LOGW(expr, ...) logger::log(logger::level::warning, __FILE__, __LINE__, expr, ##__VA_ARGS__);
