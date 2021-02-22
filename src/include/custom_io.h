#ifndef CUCTOMIO_HEADER
#define CUCTOMIO_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#if defined(_MSC_VER)
# define strcasecmp             _stricmp
# define strncasecmp            _strnicmp
#endif

void            _custom_exit(const char *, int, const char *, int, int);
void            _custom_printf(int, int, const char *, ...);
FILE*           _custom_fopen(const char [], const char []);
void            _error(const char [], int, const char [], int, const char [],
    ...);
int             CountLine(FILE *, char *, int, ...);
int             CountOccurr(FILE *, const char *);
void            FindLine(FILE *, const char *, int *, const char *);
void            NextLine(FILE *, char *, int *);
int             Readable(const char *);

// Maximum string length
#define MAXSTRING               1024

// Verbosity level
#define VL_ERROR                -999
#define VL_SILENT               -2
#define VL_BRIEF                -1
#define VL_NORMAL               0
#define VL_VERBOSE              1

#endif
