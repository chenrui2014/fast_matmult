
#ifndef _MATMULT_GET_CHAR_H_
#define _MATMULT_GET_CHAR_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/// <comment>
///
/// What is equivalent to getch() & getche() in Linux?
///
/// From: http://stackoverflow.com/questions/7469139/what-is-equivalent-to-getch-getche-in-linux
///
/// </comment>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__linux__)

void init_terminal_os(int echo);
void reset_terminal_os(void);

/* Read 1 character - echo defines echo mode */
char iso_getch_(int echo);

#endif  /* __linux__ */

/* Read 1 character without echo */
char iso_getch(void);

/* Read 1 character with echo */
char iso_getche(void);

void iso_sleep(int millisec);

#ifdef __cplusplus
}
#endif

#endif  /* _MATMULT_GET_CHAR_H_ */
