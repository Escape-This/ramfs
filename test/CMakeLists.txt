idf_component_register(
	SRC_DIRS "."
	INCLUDE_DIRS "."
	
	# Allow us to write tests against 'internal' functions, not just the external API
    # INCLUDE_DIRS "../priv_include"

    REQUIRES unity ramfs		# Test-framework, and the Module-under-Test

	# Any other components needed by the tests go under here
    PRIV_REQUIRES
#    	code_snippets
#		fs_utils

		# Useful for measuring performance
#		esp_timer

    # This component sets up eMMC memory/filesystem
    PRIV_REQUIRES testfixture_emmc_fatfs

)
