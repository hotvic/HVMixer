find_library (BOOST_PO-LIB boost_program_options)

find_package (PkgConfig)

pkg_check_modules (GTKMM REQUIRED gtkmm-3.0)


link_directories (
    ${GTKMM_LIBRARY_DIRS}
)
include_directories (
    ${GTKMM_INCLUDE_DIRS}
)

add_executable (hvmixer
    hvmixer.cpp
    settings.cpp
    main.cpp
)
target_link_libraries (hvmixer
    ${BOOST_PO-LIB}
    ${GTKMM_LIBRARIES}
)
