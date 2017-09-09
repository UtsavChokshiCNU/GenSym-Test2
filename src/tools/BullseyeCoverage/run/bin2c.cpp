// $Revision: 9459 $ $Date: 2008-11-18 17:02:30 -0800 (Tue, 18 Nov 2008) $
// Copyright (c) Bullseye Testing Technology
// This source file contains confidential proprietary information.
// Do not modify this source file.  If you need changes, contact Technical Support.
// Modification is likely to break functionality and interfere with upgrading to a future release.

// This program converts a binary file into C language definitions.
// The image data is compressed to reduce the size of of zero byte sequences.

#include <stdio.h>

static void writeByte(unsigned b)
{
	printf("0x%02x,", b);
	static unsigned count;
	count++;
	if (count == 16) {
		printf("\n");
		count = 0;
	}
}

int main(int argc, const char* const* argv)
{
	int status = 0;
	if (argc != 3) {
		printf("Usage: %s prefix path\n", argv[0]);
		status = 1;
	} else {
		FILE* file = fopen(argv[2], "rb");
		if (file == NULL) {
			perror(argv[2]);
			status = 1;
		} else {
			// Read the whole file into buf
			static unsigned char buf[99999];
			const unsigned n = fread(buf, 1, sizeof(buf), file);
			fclose(file);
			printf("/* Do not modify this automatically generated file. */\n");
			// Start definitions
			printf("static const _TCHAR %s_basename[] = _T(\"%s\");\n",
				argv[1], argv[2]);
			printf("static const unsigned char %s_image[] = {\n", argv[1]);
			// While more data
			unsigned count = 0;
			for (unsigned i = 0; i < n;) {
				// Determine number of bytes to preserve
				//   Search for two zero bytes
				buf[n] = 0;
				buf[n + 1] = 0;
				while (buf[i + count] != 0 || buf[i + count + 1] != 0) {
					count++;
				}
				while (count != 0) {
					unsigned m = count;
					if (m > 0x7f) {
						m = 0x7f;
					}
					writeByte(0x80 | m);
					for (unsigned j = 0; j < m; j++) {
						writeByte(buf[i]);
						i++;
					}
					count -= m;
				}
				// Determine number of zero bytes to eliminate
				buf[n] = 1;
				while (buf[i + count] == 0) {
					count++;
				}
				while (count != 0) {
					unsigned m = count;
					if (m > 0x7f) {
						m = 0x7f;
					}
					writeByte(m);
					i += m;
					count -= m;
				}
			}
			printf("};\n");
		}
	}
	return status;
}
