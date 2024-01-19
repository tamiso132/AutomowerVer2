# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/tom/esp/esp-idf/components/bootloader/subproject"
  "/home/tom/projects/automower/build/bootloader"
  "/home/tom/projects/automower/build/bootloader-prefix"
  "/home/tom/projects/automower/build/bootloader-prefix/tmp"
  "/home/tom/projects/automower/build/bootloader-prefix/src/bootloader-stamp"
  "/home/tom/projects/automower/build/bootloader-prefix/src"
  "/home/tom/projects/automower/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/tom/projects/automower/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/tom/projects/automower/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
