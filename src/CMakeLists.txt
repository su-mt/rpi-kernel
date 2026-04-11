add_executable(${PROJECT_NAME}
    startup.c
    uart.c
    main.c
    stubs.c
    printf.c
    memory_map/memory.c
)

# Link with the linker script from this directory.
target_link_options(${PROJECT_NAME} PRIVATE
    "-T${CMAKE_CURRENT_SOURCE_DIR}/linker.ld"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    c
    nosys
    gcc
)

add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY}
    ARGS -O binary $<TARGET_FILE:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>/${PROJECT_NAME}.img
)