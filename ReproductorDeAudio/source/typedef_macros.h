/*
 * typedef_macros.h
 *
 *  Created on: Mar 21, 2020
 *      Author: dario
 */

#ifndef TYPEDEF_MACROS_H_
#define TYPEDEF_MACROS_H_
#define KINETIS_KL25Z

typedef unsigned long T_ULONG;
typedef signed char T_SBYTE;
typedef signed int T_SWORD;
typedef signed long T_SLONG;
typedef void( *FCT_POINTER )(void);
typedef unsigned char 	T_UBYTE;
typedef unsigned short 	T_UWORD;

#define TRUE		((T_UBYTE)(1U))
#define FALSE		((T_UBYTE)(0U))

#define NULL ((void *)0)
#endif /* TYPEDEF_MACROS_H_ */
