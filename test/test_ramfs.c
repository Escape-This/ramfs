/* Not developed with TDD!
 *
 * Instead, these are just tests of an existing open-source library. Added after I found
 * that the mkdir() function wasn't working!
 */

// ---- Test framework ---- //
#include "freertos/projdefs.h"
#include "unity.h"

// ---- Code to be tested ---- //
#include "ramfs/vfs.h"

// ---- Additional test fixtures ---- //

// ---- esp-idf components & system headers ---- //
//#include <sys/param.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <sys/syslimits.h>
#include <errno.h>

#include "esp_err.h"
#include "esp_check.h"
#include "esp_log.h"

#include "esp_system.h"  // Allows measuring currently available memory

// ---- Local files (this component) ---- //

// ---- End of includes ---- //

// Tag prepended to ESP_LOG messages in this component: can also be used to filter messages at runtime
__attribute__((unused))
static const char* TAG = "test_ramfs";

__attribute__((unused))
static const char* SANITY = "sanity check for test-fixture";        //!< Marks tests which are to ensure the test-fixture is working correctly (not TDD)

// ---- private types ---- //

// ---- private Global variables ---- //


// ---- Forward-declared static functions ---- //



// ---- Cleanup functions ---- //

// This will run before each test!
static void LOCAL_TEST_setUp(void)
{
    errno = 0;
}

// This will run after each test!
static void LOCAL_TEST_tearDown(void)
{

    TEST_ASSERT_EQUAL_MESSAGE(0, errno, "If this is expected for this test, then set errno = 0 before calling teardown");	//
}

// NOTE: These tests were written for an existing libray, and NOT created using TDD!


TEST_CASE("Function prototype: register and unregister file system", "[esp_ramfs][TDD-dev]")
{
    LOCAL_TEST_setUp();

	ramfs_fs_t *fs = ramfs_init();
	assert(fs != NULL);

    ramfs_vfs_conf_t ramfs_vfs_conf = {
	    .base_path = "/ramfs",
        .fs = fs,
        .max_files = 5,
    };
    ESP_ERROR_CHECK(ramfs_vfs_register(&ramfs_vfs_conf));

	// Mounted!

	ESP_ERROR_CHECK(ramfs_vfs_unregister(&ramfs_vfs_conf));

	ramfs_deinit(fs);

    LOCAL_TEST_tearDown();
}

//TEST_CASE("Function prototype: unpack_tarball_to_dir()", "[esp_ramfs][TDD-dev]")
//{
//    LOCAL_TEST_setUp();
//
//    // Function arguments have attribute __nonnull__, so we need to pass it something...
//    const char* emptystr = "";
//    unpack_tarball_to_dir_opts_t options = {0};
//
//    // Input file path, output dir path, options
//    unpack_tarball_to_dir(emptystr, emptystr, options);
//
//    LOCAL_TEST_tearDown();
//}
//
//
//TEST_CASE("Tar and untar a single file", "[esp_ramfs][TDD-dev]")
//{
//    LOCAL_TEST_setUp();
//
//	const char* tarball_path = LOCAL_TEST_DIR "test.tar";
//	
//	// Create file
//	const char* input_file = LOCAL_TEST_DIR_INPUT "file.txt";
//	const char* filedata = "abcdef";
//	save_text(input_file, filedata);
//	TEST_ASSERT_TRUE_MESSAGE(file_exists(input_file), SANITY);
//
//	const char* expected_out_file  = LOCAL_TEST_DIR_OUTPUT "file.txt";
//	TEST_ASSERT_FALSE_MESSAGE(file_exists(expected_out_file), SANITY);
//
//	// Make tarball
//	{
//	    pack_dir_to_tarball_opts_t options = {0};
//	    esp_err_t err = pack_dir_to_tarball(LOCAL_TEST_DIR_INPUT, tarball_path, options);
//		TEST_ASSERT_EQUAL(ESP_OK, err);
//	}
//
//	TEST_ASSERT_TRUE(file_exists(tarball_path));
//	
//	// Unpack tarball
//	{
//	    unpack_tarball_to_dir_opts_t options = {0};
//	    esp_err_t err = unpack_tarball_to_dir(tarball_path, LOCAL_TEST_DIR_OUTPUT, options);
//		TEST_ASSERT_EQUAL(ESP_OK, err);
//	}
//
//	TEST_ASSERT_TRUE(file_exists(expected_out_file));
//
//	TEST_ASSERT_EQUAL(0, diff_file(input_file, expected_out_file));
//
//    LOCAL_TEST_tearDown();
//}





