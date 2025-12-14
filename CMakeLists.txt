cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Events)

add_executable("Simple-Events"
    "SimpleEvents/src/main.cpp"
    "SimpleEvents/src/event.h"
    "SimpleEvents/src/event_dispatcher.cpp"
    "SimpleEvents/src/event_dispatcher.h")

add_executable("Typesafe-Delegates"
    "TypeSafeDelegates/src/main.cpp"
    "TypeSafeDelegates/src/delegate.h"
    "TypeSafeDelegates/src/multicast_delegate.h")