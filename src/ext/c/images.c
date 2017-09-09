/* -*- c-file-style:"stroustrup"; indent-tabs-mode: nil -*- */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      images.c
 +
 + CVS location: ext/c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):  Fred White
 +
 + Description:  This file contains the primitives used to read image files in
 +               various formats.  This file does not depend on any particular
 +               window system.
 +
 + Dependencies:
 +      The Independent JPEG Group library, in $SRCBOX/jpeg/c
 +
 + Notes:
 +      There is a main program at the end which can be used for testing.
 +      Compile with IMAGES_MAIN defined to get the test program.
 +
 +      This file happens to teeter on the edge of a bug in the hp9000s700
 +      C compiler.  You might want to test changes with:
 +
 +      rsh rwanda "cd $PWD ; cc -c +O3 -w +Nd75000 +Ns75000 -Wp,-H1000000 images.c"
 +
 + Modifications:
 +  JPEG added -fmw, 1/31/02
 +  JPEG output -fmw, 5/11/04
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* todo:
   export better error msgs to lisp
   read more than one scan line per call
   read from in-memory buffers
   BMP support
   PNG support
   */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <setjmp.h>                /* Required for JPEG error handling. */
#include <errno.h>
#include <assert.h>

/* Independent JPEG Group library.  These include files live in $SRCBOX/jpeg/c */
#define XMD_H
#include "jpeglib.h"
#include "jerror.h"

#include "cprim.h"
#include "graphics.h"

/* Independent PNG Library*/
#define PNG_SKIP_SETJMP_CHECK
#include "png.h"
#define False 0
#define True 1

#if defined(READ_BINARY)
#else
# if defined(WIN32)
#   define READ_BINARY "rb"
# else
#   define READ_BINARY "r"
# endif
#endif


extern G2pointer g2ext_cache_cpointer(Cpointer);
extern Cpointer g2ext_map_g2pointer_to_cpointer(G2pointer);
extern void g2ext_decache_g2pointer(G2pointer);

extern long g2ext_retry_file_operation();
extern int No_window;		/* defined in networks.c */
extern int g2ext_too_many_fds;
extern void g2ext_unset_too_many_fds();
#if !defined(win32)
#  define NOTICE_FD_CLOSE() if(g2ext_too_many_fds)g2ext_unset_too_many_fds()
#else
#  define NOTICE_FD_CLOSE()
#endif

/*
 * jh, 7/8/94.  Need explicit externs now that the following functions return
 * longs instead of ints.  See my note this date in /bt/ab/rtl/c/gensym.h for
 * further details.
 */
extern long g2ext_close_image_stream(/* long */);
extern long g2ext_image_stream_format(/* long */);
extern long g2ext_image_stream_height(/* long */);
extern long g2ext_image_stream_width(/* long */);
extern long g2ext_image_stream_depth(/* long */);
extern long g2ext_image_stream_size(/* long */);
extern long g2ext_image_stream_error(G2pointer istream, char *buffer, long buflen);
extern long g2ext_str_directory_p();

/*
** bitreverse.h
**
** This particular array seems to be useful in a lot of bitmap
** conversion programs.  It's not used in pbm because bits are
** stored one per byte, for easier manipulation.  But if you wanted
** to write, for example, a program to directly convert Sun raster
** format into X bitmaps, you could use this.
**
** Of course, you could also use this fairly slick chunk of code:
**
**     c = ((c >>  1) & 0x55) | ((c <<  1) & 0xaa);
**     c = ((c >>  2) & 0x33) | ((c <<  2) & 0xcc);
**     c = ((c >>  4) & 0x0f) | ((c <<  4) & 0xf0);
*/

static unsigned char bitreverse[256] = {
    0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0, 0x10, 0x90, 0x50, 0xd0,
    0x30, 0xb0, 0x70, 0xf0, 0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
    0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8, 0x04, 0x84, 0x44, 0xc4,
    0x24, 0xa4, 0x64, 0xe4, 0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
    0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec, 0x1c, 0x9c, 0x5c, 0xdc,
    0x3c, 0xbc, 0x7c, 0xfc, 0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
    0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2, 0x0a, 0x8a, 0x4a, 0xca,
    0x2a, 0xaa, 0x6a, 0xea, 0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
    0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6, 0x16, 0x96, 0x56, 0xd6,
    0x36, 0xb6, 0x76, 0xf6, 0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
    0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe, 0x01, 0x81, 0x41, 0xc1,
    0x21, 0xa1, 0x61, 0xe1, 0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
    0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9, 0x19, 0x99, 0x59, 0xd9,
    0x39, 0xb9, 0x79, 0xf9, 0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
    0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5, 0x0d, 0x8d, 0x4d, 0xcd,
    0x2d, 0xad, 0x6d, 0xed, 0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
    0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3, 0x13, 0x93, 0x53, 0xd3,
    0x33, 0xb3, 0x73, 0xf3, 0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
    0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb, 0x07, 0x87, 0x47, 0xc7,
    0x27, 0xa7, 0x67, 0xe7, 0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
    0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef, 0x1f, 0x9f, 0x5f, 0xdf,
    0x3f, 0xbf, 0x7f, 0xff};



/* Return an ImageStream given a G2 pointer */
#define GetImageStream(g2pointer) ((ImageStream *)(g2ext_map_g2pointer_to_cpointer(g2pointer)))

#define GENSYM_RGB(r,g,b) ((r)<<16 | (g)<<8 | (b))

/* Keep in sync in image-stream-format in images.lisp */
#define UNKNOWN_FORMAT 0
#define XBM_FORMAT 1
#define GIF_FORMAT 2
#define PBM_FORMAT 3                /* Not documented. */
#define PPM_FORMAT 4                /* Not yet supported. */
#define JPG_FORMAT 5                /* Really JFIF, of course. -fmw, 12/17/01 */
#define PNG_FORMAT 6                /* Not yet supported. */
#define BMP_FORMAT 7                /* Not yet supported. */
#define ICO_FORMAT 7                /* Not yet supported. */
#define CUR_FORMAT 8                /* Not yet supported. */
#define XPM_FORMAT 9                /* Not yet supported. */

#define MAX_ERROR_MSGLEN 200

/* Special error manager object for JPEG which includes a jmp_buf */
struct jpg_error_mgr {
  struct jpeg_error_mgr pub;        /* "public" fields */
  struct ISS *stream;                /* ImageStream */
};

/* Lisp gets back a G2pointer to one of these guys when it opens an image. */
typedef struct ISS {
  FILE *file;                        /* Generalize to be in-core ICP buffer, etc. */
  int in_use;                        /* True or False */
  G2pointer g2pointer;
  struct IFF *format;                /* Deduced file format (statically allocated). */
  int width;
  int height;
  int depth;
  int position;                        /* Number of scans read so far. */
  int user_data;                /* Per-format data. */
  int ncolors;
  long colormap[256];                /* Packed RGB values. */
  int error;                        /* Last reported error. */
  char error_msg[MAX_ERROR_MSGLEN]; /* Associated message(s). */
  int transparentindex;         /* Transparent Color Index */

  /* For the JPEG decoder. */
  int started;                        /* Non-zero if decompresser was started. */
  jmp_buf jmpbuf;
  struct jpeg_decompress_struct cinfo;
  struct jpg_error_mgr jerr;

  /*For png decoder*/

  png_structp png_ptr;
     png_infop info_ptr;

} ImageStream;

/* An image file format.  We assume all images files have a distinctive signature. */
typedef struct IFF {
  int number;
  const char *name;
  const unsigned char *signature;
  int siglen;
  int (*read_header) (ImageStream *stream);
  int (*read_row)    (ImageStream *stream, unsigned char *buffer, long buflen);
  int (*close)       (ImageStream *stream);
} ImageFileFormat;


static int xbm_read_header(ImageStream *);
static int xbm_read_row(ImageStream *, unsigned char *, long buflen);
static int gif_read_header(ImageStream *);
static int gif_read_row(ImageStream *, unsigned char *, long buflen);
static int jpg_read_header(ImageStream *);
static int jpg_read_row(ImageStream *, unsigned char *, long buflen);
static int jpg_close(ImageStream *);
static int pbm_read_header(ImageStream *);
static int pbm_read_row(ImageStream *, unsigned char *, long buflen);
static int read_image_bytes(unsigned char *, int, FILE *);
static int png_read_header(ImageStream *);
static int png_read_row_local(ImageStream *, unsigned char *, long buflen);
static int png_close(ImageStream *);

static int images_trace = 0;

#define MAX_SIGNATURE_LENGTH 16        /* Longer than any signature. */

