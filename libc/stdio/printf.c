#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool print(const char *data, size_t length) {
  const unsigned char *bytes = (const unsigned char *)data;
  for (size_t i = 0; i < length; i++)
    if (putchar(bytes[i]) == EOF)
      return false;
  return true;
}

static int int_to_string(int i, char *buf, unsigned base) {
  char tbuf[32];
  char bchars[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                   '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
  int pos = 0;
  int opos = 0;
  int top = 0;
  int negative = 0;
  memset(tbuf, 0, 32);

  if (i < 0) {
    negative = 1;
    i = -i;
  }

  if (i == 0 || base > 16) {
    buf[0] = '0';
    buf[1] = '\0';
    return 1;
  }

  while (i != 0) {
    tbuf[pos] = bchars[i % base];
    pos++;
    i /= base;
  }
  top = pos--;

  if (negative)
    buf[opos++] = '-';

  for (; opos < top; pos--, opos++)
    buf[opos] = tbuf[pos];
  buf[opos] = '\0';

  return top;
}

int printf(const char *restrict format, ...) {
  va_list parameters;
  va_start(parameters, format);

  int written = 0;

  while (*format != '\0') {
    size_t maxrem = INT_MAX - written;

    if (format[0] != '%' || format[1] == '%') {
      if (format[0] == '%')
        format++;
      size_t amount = 1;
      while (format[amount] && format[amount] != '%')
        amount++;
      if (maxrem < amount) {
        // TODO: Set errno to EOVERFLOW.
        return -1;
      }
      if (!print(format, amount))
        return -1;
      format += amount;
      written += amount;
      continue;
    }

    const char *format_begun_at = format++;

    switch (*format) {
    case 'c': {
      format++;
      char c = (char)va_arg(parameters, int /* char promotes to int */);
      if (!maxrem) {
        // TODO: Set errno to EOVERFLOW.
        return -1;
      }
      if (!print(&c, sizeof(c)))
        return -1;
      written++;
      break;
    }
    case 's': {
      format++;
      const char *str = va_arg(parameters, const char *);
      size_t len = strlen(str);
      if (maxrem < len) {
        // TODO: Set errno to EOVERFLOW.
        return -1;
      }
      if (!print(str, len))
        return -1;
      written += len;
      break;
    }
    case 'd': {
      format++;
      int num = va_arg(parameters, int);
      char num_str[12] = {0}; // Maximum 12 characters for an integer
      size_t len = int_to_string(num, num_str, 10);
      if (maxrem < len) {
        // TODO: Set errno to EOVERFLOW.
        return -1;
      }
      if (!print(num_str, len))
        return -1;
      written += len;
      break;
    }
    case 'x': {
      format++;
      int num = va_arg(parameters, int);
      char num_str[12] = {0}; // Maximum 12 characters for an integer
      size_t len = int_to_string(num, num_str, 16);
      if (maxrem < len) {
        // TODO: Set errno to EOVERFLOW.
        return -1;
      }
      if (!print(num_str, len))
        return -1;
      written += len;
      break;
    }
    default: {
      format = format_begun_at;
      size_t len = strlen(format);
      if (maxrem < len) {
        // TODO: Set errno to EOVERFLOW.
        return -1;
      }
      if (!print(format, len))
        return -1;
      written += len;
      format += len;
      break;
    }
    }
  }

  va_end(parameters);
  return written;
}
