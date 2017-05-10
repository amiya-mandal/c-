cmake_minimum_required(VERSION 3.7)
project(encryptionproject)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES  md5.h md5.cpp Blowfish.h Blowfish.cpp main.cpp utf8.h utf8 )
add_executable(encryptionproject ${SOURCE_FILES} md5.h Blowfish.cpp utf8.h utf8)