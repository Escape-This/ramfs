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

#define MOUNT_POINT "/ramfs"

ramfs_vfs_conf_t ramfs_vfs_conf = {
    .base_path = MOUNT_POINT,
    .fs = NULL,
    .max_files = 5,
};

// ---- Forward-declared static functions ---- //



// ---- Cleanup functions ---- //

// This will run before each test!
static void LOCAL_TEST_setUp(void)
{
	// Create and mount
	ramfs_vfs_conf.fs = ramfs_init();
	assert(ramfs_vfs_conf.fs != NULL);
    ESP_ERROR_CHECK(ramfs_vfs_register(&ramfs_vfs_conf));
	//

    errno = 0;
}

// This will run after each test!
static void LOCAL_TEST_tearDown(void)
{

    TEST_ASSERT_EQUAL_MESSAGE(0, errno, "If this is expected for this test, then set errno = 0 before calling teardown");	//

	// Unmount and destroy
	ESP_ERROR_CHECK(ramfs_vfs_unregister(&ramfs_vfs_conf));
	ramfs_deinit(ramfs_vfs_conf.fs);
	ramfs_vfs_conf.fs = NULL;
}

// NOTE: These tests were written for an existing libray, and NOT created using TDD!


TEST_CASE("Register and Unregister file system", "[esp_ramfs][TDD-dev]")
{
    LOCAL_TEST_setUp();

	// This test was essentially moved into setUp/tearDown

    LOCAL_TEST_tearDown();
}

TEST_CASE("Create a file in the root directory", "[esp_ramfs][TDD-dev]")
{
    LOCAL_TEST_setUp();

	const char* filepath = MOUNT_POINT "/file.txt";

    FILE* fd = fopen(filepath, "w");
    TEST_ASSERT_NOT_NULL(fd);

    int ret = fclose(fd);
    TEST_ASSERT_EQUAL(0, ret);
	

    LOCAL_TEST_tearDown();
}





