set(CURRENT_TARGET_NAME locales)

set(SOURCES
    main.cpp
)

add_executable_(${CURRENT_TARGET_NAME} ${SOURCES})

if (${CMAKE_CXX_COMPILER_ID} MATCHES "GNU")
    target_link_libraries(${CURRENT_TARGET_NAME} PRIVATE stdc++exp)
endif()