/* Known formats */
static ImageFileFormat image_file_formats[] = {
  {GIF_FORMAT, "GIF", (const unsigned char *)"GIF87a",            6, gif_read_header, gif_read_row, NULL},
  {GIF_FORMAT, "GIF", (const unsigned char *)"GIF89a",            6, gif_read_header, gif_read_row, NULL},
  {XBM_FORMAT, "XBM", (const unsigned char *)"#define",           7, xbm_read_header, xbm_read_row, NULL},
  {XPM_FORMAT, "XPM", (const unsigned char *)"/* XPM",            6, NULL, NULL, NULL},
  {XBM_FORMAT, "XBM", (const unsigned char *)"/*",                2, xbm_read_header, xbm_read_row, NULL},
  {JPG_FORMAT, "JPG", (const unsigned char *)"\377\330\377",      3, jpg_read_header, jpg_read_row, jpg_close},
  {PBM_FORMAT, "PBM", (const unsigned char *)"P4\n",              3, pbm_read_header, pbm_read_row, NULL},
  {PPM_FORMAT, "PPM", (const unsigned char *)"P6\n",              3, NULL, NULL, NULL},
  {PNG_FORMAT, "PNG", (const unsigned char *)"\211PNG\r\n\032\n", 8, png_read_header, png_read_row_local, png_close},
  {BMP_FORMAT, "BMP", (const unsigned char *)"BM",                2, NULL, NULL},
  {ICO_FORMAT, "ICO", (const unsigned char *)"\0\0\1\0",          4, NULL, NULL, NULL},
  {CUR_FORMAT, "CUR", (const unsigned char *)"\0\0\2\0",          4, NULL, NULL, NULL}
};

/* We statically allocate the image stream objects.  G2 never needs more than
   one at a time at the moment.  If image reading becomes scheduled, then
   we may need to permit an arbitrary number of these, and should do the
   memory management on the LISP side. -fmw, 12/27/01 */

#define MAX_IMAGE_STREAMS 5

static ImageStream *allocate_image_stream ()
{
  int i;
  ImageStream *stream;
  static ImageStream image_streams[MAX_IMAGE_STREAMS];

  for(i=0; i<MAX_IMAGE_STREAMS; i++)
    {
      stream = &image_streams[i];
      if (!stream->in_use)
        {
          stream->in_use = True;
          stream->g2pointer = -1;
          stream->format = NULL;
          stream->width = 0;
          stream->height = 0;
          stream->depth = 1;        /* Bits per pixel */
          stream->position = 0;        /* File position */
          stream->user_data = 0;
          stream->ncolors = 0;
          stream->error = 0;
          stream->error_msg[0] = '\0';
          stream->transparentindex = -1; /* No transparency is the default */
          stream->started = 0;
          stream->jerr.stream = stream;
          return stream;
        }
    }
  return NULL;
}


static void free_image_stream (stream)
ImageStream *stream;
{
  stream->in_use = False;
}


/* True iff first n bytes of a[] and b[] are equal. */
static int buffer_equal (const unsigned char *a, const unsigned char *b, int n)
{
  while(n>0 && *a++ == *b++)
     n--;
  return (n == 0);
}

static ImageFileFormat *images_guess_format(FILE *fd)
{
  ImageFileFormat *ff;
  int i,n;
  unsigned char buffer[MAX_SIGNATURE_LENGTH];

  rewind(fd);
  n = read_image_bytes(buffer, MAX_SIGNATURE_LENGTH, fd);

  for(i=0; i<sizeof(image_file_formats)/sizeof(ImageFileFormat); i++) {
    ff=&image_file_formats[i];

    if (images_trace >= 2) {
      int j;
      printf("Format %s?", ff->name);
      for (j=0; j<ff->siglen; j++)
        printf(" %02x", ff->signature[j]);
      printf("\n");
    }

    if (n >= ff->siglen && buffer_equal((const unsigned char *)buffer, ff->signature, ff->siglen))
      return ff;
  }
  return NULL;
}


/* Restartable file operation. */
static long open_image_stream_1 (FILE *stream_arg, char *filename, FILE **fileptr, void *arg4)
{
  *fileptr = GFOPEN(filename, READ_BINARY);
  return *fileptr != NULL;
}

static int close_image_stream_internal (ImageStream *stream)
{
  if(stream->format->close != NULL)
    stream->format->close(stream);

  GFCLOSE(stream->file);
  if(stream->g2pointer >= 0)
    g2ext_decache_g2pointer(stream->g2pointer);
  free_image_stream(stream);
  NOTICE_FD_CLOSE();
  return 0;
}

static char *read_file_error_string (void)
{
  /* TODO: other platforms with strerror() */
#if defined(WIN32) || defined(sparcsol) || defined(linux)
  return strerror(errno);
#else
  return "Can't read file";
#endif
}

/* Returns NULL on success, a statically allocatederror message on failure. */
static const char *open_image_stream_internal (char *pathname, ImageStream **streamp)
{
  ImageFileFormat *ff;
  ImageStream *stream;
  FILE *file = NULL;
  static char buf[256];

  *streamp = NULL;
  if(g2ext_str_directory_p(pathname) == 1)
    return "File is a directory.";

  if (!g2ext_retry_file_operation(open_image_stream_1, NULL, pathname, &file, NULL)) {
    sprintf(buf, "%s (errno=%d).", read_file_error_string(), errno);
    return buf;
  }

  if (images_trace)
    printf("Opened image file %s\n", pathname);

  /* Deduce the file format. */
  ff = images_guess_format(file);
  if(ff == NULL) {
    GFCLOSE(file);
    return "Unknown file format.";
  }

  if(ff->read_header == NULL) {
    if (images_trace >= 1) printf("Format = %s\n", ff->name);
    GFCLOSE(file);
    sprintf(buf, "%s image files are not yet suppported.", ff->name);
    return buf;
  }

  stream = allocate_image_stream();
  if (!stream) {
    GFCLOSE(file);
    return "Too many open image streams.";
  }

  stream->file = file;
  stream->format = ff;

  /* Read the file header */
  rewind(stream->file);
  if(stream->format->read_header(stream) == 0) {
    if(stream->error_msg[0])
      strncpy(buf, stream->error_msg, sizeof(buf)-1);
    else
      sprintf(buf, "Error reading %s file header.", ff->name);
    buf[sizeof(buf)-1] = '\0';
    close_image_stream_internal(stream);
    return buf;
  }

  *streamp = stream;
  return NULL;
}


/* g2ext_open_image_stream
 *
 * g2ext_open_image_stream returns either a G2pointer to an image stream,
 * if the file could be opened, or a negative integer to indicate an error.
 *
 * The error message associated with the error is returned in the given
 * error buffer, of supplied.
 *
 * Note that the fixnum 0 is a valid G2pointer.
 *
 * If the stream is opened successully, it must be filled-in with values from
 * the image header (width, height, depth, etc).
 */
long g2ext_open_image_stream (char *pathname, char *errbuf, long errlen)
{
  ImageStream *stream;
  const char *error;

  error = open_image_stream_internal(pathname, &stream);
  if(error) {
    strncpy(errbuf, error, errlen-1);
    errbuf[errlen-1] = '\0';
    return -1;
  } else {
    return (stream->g2pointer = g2ext_cache_cpointer((Cpointer)stream));
  }
}


long g2ext_close_image_stream (G2pointer istream)
{
  return close_image_stream_internal(GetImageStream(istream));
}


/* Return the size, in bytes, of the uncompressed image associated
 * with this image stream.
 * We pack 8 one-bit pixels per byte.
 * Otherwise, use 1-3 bytes per pixel.
 * Not currently used by LISP.
 */
long g2ext_image_stream_size(G2pointer istream)
{
  ImageStream *stream = GetImageStream(istream);

  switch(stream->depth)
    {
    case 1:
      return stream->height * (stream->width + 7)/LISP_SCANLINE;
    case 8:
      return stream->height * stream->width;
    case 16:
      return stream->height * stream->width * 2;
    case 24:
      return stream->height * stream->width * 3;
    default:
      return -1;                /* Is LISP ready for this? */
    }
}


/* Return stream format as a small integer. */
long g2ext_image_stream_format (G2pointer istream)
{
  ImageStream *stream = GetImageStream(istream);

  if(stream->format == NULL)
    return 0;
  else
    return stream->format->number;
}


long g2ext_image_stream_height (G2pointer istream)
{
  ImageStream *stream = GetImageStream(istream);

  return stream->height;
}


long g2ext_image_stream_width(G2pointer istream)
{
  ImageStream *stream = GetImageStream(istream);
  return stream->width;
}


