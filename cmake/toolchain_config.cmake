set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Prevent host (macOS) architecture flags from being injected into cross builds.
set(CMAKE_OSX_ARCHITECTURES "" CACHE STRING "" FORCE)

set(TOOLCHAIN_ROOT /Users/mt/embedded/raspberry/arm-gnu-toolchain-15.2.rel1-darwin-arm64-arm-none-eabi/)
set(TOOLCHAIN_PREFIX ${TOOLCHAIN_ROOT}/bin/arm-none-eabi)
set(UTILS_PREFIX ${TOOLCHAIN_ROOT}/bin/arm-none-eabi)

set(CMAKE_C_COMPILER            ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_ASM_COMPILER          ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER          ${TOOLCHAIN_PREFIX}-g++)
set(CMAKE_C_COMPILER_AR         ${TOOLCHAIN_PREFIX}-gcc-ar)
set(CMAKE_C_COMPILER_RANLIB     ${TOOLCHAIN_PREFIX}-gcc-ranlib)
set(CMAKE_CXX_COMPILER_AR       ${TOOLCHAIN_PREFIX}-gcc-ar)
set(CMAKE_CXX_COMPILER_RANLIB   ${TOOLCHAIN_PREFIX}-gcc-ranlib)
set(CMAKE_AR                    ${TOOLCHAIN_PREFIX}-gcc-ar)
set(CMAKE_RANLIB                ${TOOLCHAIN_PREFIX}-gcc-ranlib)

find_program(CMAKE_OBJCOPY
    NAMES arm-none-eabi-objcopy
    HINTS $ENV{ARM_UTILS_DIR}
          ${TOOLCHAIN_ROOT}/bin
    REQUIRED
)

string(CONCAT COMMON_FLAGS
    "-mcpu=cortex-a53 "
    "-mfloat-abi=hard "
    "-mfpu=neon-fp-armv8 "
    "-ffreestanding "
    "-nostdlib "
    "-O2"
)


string(CONCAT C_FLAGS
    ${COMMON_FLAGS}
    " -std=gnu11"
)

string(CONCAT CPP_FLAGS
    ${COMMON_FLAGS}
    " -std=c++11"
    " -fabi-version=0"
    " -fno-rtti -fno-exceptions"
    " -fno-use-cxa-atexit -fno-threadsafe-statics"
)

string(CONCAT ASM_FLAGS
    ${COMMON_FLAGS}
    " -x assembler-with-cpp"
)

set(CMAKE_C_FLAGS_INIT   ${C_FLAGS})
set(CMAKE_CXX_FLAGS_INIT ${CPP_FLAGS})
set(CMAKE_ASM_FLAGS_INIT ${ASM_FLAGS})

# Set linker flags
string(CONCAT LINK_FLAGS
    " -Wl,-Map,base_project.map"
    " -Xlinker --gc-sections"
    " -nostartfiles"
    " -lc -lnosys"
)

set(CMAKE_EXE_LINKER_FLAGS ${LINK_FLAGS})

# Set executable suffix
set(CMAKE_EXECUTABLE_SUFFIX_C ".elf")

# Set "try compile target" type for generate build system
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)