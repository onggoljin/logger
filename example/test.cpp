#include "../logger.hpp"

int main()
{
	// default logger state
	//
	// console logger : off
	// buffer logger  : off
	// file logger    : off

	logger::activate_console_logger();
	LOGI("very simple log.");
	
	std::string name = "njh0602";
	auto x = 10.0f;
	auto y = 42.3f;
	LOGD("player name: %s, pos_x: %.1f, pos_y: %.1f", name.c_str(), x, y);
	LOGE("fatal error! you must fix it!!");
	LOGW("warning~ %d", 42);

	logger::inactivate_console_logger();
	logger::activate_buffer_logger();

	LOGI("hello buffer logger");
	std::cout << logger::get_buffer_log();

	logger::inactivate_buffer_logger();
	logger::activate_file_logger("/Users/jun/Desktop/log.txt");
	LOGI("it is for file %s~", "('-')");
}
