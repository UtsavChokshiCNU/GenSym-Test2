CC = gcc
CFLAGS = -O
SRCDIR = $(SRCBOX)/util/c

all : add-postfix-line-numbers add-postfix add-prefix combine-file-revision-and-info \
 combine-revision-and-info count-duplicated-lines cvtsis get-c-identifiers \
 read-kb-flags reduce-blank-lines write-c-comment write-cdata

add-postfix-line-numbers : $(SRCDIR)/add-postfix-line-numbers.c
	$(CC) $(CFLAGS) $(SRCDIR)/add-postfix-line-numbers.c -o add-postfix-line-numbers

add-postfix : $(SRCDIR)/add-postfix.c
	$(CC) $(CFLAGS) $(SRCDIR)/add-postfix.c -o add-postfix

add-prefix : $(SRCDIR)/add-prefix.c
	$(CC) $(CFLAGS) $(SRCDIR)/add-prefix.c -o add-prefix

combine-file-revision-and-info : $(SRCDIR)/combine-file-revision-and-info.c
	$(CC) $(CFLAGS) $(SRCDIR)/combine-file-revision-and-info.c -o combine-file-revision-and-info

combine-revision-and-info : $(SRCDIR)/combine-revision-and-info.c
	$(CC) $(CFLAGS) $(SRCDIR)/combine-revision-and-info.c -o combine-revision-and-info

count-duplicated-lines : $(SRCDIR)/count-duplicated-lines.c
	$(CC) $(CFLAGS) $(SRCDIR)/count-duplicated-lines.c -o count-duplicated-lines

cvtsis : $(SRCDIR)/cvtsis.c
	$(CC) $(CFLAGS) $(SRCDIR)/cvtsis.c -o cvtsis

get-c-identifiers : $(SRCDIR)/get-c-identifiers.c
	$(CC) $(CFLAGS) $(SRCDIR)/get-c-identifiers.c -o get-c-identifiers

read-kb-flags : $(SRCDIR)/read-kb-flags.c
	$(CC) $(CFLAGS) $(SRCDIR)/read-kb-flags.c -o read-kb-flags

reduce-blank-lines : $(SRCDIR)/reduce-blank-lines.c
	$(CC) $(CFLAGS) $(SRCDIR)/reduce-blank-lines.c -o reduce-blank-lines

write-c-comment : $(SRCDIR)/write-c-comment.c
	$(CC) $(CFLAGS) $(SRCDIR)/write-c-comment.c -o write-c-comment

write-cdata : $(SRCDIR)/write-cdata.c
	$(CC) $(CFLAGS) $(SRCDIR)/write-cdata.c -o write-cdata
