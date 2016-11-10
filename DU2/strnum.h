/*
 * Author: Jiri Matejka
 * Login: xmatej52
 * School: VUT FIT, Brno
 * Date: 22-4-2016
 * Module: IJC-DU2 strnum.h
 * gcc version 4.9.2 (Debian 4.9.2-10)
 */
#ifndef STRNUM_H
#define STRNUM_H
#include <stdlib.h>
/**
 * @defgroup strnum Converting strings to numbers
 * Functions needed to convert string to numbers
 * @{
 */
 
/**
 * Check if number is integer
 * @param string String that will be checked
 * @pre string != NULL
 * @return 1 for number, 0 when string does not represent number
 */
int is_int (char *string);

/**
 * Convert string to unsigned integer
 * @param string String that will be converted
 * @pre string != NULL
 * @pre string represent number
 * @return -1 for an error or absolute value of string
 */
int string_to_uint (char *string);
 /** @} */
#endif
