#include <stdio.h>
#ifdef MSDOS
#include <stdlib.h>
#include <string.h>
#endif
#include "spdo_prv.h"
#include "hp_readr.h"
#include "pcl5fnt.h"

#ifndef SEEK_SET
#define SEEK_CUR 1
#define SEEK_END 2
#define SEEK_SET 0
#endif

/*
 * mpc@gensym.com  8-10-93:   Declare this function before it is
 *     called. Watcom somehow barfs on param types, causing an error
 *     when this is first called.
 */
#ifdef MSDOS
void  mbyte (char *, char *, fix31);
#endif

/*** EXTERNAL FUNCTIONS ***/
#ifdef MSDOS
extern boolean fill_font_buffer PROTO((ufix8 **ptr, ufix32 size, FILE *fp));
#endif


/*** STATIC VARIABLES ***/
#define  ESC_FNDESC  1
#define  ESC_CHARID  2
#define  ESC_CHDESC  3
#define  NO_ESCAPE   0
#define  ESC_UNKN   -1
#define  ESC_EOF    -2


typedef  struct
    {
    ufix8  *font;
    ufix16  last_index;
    fix31  *char_offset;
    }   dir_t;

static dir_t    char_dir;
static boolean  pcl_font_loaded = FALSE;
PC5HEAD  pcl5head;

typedef fix31 fix;

/***  STATIC FUNCTIONS ***/
static  fix31  filesize PROTO((FILE *fd));

 fix  pf_load_pcl_font(pathname, eo_font)
  char  *pathname;
  eofont_t  *eo_font;

{
real     arg;
char     buffer[4096];
fix      char_index;
fix      chsize;
FILE      *fd;
fix31    ll;
boolean     ok;
fix      escape_seq();
boolean  load_header();


/* I replaced
     if ((fd = fopen(pathname, "rb")) < 0)
   with the following line.  The SGI (strict ansi) compiler
   objected to comparing the result of fopen with 0 using <.
   Fopen is defined to return NULL if the attempt to open
   the named file fails.  --mhd, 4/22/93
   */

if ((fd = fopen(pathname, "rb")) == NULL)
    {
    printf("\nCan't open file %s\n\n", pathname);
    return(0);
    }
ll = filesize(fd);
#ifdef MSDOS
ok = fill_font_buffer(&char_dir.font, ll, fd);
if (!ok)
{
    fprintf(stderr,"Error reading font file\n");
    close(fd);
    return(FALSE);
}
#else
char_dir.font = (ufix8 *)malloc(ll);
if (char_dir.font == NULL)
    {
    printf("MALLOC fail %s line %d\n", __FILE__, __LINE__);
    goto abort;
    }
if (fread(char_dir.font, 1, ll, fd) != ll)
    {
    printf("\nRead Error (%s)!\n\n", pathname);
    goto abort;
    }
#endif

fseek(fd, (fix31)0, 0);
ok = TRUE;
while (ok)
    {
    switch (escape_seq(fd, &arg))
        {
        case ESC_FNDESC:
            if ((fix)arg < 4096)
                {
                fread(buffer, 1, (fix)arg, fd);
                load_header(buffer, &pcl5head);
                char_dir.last_index = (127 > pcl5head.last_code) ? 127 : pcl5head.last_code;
                ll = (char_dir.last_index + 1) * 4;
                char_dir.char_offset = (fix31 *)malloc(ll);
                if (char_dir.char_offset == NULL)
                    {
                    printf("MALLOC fail %s line %d\n", __FILE__, __LINE__);
                    goto abort;
                    }
                for (ll=0; ll <= char_dir.last_index; ll++)
                    char_dir.char_offset[ll] = 0;
                }
            break;
        case ESC_CHARID:
            char_index = (fix15)arg;
            break;
        case ESC_CHDESC:
            chsize = (fix)arg;
            char_dir.char_offset[char_index] = ftell(fd);
            fseek(fd, (fix31)chsize, 1);
            break;
        case NO_ESCAPE:
            printf("Escape character not found\n");
            goto abort;
            break;
        case ESC_EOF:
            ok = FALSE;
            break;
        case ESC_UNKN:
        default:
            printf("Unrecognized escape sequence\n");
            goto abort;
            break;
        }
    }
eo_font->resolution = pcl5head.scale_factor;
eo_font->unique_id = 17;
eo_font->eofont = &char_dir;
pcl_font_loaded = TRUE;
return(1);

abort:
  fclose(fd);
  return(0);
}


