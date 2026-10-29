cmake_minimum_required(VERSION 3.16)

# 将 SDK 仓库根目录注册为组件目录
set(EXTRA_COMPONENT_DIRS "../..")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(GetVersion)
