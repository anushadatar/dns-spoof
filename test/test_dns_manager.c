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
uint8_t test_message[] = {
    0x10, 0x32, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x06, 0x67, 0x6f, 0x6f,
    0x67, 0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00,
    0x00, 0x10, 0x00, 0x01};

/**
 * Start the DNS manager test suite.
 */
int initialize_dns_manager_test_suite(void)
{
    fprintf(stdout, "\nStarting DNS Manager Tests.");
    return 0;
}

/** 
 * Close down the DNS manager test suite.
 */
int cleanup_dns_manager_test_suite(void)
{
    fprintf(stdout, "\nCompleting DNS Manager Tests.");
    return 0;
}

/** 
 * Test adding answers to the message, and check that the returned message size
 * matches the expected value.
 */
void test_add_answers(void)
{
    ssize_t message_size = sizeof(test_message);
    char default_address_response[100] = "6.6.6.6";
    CU_ASSERT_EQUAL(28, add_answers(test_message + DNS_HEADER_SIZE, get_dns_qdcount(test_message), message_size, default_address_response));
}

/** 
 * Test setting the DNS flags to the default by changing the value to 
 * the default and confirming it matches the expected value.
 * This test directly leverages the get function, so this test should
 * follow the get test suite.
 */
void test_set_default_dns_flags(void)
{
    uint16_t expected_default_flags = 33152;
    set_default_dns_flags(test_message);
    uint16_t extracted_dns_flags = get_dns_flags(test_message);
    CU_ASSERT_EQUAL(expected_default_flags, extracted_dns_flags);
}

/** 
 * Test getting the name size of a known query by computing the name size of
 * the first (and only) query in a known request and comparing it to the known value.
 * 
 * Note that this only tests getting a name size with a single question, an
 * extension of this test could validate this function behaves as expected
 * in cases with multiple queries. That being said, the usual number of queries
 * is one (1) as noted in RFC 1035 4.1.2.
 */
void test_get_name_size(void)
{
    uint8_t expected_name_size = 12;
    uint8_t computed_name_size = get_name_size(test_message + DNS_HEADER_SIZE);
    CU_ASSERT_EQUAL(expected_name_size, computed_name_size);
}

/** 
 * Test getting the DNS ID by comparing it to the
 * known value of the test message. 
 */
void test_get_dns_id(void)
{
    uint16_t expected_dns_id = 4146;
    uint16_t extracted_dns_id = get_dns_id(test_message);
    CU_ASSERT_EQUAL(expected_dns_id, extracted_dns_id);
}

/** 
 * Test setting the DNS ID by changing the value,
 * confirming it matches the expected value, changing it back to the original
 * value, and confirming that the value matches the original.
 * This test directly leverages the get function, so this test should
 * follow the get test suite.
 */
void test_set_dns_id(void)
{
    uint16_t new_expected_dns_id = 4147;
    set_dns_id(test_message, new_expected_dns_id);
    uint16_t new_extracted_dns_id = get_dns_id(test_message);
    CU_ASSERT_EQUAL(new_expected_dns_id, new_extracted_dns_id);

    // Reset back to the original value.
    uint16_t expected_dns_id = 4146;
    set_dns_id(test_message, expected_dns_id);
    uint16_t extracted_dns_id = get_dns_id(test_message);
    CU_ASSERT_EQUAL(expected_dns_id, extracted_dns_id);
}

/** 
 * Test getting the DNS flags by comparing it to the
 * known value of the test message. 
 */
void test_get_dns_flags(void)
{
    uint16_t expected_dns_flags = 0x0100;
    uint16_t extracted_dns_flags = get_dns_flags(test_message);
    CU_ASSERT_EQUAL(expected_dns_flags, extracted_dns_flags);
}

/** 
 * Test setting the DNS flags by changing the value,
 * confirming it matches the expected value, changing it back to the original
 * value, and confirming that the value matches the original.
 * This test directly leverages the get function, so this test should
 * follow the get test suite.
 */
