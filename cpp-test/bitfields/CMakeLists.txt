set(CURRENT_TARGET_NAME bitfields)

set(SOURCES
    main.cpp
)

add_executable_(${CURRENT_TARGET_NAME} ${SOURCES})

deps_target_link_and_copy_runtime(${CURRENT_TARGET_NAME}
    PRIVATE
    benchmark::benchmark
)
