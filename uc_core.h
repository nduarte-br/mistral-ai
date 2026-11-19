#ifndef UC_CORE_H
#define UC_CORE_H
#include <stdio.h>
#include <stddef.h>

typedef struct { size_t total, updated, good, bad; } Counts;
typedef struct { wchar_t *data; size_t len, cap; } LogBuf;

int uc_convert(FILE *in, FILE *out, Counts *c, LogBuf *log, int cli);
#ifdef _WIN32
int uc_make_backup(const wchar_t *in, wchar_t *backup);
int uc_unique_output(const wchar_t *in, wchar_t *out, unsigned cap);
#endif
void lb_wstr(LogBuf *b, const wchar_t *s);
void lb_bytes(LogBuf *b, const unsigned char *p, size_t n);
void lb_u64(LogBuf *b, unsigned long long v);
void lb_nl(LogBuf *b);
void lb_reset(LogBuf *b);
void lb_free(LogBuf *b);
#endif
