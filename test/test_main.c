/**
 * Test the functions associated with the dns_manager function that handles
 * modifying the message buffer in place and accessing its values.
 */

#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

// Include files needed from sources.
#include "../src/dns_defns.h"
#include "../src/dns_manager.h"

// General-purpose buffer used by tests. Used Wireshark sample DNS capture
// https://wiki.wireshark.org/SampleCaptures and generated integer values
// for validation with https://www.scadacore.com/tools/programming-calculators/online-hex-converter/.
uint8_t main_test_message[] = {
    0x10, 0x32, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x06, 0x67, 0x6f, 0x6f,
    0x67, 0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00,
    0x00, 0x10, 0x00, 0x01};

/**
 * Start the DNS manager test suite.
 */
int initialize_dns_main_test_suite(void)
{
    fprintf(stdout, "\nStarting DNS Manager Tests.");
    return 0;
}

/** 
 * Close down the DNS manager test suite.
 */
int cleanup_dns_main_test_suite(void)
{
    fprintf(stdout, "\nCompleting DNS Manager Tests.");
    return 0;
}

/** 
 * Validates the functionality of the main method given some test message
 * and expected output value.
*/
void test_main(void)
{
    // TODO
}


/**
 * Main function for setting up and running all of the tests.  
 * Returns CUE_SUCCESS if tests execute successfully, and returns
 * a CUNit error code if tests fail.
*/
int MAIN_TEST()
{
    // Initialize the test registry and add the suite to the registry.

    CU_pSuite testSuite = NULL;
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    // Initialize all three test suites.
    testSuite = CU_add_suite("DNS Manager Get Tests", initialize_dns_main_test_suite, cleanup_dns_main_test_suite);

    if (NULL == testSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Ensure we can get the expected value after processing..
    if ((NULL == CU_add_test(testSuite, "Test of add_answers function", test_main)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all of the tests.
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