/*
 static  fix  escape_seq(fd, arg)
 - removed static -mhd@gensym, 4/25/93
 */
 fix  escape_seq(fd, arg)
  FILE *fd;
  real  *arg;

/* Moves file pointer beyond the escape sequence, if there is one.
   If there is no escape code in the first character, or if the escape
   sequence is unrecognized, the file pointer is left unchanged. */

{
char    buf[4];
fix     code;
fix31   curpos;
fix     dpt;
real    ftemp;
fix     ii;
boolean    minus;
boolean is_num();


curpos = fseek(fd, 0L, 1);
if (fread (buf, 1, 1, fd) != 1)
    return (ESC_EOF);
if (*buf != 0x1B)
    {
    fseek(fd, curpos, 0);
    return (NO_ESCAPE);
    }

fread (buf, 1, 2, fd);                      /* look for "*c", "(s", or ")s" */
if (strncmp( "*c", buf, 2 ) == 0)
    code = ESC_CHARID;
else if (strncmp( ")s", buf, 2 ) == 0)
    code = ESC_FNDESC;
else if (strncmp( "(s", buf, 2 ) == 0)
    code = ESC_CHDESC;
else
    {
    fseek(fd, curpos, 0);
    return (ESC_UNKN);
    }

fread (buf, 1, 1, fd);
for (*arg=0.0, minus=FALSE, dpt=0; is_num(*buf); fread (buf, 1, 1, fd))
    {
    if (*buf == '-')
        minus = TRUE;
    else if (*buf == '.')
        dpt = 1;
    else
        {
        if (!dpt)
            *arg = *arg * 10 + (*buf - '0');
        else
            {
            for (ftemp = *buf, ii=0; ii<dpt; ii++)
                ftemp /= 10.0;
            *arg += ftemp;
            dpt++;
            }
        }
    }
if (code == ESC_CHARID  &&  *buf == 'E')
    return (code);
else if ((code == ESC_FNDESC  ||  code == ESC_CHDESC)  &&  *buf == 'W')
    return (code);
else
    {
    fseek(fd, curpos, 0);
    return (ESC_UNKN);
    }
}


/*
  static  boolean  load_header (buffer, pcl5head)
  - removed static -- this seemed to help the sgi compiler
  --mhd@gensym, 4/25/93
  */
boolean  load_header (buffer, pcl5head)
  char     *buffer;
  PC5HEAD  *pcl5head;

