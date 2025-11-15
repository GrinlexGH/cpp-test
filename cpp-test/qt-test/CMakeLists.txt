if(WIN32 AND TARGET Qt6::Core AND TARGET Qt6::Widgets)
    set(CURRENT_TARGET_NAME qt-test)

    set(SOURCES
        main.cpp
        visual_styles.manifest
    )

    add_executable_(${CURRENT_TARGET_NAME} WIN32 ${SOURCES})

    deps_target_link_and_copy_runtime(${CURRENT_TARGET_NAME} PRIVATE
        ComCtl32 Dwmapi
        SDL3::SDL3
        Qt6::Core
        Qt6::Widgets
        nowide::nowide
    )

    get_target_property(qmake_executable_ Qt6::qmake IMPORTED_LOCATION)
    get_filename_component(qt_bin_dir_ "${qmake_executable_}" DIRECTORY)
    if(WIN32)
        find_program(qt_windeployqt6_executable_ NAMES windeployqt6 HINTS ${qt_bin_dir_})
        add_custom_command(TARGET ${CURRENT_TARGET_NAME} POST_BUILD
            COMMAND "${qt_windeployqt6_executable_}"
                    --verbose 0
                    --no-compiler-runtime
                    --no-system-d3d-compiler
                    --no-translations
                    "--$<IF:$<OR:$<CONFIG:Debug>>,debug,release>"
                    $<TARGET_FILE:${CURRENT_TARGET_NAME}>
            COMMENT "Deploying Qt libraries using windeployqt for compilation target '${CURRENT_TARGET_NAME}' ..."
        )
    endif()
endif()
