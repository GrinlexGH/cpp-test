set(CURRENT_TARGET_NAME fast)

set(SOURCES
    main.cpp
)

add_executable_(${CURRENT_TARGET_NAME} ${SOURCES})

target_link_libraries(${CURRENT_TARGET_NAME} PRIVATE
    Vulkan::Headers
)
