set(CURRENT_TARGET_NAME bitfields)

if(NOT (TARGET benchmark::benchmark))
    message(STATUS "[${CURRENT_TARGET_NAME}] skipped.")
    return()
endif()

set(SOURCES
    main.cpp
)

add_executable_(${CURRENT_TARGET_NAME} ${SOURCES})

deps_target_link_libraries(${CURRENT_TARGET_NAME}
    PRIVATE
    benchmark::benchmark
)
