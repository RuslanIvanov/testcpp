#ifndef DEBUG_PRINT_H
#define DEBUG_PRINT_H

#ifdef DBG
#define DEBUGP(stmt) printf stmt
#else
#define DEBUGP(stmt)
#endif

#ifdef PRNT
#define PRINTF(stmt) printf stmt
#else
#define PRINTF(stmt)
#endif

#ifdef PRNT1
#define PRINTF1(stmt) printf stmt
#else
#define PRINTF1(stmt)
#endif

/*#ifdef PRERR
#define PERROR(stmt) perror stmt
#else
#define PERROR(stmt)
#endif*/

#ifdef LOGWR
#define LOGWRITE(stmt) fprintf stmt
#else
#define LOGWRITE(stmt)
#endif

#define ERRORP(stmt) printf stmt

#endif
