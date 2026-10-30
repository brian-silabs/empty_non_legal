# Replace the generated linker script with the source controlled project copy.
get_property(_slc_link_options TARGET slc PROPERTY INTERFACE_LINK_OPTIONS)
list(FILTER _slc_link_options EXCLUDE REGEX "^-T.*autogen/linkerfile\\.ld$")
list(APPEND _slc_link_options "-T${CMAKE_CURRENT_LIST_DIR}/../linkerfile.ld")
set_property(TARGET slc PROPERTY INTERFACE_LINK_OPTIONS "${_slc_link_options}")
