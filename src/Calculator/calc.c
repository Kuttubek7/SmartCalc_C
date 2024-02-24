#include "calc.h"

// int main() {
//   char str_1[200] = "2*2"; // -0.1+0.2
//   int err = 0;
//   err = check_input(str_1);
//   printf("Error: %d\n", err);
//   if (err == 0) {
//     Node *number_list = parsing(str_1);
//     number_list = polish_notation(number_list, 5);
//     double result = calculation(number_list);
//     printf("%lf\n", result);
//   }
//   return 0;
// }

/// @brief - парсит строку которая дается ввиде выражения
/// @param str - получает строку с математическим выражением
/// @return - возвращет структуру
Node *parsing(const char *str) {
  Node *number_list = NULL;
  char number_str[200] = {};
  for (size_t i = 0, j = 0; str[i] != '\0'; i++) {
    if ((str[i] >= '0' && str[i] <= '9') ||
        (str[i] == '.' && isdigit(str[i - 1]))) {
      number_str[j] = str[i];
      j++;
    }
    if ((!(str[i] >= '0' && str[i] <= '9') && (j && str[i] != '.')) ||
        (str[i + 1] == '\0' && j)) {
      push(&number_list, number, atof(number_str), number);
      bzero(&number_str, strlen(number_str));
      j = 0;
    }
    if (str[i] == 'x') {
      push(&number_list, 0, 0, X);
    }
    if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' ||
        str[i] == '%') {
      if (str[i] == '+') {
        if (str[0] == '+' && i == 0) {
          push(&number_list, 0, 0, number);
        }
        push(&number_list, 1, 0, plus_1);
      }
      if (str[i] == '-') {
        if (str[0] == '-' && i == 0) {
          push(&number_list, 0, 0, number);
        }
        push(&number_list, 1, 0, minus_1);
      }
      if (str[i] == '*') {
        push(&number_list, 2, 0, mult_1);
      }
      if (str[i] == '/') {
        push(&number_list, 2, 0, div_1);
      }
      if (str[i] == '%') {
        push(&number_list, 2, 0, mod_1);
      }
    } else if (str[i] == '^') {
      push(&number_list, 3, 0, pow_1);
    } else if (str[i] == 'c' || str[i] == 's' || str[i] == 't' ||
               str[i] == 'a' || str[i] == 'l' || str[i] == 'm') {
      if (str[i] == 'm' && str[i + 1] == 'o' && str[i + 2] == 'd') {
        push(&number_list, 3, 0, mod_1);
        i = i + 2;
      }
      if (str[i] == 's' && str[i + 1] == 'q' && str[i + 2] == 'r' &&
          str[i + 3] == 't') {
        push(&number_list, 3, 0, sqrt_1);
        i = i + 3;
      }
      if (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's') {
        push(&number_list, 3, 0, cos_1);
        i = i + 2;
      }
      if (str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n') {
        push(&number_list, 3, 0, sin_1);
        i = i + 2;
      }
      if (str[i] == 't' && str[i + 1] == 'a' && str[i + 2] == 'n') {
        push(&number_list, 3, 0, tan_1);
        i = i + 2;
      }
      if (str[i] == 'c' && str[i + 1] == 'o' &&
          str[i + 2] == 's') {  // не заходит
        push(&number_list, 3, 0, cos_1);
        i = i + 2;
      }
      if (str[i] == 'a') {
        if (str[i + 1] == 'c' && str[i + 2] == 'o' && str[i + 3] == 's') {
          push(&number_list, 3, 0, acos_1);
          i = i + 3;
        }
        if (str[i + 1] == 's' && str[i + 2] == 'i' && str[i + 3] == 'n') {
          push(&number_list, 3, 0, asin_1);
          i = i + 3;
        }
        if (str[i + 1] == 't' && str[i + 2] == 'a' && str[i + 3] == 'n') {
          push(&number_list, 3, 0, atan_1);
          i = i + 3;
        }
      }
      if (str[i] == 'l') {
        if (str[i + 1] == 'n') {
          push(&number_list, 3, 0, ln_1);
          i = i + 1;
        }
        if (str[i + 1] == 'o' && str[i + 2] == 'g') {
          push(&number_list, 3, 0, log_1);
          i = i + 2;
        }
      }
    } else if (str[i] == '(' || str[i] == ')') {
      if (str[i] == '(') {
        push(&number_list, 4, 0, Lbracket_1);
        if (str[i + 1] == '+' || str[i + 1] == '-') {
          push(&number_list, 0, 0, number);
        }
      }
      if (str[i] == ')') {
        push(&number_list, 4, 0, Rbracket_1);
      }
    }
  }
  return number_list;
}