long g2ext_image_stream_depth (G2pointer istream)
{
  ImageStream *stream = GetImageStream(istream);
  return stream->depth;
}


long g2ext_image_stream_ncolors (G2pointer istream)
{
  ImageStream *stream = GetImageStream(istream);
  return stream->ncolors;
}

/* Return the color map index which should be considered
 * transparent.  Only GIFs support this at the moment. */
long g2ext_image_stream_transparentindex (G2pointer istream)
{
  ImageStream *stream = GetImageStream(istream);
  return stream->transparentindex;
}

/* Return the index-th entry from the color map.
 * Each entry is a packed RGB 24 bit integer. */
long g2ext_image_stream_color_map (G2pointer istream, long index)
{
  ImageStream *stream = GetImageStream(istream);

  if (index <0 || stream->ncolors < index)
    return -1;
  else
    return stream->colormap[index];
}


/* g2ext_image_stream_error returns the last error code for the stream,
 * and copies any associated error text into the buffer. */
long g2ext_image_stream_error (G2pointer istream, char *buffer, long buflen)
{
  ImageStream *stream = GetImageStream(istream);

  if(buflen > 0) {
    strncpy(buffer, stream->error_msg, buflen-1);
    buffer[buflen-1] = '\0';
  }
  return stream->error;
}


/* An internal function called for all errors.
 * Print message to stderr and save into stream's buffer.
 * Multiple messages are delimited by newlines. */
static void images_note_error(ImageStream *stream, const char *context, char *msg)
{
  int n;

  /* Send it to stderr, adding a newline */
  if(images_trace)
    fprintf(stderr, "[%s] %s\n", context, msg);

  /* And stash it in the stream's error buffer. */
  n = strlen(stream->error_msg);
  if(n < MAX_ERROR_MSGLEN-3) {
    if(n > 0) {
      stream->error_msg[n++] = '.';
      stream->error_msg[n++] = ' ';
    }
    strncpy(stream->error_msg+n, msg, MAX_ERROR_MSGLEN-n-1);
  }
}


/* g2ext_read_image_row fills the buffer with the next scan line
   from the image.  The stream MUST be positioned AFTER its header to read the
   first row of data.  Pixels are either 8 bits or packed 1 bit
   and are in the order required by XCreate{Bit,Pix}mapFromData.

     One bit images are packed 8 pixels/byte.  All other depths are
   stored with one pixel per byte or three bytes per pixel.

   The buffer is assumed to be large enough to hold that many scan lines.
   Returns the number of BYTES read or -1 if some error.
   --- Should allow reading any number of rows into any size buffer.
   */
long g2ext_read_image_row (G2pointer istream, unsigned char *buffer, long buflen)
{
  ImageStream *stream = GetImageStream(istream);

  return stream->format->read_row(stream,buffer,buflen);
}




/* File reading routines for images, with multiple retries. */
static long read_image_bytes_1 (FILE *stream,
                                char *name_arg,
                                char **start_ptr,
                                char *end)
{
  char *start = *start_ptr;
  start += fread(start, 1, end - start, stream);
  *start_ptr = start;
  return start == end;
}

/* Note that this is NOT used by the JPEG reader. */
static int read_image_bytes(unsigned char *buffer,
                            int nbytes,
                            FILE *stream)
{
  char *start = (char *)&buffer[0];
  char *original_start = start;
  char *end = start + nbytes;
  int i, rc = 0;
  static int counter = 0;

  g2ext_retry_file_operation(read_image_bytes_1, stream, NULL, &start, end);
  rc = start - original_start;

  if (images_trace >= 3) {
    counter++;
    printf("Image read #%03d: %d/%d bytes: ", counter, rc, nbytes);
    for (i=0; i<rc; i++) {
      if (i%16 == 0 && rc>10)
        printf("\n %3d: ", i);
      printf ("%02x ", buffer[i]);
    }
    printf("\n");
  }
  return rc;
}

static long images_getc_1(FILE *stream, char *name_arg, long *character_ptr, void *arg3)
{
  return EOF != (*character_ptr = fgetc(stream));
}

static int images_getc(FILE *file)
{
  long character;

  if (g2ext_retry_file_operation(images_getc_1, file, NULL, &character, NULL))
    return character;
  else
    return EOF;
}

static long images_fgets_1(FILE *stream, char *name_arg, char *line, int size)
{
  fgets(line, size, stream);
  return 1;
}

static char *images_fgets(char *line, int size, FILE *file)
{
  long rc;

  line[0] = '\0';
  rc = g2ext_retry_file_operation(images_fgets_1, file, NULL, line, size);
  if(line[0] == '\0')
    return NULL;
  return line;
}




/* Portable BitMap files */

/* Read the header of a Portable BitMap file and return non-zero on success. */

static int pbm_read_header (ImageStream *stream)
{
  FILE *file = stream->file;
  char line[256];
  int rc;

  /* Bitmap files look like:  P4\nwidth height\npacked data...*/
  /* Pixmap files look like:  P6\nwidth height\npixel_mask\npacked data... */

  line[0] = '\0';
  images_fgets(line, 256, file);
  if (strcmp(line,"P4\n"))        /* We only handle PBM files, not PPM. */
    return 0;

  do {
    line[0] = '\0';
    images_fgets(line, 256, file);
  } while (line[0] == '#');


  rc = sscanf(line,"%d %d", &stream->width, &stream->height);
  if (rc != 2)
    return 0;

  stream->depth = 1;                /* Not allowing PBM files */
  stream->transparentindex = 0; /* Allow use as a mask. */

  return 1;
}



/* pbm_read_row returns the number of bytes read if successful,
   or -1 on EOF. */

static int pbm_read_row (ImageStream *stream, unsigned char *buffer, long buflen)
{
  int nbytes = (stream->width + 7) / LISP_SCANLINE;
  unsigned char *cp;
  int i, nc;

  if (nbytes > 1024)                /* ?? */
    nbytes = 1024;

  nc = read_image_bytes(buffer, nbytes, stream->file);

  for (i=0, cp=buffer; i<nc; i++, cp++)
    *cp = bitreverse[*cp];

  return nc == nbytes ? nbytes : -1;
}



/* g2ext_reverse_bits_in_byte is used by G2 to reverse bits for printing.
   */
long g2ext_reverse_bits_in_byte (long n)
{
  if (n < 0 || n > 255)
    return 0;
  else
    return bitreverse[n];
}





/* XBM reading.
   This code has been copied from XmuReadBitmapData (in RdBitF.c in the Xmu lib).
   */
/*
 * $XConsortium: RdBitF.c,v 1.8 91/03/09 16:27:55 rws Exp $
 *
 * Copyright 1988 Massachusetts Institute of Technology
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of M.I.T. not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  M.I.T. makes no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 * M.I.T. DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL M.I.T.
 * BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */


#define MAX_SIZE 255

/* shared data for the image read/parse logic */
static short hexTable[256];                /* conversion value */
static int initialized = False;        /* easier to fill in at run time */


/*
 *        Table index for the hex values. Initialized once, first time.
 *        Used for translation value or delimiter significance lookup.
 */
static void initHexTable()
{
    /*
     * We build the table at run time for several reasons:
     *
     *     1.  portable to non-ASCII machines.
     *     2.  still reentrant since we set the init flag after setting table.
     *     3.  easier to extend.
     *     4.  less prone to bugs.
     */
    hexTable['0'] = 0;        hexTable['1'] = 1;
    hexTable['2'] = 2;        hexTable['3'] = 3;
    hexTable['4'] = 4;        hexTable['5'] = 5;
    hexTable['6'] = 6;        hexTable['7'] = 7;
    hexTable['8'] = 8;        hexTable['9'] = 9;
    hexTable['A'] = 10;        hexTable['B'] = 11;
    hexTable['C'] = 12;        hexTable['D'] = 13;
    hexTable['E'] = 14;        hexTable['F'] = 15;
    hexTable['a'] = 10;        hexTable['b'] = 11;
    hexTable['c'] = 12;        hexTable['d'] = 13;
    hexTable['e'] = 14;        hexTable['f'] = 15;

    /* delimiters of significance are flagged w/ negative value */
    hexTable[' '] = -1;        hexTable[','] = -1;
    hexTable['}'] = -1;        hexTable['\n'] = -1;
    hexTable['\t'] = -1;

    initialized = True;
}


/*
 *        read next hex value in the input stream, return -1 if EOF
 */
