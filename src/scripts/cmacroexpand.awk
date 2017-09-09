# jh, 5/3/93.  awk command to print last contiguous block of nonempty lines.
# used by cmacroexpand shell script in <sandbox>/scripts
{ if ( $0 == "" )
   newlines = 1
  else
   { if (newlines == 1)
      { newlines = 0
        ind = 0 }
     line[ind] = $0 
     ind++ } }
END { for (i = 0; i < ind ; i++)
       print line[i] }



