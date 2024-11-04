cmake_minimum_required(VERSION 3.10)
project(taskScheduler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/task_scheduler.cpp
)

set(HEADERS
    inc/task_scheduler.h
)

# build options
option(BUILD_SHARED_LIBS "Build shared library" ON)
option(BUILD_EXECUTABLE "Build executable" ON)

# create library
if(BUILD_SHARED_LIBS)
    add_library(taskSchedulerLib SHARED ${SOURCES} ${HEADERS})
else()
    add_library(taskSchedulerLib STATIC ${SOURCES} ${HEADERS})
endif()

# create executable file
if(BUILD_EXECUTABLE)
    add_executable(taskScheduler src/main.cpp)
    target_link_libraries(taskScheduler PRIVATE taskSchedulerLib)
    target_include_directories(taskScheduler PRIVATE inc)
endif()

target_include_directories(taskSchedulerLib PUBLIC inc)

install(TARGETS taskSchedulerLib taskScheduler
        DESTINATION bin)