static int NextInt (fstream)
FILE *fstream;
{
    int        ch;
    int        value = 0;
    int gotone = 0;
    int done = 0;

    /* loop, accumulate hex value until find delimiter  */
    /* skip any initial delimiters found in read stream */

    while (!done) {
        ch = images_getc(fstream);
        if (ch == EOF) {
            value        = -1;
            done++;
        } else {
            /* trim high bits, check type and accumulate */
            ch &= 0xff;
            if (isascii(ch) && isxdigit(ch)) {
                value = (value << 4) + hexTable[ch];
                gotone++;
            } else if ((hexTable[ch]) < 0 && gotone)
              done++;
        }
    }
    return value;
}



/* This is derived from XmuReadBitmapDataFromFile */

static int xbm_read_header (ImageStream *stream)
{
  FILE *file = stream->file;
  char line[MAX_SIZE];                /* input line from file */
  char name_and_type[MAX_SIZE];        /* an input line */
  char *type;                        /* for parsing */
  int value;                        /* from an input line */
  int version10p;                /* boolean, old format */
  unsigned int ww = 0;                /* width */
  unsigned int hh = 0;                /* height */
  int hx = -1;                        /* x hotspot */
  int hy = -1;                        /* y hotspot */

  /* first time initialization */
  if (initialized == False) initHexTable();

  while (images_fgets(line, MAX_SIZE, file))
    {
      if (strlen(line) == MAX_SIZE-1)
        return 0;

      if (sscanf(line,"#define %s %d",name_and_type,&value) == 2)
        {
          if (!(type = strrchr(name_and_type, '_')))
            type = name_and_type;
          else
            type++;

          if (!strcmp("width", type))
            ww = (unsigned int) value;
          if (!strcmp("height", type))
            hh = (unsigned int) value;
          if (!strcmp("hot", type)) {
            if (type-- == name_and_type || type-- == name_and_type)
              continue;
            if (!strcmp("x_hot", type))
              hx = value;
            if (!strcmp("y_hot", type))
              hy = value;
          }
          continue;
        }

      if (sscanf(line, "static short %s = {", name_and_type) == 1)
        version10p = 1;
      else if (sscanf(line,"static unsigned char %s = {",name_and_type) == 1)
        version10p = 0;
      else if (sscanf(line, "static char %s = {", name_and_type) == 1)
        version10p = 0;
      else
        continue;

      if (!(type = strrchr(name_and_type, '_')))
        type = name_and_type;
      else
        type++;

/* This test was unnecessarily strict -- moon.bm would not load. */
/*       if (strcmp("bits[]", type)) */
/*         continue; */

      if (!ww || !hh)
        return 0;

      stream->width = ww;
      stream->height = hh;
      stream->user_data = version10p;
      stream->transparentindex = 0; /* Allow use as a mask. */
      return 1;
    }

  return 0;
}


static int xbm_read_row (ImageStream *stream, unsigned char *buffer, long buflen)
{
  FILE *fstream = stream->file;
  int ww = stream->width;
  int padding, bytes_per_line, size, bytes, value;
  unsigned char *ptr;
  int version10p = stream->user_data;

  if ((ww % 16) && ((ww % 16) < 9) && version10p)
    padding = 1;
  else
    padding = 0;

  bytes_per_line = (ww+7)/NBITS_IN_BYTE + padding;

  size = bytes_per_line;

  if (version10p)
    {
      for (bytes=0, ptr=buffer; bytes<size && bytes<buflen; bytes += 2)
        {
          if ((value = NextInt(fstream)) < 0)
            return -1;
          *(ptr++) = value;
          if (!padding || ((bytes+2) % bytes_per_line))
            if(bytes<buflen)
              *(ptr++) = value >> NBITS_IN_BYTE;
        }
    }
  else
    {
      for (bytes=0, ptr=buffer; bytes<size && bytes<buflen; bytes++, ptr++)
        {
          if ((value = NextInt(fstream)) < 0)
            return -1;
          *ptr=value;
        }
    }
  return bytes;
}






/*
   Gif Reader rdf
 */

#define GIF_READ_OK                   0   /* success */
#define GIF_READ_DONE                 1   /* no more images */

#define GIF_READ_ERROR_BAD_SCREEN_DESCRIPTOR        -1
#define GIF_READ_ERROR_BAD_SEPARATOR                -2
#define GIF_READ_ERROR_BAD_SIGNATURE                -3
#define GIF_READ_ERROR_EOD           -4   /* unexpected end of raster data */
#define GIF_READ_ERROR_EOF           -5   /* unexpected end of input stream */
#define GIF_READ_ERROR_CORRUPT       -6   /* Corrupted data: push_pixel overflow */

/* indices into the colormap */

#define GIF_RED_INDEX  0
#define GIF_GREEN_INDEX  1
#define GIF_BLUE_INDEX  2

/* typedef BYTE to eliminate confusion */

typedef unsigned char BYTE;

static int gif_read_open_file();
static int gif_read_open_image();
static int gif_read_next_pixel();
static int gif_read_load_colormap();
static int gif_read_next_data_block();
static int gif_read_push_string();
static int gif_read_add_string();

/* #defines, typedefs, and such
 */

#define GIF_SIGNATURE_LENGTH  6          /* GIF signature length */
#define GIF_SD_SIZE  7          /* GIF screen descriptor size */
#define GIF_ID_SIZE  9          /* GIF image descriptor size */

#define GIF_SEPARATOR   ','     /* GIF image separator */
#define GIF_EXTENSION   '!'     /* GIF extension block marker */
#define GIF_TERMINATOR  ';'     /* GIF terminator */

#define S_TABLE_SIZE  4096         /* string table size */
#define PIXEL_STACK_SIZE  4096         /* pixel stack size */

#define NULL_CODE  -1           /* integer null code */
#define NULL_BYTE_CODE  0xFF    /* string table null code */


/* macros  */

#define PUSH_PIXEL(stream,p)                                \
{                                                           \
  if (pixel_stack_index == PIXEL_STACK_SIZE)                \
   { \
    images_note_error(stream, "GIF", "(PUSH_PIXEL):pixel stack overflow");    \
    goto FATAL; \
   } \
  else                                                      \
    pixel_stack[pixel_stack_index++] = (p);                 \
}


static char *gif_sig    =  "GIF87a";
static char *gif_sig_89 =  "GIF89a";

static int  root_code_size;
static int  clear_code;
static int  end_of_information_code;
static int  current_code_size;
static int  current_code_mask;
static int  previous_code;

static long bit_buffer;          /* working bit buffer */
static int  bit_buffer_count;          /* working bit count */

static BYTE byte_buffer[256];           /* byte buffer */
static int  buffer_bytes;            /* byte count */
static int  buffer_index;            /* buffer index */

static int table_size;          /* string table size */
static int prefix[S_TABLE_SIZE];   /* string table : prefixes */
static int extension[S_TABLE_SIZE];   /* string table : extensions */

static BYTE pixel_stack[PIXEL_STACK_SIZE];    /* pixel stack */
static int  pixel_stack_index;           /* pixel stack pointer */


static int  gif_read_raster_width;          /* raster width */
static int  gif_read_raster_height;         /* raster height */
static BYTE gif_read_g_cmap_p;         /* global colormap flag */
static int  gif_read_g_pixel_bits;        /* bits per pixel, global colormap */
static int  gif_read_g_ncolors;           /* number of colors, global colormap */
static int  gif_read_bg_color;            /* background color index */
static int gif_transparent_color_index;
static int transparent_color_flag;
static int  gif_read_color_resolution;          /* bits of color resolution */

static int  gif_read_image_left;            /* image position on raster */
static int  gif_read_image_top;             /* image position on raster */
static int  gif_read_image_width;           /* image width */
static int  gif_read_image_height;          /* image height */
static BYTE gif_read_l_cmap_p;         /* local colormap flag */
static int  gif_read_l_pixel_bits;        /* bits per pixel, local colormap */
static int  gif_read_l_ncolors;           /* number of colors, local colormap */
static BYTE gif_read_interlace_p;      /* interlace image format flag */

/*
 * open a GIF file, using s as the input stream
 */
