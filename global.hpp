#ifndef GLOBAL_H
#define GLOBAL_H

#include <atomic>
#include <iostream>

/** Boolean which allows recording of further frames.
 * it should not be static. */
inline std::atomic_bool on = false;

inline void footerMsg() {
    std::cout << "Press Enter to stop...";
    std::cout.flush();
}

inline void print(const std::string &s) {
    if (!s.empty()) std::cout << "\r" << s.c_str() << std::endl;
    if (on) footerMsg();
}

template<typename ... Args>
inline void print(const std::string &s, Args ... args) {
    char buf[s.length() + 20u];
    std::snprintf(buf, sizeof(buf), s.c_str(), args...);
    if (!s.empty()) std::cout << "\r" << buf << std::endl;
    if (on) footerMsg();
}

#endif //GLOBAL_H
