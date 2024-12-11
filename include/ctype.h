#ifndef _CTYPE_H
#define _CTYPE_H

#include <cdefs.h>

__BEGIN_DECLS

/**
 * @brief Check if character is alphanumeric
 *
 * @param c Character to be checked
 * @return int Non-zero value if the character is alphanumeric, zero otherwise
 */
int isalnum(int c);

/**
 * @brief Check if character is alphabetic
 *
 * @param c Character to be checked
 * @return int Non-zero value if the character is alphabetic, zero otherwise
 */
int isalpha(int c);

/**
 * @brief Check if character is a blank character (space or tab)
 *
 * @param c Character to be checked
 * @return int Non-zero value if the character is a blank character, zero otherwise
 */
int isblank(int c);

/**
 * @brief Check if character is a control character
 *
 * @param c Character to be checked
 * @return int Non-zero value if the character is a control character, zero otherwise
 */
int iscntrl(int c);

/**
 * @brief Check if character is a digit
 *
 * @param c Character to be checked
 * @return int Non-zero value if the character is a digit, zero otherwise
 */
int isdigit(int c);

/**
 * @brief Check if character has a graphical representation
 *
 * @param c Character to be checked
 * @return int Non-zero value if the character has a graphical representation, zero otherwise
 */
int isgraph(int c);

/**
 * @brief Check if character is a lowercase letter
 *
 * @param c Character to be checked
 * @return int Non-zero value if the character is a lowercase letter, zero otherwise
 */
int islower(int c);

/**
 * @brief Check if character is printable
 *
 * @param c Character to be checked
 * @return int Non-zero value if the character is printable, zero otherwise
 */
int isprint(int c);

/**
 * @brief Check if character is a punctuation character
 *
 * @param c Character to be checked
 * @return int Non-zero value if the character is a punctuation character, zero otherwise
 */
int ispunct(int c);

/**
 * @brief Check if character is a whitespace character
 *
 * @param c Character to be checked
 * @return int Non-zero value if the character is a whitespace character, zero otherwise
 */
int isspace(int c);

/**
 * @brief Check if character is an uppercase letter
 *
 * @param c Character to be checked
 * @return int Non-zero value if the character is an uppercase letter, zero otherwise
 */
int isupper(int c);

/**
 * @brief Convert character to lowercase
 *
 * @param c Character to be converted
 * @return int Lowercase equivalent of the character if it is an uppercase letter, otherwise the character itself
 */
int tolower(int c);

/**
 * @brief Convert character to uppercase
 *
 * @param c Character to be converted
 * @return int Uppercase equivalent of the character if it is a lowercase letter, otherwise the character itself
 */
int toupper(int c);

/**
 * @brief Check if character is an ASCII character
 *
 * @param c Character to be checked
 * @return int Non-zero value if the character is an ASCII character, zero otherwise
 */
int isascii(int c);

/**
 * @brief Check if character is a hexadecimal digit
 *
 * @param c Character to be checked
 * @return int Non-zero value if the character is a hexadecimal digit, zero otherwise
 */
int isxdigit(int c);

__END_DECLS

#endif /* _CTYPE_H */