static int gif_read_open_file(ImageStream *stream)
{
  /* check GIF signature */
  if (read_image_bytes(byte_buffer, GIF_SIGNATURE_LENGTH, stream->file)
      != GIF_SIGNATURE_LENGTH)
    return GIF_READ_ERROR_EOF;

  if ((memcmp((char *) byte_buffer, gif_sig, GIF_SIGNATURE_LENGTH) != 0) &&
      (memcmp((char *) byte_buffer, gif_sig_89, GIF_SIGNATURE_LENGTH) != 0))
    return GIF_READ_ERROR_BAD_SIGNATURE;


  /* read and decode screen descriptor */
  if (read_image_bytes(byte_buffer, GIF_SD_SIZE, stream->file) != GIF_SD_SIZE)
    return GIF_READ_ERROR_EOF;

  gif_read_raster_width   = (byte_buffer[1] << NBITS_IN_BYTE) + byte_buffer[0];
  gif_read_raster_height  = (byte_buffer[3] << NBITS_IN_BYTE) + byte_buffer[2];
  gif_read_g_cmap_p  = (byte_buffer[4] & 0x80) ? 1 : 0;
  gif_read_color_resolution  = ((byte_buffer[4] & 0x70) >> 4) + 1;
  gif_read_g_pixel_bits = (byte_buffer[4] & 0x07) + 1;
  gif_read_bg_color     = byte_buffer[5];

  /* Must be non zero */
  if (byte_buffer[6] != 0)
    return GIF_READ_ERROR_BAD_SCREEN_DESCRIPTOR;

  /* load global colormap */
  if (gif_read_g_cmap_p)
  {
    gif_read_g_ncolors = (1 << gif_read_g_pixel_bits);

    if (gif_read_load_colormap(stream, gif_read_g_ncolors) != GIF_READ_OK)
      return GIF_READ_ERROR_EOF;
  }
  else
  {
    gif_read_g_ncolors = 0;
  }

  stream->width = gif_read_raster_width;
  stream->height = gif_read_raster_height;
  stream->ncolors = gif_read_g_ncolors;
  stream->depth = gif_read_g_pixel_bits;

  return GIF_READ_OK;
}


/*
 * open the next GIF image in the input stream; returns GIF_READ_OK if
 * successful. if there are no more images, returns GIF_READ_DONE.
 * if there are errors, it returns whatever errror code it can
 */
static int gif_read_open_image(ImageStream *stream)
{
  int i;
  int separator, introducer, first;
  FILE *file = stream->file;

  transparent_color_flag = 0;
  gif_transparent_color_index = -1;
  /* skip over any extension blocks */
  do
  {
    separator = images_getc(file);
    if (separator == GIF_EXTENSION)
    {
      /* GENSYMCID-987: Importing .gif into g2 without flaws
         Add check for Graphic Control Extension (spec-gif98a) */
      introducer = images_getc(file);
      first = 1;
     do
       {
         if (gif_read_next_data_block(file) != GIF_READ_OK)
           return GIF_READ_ERROR_EOF;

         /* transparent color index is held in the first block */
         if (introducer == 0xf9 && first) {
            /*Transparent flag is held in byte 1(zero since we strip the header), bit 0 */
            transparent_color_flag = (byte_buffer[0] & 0x01) ? 1 : 0;
            if (transparent_color_flag)
                gif_transparent_color_index = byte_buffer[3];
            first = 0;
         }
       }
     while (buffer_bytes > 0);
   /*return GIF_READ_OK;*/
    }
  }
  while (separator == GIF_EXTENSION);

  /* check for EOF  marker */
  if (separator == GIF_TERMINATOR)
    return GIF_READ_DONE;

  /* make sure there is  an image separator */
  if (separator != GIF_SEPARATOR)
    return GIF_READ_ERROR_BAD_SEPARATOR;

  /* read  descriptor */
  if (read_image_bytes(byte_buffer, GIF_ID_SIZE, file) != GIF_ID_SIZE)
    return GIF_READ_ERROR_EOF;

  /* decode descriptor */
  gif_read_image_left       = (byte_buffer[1] << NBITS_IN_BYTE) + byte_buffer[0];
  gif_read_image_top        = (byte_buffer[3] << NBITS_IN_BYTE) + byte_buffer[2];
  gif_read_image_width      = (byte_buffer[5] << NBITS_IN_BYTE) + byte_buffer[4];
  gif_read_image_height     = (byte_buffer[7] << NBITS_IN_BYTE) + byte_buffer[6];
  gif_read_l_cmap_p    = (byte_buffer[8] & 0x80) ? 1 : 0;
  gif_read_interlace_p = (byte_buffer[8] & 0x40) ? 1 : 0;
  gif_read_l_pixel_bits   = (byte_buffer[8] & 0x07) + 1;


  stream->width = gif_read_image_width;
  stream->height = gif_read_image_height;


  /* get local colormap */
  if (gif_read_l_cmap_p)
  {
    gif_read_l_ncolors = (1 << gif_read_l_pixel_bits);

    if (gif_read_load_colormap(stream, gif_read_l_ncolors) != GIF_READ_OK)
      return GIF_READ_ERROR_EOF;
  }
  else
  {
    gif_read_l_ncolors = 0;
  }

  /* initialize raster data stream decoder */
  root_code_size = images_getc(file);
  clear_code  = 1 << root_code_size;
  end_of_information_code  = clear_code + 1;
  current_code_size = root_code_size + 1;
  current_code_mask = (1 << current_code_size) - 1;
  bit_buffer_count = 0;
  bit_buffer = 0;
  buffer_bytes   = 0;
  buffer_index   = 0;

  /* initialize string table */
  for (i=0; i<S_TABLE_SIZE; i++)
  {
    prefix[i] = NULL_CODE;
    extension[i] = i;
  }

  /* initialize pixel stack */
  pixel_stack_index = 0;

  /* everything OK */
  return GIF_READ_OK;
}



/* try to read next pixel from the raster, */
/* return result in *pixel */

static int gif_read_next_pixel(ImageStream *stream, FILE *file, int *pixel)
{
  int  code;
  int  first_pixel;
  int  place;
  int  junk;

  /* get some pixels on the pixel stack */
  while (pixel_stack_index == 0)
  {
    /* load bytes until we have enough bits for another code */
    while (bit_buffer_count < current_code_size)
      {
        if (buffer_index == buffer_bytes)
          {
            /* read a new data block */
            if (gif_read_next_data_block(file) != GIF_READ_OK)
              return GIF_READ_ERROR_EOF;

            if (buffer_bytes == 0)
              return GIF_READ_ERROR_EOD;
          }

        bit_buffer |= ((long) byte_buffer[buffer_index++]) << bit_buffer_count;
        bit_buffer_count += 8;
      }

    /* get the next code */
    code        = bit_buffer & current_code_mask;
    bit_buffer >>= current_code_size;
    bit_buffer_count  -= current_code_size;

    /* interpret the code */
    if (code == clear_code)
      {
        /* reset decoder stream */
        current_code_size  = root_code_size + 1;
        current_code_mask  = (1 << current_code_size) - 1;
        previous_code  = NULL_CODE;
        table_size = end_of_information_code + 1;
      }
    else
      if (code == end_of_information_code)
        {
          /* Premature end of data */
          return GIF_READ_ERROR_EOF;
        }
      else
        if (previous_code == NULL_CODE)
          {
            junk = gif_read_push_string(stream,code);
            if (junk == GIF_READ_ERROR_CORRUPT) goto FATAL;
            previous_code = code;
          }
        else
          {
            if (code < table_size)
              {
                first_pixel = gif_read_push_string(stream,code);
              }
            else
              {
                place = pixel_stack_index;
                PUSH_PIXEL(stream,NULL_BYTE_CODE);
                first_pixel = gif_read_push_string(stream,previous_code);
                if (first_pixel == GIF_READ_ERROR_CORRUPT) goto FATAL;
                pixel_stack[place] = first_pixel;
              }

            gif_read_add_string(previous_code, first_pixel);
            previous_code = code;
          }
  }

  /* pop a pixel off the pixel stack */
  *pixel = (int) pixel_stack[--pixel_stack_index];
  return GIF_READ_OK;

 FATAL:
  return GIF_READ_ERROR_CORRUPT;
}



/* load a colormap from the stream  */

static int gif_read_load_colormap(ImageStream *stream, int color_count)
{
  int i;

  for (i=0; i<color_count; i++)
    {
      if (read_image_bytes(byte_buffer, 3, stream->file) != 3)
        return GIF_READ_ERROR_EOF;

      stream->colormap[i] = GENSYM_RGB(byte_buffer[GIF_RED_INDEX],
                                byte_buffer[GIF_GREEN_INDEX],
                                byte_buffer[GIF_BLUE_INDEX]);
    }

  stream->ncolors = color_count;

  return GIF_READ_OK;
}



/* read a new block of data from the input stream */

static int gif_read_next_data_block(FILE *file)
{
  /* read the data block header */
  buffer_bytes = images_getc(file);

  /* read the data block body */
  if (read_image_bytes(byte_buffer, buffer_bytes, file) != buffer_bytes)
    return GIF_READ_ERROR_EOF;

  buffer_index = 0;

  return GIF_READ_OK;
}

/*
 * push a string (denoted by a code) onto the pixel stack
 * (returns the code of the first pixel in the string)
 */

