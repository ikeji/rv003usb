// (lazy-make-configulation
//   (task "test" ("generate_report.h" "generate_report_test.c")
//     "gcc  -W -Wall generate_report_test.c -lcunit -o test"
//     "./test"))

#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/Console.h>
#include <CUnit/TestDB.h>
#include "generate_report.h"

void printMatrix(void) {
  for (int y=0;y<4;y++) {
    for (int x=0;x<12;x++) {
      printf("%d",matrix[y][x]?1:0);
    }
    printf("\n");
  }
}

void printReport(void) {
  for (int i=0;i<8;i++) {
    printf(" %02x", key_report[i]);
  }
  printf("\n");
}

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

void generate_report_test_two_keys(void){
  for (int x=0;x<12;x++) {
    for (int y=0;y<4;y++) {
      matrix[y][x] = false;
    }
  }
  matrix[1][1] = true;
  matrix[1][2] = true;

  generate_report();

  CU_ASSERT_EQUAL(key_report[0],0);
  CU_ASSERT_EQUAL(key_report[1],0);
  CU_ASSERT_EQUAL(key_report[2],K_A);
  CU_ASSERT_EQUAL(key_report[3],K_S);
  CU_ASSERT_EQUAL(key_report[4],0);
  CU_ASSERT_EQUAL(key_report[5],0);
  CU_ASSERT_EQUAL(key_report[6],0);
  CU_ASSERT_EQUAL(key_report[7],0);
}

void generate_report_test_shift_a(void){
  for (int x=0;x<12;x++) {
    for (int y=0;y<4;y++) {
      matrix[y][x] = false;
    }
  }
  matrix[1][1] = true;
  matrix[2][0] = true;

  generate_report();

  CU_ASSERT_EQUAL(key_report[0],0b00000010);
  CU_ASSERT_EQUAL(key_report[1],0);
  CU_ASSERT_EQUAL(key_report[2],K_A);
  CU_ASSERT_EQUAL(key_report[3],0);
  CU_ASSERT_EQUAL(key_report[4],0);
  CU_ASSERT_EQUAL(key_report[5],0);
  CU_ASSERT_EQUAL(key_report[6],0);
  CU_ASSERT_EQUAL(key_report[7],0);
}

void generate_report_test_ctrl_a(void){
  for (int x=0;x<12;x++) {
    for (int y=0;y<4;y++) {
      matrix[y][x] = false;
    }
  }
  matrix[1][1] = true;
  matrix[1][0] = true;

  generate_report();

  CU_ASSERT_EQUAL(key_report[0],0b00000001);
  CU_ASSERT_EQUAL(key_report[1],0);
  CU_ASSERT_EQUAL(key_report[2],K_A);
  CU_ASSERT_EQUAL(key_report[3],0);
  CU_ASSERT_EQUAL(key_report[4],0);
  CU_ASSERT_EQUAL(key_report[5],0);
  CU_ASSERT_EQUAL(key_report[6],0);
  CU_ASSERT_EQUAL(key_report[7],0);
}

void generate_report_test_fn_1(void){
  for (int x=0;x<12;x++) {
    for (int y=0;y<4;y++) {
      matrix[y][x] = false;
    }
  }
  matrix[0][1] = true;
  matrix[3][0] = true;

  generate_report();

  CU_ASSERT_EQUAL(key_report[0],0b00000000);
  CU_ASSERT_EQUAL(key_report[1],0);
  CU_ASSERT_EQUAL(key_report[2],F_1);
  CU_ASSERT_EQUAL(key_report[3],0);
  CU_ASSERT_EQUAL(key_report[4],0);
  CU_ASSERT_EQUAL(key_report[5],0);
  CU_ASSERT_EQUAL(key_report[6],0);
  CU_ASSERT_EQUAL(key_report[7],0);
}

void generate_report_test_num_1(void){
  for (int x=0;x<12;x++) {
    for (int y=0;y<4;y++) {
      matrix[y][x] = false;
    }
  }
  matrix[0][1] = true; // 1
  matrix[3][7] = true; // num

  generate_report();

  CU_ASSERT_EQUAL(key_report[0],0b00000000);
  CU_ASSERT_EQUAL(key_report[1],0);
  CU_ASSERT_EQUAL(key_report[2],K_1);
  CU_ASSERT_EQUAL(key_report[3],0);
  CU_ASSERT_EQUAL(key_report[4],0);
  CU_ASSERT_EQUAL(key_report[5],0);
  CU_ASSERT_EQUAL(key_report[6],0);
  CU_ASSERT_EQUAL(key_report[7],0);
}

void generate_report_test_sym_1(void){
  for (int x=0;x<12;x++) {
    for (int y=0;y<4;y++) {
      matrix[y][x] = false;
    }
  }
  matrix[0][1] = true;
  matrix[3][4] = true;

  generate_report();

  CU_ASSERT_EQUAL(key_report[0],0b00000010);
  CU_ASSERT_EQUAL(key_report[1],0);
  CU_ASSERT_EQUAL(key_report[2],K_1);
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
    CU_add_test(suite,
        "generate_report_test_zero_key",
        generate_report_test_zero_key);
    CU_add_test(suite,
        "generate_report_test_one_key",
        generate_report_test_one_key);
    CU_add_test(suite,
        "generate_report_test_two_keys",
        generate_report_test_two_keys);
    CU_add_test(suite,
        "generate_report_test_shift_a",
        generate_report_test_shift_a);
    CU_add_test(suite,
        "generate_report_test_ctrl_a",
        generate_report_test_ctrl_a);
    CU_add_test(suite,
        "generate_report_test_fn_1",
        generate_report_test_fn_1);
    CU_add_test(suite,
        "generate_report_test_num_1",
        generate_report_test_num_1);
    CU_add_test(suite,
        "generate_report_test_sym_1",
        generate_report_test_sym_1);

    // CU_console_run_tests();
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
