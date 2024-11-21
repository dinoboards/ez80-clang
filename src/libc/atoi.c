/************************************************************************/
/*								                                                    	*/
/*			Copyright (C) 2000-2008 Zilog, Inc.	                          	*/
/*							                                                     		*/
/************************************************************************/
#include <stddef.h>
#include <stdlib.h>

/*************************************************
 *
 * atoi - ASCII to integer conversion
 *
 * Inputs:
 *	str - pointer to the character string
 *
 * Returns:
 *	the value of the number
 *
 *************************************************/
int atoi(const char *cp) { return (strtol(cp, NULL, 10)); }
