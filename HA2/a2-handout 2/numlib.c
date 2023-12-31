#include "numlib.h"
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <math.h>

void skipspaces(FILE *f) {
  assert(f != NULL);
  while (1) {
    int c = fgetc(f);
    if (!isspace(c)) {
      if (c != EOF) {
        ungetc(c, f);
      }
      return;
    }
  }
}

int read_uint_ascii(FILE *f, uint32_t *out) {
  assert(f != NULL);
  assert(out != NULL);
  int read = 0;
  uint32_t num = 0;

  while (1) {
    int c = fgetc(f);

    if (c >= '0' && c <= '9') {
      num = num * 10 + (c - '0');
    } else {
      if (c != EOF) {
        ungetc(c, f);
      }
      if (read == 0) {
        if (c == EOF) {
          return EOF;
        } else {
          return 1;
        }
      } else {
        *out = num;
        return 0;
      }
    }
    read++;
  }
}

// Dividing num by 10 to the power of decimal. 
// The fuction stores input(num) with input(decimal) number of decimals in out
void divide_by_power_of_ten(int decimal, double* out) {
    assert(out != NULL);
    double divisor = 1.0;
    for(int i = 0; i < decimal; i++) {
        divisor *= 10.0;
    }
    *out = divisor;
}

// make double_ascii_to_double_bin && make double_bin_to_double_ascii && echo 123 456 789 | ./double_ascii_to_double_bin | ./double_bin_to_double_ascii
/*
Input:
  - *f: pointer to a file (command line arguments) / input stream
  - *out: pointer to a double

Variables:
  - read: Tracks the number of characters read. 
          This gets incremented every time a character is read, 
          as the last thing in the while loop.
  - num: The number that is read from the file.

*/
int read_double_ascii(FILE *f, double *out) {
  assert(f != NULL);
  assert(out != NULL);
  int read = 0;
  double num = 0;
  
  while (1) {
    int c = fgetc(f);
  
    if (c >= '0' && c <= '9') {
      num = num * 10 + (c - '0');
// When we get to a decimal point, we need to read the next characters as decimals
    } else if (c == '.') {
      int decimal = 0;

      while (1) {
        c = fgetc(f);
        if (c >= '0' && c <= '9') {
          num = num * 10 + (c - '0');
          decimal++;
        } else {
          if (c != EOF) {
            ungetc(c, f);
          }
          if (read == 0) {
            if (c == EOF) {
              return EOF;
            } else {
              return 1;
            }
          } else {
            double pow;
            divide_by_power_of_ten(decimal, &pow);
            *out = num / pow;
            return 0;
          }
        }
      }
    } else {
      if (c != EOF) {
        ungetc(c, f);
      }
      if (read == 0) {
        if (c == EOF) {
          return EOF;
        } else {
          return 1;
        }
      } else {
        *out = num;
        return 0;
      }
    }
    read++;
  }
} 

/*
  type uint32_t is a word containg 4 bytes
  *out is a pointer to a uint32_t (* means pointer)
*/
int read_uint_le(FILE *f, uint32_t *out) {
  assert(f != NULL);
  assert(out != NULL);
  int b0, b1, b2, b3;
//fgetc reads a single byte from a file
  b0 = fgetc(f);
  if (b0 == EOF) {
    return EOF;
  }

// read the next 3 bytes
  b1 = fgetc(f);
  b2 = fgetc(f);
  b3 = fgetc(f);

  if (b1 == EOF || b2 == EOF || b3 == EOF) {
    return 1;
  }

// Combines into an integer:
  // shift the bytes to the left by 24, 16, 8, 0
  // 0xFF << 8 == 0xFF00
  *out =
    ((uint32_t)b0)
    | ((uint32_t)b1 << 8)
    | ((uint32_t)b2 << 16)
    | ((uint32_t)b3 << 24);
  return 0;
}

// implement read_uint_be using big endian rather than little endian from read_uint_le
int read_uint_be(FILE *f, uint32_t *out) {
  assert(f != NULL);
  assert(out != NULL);
  int b0, b1, b2, b3;

  b0 = fgetc(f);
  if (b0 == EOF) {
    return EOF;
  }

  b1 = fgetc(f);
  b2 = fgetc(f);
  b3 = fgetc(f);

  if (b1 == EOF || b2 == EOF || b3 == EOF) {
    return 1;
  }

  *out =
    ((uint32_t)b0 << 24) |
    ((uint32_t)b1 << 16) | 
    ((uint32_t)b2 << 8) |
    ((uint32_t)b3);
  return 0;
}

int read_double_bin(FILE *f, double *out) {
// sizeof(double)==8 and use little endian
  assert(f != NULL);
  assert(out != NULL);
  char bytes[sizeof(double)];
  if (fread(bytes, sizeof(char), sizeof(double), f) != sizeof(double)) {
    // The next 3 lines, saves us, as it gets rid of the input error:) 
    if (feof(f)) { 
      return EOF;
    } else {
      return 1;
    }
  }
  *out = *((double*)bytes);
  return 0;
}

int write_uint_ascii(FILE *f, uint32_t x) {
  assert(f != NULL);
  if (fprintf(f, "%u", x) < 0) {
    return 1;
  } else {
    return 0;
  }
}

int write_double_ascii(FILE *f, double x) {
  assert(f != NULL);
  if (fprintf(f, "%f", x) < 0) {
    return 1;
  } else {
    return 0;
  }
}

int write_uint_le(FILE *f, uint32_t x) {
  assert(f != NULL);
  fputc(x>>0, f);
  fputc(x>>8, f);
  fputc(x>>16, f);
  fputc(x>>24, f);
  return 0;
}

int write_uint_be(FILE *f, uint32_t x) {
  assert(f != NULL);
  fputc(x>>24, f);
  fputc(x>>16, f);
  fputc(x>>8, f);
  fputc(x>>0, f);
  return 0;
}

int write_double_bin(FILE *f, double x) {
  assert(f != NULL);
  if (fwrite(&x, sizeof(char), sizeof(double), f) != sizeof(double)) 
  {
    return 1;
  }
  return 0;
}