cmake_minimum_required(VERSION 3.23)
project(WBlog)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(op
        Area.cpp
        Area.h
        BlogPart6.cpp
        Post.cpp
        Post.h
        User.cpp
        User.h SuperUser.cpp SuperUser.h)
