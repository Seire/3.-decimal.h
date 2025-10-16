#include "../s21_decimal.h"

int both_zeroes(s21_long_decimal *value1, s21_long_decimal *value2) {
  int res = 1;
  for (int i = 0; i < 7; i++) {
    if (value1->bits[i] != 0 || value2->bits[i] != 0) {
      res = 0;
    }
  }
  return res;
}

/**
 * @brief Сравнивает 2 числа s21_decimal
 * @param value1 первый s21_decimal
 * @param value2 второй s21_decimal
 * @return Результат сравнения:
 * 0 - value1==value2.
 * 1 - value1>value2.
 * 2 - value1<value2,
 */
int s21_compare(s21_long_decimal value1, s21_long_decimal value2) {
  int vs1 = s21_get_sign_ldec(value1);
  int vs2 = s21_get_sign_ldec(value2);
  int res = 0;
  if (both_zeroes(&value1, &value2))
    ;
  else if (!vs1 && vs2)
    res = 1;
  else if (vs1 && !vs2)
    res = 2;
  else {
    for (int i = 6; i >= 0 && !res; i--) {
      if (value1.bits[i] > value2.bits[i]) {
        res = 1;
      } else if (value1.bits[i] < value2.bits[i]) {
        res = 2;
      }
    }
  }

  if (vs1 && vs2) {
    if (res == 1) {
      res = 2;
    } else if (res == 2) {
      res = 1;
    }
  }
  return res;
}