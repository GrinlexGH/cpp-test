set(CURRENT_TARGET_NAME win32xx)

set(SOURCES
    main.cpp
    DialogApp.h
    DialogApp.cpp
    MyDialog.h
    MyDialog.cpp
    stdafx.cpp
    resource.rc
    res/main.manifest
)

add_executable_(${CURRENT_TARGET_NAME} WIN32 ${SOURCES})

target_precompile_headers(${CURRENT_TARGET_NAME} PRIVATE stdafx.h)

target_link_libraries(${CURRENT_TARGET_NAME} PRIVATE
    Comctl32
    Win32xx::Win32xx
)
