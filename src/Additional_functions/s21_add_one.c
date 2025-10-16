#include "../s21_decimal.h"

void s21_add_one(s21_decimal *val) {
  for (int i = 0; i < 3; i++) {
    if (++val->bits[i] == 0) {
      val->bits[i]--;
    } else {
      i = 3;
    }
  }
}