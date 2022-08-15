/**
 *  Jordan Strande
 *  jstrande@rams.colostate,edu
 */

#include <stdio.h>

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
char int2char (int radix, int value) {
  char digit;

  if(value < 0 || value > radix - 1 || value > 'Z' || radix < 2 || radix > 36){
        return '?';
  }

  if(value < 9 && value > 0){
	digit = value + '0';
  }else{
	digit = value - 10 + 'A';
       }
  return digit;
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
int char2int (int radix, char digit) {
  int num;

  if(digit <= '9'){
        num = digit - '0';
  }else{
        if(digit >= 'a' && digit <= 'z'){
                num = (digit - 32) - 'A' + 10;
        }else{
                num = digit - 'A' + 10;
        }
  }
  if((num >= radix) || radix > 36 || radix < 0){
        return -1;
  }
  if(digit > 'z'){
        return -1;
  }
  if(digit < 'a' && digit > 'Z'){
        return -1;
  }
  if(digit > '9' && digit < 'A'){
        return -1;
  }
  return num;


//Returns -1 every for any given value
  //  if(digit < 0 || digit > radix - 1 || digit > 'Z' || radix < 2 || radix > 36){
  //	return -1;
  //}
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
void divRem (int numerator, int divisor, int* quotient, int* remainder) {
  if(numerator != 0 && divisor != 0){
	*quotient = (numerator / divisor);
	*remainder = (numerator % divisor);
  }
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
int ascii2int (int radix, int valueOfPrefix) {
  int num = getchar();

  if(num  == '\n'){
	return valueOfPrefix;
  }
  char cha = (char)num;
  int pre = valueOfPrefix * radix;
  return ascii2int(radix, pre + char2int(radix, cha));
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
void int2ascii (int radix, int value) {
  int num1;
  int num2;

  if(value == 0){
	return;
  }

  divRem(value, radix, &num1, &num2);
  int2ascii(radix, num1);
  putchar(int2char(radix, num2));
}

/** @todo implement in <code>numconv.c</code> based on documentation contained 
 *  in <code>numconv.h</code>.
 */
double frac2double (int radix) {
  return -1.0;
}