void test_set_dns_flags(void)
{
    uint16_t new_expected_dns_flags = 0x0120;
    set_dns_flags(test_message, new_expected_dns_flags);
    uint16_t new_extracted_dns_flags = get_dns_flags(test_message);
    CU_ASSERT_EQUAL(new_expected_dns_flags, new_extracted_dns_flags);

    // Reset back to the original value.
    uint16_t expected_dns_flags = 0x0100;
    set_dns_flags(test_message, expected_dns_flags);
    uint16_t extracted_dns_flags = get_dns_flags(test_message);
    CU_ASSERT_EQUAL(expected_dns_flags, extracted_dns_flags);
}

/** 
 * Test getting the DNS question count by comparing it to the
 * known value of the test message. 
 */
void test_get_dns_qdcount(void)
{
    uint16_t expected_dns_qdcount = 1;
    uint16_t extracted_dns_qdcount = get_dns_qdcount(test_message);
    CU_ASSERT_EQUAL(expected_dns_qdcount, extracted_dns_qdcount);
}

/** 
 * Test setting the DNS questions count by changing the value,
 * confirming it matches the expected value, changing it back to the original
 * value, and confirming that the value matches the original.
 * This test directly leverages the get function, so this test should
 * follow the get test suite.
 */
void test_set_dns_qdcount(void)
{
    uint16_t new_expected_dns_qdcount = 2;
    set_dns_qdcount(test_message, new_expected_dns_qdcount);
    uint16_t new_extracted_dns_qdcount = get_dns_qdcount(test_message);
    CU_ASSERT_EQUAL(new_expected_dns_qdcount, new_extracted_dns_qdcount);

    // Reset back to the original value.
    uint16_t expected_dns_qdcount = 1;
    set_dns_qdcount(test_message, expected_dns_qdcount);
    uint16_t extracted_dns_qdcount = get_dns_qdcount(test_message);
    CU_ASSERT_EQUAL(expected_dns_qdcount, extracted_dns_qdcount);
}

/** 
 * Test getting the DNS answer count by comparing it to the
 * known value of the test message.
 */
void test_get_dns_ancount(void)
{
    uint16_t expected_dns_ancount = 0;
    uint16_t extracted_dns_ancount = get_dns_ancount(test_message);
    CU_ASSERT_EQUAL(expected_dns_ancount, extracted_dns_ancount);
}

/** 
 * Test setting the DNS answer count by changing the value,
 * confirming it matches the expected value, changing it back to the original
 * value, and confirming that the value matches the original.
 * This test directly leverages the get function, so this test should
 * follow the get test suite.
 */
void test_set_dns_ancount(void)
{
    uint16_t new_expected_dns_ancount = 1;
    set_dns_ancount(test_message, new_expected_dns_ancount);
    uint16_t new_extracted_dns_ancount = get_dns_ancount(test_message);
    CU_ASSERT_EQUAL(new_expected_dns_ancount, new_extracted_dns_ancount);

    // Reset back to the original value.
    uint16_t expected_dns_ancount = 0;
    set_dns_ancount(test_message, expected_dns_ancount);
    uint16_t extracted_dns_ancount = get_dns_ancount(test_message);
    CU_ASSERT_EQUAL(expected_dns_ancount, extracted_dns_ancount);
}

/** 
 * Test getting the DNS name server records count by comparing it to the
 * known value of the test message.
 */
void test_get_dns_nscount(void)
{
    uint16_t expected_dns_nscount = 0;
    uint16_t extracted_dns_nscount = get_dns_nscount(test_message);
    CU_ASSERT_EQUAL(expected_dns_nscount, extracted_dns_nscount);
}

/** 
 * Test setting the DNS name server records count by changing the value,
 * confirming it matches the expected value, changing it back to the original
 * value, and confirming that the value matches the original.
 * This test directly leverages the get function, so this test should
 * follow the get test suite.
 */
void test_set_dns_nscount(void)
{
    uint16_t new_expected_dns_nscount = 1;
    set_dns_nscount(test_message, new_expected_dns_nscount);
    uint16_t new_extracted_dns_nscount = get_dns_nscount(test_message);
    CU_ASSERT_EQUAL(new_expected_dns_nscount, new_extracted_dns_nscount);

    // Reset back to the original value.
    uint16_t expected_dns_nscount = 0;
    set_dns_nscount(test_message, expected_dns_nscount);
    uint16_t extracted_dns_nscount = get_dns_nscount(test_message);
    CU_ASSERT_EQUAL(expected_dns_nscount, extracted_dns_nscount);
}

