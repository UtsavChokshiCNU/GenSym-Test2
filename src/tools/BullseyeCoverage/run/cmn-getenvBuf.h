/* $Revision: 9421 $ $Date: 2008-10-31 16:58:55 -0700 (Fri, 31 Oct 2008) $
 * Copyright (c) Bullseye Testing Technology
 * This source file contains confidential proprietary information.
 */

static char* getenvBuf(const char* name, char* buf, unsigned n)
{
	char* value = NULL;
	/* Whether current name matches */
	int isMatch = 1;
	/* Index to name */
	unsigned name_i = 0;
	/* Index to buf */
	unsigned i;
	/* For each byte in file */
	for (i = 0; i < n; i++) {
		switch (buf[i]) {
		case '=':
			/* If name matched up to this point and end of name reached */
			if (isMatch && name[name_i] == '\0') {
				value = buf + i + 1;
				isMatch = 0;
			}
			break;
		case '\0':
		case '\r':
		case '\n':
			/* NUL terminate return value */
			buf[i] = '\0';
			/* Ready for next line */
			name_i = 0;
			isMatch = 1;
			break;
		default:
			/* If name does not match */
			if (name[name_i] != buf[i]) {
				isMatch = 0;
			}
			/* If not end of name */
			if (name[name_i] != '\0') {
				name_i++;
			}
			break;
		}
	}
	return value;
}
