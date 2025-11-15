if(TARGET wxWidgets::wxWidgets)
    set(CURRENT_TARGET_NAME wxwidgets-test)

    set(SOURCES
        main.cpp
    )

    add_executable_(${CURRENT_TARGET_NAME} ${SOURCES})

    target_compile_definitions(${CURRENT_TARGET_NAME} PRIVATE "WX_PRECOMP")

    deps_target_link_and_copy_runtime(${CURRENT_TARGET_NAME} PRIVATE
        Comctl32
        wxWidgets::wxWidgets
    )
endif()