/** 
 * Test getting the DNS additional records count by comparing it to the
 * known value of the test 
 */
void test_get_dns_arcount(void)
{
    uint16_t expected_dns_arcount = 0;
    uint16_t extracted_dns_arcount = get_dns_arcount(test_message);
    CU_ASSERT_EQUAL(expected_dns_arcount, extracted_dns_arcount);
}

/** 
 * Test setting the DNS additional records count by changing the value,
 * confirming it matches the expected value, changing it back to the original
 * value, and confirming that the value matches the original.
 * This test directly leverages the get function, so this test should
 * follow the get test suite.
 */
void test_set_dns_arcount(void)
{
    uint16_t new_expected_dns_arcount = 0;
    set_dns_arcount(test_message, new_expected_dns_arcount);
    uint16_t new_extracted_dns_arcount = get_dns_nscount(test_message);
    CU_ASSERT_EQUAL(new_expected_dns_arcount, new_extracted_dns_arcount);

    // Reset back to the original value.
    uint16_t expected_dns_arcount = 0;
    set_dns_arcount(test_message, expected_dns_arcount);
    uint16_t extracted_dns_arcount = get_dns_arcount(test_message);
    CU_ASSERT_EQUAL(expected_dns_arcount, extracted_dns_arcount);
}

/**
 * Main function for setting up and running all of the tests.  
 * Returns CUE_SUCCESS if tests execute successfully, and returns
 * a CUNit error code if tests fail.
*/
int main()
{
    // Initialize the test registry and add the suite to the registry.

    CU_pSuite getSuite = NULL;
    CU_pSuite setSuite = NULL;
    CU_pSuite processSuite = NULL;
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    // Initialize all three test suites.
    getSuite = CU_add_suite("DNS Manager Get Tests", initialize_dns_manager_test_suite, cleanup_dns_manager_test_suite);
    setSuite = CU_add_suite("DNS Manager Set Tests", initialize_dns_manager_test_suite, cleanup_dns_manager_test_suite);
    processSuite = CU_add_suite("DNS Processing Set Tests", initialize_dns_manager_test_suite, cleanup_dns_manager_test_suite);

    if (NULL == getSuite || NULL == setSuite || NULL == processSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Ensure that we can get values from the test buffer.
    if ((NULL == CU_add_test(getSuite, "Test of get_dns_id function", test_get_dns_id)) ||
        (NULL == CU_add_test(getSuite, "Test of get_dns_flags function", test_get_dns_flags)) ||
        (NULL == CU_add_test(getSuite, "Test of get_dns_qdcount function", test_get_dns_qdcount)) ||
        (NULL == CU_add_test(getSuite, "Test of get_dns_ancount function", test_get_dns_ancount)) ||
        (NULL == CU_add_test(getSuite, "Test of get_dns_nscount function", test_get_dns_nscount)) ||
        (NULL == CU_add_test(getSuite, "Test of get_dns_arcount function", test_get_dns_arcount)) ||
        (NULL == CU_add_test(getSuite, "Test of get_name_size function", test_get_name_size)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Change the values and ensure they match what we expect, and then reset
    // them to their original values and ensure they still match.
    if ((NULL == CU_add_test(setSuite, "Test of set_dns_id function", test_set_dns_id)) ||
        (NULL == CU_add_test(setSuite, "Test of set_dns_flags function", test_set_dns_flags)) ||
        (NULL == CU_add_test(setSuite, "Test of set_dns_qdcount function", test_set_dns_qdcount)) ||
        (NULL == CU_add_test(setSuite, "Test of set_dns_ancount function", test_set_dns_ancount)) ||
        (NULL == CU_add_test(setSuite, "Test of set_dns_nscount function", test_set_dns_nscount)) ||
        (NULL == CU_add_test(setSuite, "Test of set_dns_arcount function", test_set_dns_arcount)) ||
        (NULL == CU_add_test(setSuite, "Test of set_default_dns_flags function", test_set_default_dns_flags)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Ensure we can get the expected value after processing. This would be a
    // good place for additional testing methods.
    if ((NULL == CU_add_test(processSuite, "Test of add_answers function", test_add_answers)))
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
