include(FindPackageHandleStandardArgs)

if(NOT Win32xx_FOUND)
    find_path(
        Win32xx_INCLUDE_DIR
        wxx_appcore.h
        PATH_SUFFIXES
        Win32xx/include/
    )

    add_library(Win32xx::Win32xx INTERFACE IMPORTED)

    set_target_properties(Win32xx::Win32xx PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${Win32xx_INCLUDE_DIR}"
    )

    #-----------------------------------------

    find_package_handle_standard_args(Win32xx DEFAULT_MSG
        Win32xx_INCLUDE_DIR
    )
endif()
