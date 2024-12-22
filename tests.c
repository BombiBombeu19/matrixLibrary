#include <check.h>
#include <stdlib.h>

#include "s21_matrix.h"

START_TEST(s21_create_matrix1) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix;

  ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), OK);
  ck_assert_int_eq(matrix.rows, rows);
  ck_assert_int_eq(matrix.columns, columns);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_create_matrix2) {
  int rows = 1919;
  int columns = 19;
  matrix_t matrix;

  ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), OK);
  ck_assert_int_eq(matrix.rows, rows);
  ck_assert_int_eq(matrix.columns, columns);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_create_matrix3) {
  int rows = 1;
  int columns = 1;
  matrix_t matrix;

  ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), OK);
  ck_assert_int_eq(matrix.rows, rows);
  ck_assert_int_eq(matrix.columns, columns);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_create_matrix4) {
  int rows = rand() % 100 + 1;
  int columns = 0;
  matrix_t matrix;

  ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), MATRIX_ERROR);
}
END_TEST

START_TEST(s21_create_matrix5) {
  int rows = 0;
  int columns = rand() % 100 + 1;
  matrix_t matrix;

  ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), MATRIX_ERROR);
}
END_TEST

START_TEST(s21_create_matrix6) {
  int rows = -5;
  int columns = -5;
  matrix_t matrix;

  ck_assert_int_eq(s21_create_matrix(rows, columns, &matrix), MATRIX_ERROR);
}
END_TEST

