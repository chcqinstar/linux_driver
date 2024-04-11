## CMake最小版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(ledtest)

# 设置C标准
set(CMAKE_C_STANDARD 99)

#设置gcc编译器
set(CMAKE_C_COMPILER "/home/book/100ask_imx6ull_mini-sdk/ToolChain/arm-buildroot-linux-gnueabihf_sdk-buildroot/bin/arm-buildroot-linux-gnueabihf-gcc")

# 添加源代码文件到你的项目中
aux_source_directory(src SRC_SUB)
# 添加子目录--src 目录下的所有源文件打包为 SRC_SUB
aux_source_directory(. SRC_CUR)
# 添加子目录--根目录下的所有源文件打包为 SRC_CUR

# 指定生成目标
add_executable(${PROJECT_NAME} ${SRC_CUR} ${SRC_SUB})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

#声明构建此可执行文件需要链接的库


# 添加头文件目录
include_directories(/home/book/100ask_imx6ull_mini-sdk/ToolChain/arm-buildroot-linux-gnueabihf_sdk-buildroot/bin/../lib/gcc/arm-buildroot-linux-gnueabihf/7.5.0/include)

#生成compile_commands.json文件
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)