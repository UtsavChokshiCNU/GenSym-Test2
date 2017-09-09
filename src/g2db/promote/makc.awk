# Format output from showsum to create contents.txt
/\/contents.txt/ { next }
{ cl = $1 }
{ if (match($1,sd) == 1 && sd == "/") cl = substr($1,length(sd)+1) }
{ if (match($1,sd) == 1 && sd != "/") cl = substr($1,length(sd)+2) }
{ if (match($1,"./") == 1) cl = substr($1,3) }
{ fnm[NR] = cl
  fl2[NR] = $2
  fl3[NR] = $3
  if (length(cl) > max1) max1 = length(cl)
  if (length($2) > max2) max2 = length($2)
  if (length($3) > max3) max3 = length($3)
}
END {
  for (i = 1 ; i <= NR ; i++) 
    if (length(fnm[i]) > 0) printf("%-*s %*s %*s\n", max1, fnm[i], max2, fl2[i], max3, fl3[i])
}
