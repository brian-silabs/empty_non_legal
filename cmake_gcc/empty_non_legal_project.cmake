target_sources(empty_non_legal PRIVATE
	"../radio_ccm.c"
	"../app_radio.c"
)

# User-maintained linker customization; this managed project file is preserved.
include(${CMAKE_CURRENT_LIST_DIR}/custom_linkerfile.cmake)
