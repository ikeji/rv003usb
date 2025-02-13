// (lazy-make-configulation
//   (task "test" ("generate_report.h" "generate_report_test.c")
//     "gcc  -W -Wall generate_report_test.c -lcunit -o test"
//     "./test"))

#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/Console.h>
#include <CUnit/TestDB.h>
#include "generate_report.h"

void generate_report_test_zero_key(void){
  for (int x=0;x<12;x++) {
    for (int y=0;y<4;y++) {
      matrix[y][x] = false;
    }
  }

  generate_report();

  CU_ASSERT_EQUAL(key_report[0],0);
  CU_ASSERT_EQUAL(key_report[1],0);
  CU_ASSERT_EQUAL(key_report[2],0);
  CU_ASSERT_EQUAL(key_report[3],0);
  CU_ASSERT_EQUAL(key_report[4],0);
  CU_ASSERT_EQUAL(key_report[5],0);
  CU_ASSERT_EQUAL(key_report[6],0);
  CU_ASSERT_EQUAL(key_report[7],0);
}

void generate_report_test_one_key(void){
  for (int x=0;x<12;x++) {
    for (int y=0;y<4;y++) {
      matrix[y][x] = false;
    }
  }
  matrix[1][1] = true;

  generate_report();

  CU_ASSERT_EQUAL(key_report[0],0);
  CU_ASSERT_EQUAL(key_report[1],0);
  CU_ASSERT_EQUAL(key_report[2],0x04);
  CU_ASSERT_EQUAL(key_report[3],0);
  CU_ASSERT_EQUAL(key_report[4],0);
  CU_ASSERT_EQUAL(key_report[5],0);
  CU_ASSERT_EQUAL(key_report[6],0);
  CU_ASSERT_EQUAL(key_report[7],0);
}

int main(void) {
    CU_pSuite suite;
    CU_initialize_registry();

    suite = CU_add_suite("generate_report_test", NULL, NULL);
    CU_add_test(suite, "generate_report_test_zero_key", generate_report_test_zero_key);
    CU_add_test(suite, "generate_report_test_one_key", generate_report_test_one_key);

    // CU_console_run_tests();
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