static int gif_read_push_string(ImageStream *stream, int code)
{
  int result;

  while (prefix[code] != NULL_CODE)
    {
      PUSH_PIXEL(stream,extension[code]);
      code = prefix[code];
    }

  PUSH_PIXEL(stream,extension[code]);
  result = extension[code];

  return result;

 FATAL:
  return GIF_READ_ERROR_CORRUPT;
}



/*
 * add a new string to the string table
 */

static int gif_read_add_string(int a_prefix, int an_extension)
{
  prefix[table_size] = a_prefix;
  extension[table_size] = an_extension;

  if ((table_size == current_code_mask) && (current_code_size < 12))
    {
      current_code_size += 1;
      current_code_mask  = (1 << current_code_size) - 1;
    }

  table_size += 1;
  return 0;
}

/* ------------------------------------------- */


/*** Our interface to the GIF reader. */

/* This needs *lots* of state vars, which may need to be slots in the stream! */
/* If we want to cache files in the KB in GIF format, then the GIF reader
   will have to be able to read from in-memory LISP buffers.
   */

static int gif_read_header (ImageStream *stream)
{
  if (gif_read_open_file(stream) != GIF_READ_OK) /* read GIF header */
    return 0;

  if (gif_read_open_image(stream) != GIF_READ_OK) /* read image header */
    return 0;

  if (stream->depth > 1 && stream->depth < DEPTH_EIGHT) /* FORCE 2-7 bit GIFs to be 8 bit */
    stream->depth = DEPTH_EIGHT;

  if (transparent_color_flag)
    stream->transparentindex = gif_transparent_color_index;
  else
    stream->transparentindex = -1;

  if (gif_read_interlace_p)
    {
      images_note_error(stream, "GIF", "Interlaced GIF images are not supported.");
      return 0;
    }
  else
    {
      return 1;
    }
}


/* If the bits per pixel is 1, pack them 8 per byte.
   (Joyous that 8 bit bytes can be assumed, no old CDC support)
 *  For all other sizes, we store just one pixel per byte.
   */
static int gif_read_row (ImageStream *stream, unsigned char *buffer, long buflen)
{
  int i, pixel;
  unsigned char *data;
  int width = stream->width;
  int bytes_read = 0;

  if (stream->position >= stream->height)
    return -1;

  if (stream->depth == 1)
    {
      int bits = 0;
      int sum = 0;
      data = buffer;
      for (i=0; i < stream->width; i++)
        {
          if (gif_read_next_pixel(stream,stream->file,&pixel) != GIF_READ_OK)
            {
              images_note_error(stream, "GIF", "Error getting next pixel.");
              return -1;
            }
          sum |= pixel<<bits;
          bits++;
          if (bits == 8)
            {
              *data++ = sum;
              bits = sum = 0;
            }
        }
      if (bits > 0)                /* didn't fill the complete byte  */
        *data++ = sum;
      bytes_read = data - buffer;
    }
  else
    {
      data = buffer;
      for (i=0; i < stream->width; i++)
        {
          if (gif_read_next_pixel(stream,stream->file,&pixel) != GIF_READ_OK)
            {
              images_note_error(stream, "GIF", "Error getting next pixel.");
              return -1;
            }
          *data++ = pixel;
        }
      bytes_read = width;
    }
  stream->position++;

  return bytes_read;
}





/***********************************************************************
 * JPEG/JFIF Reader using the Independent JPEG Group library  -fmw, 12/17/01
 ***********************************************************************/

void jpg_error (j_common_ptr cinfo)
{
  /* Get our error mgr */
  struct jpg_error_mgr *err = (struct jpg_error_mgr*) cinfo->err;
  ImageStream *stream = err->stream;

  /* Get the error message somehow */
  (*cinfo->err->output_message) (cinfo);

  /* Return control to the setjmp point */
  longjmp(stream->jmpbuf, 1);
}

/* Copied and modified from jerror.c */
void jpg_message (j_common_ptr cinfo)
{
  /* Get our error mgr */
  struct jpg_error_mgr *err = (struct jpg_error_mgr*) cinfo->err;
  ImageStream *stream = err->stream;
  char buffer[JMSG_LENGTH_MAX];

  /* Create the message */
  (*cinfo->err->format_message) (cinfo, buffer);

  /* Note it */
  images_note_error(stream, "JPEG", buffer);
}

/* Read the JFIF file header and fill in stream's width, height, and format */
static int jpg_read_header (ImageStream *stream)
{
  int i;
  struct jpeg_decompress_struct *cinfo = &stream->cinfo;
  struct jpg_error_mgr *jerr = &stream->jerr;

  /* Establish the setjmp return context. */
  if (setjmp(stream->jmpbuf))
    return 0;                        /* Error return. */

  /* We set up the normal JPEG error routines, then override error_exit. */
  cinfo->err = jpeg_std_error(&jerr->pub);
  jerr->pub.error_exit = jpg_error;
  jerr->pub.output_message = jpg_message;

  /* Create the decompresser */
  jpeg_create_decompress(cinfo);
  cinfo->err->trace_level = images_trace; /* Tracing */

  /* Data source is a FILE* */
  jpeg_stdio_src(cinfo, stream->file);

  /* Read file header, set default decompression parameters */
  (void) jpeg_read_header(cinfo, TRUE);

  stream->width = cinfo->image_width;
  stream->height = cinfo->image_height;

  /* cinfo->num_components is the number of bytes/pixel */
  if(cinfo->jpeg_color_space == JCS_GRAYSCALE) { /* todo: right way to get this? */
    stream->depth = 8;
    stream->ncolors = 256;        /* Create a linear colormap */
    for(i=0; i<255; i++)
      stream->colormap[i] = GENSYM_RGB(i,i,i);
  }
  else {
    stream->depth = 24;
    stream->ncolors = 0;        /* Means truecolor */
  }
  return 1;
}


/* Read one scan line from image stream into pre-allocated buffer.
 * Returns number of bytes read, or -1 on EOF */

static int jpg_read_row (ImageStream *stream, unsigned char *buffer, long buflen)
{
  struct jpeg_decompress_struct *cinfo = &stream->cinfo;
  int n;                        /* Number of bytes copied into buffer. */
  int stride;                        /* Number of bytes in buffer per image scanline. */
  JSAMPROW row;
  JSAMPARRAY buf = &row;

  /* Start decompressor */
  /* For progressive JPEG files, I think that this call reads the entire file. */
  if(stream->started == 0) {
    /* Returns true for PJPEG files */
    jpeg_has_multiple_scans(cinfo);     /* no-op? */
    jpeg_start_decompress(cinfo);
    stream->started++;
  }
  if (cinfo->output_scanline >= cinfo->output_height)
    return 0;                        /* EOF */

  row = buffer;
  stride = (stream->width * stream->depth + 7)/8;        /* JSAMPLEs per row in image_buffer */

  /* Establish the setjmp return context. */
  if (setjmp(stream->jmpbuf))
    return 0;                        /* Error return. */

  n = jpeg_read_scanlines(cinfo, buf, 1);

  return n*stride;
}


static int jpg_close(ImageStream *stream)
{
  struct jpeg_decompress_struct *cinfo = &stream->cinfo;

  /* Finish decompression and release memory.
   * I must do it in this order because output module has allocated memory
   * of lifespan JPOOL_IMAGE; it needs to finish before releasing memory. */

  if(stream->started)
    jpeg_finish_decompress(cinfo);

  jpeg_destroy_decompress(cinfo);

  return 0;
}




/*
 * JPEG compressor
 */

static void jpg_compression_error(j_common_ptr cinfo)
{
  jmp_buf *jmpbuf = (jmp_buf*) cinfo->client_data;
  char buffer[JMSG_LENGTH_MAX];

  (*cinfo->err->format_message) (cinfo, buffer);
  fprintf(stderr, "JPEG: %s\n", buffer);

  longjmp(*jmpbuf, 1);
}




/* PNG code starts here */