{
ufix16  temp16;
void    mbyte();


pcl5head->size = GET_WORD(buffer);
pcl5head->dformat = buffer[2];
pcl5head->font_type = buffer[3];
temp16 = (buffer[4] << 8) | (ufix8)buffer[23];
pcl5head->style.structure = (temp16 & 0x3E0) >> 5;
pcl5head->style.width = (temp16 & 0x1C) >> 2;
pcl5head->style.posture = (temp16 & 3);
pcl5head->baseline = GET_WORD((buffer+6));
pcl5head->cell_width = GET_WORD((buffer+8));
pcl5head->cell_height = GET_WORD((buffer+10));
pcl5head->orientation = buffer[12];
pcl5head->spacing = buffer[13];
pcl5head->symbol_set = GET_WORD((buffer+14));
pcl5head->pitch = GET_WORD((buffer+16));
pcl5head->height = GET_WORD((buffer+18));
pcl5head->x_height = GET_WORD((buffer+20));
pcl5head->width_type = buffer[22];
pcl5head->stroke_weight = buffer[24];
temp16 = (buffer[26] << 8) | (ufix8)buffer[25];
pcl5head->typeface.vendor = (temp16 & 0x7800) >> 11;
pcl5head->typeface.version = (temp16 & 0x0600) >> 9;
pcl5head->typeface.value = (temp16 & 0x01FF);
pcl5head->serif_style = buffer[27];
pcl5head->quality = buffer[28];
pcl5head->placement = buffer[29];
pcl5head->uline_dist = buffer[30];
pcl5head->uline_height = buffer[31];
pcl5head->text_height = GET_WORD((buffer+32));
pcl5head->text_width = GET_WORD((buffer+34));
pcl5head->first_code = GET_WORD((buffer+36));
pcl5head->last_code = GET_WORD((buffer+38));
pcl5head->pitch_extend = buffer[40];
pcl5head->height_extend = buffer[41];
pcl5head->cap_height = GET_WORD((buffer+42));
pcl5head->font_vendor_code = buffer[44];
pcl5head->font_number = GET_WORD((buffer+46)) + (((ufix32)(buffer[45])) << 16);
mbyte (buffer+48, pcl5head->fontname, 16);
pcl5head->scale_factor = GET_WORD((buffer+64));
pcl5head->x_resolution = GET_WORD((buffer+66));
pcl5head->y_resolution = GET_WORD((buffer+68));
pcl5head->mstr_uline_pos = (fix15)GET_WORD((buffer+70));
pcl5head->mstr_uline_hght = GET_WORD((buffer+72));
pcl5head->threshold = GET_WORD((buffer+74));
pcl5head->italic_angle = (fix15)GET_WORD((buffer+76));
pcl5head->scal_data_size = GET_WORD((buffer+78));
pcl5head->nobtf = GET_WORD((buffer + 80 + pcl5head->scal_data_size));
pcl5head->copyright = (char *)malloc(pcl5head->nobtf - 2);
pcl5head->checksum = GET_WORD((buffer + 80 + pcl5head->scal_data_size + pcl5head->nobtf));
return(TRUE);
}


 eo_char_t  *eo_get_char_addr (PARAMS2 eofont, index)
  GDECL
  dir_t  *eofont;
  ufix16  index;

{

if (index <= eofont->last_index)
    {
    if (eofont->char_offset[index] > 0)
        return((eo_char_t *)(eofont->font + eofont->char_offset[index]));
    else
        return(NULL);
    }
else
    return(NULL);
}


 pf_get_nr_font_chars()
{
return((fix)pcl5head.last_code);
}


/*
 static  void  mbyte (source, dest, count)
  - removed static -- this seemed to help the sgi compiler
  --mhd@gensym, 4/25/93
  */
void  mbyte (source, dest, count)
  char   *source;
  char   *dest;
  fix31   count;

/*  MBYTE (SOURCE, DEST, COUNT)
 *
 *  Arguments:
 *    source - address of source array
 *    dest - address of destination array
 *    count - number of bytes to be moved
 *  Returns:  nothing
 *
 *  Moves 'count' bytes from the source array to the destination array
 *  Error handling:
 *    If 'count' less than zero, does nothing
 *    Will crash if 'source', or 'dest' don't point to valid memory location
 */

    {
    fix31   i;
    char   *sarr, *darr;

    
    if (count <= 0)
        return;

    if (source > dest)
        {
        for (i=0; i<count; i++)
            *dest++ = *source++;
        }
    else
        {
        sarr = (char *) (source + count);
        darr = (char *) (dest + count);
        for (i=0; i<count; i++)
            *(--darr) = *(--sarr);
        }

    return;
    }


 static  fix31  filesize(fd)
  FILE   *fd;                     /* file descriptor */

{
fix31  nn;

fseek(fd,(long)0,SEEK_END);
nn = ftell(fd);
fseek(fd,0L,SEEK_SET);
return(nn); 
}



/*
 static  boolean  is_num(c)
  - removed static -- this seemed to help the sgi compiler
  --mhd@gensym, 4/25/93
  */
boolean  is_num(c)
  char  c;
{
if (c >= '0'  &&  c <= '9')
    return(TRUE);
else if (c == '-')
    return(TRUE);
else if (c == '.')
    return(TRUE);
else
    return(FALSE);
}

pf_unload_font()
{
	free(char_dir.font);
}
