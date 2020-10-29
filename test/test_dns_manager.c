/**
 * TODO Block comment
 * http://cunit.sourceforge.net/example.html
 */

#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "../src/dns_defns.h"
#include "../src/dns_manager.h"

bool debug = false;
#ifdef TEST_DEBUG
    debug = true;
#endif

// General-purpose buffer used by tests. Used Wireshark sample DNS capture
// https://wiki.wireshark.org/SampleCaptures and generated integer values
// for validation with https://www.scadacore.com/tools/programming-calculators/online-hex-converter/.

uint8_t test_message[] = {
  0x10, 0x32, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x06, 0x67, 0x6f, 0x6f,
  0x67, 0x6c, 0x65, 0x03, 0x63, 0x6f, 0x6d, 0x00,
  0x00, 0x10, 0x00, 0x01
};

/**
 * TODO Comment
 */
int initialize_dns_manager_test_suite(void)
{
   fprintf(stdout, "Starting DNS Manager Tests.");
   return 0;
}

/**
 * 
 */
int cleanup_dns_manager_test_suite(void)
{
   fprintf(stdout, "Completing DNS Manager Tests.");
   return 0;
}


void test_add_answers(void) {

}

void test_parse_message(void) {

}

// TODO maybe convert flag values to hex/ debug why that doesn't work outright
void test_set_not_implemented_flags(void) {
    uint16_t expected_not_implemented_flags = 32769;
    set_format_error_flags(test_message);
    uint16_t extracted_dns_flags = get_dns_flags(test_message);
    CU_ASSERT_EQUAL(expected_not_implemented_flags, extracted_dns_flags);

}

void test_set_format_error_flags(void) {
    uint16_t expected_format_error_flags = 32772;
    set_not_implemented_flags(test_message);
    uint16_t extracted_dns_flags = get_dns_flags(test_message);
    CU_ASSERT_EQUAL(expected_format_error_flags, extracted_dns_flags);

}

void test_set_default_dns_flags(void) {
    uint16_t expected_default_flags = 33792;
    set_default_dns_flags(test_message);
    uint16_t extracted_dns_flags = get_dns_flags(test_message);
    CU_ASSERT_EQUAL(expected_default_flags, extracted_dns_flags);
}

void test_get_name_size(void) {

}

void test_get_dns_id(void) {
    uint16_t expected_dns_id = 4146;
    uint16_t extracted_dns_id = get_dns_id(test_message);
    CU_ASSERT_EQUAL(expected_dns_id, extracted_dns_id);
}

void test_set_dns_id(void) {
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

void test_get_dns_flags(void) {
    uint16_t expected_dns_flags = 0x0100;
    uint16_t extracted_dns_flags = get_dns_flags(test_message);
    CU_ASSERT_EQUAL(expected_dns_flags, extracted_dns_flags);

}

void test_set_dns_flags(void) {
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

void test_get_dns_qdcount(void) {
    uint16_t expected_dns_qdcount = 1;
    uint16_t extracted_dns_qdcount = get_dns_qdcount(test_message);
    CU_ASSERT_EQUAL(expected_dns_qdcount, extracted_dns_qdcount);
}

void test_set_dns_qdcount(void) {
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

void test_get_dns_ancount(void) {
    uint16_t expected_dns_ancount = 0;
    uint16_t extracted_dns_ancount = get_dns_ancount(test_message);
    CU_ASSERT_EQUAL(expected_dns_ancount, extracted_dns_ancount);
}

void test_set_dns_ancount(void) {
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

void test_get_dns_nscount(void) {
    uint16_t expected_dns_nscount = 0;
    uint16_t extracted_dns_nscount = get_dns_nscount(test_message);
    CU_ASSERT_EQUAL(expected_dns_nscount, extracted_dns_nscount);
}

void test_set_dns_nscount(void) {
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

void test_get_dns_arcount(void) {
    uint16_t expected_dns_arcount = 0;
    uint16_t extracted_dns_arcount = get_dns_arcount(test_message);
    CU_ASSERT_EQUAL(expected_dns_arcount, extracted_dns_arcount);
}

void test_set_dns_arcount(void) {
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
    fprintf(stdout, "Initialifdsdfzing main method");
    // Initialize the test registry and add the suite to the registry.
    CU_pSuite getSuite = NULL;
    CU_pSuite setSuite = NULL;
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    // TODO Give the init values 
    getSuite = CU_add_suite("DNS Manager Get Tests", initialize_dns_manager_test_suite, cleanup_dns_manager_test_suite);
    setSuite = CU_add_suite("DNS Manager Set Tests", initialize_dns_manager_test_suite, cleanup_dns_manager_test_suite);
    
    if (NULL == getSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Ensure that we can get values from the test buffer.
    if ((NULL == CU_add_test(getSuite, "Test of get_dns_id function", test_get_dns_id)) ||
        (NULL == CU_add_test(getSuite, "Test of get_dns_flags function", test_get_dns_flags)) ||
        (NULL == CU_add_test(getSuite, "Test of get_dns_qdcount function", test_get_dns_qdcount)) ||
        (NULL == CU_add_test(getSuite, "Test of get_dns_ancount function", test_get_dns_ancount)) ||
        (NULL == CU_add_test(getSuite, "Test of get_dns_nscount function", test_get_dns_nscount)) ||
        (NULL == CU_add_test(getSuite, "Test of get_dns_arcount function", test_get_dns_arcount))) {
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
        (NULL == CU_add_test(setSuite, "Test of set_not_implemented_flags function", test_set_not_implemented_flags)) ||
        (NULL == CU_add_test(setSuite, "Test of set_format_error_flags function", test_set_format_error_flags)) || 
        (NULL == CU_add_test(setSuite, "Test of set_default_dns_flags function", test_set_default_dns_flags)))       
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