START_TEST(s21_eq_matrix1) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(rows, columns, &matrix1);
  s21_create_matrix(rows, columns, &matrix2);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix1.matrix[i][j] = 0;
      matrix2.matrix[i][j] = 0;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(s21_eq_matrix2) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(rows, columns, &matrix1);
  s21_create_matrix(rows, columns, &matrix2);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double rand_num = (double)rand() / 1919 + 0.1;
      matrix1.matrix[i][j] = rand_num;
      matrix2.matrix[i][j] = rand_num;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(s21_eq_matrix3) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(rows, columns, &matrix1);
  s21_create_matrix(rows, columns, &matrix2);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double rand_num = (double)rand() / 1919 + 0.1;
      matrix1.matrix[i][j] = rand_num;
      matrix2.matrix[i][j] = rand_num;
    }
  }
  matrix1.matrix[0][0] = 0;

  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(s21_eq_matrix4) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(rows, columns, &matrix1);
  s21_create_matrix(rows, columns, &matrix2);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double rand_num = (double)rand() / 1919 + 0.1;
      matrix1.matrix[i][j] = rand_num;
      matrix2.matrix[i][j] = -rand_num;
    }
  }

  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(s21_eq_matrix5) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix1;
  matrix_t matrix2;
  s21_create_matrix(rows, columns, &matrix1);
  s21_create_matrix(rows, columns, &matrix2);

  matrix1.matrix[0][0] = 1919191919;
  matrix2.matrix[0][0] = 1919191919;
  matrix1.matrix[1][1] = 0.11111111;
  matrix2.matrix[1][1] = 0.11111110;

  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(s21_sum_matrix1) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix1;
  matrix_t matrix2;
  matrix_t check;
  matrix_t result;
  s21_create_matrix(rows, columns, &matrix1);
  s21_create_matrix(rows, columns, &matrix2);
  s21_create_matrix(rows, columns, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix1.matrix[i][j] = (double)rand() / 1919 + 0.1;
      matrix2.matrix[i][j] = (double)rand() / 1919 + 0.1;
      check.matrix[i][j] = matrix1.matrix[i][j] + matrix2.matrix[i][j];
    }
  }

  ck_assert_int_eq(s21_sum_matrix(&matrix1, &matrix2, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sum_matrix2) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix1;
  matrix_t matrix2;
  matrix_t check;
  matrix_t result;
  s21_create_matrix(rows, columns, &matrix1);
  s21_create_matrix(rows, columns, &matrix2);
  s21_create_matrix(rows, columns, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix1.matrix[i][j] = 0;
      matrix2.matrix[i][j] = 0;
      check.matrix[i][j] = matrix1.matrix[i][j] + matrix2.matrix[i][j];
    }
  }

  ck_assert_int_eq(s21_sum_matrix(&matrix1, &matrix2, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sum_matrix3) {
  matrix_t matrix1;
  matrix_t matrix2;
  matrix_t result;

  s21_create_matrix(3, 1, &matrix1);
  s21_create_matrix(3, 2, &matrix2);

  ck_assert_int_eq(s21_sum_matrix(&matrix1, &matrix2, &result),
                   CALCULATION_ERROR);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(s21_sum_matrix4) {
  matrix_t matrix1;
  matrix_t matrix2;
  matrix_t result;

  s21_create_matrix(-5, 1, &matrix1);
  s21_create_matrix(3, 0, &matrix2);

  ck_assert_int_eq(s21_sum_matrix(&matrix1, &matrix2, &result), MATRIX_ERROR);
}
END_TEST

START_TEST(s21_sub_matrix1) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix1;
  matrix_t matrix2;
  matrix_t check;
  matrix_t result;

  s21_create_matrix(rows, columns, &matrix1);
  s21_create_matrix(rows, columns, &matrix2);
  s21_create_matrix(rows, columns, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix1.matrix[i][j] = (double)rand() / 1919 + 0.1;
      matrix2.matrix[i][j] = (double)rand() / 1919 + 0.1;
      check.matrix[i][j] = matrix1.matrix[i][j] - matrix2.matrix[i][j];
    }
  }

  ck_assert_int_eq(s21_sub_matrix(&matrix1, &matrix2, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix2) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix1;
  matrix_t matrix2;
  matrix_t check;
  matrix_t result;

  s21_create_matrix(rows, columns, &matrix1);
  s21_create_matrix(rows, columns, &matrix2);
  s21_create_matrix(rows, columns, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix1.matrix[i][j] = 0;
      matrix2.matrix[i][j] = 0;
      check.matrix[i][j] = matrix1.matrix[i][j] - matrix2.matrix[i][j];
    }
  }

  ck_assert_int_eq(s21_sub_matrix(&matrix1, &matrix2, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix3) {
  matrix_t matrix1;
  matrix_t matrix2;
  matrix_t result;

  s21_create_matrix(1, 2, &matrix1);
  s21_create_matrix(3, 4, &matrix2);

  ck_assert_int_eq(s21_sub_matrix(&matrix1, &matrix2, &result),
                   CALCULATION_ERROR);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(s21_sub_matrix4) {
  matrix_t matrix1;
  matrix_t matrix2;
  matrix_t result;

  s21_create_matrix(-1, 9, &matrix1);
  s21_create_matrix(1, -9, &matrix2);

  ck_assert_int_eq(s21_sub_matrix(&matrix1, &matrix2, &result), MATRIX_ERROR);
}
END_TEST

START_TEST(s21_mult_number1) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix;
  matrix_t check;
  matrix_t result;
  s21_create_matrix(rows, columns, &matrix);
  s21_create_matrix(rows, columns, &check);

  double number = (double)rand() / 1919 + 0.1;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix.matrix[i][j] = (double)rand() / 1919 + 0.1;
      check.matrix[i][j] = matrix.matrix[i][j] * number;
    }
  }

  ck_assert_int_eq(s21_mult_number(&matrix, number, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_number2) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix;
  matrix_t check;
  matrix_t result;
  s21_create_matrix(rows, columns, &matrix);
  s21_create_matrix(rows, columns, &check);

  double number = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix.matrix[i][j] = (double)rand() / 1919 + 0.1;
      check.matrix[i][j] = matrix.matrix[i][j] * number;
    }
  }

  ck_assert_int_eq(s21_mult_number(&matrix, number, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_number3) {
  double number = 19;
  matrix_t matrix;
  matrix_t result;

  s21_create_matrix(1, -9, &matrix);

  ck_assert_int_eq(s21_mult_number(&matrix, number, &result), MATRIX_ERROR);
}
END_TEST

START_TEST(s21_mult_matrix1) {
  int rows = rand() % 100 + 1;
  int rows_columns = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix1;
  matrix_t matrix2;
  matrix_t check;
  matrix_t result;

  s21_create_matrix(rows, rows_columns, &matrix1);
  s21_create_matrix(rows_columns, columns, &matrix2);
  s21_create_matrix(rows, columns, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < rows_columns; j++)
      matrix1.matrix[i][j] = (double)rand() / 1919 + 0.1;
  }

  for (int i = 0; i < rows_columns; i++) {
    for (int j = 0; j < columns; j++)
      matrix2.matrix[i][j] = (double)rand() / 1919 + 0.1;
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      check.matrix[i][j] = 0;
      for (int k = 0; k < rows_columns; k++) {
        check.matrix[i][j] += matrix1.matrix[i][k] * matrix2.matrix[k][j];
      }
    }
  }

  ck_assert_int_eq(s21_mult_matrix(&matrix1, &matrix2, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_matrix2) {
  matrix_t matrix1;
  matrix_t matrix2;
  matrix_t result;

  s21_create_matrix(-1, 9, &matrix1);
  s21_create_matrix(9, -1, &matrix2);

  ck_assert_int_eq(s21_mult_matrix(&matrix1, &matrix2, &result), MATRIX_ERROR);
}
END_TEST

START_TEST(s21_mult_matrix3) {
  matrix_t matrix1;
  matrix_t matrix2;
  matrix_t result;

  s21_create_matrix(1, 9, &matrix1);
  s21_create_matrix(1, 9, &matrix2);

  ck_assert_int_eq(s21_mult_matrix(&matrix1, &matrix2, &result),
                   CALCULATION_ERROR);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(s21_transpose1) {
  int num = rand() % 100 + 1;
  matrix_t matrix;
  matrix_t check;
  matrix_t result;

  s21_create_matrix(num, num, &matrix);
  s21_create_matrix(num, num, &check);

  for (int i = 0; i < num; i++) {
    for (int j = 0; j < num; j++) {
      matrix.matrix[i][j] = (double)rand() / 1919 + 0.1;
      check.matrix[j][i] = matrix.matrix[i][j];
    }
  }

  ck_assert_int_eq(s21_transpose(&matrix, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose2) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t matrix;
  matrix_t check;
  matrix_t result;

  s21_create_matrix(rows, columns, &matrix);
  s21_create_matrix(columns, rows, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix.matrix[i][j] = (double)rand() / 1919 + 0.1;
      check.matrix[j][i] = matrix.matrix[i][j];
    }
  }

  ck_assert_int_eq(s21_transpose(&matrix, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose3) {
  int num = 3;
  matrix_t matrix;
  matrix_t check;
  matrix_t result;

  s21_create_matrix(num, num, &matrix);
  s21_create_matrix(num, num, &check);

  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 5;
  matrix.matrix[0][2] = 7;
  matrix.matrix[1][0] = 1;
  matrix.matrix[1][1] = 4.3;
  matrix.matrix[1][2] = 4;
  matrix.matrix[2][0] = 5;
  matrix.matrix[2][1] = 1;
  matrix.matrix[2][2] = 6;

  check.matrix[0][0] = 1;
  check.matrix[0][1] = 1;
  check.matrix[0][2] = 5;
  check.matrix[1][0] = 5;
  check.matrix[1][1] = 4.3;
  check.matrix[1][2] = 1;
  check.matrix[2][0] = 7;
  check.matrix[2][1] = 4;
  check.matrix[2][2] = 6;

  ck_assert_int_eq(s21_transpose(&matrix, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose4) {
  matrix_t matrix;
  matrix_t result;

  s21_create_matrix(-1, 9, &matrix);

  ck_assert_int_eq(s21_transpose(&matrix, &result), MATRIX_ERROR);
}
END_TEST

START_TEST(s21_determinant1) {
  int num = 3;
  matrix_t matrix;
  double check = -51.7;
  double result = 0;

  s21_create_matrix(num, num, &matrix);

  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 5;
  matrix.matrix[0][2] = 7;
  matrix.matrix[1][0] = 1;
  matrix.matrix[1][1] = 4.3;
  matrix.matrix[1][2] = 4;
  matrix.matrix[2][0] = 5;
  matrix.matrix[2][1] = 1;
  matrix.matrix[2][2] = 6;

  ck_assert_int_eq(s21_determinant(&matrix, &result), OK);
  ck_assert_double_eq_tol(result, check, 1e-6);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_determinant2) {
  matrix_t matrix;
  double check = 0;
  double result = 0;

  s21_create_matrix(1, 1, &matrix);

  matrix.matrix[0][0] = (double)rand() / 1919 + 0.1;

  check = matrix.matrix[0][0];

  ck_assert_int_eq(s21_determinant(&matrix, &result), OK);
  ck_assert_double_eq(result, check);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_determinant3) {
  matrix_t matrix;
  double check = 6.908;
  double result = 0;

  s21_create_matrix(2, 2, &matrix);

  matrix.matrix[0][0] = 0.56;
  matrix.matrix[0][1] = -4.5;
  matrix.matrix[1][0] = 1;
  matrix.matrix[1][1] = 4.3;

  ck_assert_int_eq(s21_determinant(&matrix, &result), OK);
  ck_assert_double_eq_tol(result, check, 1e-6);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_determinant4) {
  double result = 0;
  matrix_t matrix;
  s21_create_matrix(0, 4, &matrix);
  ck_assert_int_eq(MATRIX_ERROR, s21_determinant(&matrix, &result));
}
END_TEST

START_TEST(s21_determinant5) {
  matrix_t matrix;
  double result = 0;

  s21_create_matrix(1, 9, &matrix);

  ck_assert_int_eq(s21_determinant(&matrix, &result), CALCULATION_ERROR);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_determinant6) {
  int num = 4;
  matrix_t matrix;
  double check = 123;
  double result = 0;

  s21_create_matrix(num, num, &matrix);

  matrix.matrix[0][0] = 3;
  matrix.matrix[0][1] = 6;
  matrix.matrix[0][2] = 7;
  matrix.matrix[0][3] = 8;
  matrix.matrix[1][0] = -1;
  matrix.matrix[1][1] = 7;
  matrix.matrix[1][2] = 0;
  matrix.matrix[1][3] = 1;
  matrix.matrix[2][0] = 0;
  matrix.matrix[2][1] = 5;
  matrix.matrix[2][2] = 3;
  matrix.matrix[2][3] = 2;
  matrix.matrix[3][0] = 1;
  matrix.matrix[3][1] = -1;
  matrix.matrix[3][2] = 7;
  matrix.matrix[3][3] = 4;

  ck_assert_int_eq(s21_determinant(&matrix, &result), OK);
  ck_assert_double_eq_tol(result, check, 1e-6);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_determinant7) {
  int num = 4;
  matrix_t matrix;
  double check = 128.1795;
  double result = 0;

  s21_create_matrix(num, num, &matrix);

  matrix.matrix[0][0] = -3.576;
  matrix.matrix[0][1] = 67;
  matrix.matrix[1][0] = -1.9665;
  matrix.matrix[1][1] = 1;
  matrix.matrix[2][2] = 1;
  matrix.matrix[3][3] = 1;

  ck_assert_int_eq(s21_determinant(&matrix, &result), OK);
  ck_assert_double_eq_tol(result, check, 1e-6);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_determinant8) {
  int num = 4;
  matrix_t matrix;
  double check = 979.613088;
  double result = 0;

  s21_create_matrix(num, num, &matrix);

  matrix.matrix[0][0] = 3.004;
  matrix.matrix[0][1] = 5.000201;
  matrix.matrix[0][2] = 7.00032;
  matrix.matrix[0][3] = 8;
  matrix.matrix[1][0] = -1;
  matrix.matrix[1][1] = 7;
  matrix.matrix[1][2] = 0;
  matrix.matrix[1][3] = 1;
  matrix.matrix[2][0] = 0;
  matrix.matrix[2][1] = 5;
  matrix.matrix[2][2] = 12;
  matrix.matrix[2][3] = 0;
  matrix.matrix[3][0] = 1;
  matrix.matrix[3][1] = -1;
  matrix.matrix[3][2] = 7.0014;
  matrix.matrix[3][3] = 4;

  ck_assert_int_eq(s21_determinant(&matrix, &result), OK);
  ck_assert_double_eq_tol(result, check, 1e-6);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_inverse_matrix1) {
  int num = 1;
  matrix_t matrix;
  matrix_t check;
  matrix_t result;

  s21_create_matrix(num, num, &matrix);
  s21_create_matrix(num, num, &check);

  matrix.matrix[0][0] = 0.5;
  check.matrix[0][0] = 2;

  ck_assert_int_eq(s21_inverse_matrix(&matrix, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix2) {
  int num = 2;
  matrix_t matrix;
  matrix_t check;
  matrix_t result;

  s21_create_matrix(num, num, &matrix);
  s21_create_matrix(num, num, &check);

  matrix.matrix[0][0] = 2;
  matrix.matrix[0][1] = 3;
  matrix.matrix[1][0] = 1;
  matrix.matrix[1][1] = 4;

  check.matrix[0][0] = 0.8;
  check.matrix[0][1] = -0.6;
  check.matrix[1][0] = -0.2;
  check.matrix[1][1] = 0.4;

  ck_assert_int_eq(s21_inverse_matrix(&matrix, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix3) {
  int num = 4;
  matrix_t matrix;
  matrix_t check;
  matrix_t result;

  s21_create_matrix(num, num, &matrix);
  s21_create_matrix(num, num, &check);

  matrix.matrix[0][0] = 6;
  matrix.matrix[0][1] = -5;
  matrix.matrix[0][2] = 8;
  matrix.matrix[0][3] = 4;
  matrix.matrix[1][0] = 9;
  matrix.matrix[1][1] = 7;
  matrix.matrix[1][2] = 5;
  matrix.matrix[1][3] = 2;
  matrix.matrix[2][0] = 7;
  matrix.matrix[2][1] = 5;
  matrix.matrix[2][2] = 3;
  matrix.matrix[2][3] = 7;
  matrix.matrix[3][0] = -4;
  matrix.matrix[3][1] = 8;
  matrix.matrix[3][2] = -8;
  matrix.matrix[3][3] = -3;

  check.matrix[0][0] = 5.56;
  check.matrix[0][1] = -0.77;
  check.matrix[0][2] = -0.93;
  check.matrix[0][3] = 4.73;
  check.matrix[1][0] = -3;
  check.matrix[1][1] = 0.5;
  check.matrix[1][2] = 0.5;
  check.matrix[1][3] = -2.5;
  check.matrix[2][0] = -5.36;
  check.matrix[2][1] = 0.87;
  check.matrix[2][2] = 0.83;
  check.matrix[2][3] = -4.63;
  check.matrix[3][0] = -1.12;
  check.matrix[3][1] = 0.04;
  check.matrix[3][2] = 0.36;
  check.matrix[3][3] = -0.96;

  ck_assert_int_eq(s21_inverse_matrix(&matrix, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix4) {
  matrix_t matrix;
  matrix_t result;

  s21_create_matrix(-1, 9, &matrix);

  ck_assert_int_eq(s21_inverse_matrix(&matrix, &result), MATRIX_ERROR);
}
END_TEST

START_TEST(s21_inverse_matrix5) {
  matrix_t matrix;
  matrix_t result;

  s21_create_matrix(1, 9, &matrix);

  ck_assert_int_eq(s21_inverse_matrix(&matrix, &result), CALCULATION_ERROR);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_inverse_matrix6) {
  int num = 2;
  matrix_t matrix;
  matrix_t result;

  s21_create_matrix(num, num, &matrix);

  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 1;
  matrix.matrix[1][0] = 1;
  matrix.matrix[1][1] = 1;

  ck_assert_int_eq(s21_inverse_matrix(&matrix, &result), CALCULATION_ERROR);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_calc_complements1) {
  matrix_t matrix;
  matrix_t result;

  s21_create_matrix(-1, 9, &matrix);

  ck_assert_int_eq(s21_calc_complements(&matrix, &result), MATRIX_ERROR);
}
END_TEST

START_TEST(s21_calc_complements2) {
  matrix_t matrix;
  matrix_t result;

  s21_create_matrix(1, 9, &matrix);

  ck_assert_int_eq(s21_calc_complements(&matrix, &result), CALCULATION_ERROR);

  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(s21_calc_complements3) {
  int num = 3;
  matrix_t matrix;
  matrix_t check;
  matrix_t result;

  s21_create_matrix(num, num, &matrix);
  s21_create_matrix(num, num, &check);

  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[0][2] = 3;
  matrix.matrix[1][0] = 0;
  matrix.matrix[1][1] = 4;
  matrix.matrix[1][2] = 2;
  matrix.matrix[2][0] = 5;
  matrix.matrix[2][1] = 2;
  matrix.matrix[2][2] = 1;

  check.matrix[0][0] = 0;
  check.matrix[0][1] = 10;
  check.matrix[0][2] = -20;
  check.matrix[1][0] = 4;
  check.matrix[1][1] = -14;
  check.matrix[1][2] = 8;
  check.matrix[2][0] = -8;
  check.matrix[2][1] = -2;
  check.matrix[2][2] = 4;

  ck_assert_int_eq(s21_calc_complements(&matrix, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_complements4) {
  matrix_t matrix, result;
  s21_create_matrix(5, 5, &matrix);

  matrix.matrix[0][0] = 2;
  matrix.matrix[0][1] = 0.3;
  matrix.matrix[0][2] = 2.3;
  matrix.matrix[0][3] = -1;
  matrix.matrix[0][4] = -0.4;
  matrix.matrix[1][0] = 0.2;
  matrix.matrix[1][1] = 4;
  matrix.matrix[1][2] = 2;
  matrix.matrix[1][3] = 6;
  matrix.matrix[1][4] = 8;
  matrix.matrix[2][0] = 9;
  matrix.matrix[2][1] = -5;
  matrix.matrix[2][2] = -0.5;
  matrix.matrix[2][3] = 0.4;
  matrix.matrix[2][4] = 0.6;
  matrix.matrix[3][0] = 7;
  matrix.matrix[3][1] = 2;
  matrix.matrix[3][2] = 7;
  matrix.matrix[3][3] = 2;
  matrix.matrix[3][4] = 9;
  matrix.matrix[4][0] = -3;
  matrix.matrix[4][1] = -5;
  matrix.matrix[4][2] = -1;
  matrix.matrix[4][3] = 2;
  matrix.matrix[4][4] = -2;

  matrix_t check;
  s21_create_matrix(5, 5, &check);
  check.matrix[0][0] = 756.6;
  check.matrix[0][1] = 1070.48;
  check.matrix[0][2] = 1569.6;
  check.matrix[0][3] = 2085.34;
  check.matrix[0][4] = -2510.56;
  check.matrix[1][0] = 317.04;
  check.matrix[1][1] = 578.9;
  check.matrix[1][2] = 69.48;
  check.matrix[1][3] = 1250.41;
  check.matrix[1][4] = -707.14;
  check.matrix[2][0] = 476.4;
  check.matrix[2][1] = 16.6;
  check.matrix[2][2] = -291.96;
  check.matrix[2][3] = 378.8;
  check.matrix[2][4] = -231.32;
  check.matrix[3][0] = -350.52;
  check.matrix[3][1] = -602.048;
  check.matrix[3][2] = 137.88;
  check.matrix[3][3] = -963.796;
  check.matrix[3][4] = 998.164;
  check.matrix[4][0] = -317.58;
  check.matrix[4][1] = -602.732;
  check.matrix[4][2] = 496.872;
  check.matrix[4][3] = 361.13;
  check.matrix[4][4] = -85.76;

  ck_assert_int_eq(s21_calc_complements(&matrix, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_complements5) {
  int num = 2;
  matrix_t matrix;
  matrix_t check;
  matrix_t result;

  s21_create_matrix(num, num, &matrix);
  s21_create_matrix(num, num, &check);

  matrix.matrix[0][0] = -4;
  matrix.matrix[0][1] = 5.63;
  matrix.matrix[1][0] = 7.651;
  matrix.matrix[1][1] = 3;

  check.matrix[0][0] = 3;
  check.matrix[0][1] = -7.651;
  check.matrix[1][0] = -5.63;
  check.matrix[1][1] = -4;

  ck_assert_int_eq(s21_calc_complements(&matrix, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

Suite *suite_all_tests() {
  Suite *s = suite_create("TESTS");

  TCase *tc_create_matrix = tcase_create("s21_create_matrix");
  tcase_add_loop_test(tc_create_matrix, s21_create_matrix1, 0, 100);
  tcase_add_test(tc_create_matrix, s21_create_matrix2);
  tcase_add_test(tc_create_matrix, s21_create_matrix3);
  tcase_add_loop_test(tc_create_matrix, s21_create_matrix4, 0, 100);
  tcase_add_loop_test(tc_create_matrix, s21_create_matrix5, 0, 100);
  tcase_add_test(tc_create_matrix, s21_create_matrix6);
  suite_add_tcase(s, tc_create_matrix);

  TCase *tc_eq_matrix = tcase_create("s21_eq_matrix");
  tcase_add_loop_test(tc_eq_matrix, s21_eq_matrix1, 0, 100);
  tcase_add_loop_test(tc_eq_matrix, s21_eq_matrix2, 0, 100);
  tcase_add_loop_test(tc_eq_matrix, s21_eq_matrix3, 0, 100);
  tcase_add_loop_test(tc_eq_matrix, s21_eq_matrix4, 0, 100);
  tcase_add_loop_test(tc_eq_matrix, s21_eq_matrix5, 0, 100);
  suite_add_tcase(s, tc_eq_matrix);

  TCase *tc_sum_matrix = tcase_create("s21_sum_matrix");
  tcase_add_loop_test(tc_sum_matrix, s21_sum_matrix1, 0, 100);
  tcase_add_loop_test(tc_sum_matrix, s21_sum_matrix2, 0, 100);
  tcase_add_test(tc_sum_matrix, s21_sum_matrix3);
  tcase_add_test(tc_sum_matrix, s21_sum_matrix4);
  suite_add_tcase(s, tc_sum_matrix);

  TCase *tc_sub_matrix = tcase_create("s21_sub_matrix");
  tcase_add_loop_test(tc_sub_matrix, s21_sub_matrix1, 0, 100);
  tcase_add_loop_test(tc_sub_matrix, s21_sub_matrix2, 0, 100);
  tcase_add_test(tc_sub_matrix, s21_sub_matrix3);
  tcase_add_test(tc_sub_matrix, s21_sub_matrix4);
  suite_add_tcase(s, tc_sub_matrix);

  TCase *tc_mult_number = tcase_create("s21_mult_number");
  tcase_add_loop_test(tc_mult_number, s21_mult_number1, 0, 100);
  tcase_add_loop_test(tc_mult_number, s21_mult_number2, 0, 100);
  tcase_add_test(tc_mult_number, s21_mult_number3);
  suite_add_tcase(s, tc_mult_number);

  TCase *tc_mult_matrix = tcase_create("s21_mult_matrix");
  tcase_add_loop_test(tc_mult_matrix, s21_mult_matrix1, 0, 100);
  tcase_add_test(tc_mult_matrix, s21_mult_matrix2);
  tcase_add_test(tc_mult_matrix, s21_mult_matrix3);
  suite_add_tcase(s, tc_mult_matrix);

  TCase *tc_transpose = tcase_create("s21_transpose");
  tcase_add_loop_test(tc_transpose, s21_transpose1, 0, 100);
  tcase_add_loop_test(tc_transpose, s21_transpose2, 0, 100);
  tcase_add_test(tc_transpose, s21_transpose3);
  tcase_add_test(tc_transpose, s21_transpose4);
  suite_add_tcase(s, tc_transpose);

  TCase *tc_determinant = tcase_create("s21_determinant");
  tcase_add_test(tc_determinant, s21_determinant1);
  tcase_add_loop_test(tc_determinant, s21_determinant2, 0, 100);
  tcase_add_test(tc_determinant, s21_determinant3);
  tcase_add_test(tc_determinant, s21_determinant4);
  tcase_add_test(tc_determinant, s21_determinant5);
  tcase_add_test(tc_determinant, s21_determinant6);
  tcase_add_test(tc_determinant, s21_determinant7);
  tcase_add_test(tc_determinant, s21_determinant8);
  suite_add_tcase(s, tc_determinant);

  TCase *tc_inverse_matrix = tcase_create("s21_inverse_matrix");
  tcase_add_test(tc_inverse_matrix, s21_inverse_matrix1);
  tcase_add_test(tc_inverse_matrix, s21_inverse_matrix2);
  tcase_add_test(tc_inverse_matrix, s21_inverse_matrix3);
  tcase_add_test(tc_inverse_matrix, s21_inverse_matrix4);
  tcase_add_test(tc_inverse_matrix, s21_inverse_matrix5);
  tcase_add_test(tc_inverse_matrix, s21_inverse_matrix6);
  suite_add_tcase(s, tc_inverse_matrix);

  TCase *tc_calc_complements = tcase_create("s21_calc_complements");
  tcase_add_test(tc_calc_complements, s21_calc_complements1);
  tcase_add_test(tc_calc_complements, s21_calc_complements2);
  tcase_add_test(tc_calc_complements, s21_calc_complements3);
  tcase_add_test(tc_calc_complements, s21_calc_complements4);
  tcase_add_test(tc_calc_complements, s21_calc_complements5);
  suite_add_tcase(s, tc_calc_complements);

  return s;
}

int main() {
  int count;
  Suite *s = suite_all_tests();
  SRunner *runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  count = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}