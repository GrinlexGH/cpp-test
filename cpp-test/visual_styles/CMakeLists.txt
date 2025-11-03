if(WIN32 AND TARGET Qt6::Core AND TARGET Qt6::Widgets)
    set(CURRENT_TARGET_NAME visual_styles)

    set(SOURCES
        main.cpp
        visual_styles.manifest
    )

    add_executable_(${CURRENT_TARGET_NAME} WIN32 ${SOURCES})

    target_link_libraries(${CURRENT_TARGET_NAME} PRIVATE
        ComCtl32 Dwmapi
        SDL3::SDL3
        Qt6::Core
        Qt6::Widgets
        nowide::nowide
    )

    get_target_property(QMAKE_EXECUTABLE_ Qt6::qmake IMPORTED_LOCATION)
    get_filename_component(QT_BIN_DIR_ "${QMAKE_EXECUTABLE_}" DIRECTORY)
    find_program(QT_WINDEPLOYQT6_ NAMES windeployqt6 HINTS ${QT_BIN_DIR_})
    add_custom_command(TARGET ${CURRENT_TARGET_NAME} POST_BUILD
        COMMAND "${QT_WINDEPLOYQT6_}"
                --verbose 0
                --no-compiler-runtime
                --no-system-d3d-compiler
                "--$<IF:$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>,debug,release>"
                $<TARGET_FILE:${CURRENT_TARGET_NAME}>
        COMMENT "Deploying Qt libraries using windeployqt for compilation target '${CURRENT_TARGET_NAME}' ..."
    )
endif()
