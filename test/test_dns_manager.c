/**
 * TODO Block comment
 * http://cunit.sourceforge.net/example.html
 */

#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "../src/dns_defns.h"
#include "../src/dns_manager.h"

// General-purpose buffer used by tests. Created by calling using Wireshark to
// collect the packet bytes after calling "$ dig -p 123 @localhost google.com"

uint8_t test_message[] = {
  0x53, 0x70, 0x6f, 0x74, 0x55, 0x64, 0x70, 0x30,
  0x4b, 0xbb, 0x7b, 0x30, 0xf5, 0xc8, 0xd9, 0xa9,
  0x00, 0x01, 0x00, 0x04, 0x48, 0x95, 0xc2, 0x03,
  0xdb, 0xfb, 0x62, 0xd0, 0xda, 0x9d, 0x56, 0x01,
  0x37, 0x1d, 0x1e, 0x63, 0xc0, 0x85, 0x2e, 0xf7,
  0xcd, 0x8d, 0x26, 0x8b
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

void test_set_not_implemented_flags(void) {

}

void test_set_format_error_flags(void) {

}

void test_set_default_dns_flags(void) {

}

void test_get_name_size(void) {

}

void test_get_dns_id(void) {
        fprintf(stdout, "Initializing main method");

    uint16_t dns_id = get_dns_id(test_message);
    fprintf(stderr, "The value of the ID Is %u", dns_id);
}

void test_set_dns_id(void) {

}

void test_get_dns_flags(void) {

}

void test_set_dns_flags(void) {

}

void test_get_dns_qdcount(void) {

}

void test_set_dns_qdcount(void) {

}

void test_get_dns_ancount(void) {

}

void test_set_dns_ancount(void) {

}

void test_get_dns_nscount(void) {

}

void test_set_dns_nscount(void) {

}

void test_get_dns_arcount(void) {

}


void test_set_dns_arcount(void) {
}

/**
 * Main function for setting up and running all of the tests.  
 * Returns CUE_SUCCESS if tests execute successfully, and returns
 * a CUNit error code if tests fail.
*/
int main()
{
    fprintf(stdout, "Initializing main method");
    // Initialize the test registry and add the suite to the registry.
    CU_pSuite pSuite = NULL;
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    pSuite = CU_add_suite("Suite_1", initialize_dns_manager_test_suite, cleanup_dns_manager_test_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add the tests to the suite. TODO Add tests here.
    // Note that order matters here. Get tests should run before set tests, and
    // and the higher-level tests (name size, add answers, parse message) should run last.
    if ((NULL == CU_add_test(pSuite, "Test of DNS header get functions", test_get_dns_id)))
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