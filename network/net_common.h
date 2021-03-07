#ifndef NET_COMMON_H
#define NET_COMMON_H

#include <iostream>
#include <deque>
#include <thread>
#include <mutex>

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#include <WinSock2.h>
#endif

#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#endif //NET_COMMON_H