/// @brief - получает стек выводит значения в переменные и вычисляет
/// @param line - получает структуру в которую записан выражение ввиде польсой
/// нотации
/// @return - возвращет вычисленное значение
double calculation(Node *line) {
  Node *number = NULL;
  for (size_t i = 0; line != NULL; i++) {
    if (line->type == 0 || line->type == 1) {
      push(&number, line->priority, line->num, line->type);
      pop(&line);
    }
    if (line != NULL) {
      if (line->type > 1 && line->type < 8) {
        double val2 = number->num;
        pop(&number);
        double val1 = number->num;
        pop(&number);
        type_t operation_calc = line->type;
        pop(&line);
        double res = calculate(val1, val2, operation_calc);
        push(&number, 0, res, 0);
      }
      if (line != NULL) {
        if (line->type > 7 && line->type < 17) {
          double val2 = number->num;
          pop(&number);
          double val1 = 0;
          type_t operation_calc = line->type;
          pop(&line);
          double res = calculate(val1, val2, operation_calc);
          push(&number, 0, res, 0);
        }
      }
    }
  }
  double result = number->num;
  pop(&number);
  return result;
}

/// @brief
/// @param val1 - получает выведенный из стека число
/// @param val2 - тоже самое
/// @param operation - получает оператор
/// @return - возвращает вычисленный результат
double calculate(double val1, double val2, type_t operation) {
  double result = 0.0;
  if (operation == 2)
    result = val1 + val2;
  else if (operation == 3)
    result = val1 - val2;
  else if (operation == 4)
    result = val1 * val2;
  else if (operation == 5)
    result = val1 / val2;
  else if (operation == 7)
    result = pow(val1, val2);
  else if (operation == 6)
    result = fmod(val1, val2);
  else if (operation == 9)
    result = sin(val2);
  else if (operation == 8)
    result = cos(val2);
  else if (operation == 10)
    result = tan(val2);
  else if (operation == 11)
    result = acos(val2);
  else if (operation == 12)
    result = asin(val2);
  else if (operation == 13)
    result = atan(val2);
  else if (operation == 14)
    result = sqrt(val2);
  else if (operation == 15)
    result = log(val2);
  else if (operation == 16)
    result = log10(val2);
  return result;
}

/// @brief
/// @param s - получает строку перед парсингом для проверки ошибок
/// @return - возвращает цифру ошибки
int check_input(const char *s) {
  int err = 0, open = 0, close = 0, len = strlen(s);
  check_input_start(s, &err);
  for (int i = 0; i < len; i++) {
    if (err == 0) check_input_arithmetic(s, &err, i);
    if (err == 0) check_input_brackets(s, &err, i);
    if (err == 0) check_correct(s, &err, &open, &close, &i);
  }
  sum_brackets(&err, open, close);
  return err;
}

/// @brief - проверяет строку на корректности данных
/// @param s - получает строку с выражением
/// @param err - возвращает код ошибки
void check_input_start(const char *s, int *err) {
  if (strlen(s) < 1 || strlen(s) > 256) {
    *err = 4;
  }
  if (s[0] == '0' && s[1] == '0')
    *err = 1;
  else if (s[0] == '/' || s[0] == '*' || s[0] == '^' || s[0] == 'm' ||
           s[0] == '.')
    *err = 1;
}

