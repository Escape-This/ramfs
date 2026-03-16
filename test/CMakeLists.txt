idf_component_register(
	SRC_DIRS "."
	INCLUDE_DIRS "."
	
	# Allow us to write tests against 'internal' functions, not just the external API
    # INCLUDE_DIRS "../priv_include"

    REQUIRES unity ramfs		# Test-framework, and the Module-under-Test

	# Any other components needed by the tests go under here
    PRIV_REQUIRES
		# Useful for measuring performance
#		esp_timer

    	# Dependencies have been deliberately kept low
    	# esp-idf dependencies (e.g. vfs) are ok, but there's no need to add them
    	# if they are not used directly.
)

target_compile_options(${COMPONENT_LIB} PRIVATE -Werror)	# Doesn't work?
target_compile_options(${COMPONENT_LIB} PRIVATE -fanalyzer)