static int png_read_header(ImageStream *stream)
{
    static png_structp m_png_ptr;
    static png_infop m_info_ptr;
    char header[16];
    FILE *fp;

    assert(stream != NULL);
    assert(stream->format != NULL);
    assert(sizeof header >= stream->format->siglen);

    fp = stream->file;
    fread(header, 1, stream->format->siglen, fp);
    if (!png_check_sig(header, stream->format->siglen)) {
        return 0;
    }

    // initialize stuff
    m_png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!m_png_ptr) {
        return 0;
    }
    m_info_ptr = png_create_info_struct(m_png_ptr);
    if (!m_info_ptr) {
        return 0;
    }
    if (setjmp(png_jmpbuf(m_png_ptr))) {
        return 0;
    }

    png_init_io(m_png_ptr, fp);
    png_set_sig_bytes(m_png_ptr, stream->format->siglen);
    png_read_info(m_png_ptr, m_info_ptr);

    stream->width = png_get_image_width(m_png_ptr, m_info_ptr);
    stream->height = png_get_image_height(m_png_ptr, m_info_ptr);
    stream->depth = png_get_bit_depth(m_png_ptr, m_info_ptr);

    if (m_png_ptr->color_type == 4 || m_png_ptr->color_type == 0) {
        int i;
        stream->depth = 8;
        stream->ncolors = 256;        /* Create a linear colormap */
        for (i=0; i<255; i++) {
            stream->colormap[i] = GENSYM_RGB(i,i,i);
        }
    }
    else {
        stream->depth = 24;
        stream->ncolors = 0;        /* Means truecolor */
    }

    png_read_update_info(m_png_ptr, m_info_ptr);
    stream->png_ptr = m_png_ptr;
    stream->info_ptr = m_info_ptr;

    return 1;
}


static int png_read_row_local(ImageStream *stream, unsigned char *buffer, long buflen) {

	png_byte* row_pointer;
	png_size_t cols;

	 cols = png_get_rowbytes(stream->png_ptr, stream->info_ptr);
	 if (setjmp(png_jmpbuf(stream->png_ptr)))
         return 0;
	 row_pointer = buffer;
	 png_read_rows(stream->png_ptr, &row_pointer, png_bytepp_NULL, 1);

	  if(stream->png_ptr->row_number>=stream->height)
		  png_read_end(stream->png_ptr, stream->info_ptr);

	  return cols;
}

static int png_close(ImageStream *stream) {
	free(stream->png_ptr);
	free(stream->info_ptr);
	return 1;
}
/* The bitmap is a DIBSECTION on Win32, and an XImage Unix. */

#ifdef WIN32

static void *get_bitmap(int bigmap_index)
{
  HBITMAP hbm = (HBITMAP) g2ext_map_g2pointer_to_cpointer(bigmap_index);
  DIBSECTION *ds;
  int width, height;

  GdiFlush();

  ds = MakeInstance(DIBSECTION);
  GetObject(hbm, sizeof(DIBSECTION), ds);
  width = ds->dsBm.bmWidth;
  height = ds->dsBm.bmHeight;
  return (void *)ds;
}

static JSAMPROW getrow (void *bitmap, int i, int cx, int cy, JSAMPROW buf)
{
  DIBSECTION *ds = (DIBSECTION*) bitmap;
  int stride;
  unsigned char *row;
  int j,k;

  if(ds->dsBm.bmBits == NULL)        /* This means we have a DDB instead of a DIB. */
    return buf;

  /* Stride must be a multiple of 4 bytes, but it isn't always on Win2K! */
  stride = ds->dsBm.bmWidthBytes;
  stride = 4 * ((stride+3)/4);

  row = ((unsigned char *)(ds->dsBm.bmBits)) + i*stride; /* It's a top-down DIB. */

  k=0;
  for(j=0; j<3*cx; j+=3) {        /* TODO: Avoid this loop. */
    buf[k++] = row[j+2];        /* R */
    buf[k++] = row[j+1];        /* G */
    buf[k++] = row[j+0];        /* B */
  }
  return buf;
}

static void free_bitmap(void *bitmap)
{
  free(bitmap);
}

#else

static void *get_bitmap(int bigmap_index)
{
  PixmapStruct *gpixmap = (PixmapStruct *) g2ext_map_g2pointer_to_cpointer(bigmap_index);
  XImage *im;

  im = XGetImage(gpixmap->display_ptr, gpixmap->pixmap, 0,0,
                 gpixmap->width, gpixmap->height,
                 AllPlanes, ZPixmap);
  return (void *)im;
}

static JSAMPROW getrow (void *bitmap, int i, int cx, int cy, JSAMPROW buf)
{
  XImage *im = (XImage*) bitmap;
  int j,k;
  unsigned long pixel;

  k=0;
  for(j=0; j<cx; j++) {
    pixel = XGetPixel(im,j,i);             /* TODO: avoid this call. */
    buf[k++] = (pixel >> 0) & 0xFF;
    buf[k++] = (pixel >> 8) & 0xFF;
    buf[k++] = (pixel >> 16) & 0xFF;
  }
  return buf;
}

static void free_bitmap(void *bitmap)
{
  XDestroyImage((XImage*)bitmap);
}

#endif


#ifndef WIN32
extern GC g2pvt_get_pix_gc(GensymXWindow *gwindow, Pixmap pixmap, int width, int height, int depth);

static int x11_last_error;

static int x11_capture_error_code(Display *display, XErrorEvent *event)
{
  x11_last_error = event->error_code;
  return 0;
}
#endif


/*
 * g2ext_create_bigmap
 *
 * Creates a truecolor buffer bitmap for printing, if possible. Optimized (heh),
 * for larger images.
 */

long g2ext_create_bigmap(long window_index, long width, long height, long depth)
{
#ifdef WIN32
  BITMAPINFO bmi;
  LPBYTE pBits;
  HBITMAP hbm;
  extern HDC Ghdc;
  ZeroMemory(&bmi, sizeof(bmi));
  bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmi.bmiHeader.biWidth = width;
  bmi.bmiHeader.biHeight = -height; /* Want a top-down DIB. */
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biBitCount = 24; /* Always truecolor. */
  bmi.bmiHeader.biCompression = BI_RGB;
  hbm = CreateDIBSection(Ghdc, &bmi, DIB_RGB_COLORS, &pBits, NULL, 0);
  return hbm ? g2ext_cache_cpointer((long)hbm) : -1;
#else
  extern long g2ext_x11_screen_depth(long);
  long x11_depth;

  if (No_window)
      return -1;
  GensymXWindow *gwindow = (GensymXWindow *)g2ext_map_g2pointer_to_cpointer(window_index);
  Pixmap pixmap;
  PixmapStruct *gpixmap;
  XErrorHandler x11_last_handler = NULL;

  /* Create a pixmap, handling X errors. */
  x11_last_error = Success;
  x11_last_handler = XSetErrorHandler(x11_capture_error_code);
  x11_depth = g2ext_x11_screen_depth(window_index);
  pixmap = XCreatePixmap(gwindow->display_ptr, gwindow->xwindow, width, height,
                         (x11_depth < depth) ? x11_depth : depth);
  XSync(gwindow->display_ptr,False); /* Missing from g2ext_create_pixmap */
  XSetErrorHandler(x11_last_handler);

  if(x11_last_error != Success) {
    fprintf(stderr, "Failed to create %dx%dx%d pixmap: %d\n", (int) width,
            (int) height, (int) depth, (int) x11_last_error);
    return -1;
  }

  gpixmap = MakeInstance(PixmapStruct);
  if (gpixmap == NULL) {
    XFreePixmap(gwindow->display_ptr, pixmap);
    return -1;
  }

  gpixmap->gensym_x_window_ptr = gwindow;
  gpixmap->display_ptr = gwindow->display_ptr;
  gpixmap->pixmap = pixmap;
  gpixmap->gc = g2pvt_get_pix_gc(gwindow, pixmap, width, height, depth);
  gpixmap->xcolor = 0;
  gpixmap->width = width;
  gpixmap->height = height;
  gpixmap->depth = depth;
  return g2ext_cache_cpointer((long)gpixmap);
#endif
}


/*
 * g2ext_compress_image -- Write pixmap to stream in JPEG/JFIF format.
 *
 * FIXME: Assuming pixmap is 24bpp for now.
 */