/// @brief - проверяет строку на корректности данных
/// @param s - получает строку
/// @param err - получает переменную, для возврщения ошибки
/// @param i - получает порядок проверки элемента
void check_input_arithmetic(const char *s, int *err, int i) {
  if ((s[i] == '+' || s[i] == '-' || s[i] == '/' || s[i] == '*' ||
       s[i] == '^') &&
      (s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == '/' ||
       s[i + 1] == '*' || s[i + 1] == '^')) {
    *err = 1;
  }
  if (*err == 0) {
    int z = strlen(s) - 1;
    if ((s[z] == '+' || s[z] == '-' || s[z] == '*' || s[z] == '/' ||
         s[z] == '^') &&
        (err == 0)) {
      *err = 1;
    }
    if (*err == 0 && (s[z] == '+' || s[z] == '-' || s[z] == '*' ||
                      s[z] == '/' || s[z] == '^')) {
      *err = 1;
    }
  }
  if (*err == 0 && s[i] == '/' && s[i + 1] == '0') {
    *err = 5;
  }
}

/// @brief - проверяет строку на корректности данных
/// @param s - строка
/// @param err - код ошибки
/// @param i - порядок элемента
void check_input_brackets(const char *s, int *err, int i) {
  if ((s[i] == '(') && (s[i + 1] == ')')) {
    *err = 2;
  }
  if ((*err == 0) &&
      (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' ||
       s[i] == '^') &&
      (s[i + 1] == ')')) {
    *err = 1;
  }
}

/// @brief - проверяет на несовпадения количество скобок
/// @param err - принимает код ошибки которая в случае срабатывания ифа вернет
/// код ошибки
/// @param open - принимает количество открывающих скобок
/// @param close - принимает количество закрывающих скобок
void sum_brackets(int *err, int open, int close) {
  if (*err == 0 && open != close) {
    *err = 3;
  }
}

/// @brief - на этот раз он проверяет на скобки и функции
/// @param s - также получает строку
/// @param err - также возвращает код ошибки в случае ошибки
/// @param open - если скобка есть то возврващет единичку указывая что в
/// выражении есть скобка
/// @param close - так же возврашает единицу при случае нахождения закрывающиеся
/// скобки
/// @param i - элемент для проверки
void check_correct(const char *s, int *err, int *open, int *close, int *i) {
  if (s[*i] == '.') {
    *i = *i;
  } else if (s[*i] == 'x') {
    *i = *i;
  } else if (s[*i] >= '0' && s[*i] <= '9') {
    *i = *i;
  } else if (s[*i] == '+' || s[*i] == '-' || s[*i] == '*' || s[*i] == '/' ||
             s[*i] == '^') {
    *i = *i;
  } else if (s[*i] == '(') {
    *open = *open + 1;
  } else if (s[*i] == ')') {
    *close = *close + 1;
  } else if ((s[*i] == 'm' && s[*i + 1] == 'o' && s[*i + 2] == 'd') &&
             (s[*i + 3] >= '0' && s[*i + 3] <= '9')) {
    *i = *i + 2;
  } else if (s[*i] == 'c' && s[*i + 1] == 'o' && s[*i + 2] == 's' &&
             s[*i + 3] == '(') {
    *i = *i + 2;
  } else if (s[*i] == 's' && s[*i + 1] == 'i' && s[*i + 2] == 'n' &&
             s[*i + 3] == '(') {
    *i = *i + 2;
  } else if (s[*i] == 't' && s[*i + 1] == 'a' && s[*i + 2] == 'n' &&
             s[*i + 3] == '(') {
    *i = *i + 2;
  } else if (s[*i] == 'a' && s[*i + 1] == 'c' && s[*i + 2] == 'o' &&
             s[*i + 3] == 's' && s[*i + 4] == '(') {
    *i = *i + 3;
  } else if (s[*i] == 'a' && s[*i + 1] == 's' && s[*i + 2] == 'i' &&
             s[*i + 3] == 'n' && s[*i + 4] == '(') {
    *i = *i + 3;
  } else if (s[*i] == 'a' && s[*i + 1] == 't' && s[*i + 2] == 'a' &&
             s[*i + 3] == 'n' && s[*i + 4] == '(') {
    *i = *i + 3;
  } else if (s[*i] == 's' && s[*i + 1] == 'q' && s[*i + 2] == 'r' &&
             s[*i + 3] == 't' && s[*i + 4] == '(') {
    *i = *i + 3;
  } else if (s[*i] == 'l' && s[*i + 1] == 'n' && s[*i + 2] == '(') {
    *i = *i + 1;
  } else if (s[*i] == 'l' && s[*i + 1] == 'o' && s[*i + 2] == 'g' &&
             s[*i + 3] == '(') {
    *i = *i + 2;
  } else {
    *err = 1;
  }
  if (*close > *open) *err = 1;
}

