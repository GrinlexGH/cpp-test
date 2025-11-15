set(CURRENT_TARGET_NAME wxwidgets-test)

if(NOT (TARGET wx::wxbase))
    message(STATUS "[${CURRENT_TARGET_NAME}] skipped.")
    return()
endif()

set(SOURCES
    main.cpp
)

if(WIN32)
    get_target_property(wxWidgets_INCLUDES wx::wxbase INTERFACE_INCLUDE_DIRECTORIES)
    list(GET wxWidgets_INCLUDES 1 wxWidgets_INCLUDE)
    list(APPEND SOURCES ${wxWidgets_INCLUDE}/wx/msw/wx.rc)
endif()

add_executable_(${CURRENT_TARGET_NAME} ${SOURCES})

target_precompile_headers(${CURRENT_TARGET_NAME} PRIVATE pch.hpp)

deps_target_link_libraries(${CURRENT_TARGET_NAME} PRIVATE wxWidgets::wxWidgets)