long g2ext_compress_image(long stream_index, long bigmap_index, int cx, int cy, int quality)
{
  FILE *fd = (FILE *) g2ext_map_g2pointer_to_cpointer(stream_index);
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
  jmp_buf jmpbuf;
  int i;
  JSAMPROW buf = NULL;                        /* volatile ? */
  void *bitmap = NULL;

  memset(&cinfo, 0, sizeof(cinfo));
  memset(&jerr, 0, sizeof(jerr));

  cinfo.err = jpeg_std_error(&jerr);
  jerr.error_exit = jpg_compression_error;

  cinfo.client_data = &jmpbuf;

  if (setjmp(jmpbuf) != 0) {
    if (buf) free(buf);
    if (bitmap) free_bitmap(bitmap);
    return -2;
  }

  jpeg_create_compress(&cinfo);

  cinfo.image_width = cx;
  cinfo.image_height = cy;
  cinfo.input_components = 3;
  cinfo.in_color_space = JCS_RGB;
  jpeg_set_defaults(&cinfo);

  if (quality >= 0) jpeg_set_quality(&cinfo, quality, TRUE);
  /*if (progressive) jpeg_simple_progression (&cinfo); */

  buf = (JSAMPROW) calloc(cinfo.image_width * cinfo.input_components, sizeof(JSAMPLE));
  if (buf == NULL)
    return -3;

  bitmap = get_bitmap(bigmap_index);
  if(bitmap == NULL) {
    free(buf);
    return -4;
  }

  jpeg_stdio_dest(&cinfo, fd);
  jpeg_start_compress(&cinfo, TRUE);

  {
    /* TODO: User will want to customize this. */
    char comment[255];
    sprintf(comment, "CREATOR: Gensym G2 (via IJG JPEG %d.%d),",
            JPEG_LIB_VERSION/10, JPEG_LIB_VERSION%10);
    if (quality >= 0)
      sprintf(comment + strlen (comment), " quality = %d\n", quality);
    else
      strcat(comment + strlen (comment), " default quality\n");
    jpeg_write_marker(&cinfo, JPEG_COM, (unsigned char*)comment, strlen(comment));
  }

  for(i=0; i<cy; i++) {
    getrow(bitmap, i, cx, cy, buf);
    jpeg_write_scanlines(&cinfo, &buf, 1);
  }

  jpeg_finish_compress(&cinfo);
  jpeg_destroy_compress(&cinfo);
  free(buf);
  free_bitmap(bitmap);
  return 1;
}


/*
 * g2ext_get_pixmap_bits -- Retrieve pixmap's pixels into buffer.
 *
 * Return value: 1 if big endian, 0 if little endian, -1 on error.
 *
 */
long g2ext_get_pixmap_bits(long bigmap_index, long cx, long cy, long stride,
                           unsigned short *wide_string)
{
#ifdef WIN32
  int nbytes = cy*stride;
#endif
  void *bitmap = get_bitmap(bigmap_index);

  if(bitmap == NULL)
    return -1;

#ifdef WIN32
  {
    DIBSECTION *ds = (DIBSECTION *) bitmap;
    GdiFlush();
    if(ds->dsBm.bmBits != NULL)
      memcpy((void *)wide_string, (void *)ds->dsBm.bmBits, nbytes);
  }
#else
  {
    XImage *im = (XImage*) bitmap;
    unsigned char *p = (unsigned char *)wide_string;
    int x,y,k;
    unsigned long pixel;

    if(im->depth == 24)                /* TODO: Pseudo-color X servers */
      for(y=0; y<cy; y++) {
        k = y*stride;
        for(x=0; x<cx; x++) {
          pixel = XGetPixel(im,x,y);
          p[k++] = (pixel >> 16) & 0xFF; /* B */    /* FIXME: Check rgb masks in XImage !! */
          p[k++] = (pixel >>  8) & 0xFF; /* G */
          p[k++] = (pixel >>  0) & 0xFF; /* R */
        }
      }
    else {
      fprintf(stderr, "Image depth of %d is not supported.\n", im->depth);
    }
  }
#endif
  free_bitmap(bitmap);
  return BIG_ENDIAN_P;
}


/* g2ext_get_truecolor_pixel
 *
 * Given a buffer of pixels as created above, return the x,y-th pixel, as
 * a 24-bit BGR value.
 */
long g2ext_get_truecolor_pixel(unsigned short *wide_string, long x, long y, long stride)
{
  unsigned char *buf = (unsigned char *)wide_string;
  int k = 3*x + stride*y;
  return buf[k]<<16 | buf[k+1]<<8 | buf[k+2];
}





/* test main */

#ifdef IMAGES_MAIN

#include <stdio.h>
#include <math.h>

#ifdef WIN32
double sec(void) {return (double)time(NULL);}
#else
#include <sys/time.h>

/* Note: there is some very similar code, including a similar (but not identical)
 * function also named describe_image_stream, in test-cprim.c.  -jv, 12/17/07
 */
void describe_image_stream(G2pointer istream)
{
  ImageStream *stream = GetImageStream(istream);

  printf("%ldx%ldx%ld, bytes %ld, format %ld (%s)\n",
         g2ext_image_stream_width(istream), g2ext_image_stream_height(istream),
         g2ext_image_stream_depth(istream), g2ext_image_stream_size(istream),
         g2ext_image_stream_format(istream), stream->format->name);
/*   OutputDebugString(buf); */
}

double sec(void) {
    struct timeval   buffer;

    gettimeofday(&buffer, NULL);

    return buffer.tv_sec + buffer.tv_usec/1.0e6;
}
#endif


/* Stubs for G2 functions. */

#include <sys/types.h>
#include <sys/stat.h>

#if defined(WIN32)
long g2ext_str_directory_p(fname)
     char *fname;
{
    long retval;
    struct stat     s;
    return 0;
    /**
    if (stat(fname,&s) != -1) {
        retval = ( S_ISDIR(s.st_mode) ?  1 : 0L );
    } else {
        retval = -1;
    }
    return (retval);
    **/
}
#else
static long cc_g2_stream_directory_p_1 (stream_arg, fname, stat_ptr, arg4)
  FILE *stream_arg;
  char *fname;
  struct stat *stat_ptr;
  void *arg4;
{
  return -1 != stat(fname,stat_ptr);
}

long g2ext_str_directory_p(fname)
     char *fname;
{
  struct stat s;

  if (g2ext_retry_file_operation(cc_g2_stream_directory_p_1, NULL, fname, &s, NULL))
    return S_ISDIR(s.st_mode) ?  1 : 0L;
  else
    return -1;
}
#endif

G2pointer g2ext_cache_cpointer(Cpointer ptr)
{
  return((G2pointer) ptr);
}

long g2ext_map_g2pointer_to_cpointer(G2pointer gptr)
{
  return((Cpointer)gptr);
}

void g2ext_decache_g2pointer(G2pointer ptr)
{
}


int g2ext_too_many_fds;

void g2ext_unset_too_many_fds() {}

long g2ext_retry_file_operation(function,stream_arg,name_arg,arg3,arg4)
  long (*function)();
  FILE *stream_arg;
  char *name_arg;
  void *arg3,*arg4;

{
  return (*function) (stream_arg, name_arg, arg3, arg4);
}

int jpg_trace_memory = 0;

/* Images test program. */
int main(int argc, char **argv)
{
  G2pointer istream;
  unsigned char *buffer, *cp;
  int i,j,n,m,k;
  int width, height, depth, size;
  int verbose = 0;
  double start, stop, total = 0;
  char *filename;
  char error[256];
  extern int jpg_trace_memory;        /* Added to jmemnobs.c */

  if (argc <= 1) {
    printf("Usage: %s [-v] [-m] [-t] image-filename\n", argv[0]);
    exit(1);
  }

  k=1;

  if (!strcmp(argv[k],"-v")) {
    verbose++;
    k++;
  }

  while(!strcmp(argv[k],"-m")) {
    jpg_trace_memory++;
    k++;
  }

  while(!strcmp(argv[k],"-t")) {
    images_trace++;
    k++;
  }

  for(k=k; k<argc; k++) {
    filename = argv[k];

    printf("%-45s", filename);
    fflush(stdout);

    start = sec();
    error[0] = '\0';
    istream = g2ext_open_image_stream(filename, error, sizeof(error));

    if (istream < 0)
      printf("** Error: %s **\n", error);
    else {
      width = g2ext_image_stream_width(istream);
      height = g2ext_image_stream_height(istream);
      depth = g2ext_image_stream_depth(istream);
      size = g2ext_image_stream_size(istream);

      cp = buffer = (unsigned char *)malloc(size);
        m=0;
      while ((n = g2ext_read_image_row(istream,cp,size-(cp-buffer))) > 0) {
        cp += n;
        m++;
      }

      stop = sec();
      total += stop-start;
      printf(" %6.3lfsec ", stop-start);
      if (m<height)
        printf("Error: read only %d rows out of %d\n", m, height);

      describe_image_stream(istream);

      if (verbose) {                /* Dump image bytes. */
        cp = buffer;
        for (i=0; i<height; i++) {
          for (j=0; j< (width + 7) /8; j++)
            printf("0x%02x ", *cp++);
          printf("\n");
        }
      }
      g2ext_close_image_stream(istream);
    }
  }
  printf("%-25s %6.3lfsec\n", "Total time", total);
  return 1;
}

/* gcc -g -Dsparcsol -DIMAGES_MAIN images.c -L../../jpeg/opt -ljpeg -I../../jpeg/c -o images */
/* cc -DIMAGES_MAIN images.c -o images.exe */

#endif /* IMAGES_MAIN */
