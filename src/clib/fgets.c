#include <stdio.h>

/* fgets: get at most n chars from iop */
char *fgets(char *s, int n, FILE *iop) {
  int   c;
  char *cs;

  cs = s;

  while (--n > 0 && (c = getc(iop)) != EOF)
    if ((*cs++ = c) == '\r') // TODO consider CR/LF Translations
      break;

  *cs = '\0';

  return (c == EOF && cs == s) ? NULL : s;
}
