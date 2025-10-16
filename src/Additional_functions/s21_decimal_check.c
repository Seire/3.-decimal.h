#include "../s21_decimal.h"

int s21_decimal_check(s21_decimal value) {
  int errcode = 0;

  for (int pointer = 30; pointer >= 0; pointer--) {
    if (pointer > 23 || pointer < 16) {
      if (value.bits[3] & ACTIVE_FIRST_BIT << pointer) {
        errcode = 4;
      }
    }
    if (pointer > 20 && !errcode) {
      if (value.bits[3] & ACTIVE_FIRST_BIT << pointer) {
        errcode = 2;
      }
    }
  }

  return errcode;
}

#define MAX_EXP 28

/**
 * @brief Проверяет s21_decimal на коррекность
 * @param value Проверяемый s21_decimal
 * @return Коды ошибок:
 * 0 - Значение корректно.
 * 1 - Наличие записи в пустых битах в bits[3].
 * 2 - Экспонента > 28 (считается как беззнаковая).
 * 3 - Оба вышеперечисленных варианта одновременно.
 */
int s21_is_decimal_correct(s21_decimal value) {
  int res = 0;
  s21_decimal_union deconstruct;
  deconstruct.number = value;
  if (deconstruct.parts.useless1 || deconstruct.parts.useless2) {
    res += 1;
  }

  if (deconstruct.parts.exponent > MAX_EXP) {
    res += 2;
  }

  return res;
}