/// @brief -
/// @param line - получает стек
/// @param x_value - это цифра для построения графика соответствующей функции
/// @return - возвращет стек
Node *polish_notation(Node *line, double x_value) {
  line = inverse_stack(line);
  Node *oper_func = NULL;
  Node *polish = NULL;
  while (line) {
    if (operator_1(line->type) || func(line->type)) {
      if (oper_func == NULL) {
        push(&oper_func, line->priority, line->num, line->type);
      } else if (oper_func->priority < line->priority ||
                 oper_func->type == Lbracket_1) {
        push(&oper_func, line->priority, line->num, line->type);
      } else if (oper_func->priority == line->priority) {
        push(&polish, oper_func->priority, oper_func->num, oper_func->type);
        pop(&oper_func);
        push(&oper_func, line->priority, line->num, line->type);
      } else {
        push(&polish, oper_func->priority, oper_func->num, oper_func->type);
        pop(&oper_func);
        if (polish->priority >= 2) {
          if (oper_func != NULL) {
            if (oper_func->priority >= 1 && oper_func->priority != 5) {
              push(&polish, oper_func->priority, oper_func->num,
                   oper_func->type);
              pop(&oper_func);
            }
          }
        }
        push(&oper_func, line->priority, line->num, line->type);
      }
    }
    if (line->type == Lbracket_1) {
      push(&oper_func, line->priority, line->num, line->type);
    }
    if (line->type == number || line->type == zero || line->type == X) {
      if (line->type == X) {
        line->num = x_value;
      }
      push(&polish, line->priority, line->num, line->type);
    }
    if (line->type == Rbracket_1) {
      if (oper_func != NULL) {
        while (oper_func->type != Lbracket_1) {
          push(&polish, oper_func->priority, oper_func->num, oper_func->type);
          pop(&oper_func);
        }
      }
      pop(&oper_func);
    }
    pop(&line);
  }
  while (oper_func) {
    push(&polish, oper_func->priority, oper_func->num, oper_func->type);
    pop(&oper_func);
  }
  polish = inverse_stack(polish);
  return polish;
}

// вспомогательные функции
int operator_1(type_t type) {
  int res = 0;
  if (type == plus_1 || type == minus_1 || type == mult_1 || type == div_1 ||
      type == mod_1 || type == pow_1) {
    res = 1;
  }
  return res;
}

int func(type_t type) {
  int res = 0;
  if (type == cos_1 || type == sin_1 || type == tan_1 || type == acos_1 ||
      type == asin_1 || type == atan_1 || type == sqrt_1 || type == ln_1 ||
      type == log_1) {
    res = 1;
  }
  return res;
}

/// @brief
/// @param line - получает стек
/// @return - возвращает инверсионный стек (то есть обратно записанный)
Node *inverse_stack(Node *line) {
  Node *tmp = NULL;
  while (line != NULL) {
    push(&tmp, line->priority, line->num, line->type);
    pop(&line);
  }
  return tmp;
}

/// @brief
/// @param plist - получает структуру. сначала список пустой
/// @param prioritet - получает приоритетность
/// @param number - получает цифру
/// @param type_d - получает функции. ничего не возвращает
void push(Node **plist, int prioritet, double number, type_t type_d) {
  Node *p = malloc(sizeof(Node));
  p->priority = prioritet;
  p->num = number;
  p->type = type_d;
  p->next = *plist;
  *plist = p;
}

/// @brief
/// @param plist - удаляет вверхний элемент стека
void pop(Node **plist) {
  Node *p = *plist;
  if (plist == NULL) {
    exit(0);
  }
  *plist = p->next;
  free(p);
}

// принтует стек
// void print(Node *list) {
//   if (list == NULL) {
//     printf("NULL\n");
//     exit(0);
//   }
//   for (Node *p = list; p != NULL; p = p->next) {
//     printf("Приоритет - %d\nЧисло - %lf\nТип - %d\n-------------------\n",
//            p->priority, p->num, p->type);
//   }
//   printf("\n");
// }
