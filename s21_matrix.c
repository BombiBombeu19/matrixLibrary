#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = OK;

  if (rows > 0 && columns > 0) {
    result->rows = rows;
    result->columns = columns;

    result->matrix = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)malloc(columns * sizeof(double));
      for (int j = 0; j < columns; j++) {
        result->matrix[i][j] = 0;
      }
    }
  } else
    res = MATRIX_ERROR;

  return res;
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }
  free(A->matrix);

  A->rows = 0;
  A->columns = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int flag = 1;
  if (A->rows == B->rows && A->columns == B->columns) {
    if (A->rows > 0 && A->columns > 0) {
      flag = 0;
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= EPS) {
            flag = 1;
            break;
          }
        }
        if (flag == 1) break;
      }
    }
  }
  int res = (flag == 0) ? SUCCESS : FAILURE;
  return res;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (A->rows > 0 && A->columns > 0 && B->rows > 0 && B->columns > 0) {
    if (A->rows == B->rows && A->columns == B->columns) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    } else
      res = CALCULATION_ERROR;
  } else
    res = MATRIX_ERROR;

  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (A->rows > 0 && A->columns > 0 && B->rows > 0 && B->columns > 0) {
    if (A->rows == B->rows && A->columns == B->columns) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    } else
      res = CALCULATION_ERROR;
  } else
    res = MATRIX_ERROR;

  return res;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = OK;
  if (A->rows > 0 && A->columns > 0) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  } else
    res = MATRIX_ERROR;

  return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (A->rows > 0 && A->columns > 0 && B->rows > 0 && B->columns > 0) {
    if (A->columns == B->rows) {
      s21_create_matrix(A->rows, B->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          result->matrix[i][j] = 0;
          for (int k = 0; k < A->columns; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    } else
      res = CALCULATION_ERROR;
  } else
    res = MATRIX_ERROR;

  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (A->rows > 0 && A->columns > 0) {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  } else
    res = MATRIX_ERROR;

  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  int res = OK;
  if (A->rows > 0 && A->columns > 0) {
    if (A->rows == A->columns) {
      if (A->rows == 1)
        *result = A->matrix[0][0];
      else if (A->rows == 2)
        *result = A->matrix[0][0] * A->matrix[1][1] -
                  A->matrix[0][1] * A->matrix[1][0];

      else {
        int k = 0;
        double determinant = 1;
        while (k < A->rows) {
          double del1 = A->matrix[k][k];
          for (int i = k + 1; i < A->rows; i++) {
            double del2 = A->matrix[i][k] / del1;
            for (int j = k; j < A->columns; j++) {
              A->matrix[i][j] = A->matrix[i][j] - A->matrix[k][j] * del2;
            }
          }
          k++;
        }
        for (int i = 0; i < A->columns; i++) determinant *= A->matrix[i][i];
        *result = determinant;
      }
    } else {
      res = CALCULATION_ERROR;
    }
  } else {
    res = MATRIX_ERROR;
  }
  return res;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (A->rows > 0 && A->columns > 0) {
    if (A->rows == A->columns) {
      double det;
      matrix_t B;
      s21_create_matrix(A->rows, A->columns, &B);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) B.matrix[i][j] = A->matrix[i][j];
      }
      if (s21_determinant(&B, &det) == 0 && det != 0) {
        s21_create_matrix(A->rows, A->columns, result);

        if (A->rows == 1)
          result->matrix[0][0] = pow(A->matrix[0][0], -1);
        else if (A->rows == 2) {
          double del = 1 / (A->matrix[0][0] * A->matrix[1][1] -
                            A->matrix[0][1] * A->matrix[1][0]);
          result->matrix[0][0] = A->matrix[1][1] * del;
          result->matrix[0][1] = (-A->matrix[0][1]) * del;
          result->matrix[1][0] = (-A->matrix[1][0]) * del;
          result->matrix[1][1] = A->matrix[0][0] * del;
        }

        else {
          for (int i = 0; i < A->columns; i++) result->matrix[i][i] = 1;

          int k = 0;
          while (k < A->columns) {
            double preob = A->matrix[k][k];
            for (int i = k; i < A->rows; i++) {
              A->matrix[k][i] = A->matrix[k][i] / preob;
            }
            for (int i = 0; i < A->rows; i++) {
              result->matrix[k][i] = result->matrix[k][i] / preob;
            }

            double del1 = A->matrix[k][k];
            for (int i = k + 1; i < A->rows; i++) {
              double del2 = A->matrix[i][k] / del1;
              for (int j = k; j < A->columns; j++) {
                A->matrix[i][j] = A->matrix[i][j] - A->matrix[k][j] * del2;
              }
              for (int j = 0; j < A->columns; j++) {
                result->matrix[i][j] =
                    result->matrix[i][j] - result->matrix[k][j] * del2;
              }
            }
            k++;
          }

          while (k > 0) {
            k--;
            double preob = A->matrix[k][k];
            for (int i = k; i >= 0; i--) {
              A->matrix[k][i] = A->matrix[k][i] / preob;
            }
            for (int i = A->columns - 1; i >= 0; i--) {
              result->matrix[k][i] = result->matrix[k][i] / preob;
            }

            double del1 = A->matrix[k][k];
            for (int i = k - 1; i >= 0; i--) {
              double del2 = A->matrix[i][k] / del1;
              for (int j = k; j >= 0; j--) {
                A->matrix[i][j] = A->matrix[i][j] - A->matrix[k][j] * del2;
              }
              for (int j = A->columns - 1; j >= 0; j--) {
                result->matrix[i][j] =
                    result->matrix[i][j] - result->matrix[k][j] * del2;
              }
            }
          }
        }
      } else
        res = CALCULATION_ERROR;
      s21_remove_matrix(&B);
    } else
      res = CALCULATION_ERROR;
  } else
    res = MATRIX_ERROR;

  return res;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (A->rows > 0 && A->columns > 0) {
    if (A->rows == A->columns) {
      double det;
      matrix_t B;
      s21_create_matrix(A->rows, A->columns, &B);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) B.matrix[i][j] = A->matrix[i][j];
      }
      if (s21_determinant(&B, &det) == OK) {
        matrix_t trans;
        s21_create_matrix(A->rows, A->columns, &trans);
        matrix_t C;
        s21_create_matrix(A->rows, A->columns, &C);
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) C.matrix[i][j] = A->matrix[i][j];
        }
        s21_inverse_matrix(A, &C);

        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++)
            trans.matrix[i][j] = C.matrix[i][j] * det;
        }
        s21_transpose(&trans, result);
        s21_remove_matrix(&C);
        s21_remove_matrix(&trans);
      }
      s21_remove_matrix(&B);
    } else
      res = CALCULATION_ERROR;
  } else
    res = MATRIX_ERROR;

  return res;
}
