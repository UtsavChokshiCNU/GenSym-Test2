;;;; Run Released G2 version


(defconst released-g2-versions
    '(
      ("G2 Test" .
       "/gensym/ut/g2-test/g2 -name \"G2-Test\" -fonts /gensym/ut/fonts-test/  -kfepmain /gensym/ut/g2-test/main.dic -kfepindex /gensym/ut/g2-test/index.dic -kfepkojin /gensym/ut/g2-test/kojin.dic")
      ("G2 Shipping" .
       "/gensym/ut/g2-shipping/g2 -name \"G2-Shipping\" -fonts /gensym/ut/fonts-shipping/  -kfepmain /gensym/ut/g2-shipping/main.dic -kfepindex /gensym/ut/g2-shipping/index.dic -kfepkojin /gensym/ut/g2-shipping/kojin.dic")
      ("G2 Latest" .
       "/gensym/udev/g2-latest/g2 -name \"G2-Latest\" -fonts /gensym/udev/fonts-latest/  -kfepmain /gensym/udev/g2-latest/main.dic -kfepindex /gensym/udev/g2-latest/index.dic -kfepkojin /gensym/udev/g2-latest/kojin.dic")



      ("8.3 (Rev. 1)" .
       "/gensym/ut/g2-83r1/g2 -ok $G2V83_OK -name \"G2-83r1\" -fonts /gensym/ut/fonts-83r1/ -module-search-path /gensym/ut/kbs-83r1/utils -kfepmain /gensym/ut/g2-83r1/main.dic -kfepindex /gensym/ut/g2-83r1/index.dic -kfepkojin /gensym/ut/g2-83r1/kojin.dic  -netinfo")
      ("8.3 (Rev. 0)" .
       "/gensym/ut/g2-83r0/g2 -ok $G2V83_OK -name \"G2-83r0\" -fonts /gensym/ut/fonts-83r0/ -module-search-path /gensym/ut/kbs-83r0/utils -kfepmain /gensym/ut/g2-83r0/main.dic -kfepindex /gensym/ut/g2-83r0/index.dic -kfepkojin /gensym/ut/g2-83r0/kojin.dic  -netinfo")
      ("8.3 (Beta Rev. 0)" .
       "/gensym/ut/g2-83b0/g2 -ok $G2V83_OK -name \"G2-83b0\" -fonts /gensym/ut/fonts-83b0/ -module-search-path /gensym/ut/kbs-83b0/utils -kfepmain /gensym/ut/g2-83b0/main.dic -kfepindex /gensym/ut/g2-83b0/index.dic -kfepkojin /gensym/ut/g2-83b0/kojin.dic  -netinfo")
      ("8.3 (Alpha Rev. 1)" .
       "/gensym/ut/g2-83a1/g2 -ok $G2V8_OK -name \"G2-83a1\" -fonts /gensym/ut/fonts-83a1/ -module-search-path /gensym/ut/kbs-83a1/utils -kfepmain /gensym/ut/g2-83a1/main.dic -kfepindex /gensym/ut/g2-83a1/index.dic -kfepkojin /gensym/ut/g2-83a1/kojin.dic  -netinfo")
      ("8.2 (Rev. 4)" .
       "/gensym/ut/g2-82r4/g2 -ok $G2V8_OK -name \"G2-82r4\" -fonts /gensym/ut/fonts-82r4/ -module-search-path /gensym/ut/kbs-82r4/utils -kfepmain /gensym/ut/g2-82r4/main.dic -kfepindex /gensym/ut/g2-82r4/index.dic -kfepkojin /gensym/ut/g2-82r4/kojin.dic  -netinfo")
      ("8.2 (Rev. 3)" .
       "/gensym/ut/g2-82r3/g2 -ok $G2V8_OK -name \"G2-82r3\" -fonts /gensym/ut/fonts-82r3/ -module-search-path /gensym/ut/kbs-82r3/utils -kfepmain /gensym/ut/g2-82r3/main.dic -kfepindex /gensym/ut/g2-82r3/index.dic -kfepkojin /gensym/ut/g2-82r3/kojin.dic  -netinfo")
      ("8.2 (Rev. 2)" .
       "/gensym/ut/g2-82r2/g2 -ok $G2V8_OK -name \"G2-82r2\" -fonts /gensym/ut/fonts-82r2/ -module-search-path /gensym/ut/kbs-82r2/utils -kfepmain /gensym/ut/g2-82r2/main.dic -kfepindex /gensym/ut/g2-82r2/index.dic -kfepkojin /gensym/ut/g2-82r2/kojin.dic  -netinfo")
      ("8.2 (Rev. 1)" .
       "/gensym/ut/g2-82r1/g2 -ok $G2V8_OK -name \"G2-82r1\" -fonts /gensym/ut/fonts-82r1/ -module-search-path /gensym/ut/kbs-82r1/utils -kfepmain /gensym/ut/g2-82r1/main.dic -kfepindex /gensym/ut/g2-82r1/index.dic -kfepkojin /gensym/ut/g2-82r1/kojin.dic  -netinfo")
      ("8.2 (Rev. 0)" .
       "/gensym/ut/g2-82r0/g2 -ok $G2V8_OK -name \"G2-82r0\" -fonts /gensym/ut/fonts-82r0/ -module-search-path /gensym/ut/kbs-82r0/utils -kfepmain /gensym/ut/g2-82r0/main.dic -kfepindex /gensym/ut/g2-82r0/index.dic -kfepkojin /gensym/ut/g2-82r0/kojin.dic  -netinfo")
      ("8.2 (Alpha Rev. 0)" .
       "/gensym/ut/g2-82a0/g2 -ok $G2V8_OK -name \"G2-82a0\" -fonts /gensym/ut/fonts-82a0/ -module-search-path /gensym/ut/kbs-82a0/utils -kfepmain /gensym/ut/g2-82a0/main.dic -kfepindex /gensym/ut/g2-82a0/index.dic -kfepkojin /gensym/ut/g2-82a0/kojin.dic  -netinfo")
      ("8.1 (Rev. 1)" .
       "/gensym/ut/g2-81r1/g2 -ok $G2V8_OK -name \"G2-81r1\" -fonts /gensym/ut/fonts-81r1/ -module-search-path /gensym/ut/kbs-81r1/utils -kfepmain /gensym/ut/g2-81r1/main.dic -kfepindex /gensym/ut/g2-81r1/index.dic -kfepkojin /gensym/ut/g2-81r1/kojin.dic  -netinfo")
      ("8.1 (Rev. 0)" .
       "/gensym/ut/g2-81r0/g2 -ok $G2V8_OK -name \"G2-81r0\" -fonts /gensym/ut/fonts-81r0/ -module-search-path /gensym/ut/kbs-81r0/utils -kfepmain /gensym/ut/g2-81r0/main.dic -kfepindex /gensym/ut/g2-81r0/index.dic -kfepkojin /gensym/ut/g2-81r0/kojin.dic  -netinfo")
      ("8.1 (Beta Rev. 0)" .
       "/gensym/ut/g2-81b0/g2 -ok $G2V8_OK -name \"G2-81b0\" -fonts /gensym/ut/fonts-81b0/ -module-search-path /gensym/ut/kbs-81b0/utils -kfepmain /gensym/ut/g2-81b0/main.dic -kfepindex /gensym/ut/g2-81b0/index.dic -kfepkojin /gensym/ut/g2-81b0/kojin.dic  -netinfo")
      ("8.1 (Alpha Rev. 0)" .
       "/gensym/ut/g2-81a0/g2 -ok $G2V8_OK -name \"G2-81a0\" -fonts /gensym/ut/fonts-81a0/ -module-search-path /gensym/ut/kbs-81a0/utils -kfepmain /gensym/ut/g2-81a0/main.dic -kfepindex /gensym/ut/g2-81a0/index.dic -kfepkojin /gensym/ut/g2-81a0/kojin.dic  -netinfo")
      ("8.0 (Rev. 1)" .
       "/gensym/ut/g2-80r1/g2 -ok $G2V8_OK -name \"G2-80r1\" -fonts /gensym/ut/fonts-80r1/ -module-search-path /gensym/ut/kbs-80r1/utils -kfepmain /gensym/ut/g2-80r1/main.dic -kfepindex /gensym/ut/g2-80r1/index.dic -kfepkojin /gensym/ut/g2-80r1/kojin.dic  -netinfo")
      ("8.0 (Rev. 0)" .
       "/gensym/ut/g2-80r0/g2 -ok $G2V8_OK -name \"G2-80r0\" -fonts /gensym/ut/fonts-80r0/ -module-search-path /gensym/ut/kbs-80r0/utils -kfepmain /gensym/ut/g2-80r0/main.dic -kfepindex /gensym/ut/g2-80r0/index.dic -kfepkojin /gensym/ut/g2-80r0/kojin.dic  -netinfo")

      ;; adding -netinfo command line option starting with G2 7.1r0, the first
      ;; release to support it. (shows [<host>:<port>] on title bar) (MHD 11/14/03)
      ("7.1 (Rev. 2)" .
       "/gensym/ut/g2-71r2/g2 -name \"G2-71r2\" -fonts /gensym/ut/fonts-71r2/ -module-search-path /gensym/ut/kbs-71r2/utils -kfepmain /gensym/ut/g2-71r2/main.dic -kfepindex /gensym/ut/g2-71r2/index.dic -kfepkojin /gensym/ut/g2-71r2/kojin.dic  -netinfo")

      ("7.1 (Rev. 1)" .
       "/gensym/ut/g2-71r1/g2 -name \"G2-71r1\" -fonts /gensym/ut/fonts-71r1/ -module-search-path /gensym/ut/kbs-71r1/utils -kfepmain /gensym/ut/g2-71r1/main.dic -kfepindex /gensym/ut/g2-71r1/index.dic -kfepkojin /gensym/ut/g2-71r1/kojin.dic  -netinfo")

      ("7.1 (Rev. 0)" .
       "/gensym/ut/g2-71r0/g2 -name \"G2-71r0\" -fonts /gensym/ut/fonts-71r0/ -module-search-path /gensym/ut/kbs-71r0/utils -kfepmain /gensym/ut/g2-71r0/main.dic -kfepindex /gensym/ut/g2-71r0/index.dic -kfepkojin /gensym/ut/g2-71r0/kojin.dic  -netinfo")


      ("7.0 (Rev. 1)" .
       "/gensym/ut/g2-70r1/g2 -name \"G2-70r1\" -fonts /gensym/ut/fonts-70r1/ -module-search-path /gensym/ut/kbs-70r1/utils -kfepmain /gensym/ut/g2-70r1/main.dic -kfepindex /gensym/ut/g2-70r1/index.dic -kfepkojin /gensym/ut/g2-70r1/kojin.dic")
      ("7.0 (Rev. 0)" .
       "/gensym/ut/g2-70r0/g2 -name \"G2-70r0\" -fonts /gensym/ut/fonts-70r0/ -module-search-path /gensym/ut/kbs-70r0/utils -kfepmain /gensym/ut/g2-70r0/main.dic -kfepindex /gensym/ut/g2-70r0/index.dic -kfepkojin /gensym/ut/g2-70r0/kojin.dic")
      ))

(defconst older-g2-versions
    '(
      ("6.2 (Rev. 3)" .
       "/gensym/ut/g2-62r3/g2 -name \"G2-62r3\" -fonts /gensym/ut/fonts-62r3/ -module-search-path /gensym/ut/kbs-62r3/utils -kfepmain /gensym/ut/g2-62r3/main.dic -kfepindex /gensym/ut/g2-62r3/index.dic -kfepkojin /gensym/ut/g2-62r3/kojin.dic")
      ("6.2 (Rev. 2)" .          ; NOTE: there was only an internal release of r1
       "/gensym/ut/g2-62r2/g2 -name \"G2-62r2\" -fonts /gensym/ut/fonts-62r2/ -module-search-path /gensym/ut/kbs-62r2/utils -kfepmain /gensym/ut/g2-62r2/main.dic -kfepindex /gensym/ut/g2-62r2/index.dic -kfepkojin /gensym/ut/g2-62r2/kojin.dic")
      ("6.2 (Rev. 0)" .
       "/gensym/ut/g2-62r0/g2 -name \"G2-62r0\" -fonts /gensym/ut/fonts-62r0/ -module-search-path /gensym/ut/kbs-62r0/utils -kfepmain /gensym/ut/g2-62r0/main.dic -kfepindex /gensym/ut/g2-62r0/index.dic -kfepkojin /gensym/ut/g2-62r0/kojin.dic")
      ("6.1 (Rev. 0)" .
       "/gensym/ut/g2-61r0/g2 -name \"G2-61r0\" -fonts /gensym/ut/fonts-61r0/ -module-search-path /gensym/ut/kbs-61r0/utils -kfepmain /gensym/ut/g2-61r0/main.dic -kfepindex /gensym/ut/g2-61r0/index.dic -kfepkojin /gensym/ut/g2-61r0/kojin.dic")
      ("6.0 (Rev. 1)" .
       "/gensym/ut/g2-60r1/g2 -name \"G2-60r1\" -fonts /gensym/ut/fonts-60r1/ -module-search-path /gensym/ut/kbs-60r1/utils -kfepmain /gensym/ut/g2-60r1/main.dic -kfepindex /gensym/ut/g2-60r1/index.dic -kfepkojin /gensym/ut/g2-60r1/kojin.dic")
      ("6.0 (Rev. 0)" .
       "/gensym/ut/g2-60r0/g2 -name \"G2-60r0\" -fonts /gensym/ut/fonts-60r0/ -module-search-path /gensym/ut/kbs-60r0/utils -kfepmain /gensym/ut/g2-60r0/main.dic -kfepindex /gensym/ut/g2-60r0/index.dic -kfepkojin /gensym/ut/g2-60r0/kojin.dic")

      ("5.1 (Rev. 13)" .
       "/gensym/ut/g2-51r13/g2 -name \"G2-51r13\" -fonts /gensym/ut/fonts-51r13/ -module-search-path /gensym/ut/kbs-51r13/utils -kfepmain /gensym/ut/g2-51r13/main.dic -kfepindex /gensym/ut/g2-51r13/index.dic -kfepkojin /gensym/ut/g2-51r13/kojin.dic")
      ("5.1 (Rev. 12)" .
       "/gensym/ut/g2-51r12/g2 -name \"G2-51r12\" -fonts /gensym/ut/fonts-51r12/ -module-search-path /gensym/ut/kbs-51r12/utils -kfepmain /gensym/ut/g2-51r12/main.dic -kfepindex /gensym/ut/g2-51r12/index.dic -kfepkojin /gensym/ut/g2-51r12/kojin.dic")
      ("5.1 (Rev. 11)" .
       "/gensym/ut/g2-51r11/g2 -name \"G2-51r11\" -fonts /gensym/ut/fonts-51r11/ -module-search-path /gensym/ut/kbs-51r11/utils -kfepmain /gensym/ut/g2-51r11/main.dic -kfepindex /gensym/ut/g2-51r11/index.dic -kfepkojin /gensym/ut/g2-51r11/kojin.dic")
      ("5.1 (Rev. 10)" .
       "/gensym/ut/g2-51r10/g2 -name \"G2-51r10\" -fonts /gensym/ut/fonts-51r10/ -module-search-path /gensym/ut/kbs-51r10/utils -kfepmain /gensym/ut/g2-51r10/main.dic -kfepindex /gensym/ut/g2-51r10/index.dic -kfepkojin /gensym/ut/g2-51r10/kojin.dic")
      ("5.1 (Rev. 9)" .
       "/gensym/ut/g2-51r9/g2 -name \"G2-51r9\" -fonts /gensym/ut/fonts-51r9/ -module-search-path /gensym/ut/kbs-51r9/utils -kfepmain /gensym/ut/g2-51r9/main.dic -kfepindex /gensym/ut/g2-51r9/index.dic -kfepkojin /gensym/ut/g2-51r9/kojin.dic")
      ("5.1 (Rev. 8)" .
       "/gensym/ut/g2-51r8/g2 -name \"G2-51r8\" -fonts /gensym/ut/fonts-51r8/ -module-search-path /gensym/ut/kbs-51r8a/utils -kfepmain /gensym/ut/g2-51r8/main.dic -kfepindex /gensym/ut/g2-51r8/index.dic -kfepkojin /gensym/ut/g2-51r8/kojin.dic")
      ("5.1 (Rev. 7)" .
       "/gensym/ut/g2-51r7/g2 -name \"G2-51r7\" -fonts /gensym/ut/fonts-51r7/ -module-search-path /gensym/ut/kbs-51r7/utils -kfepmain /gensym/ut/g2-51r7/main.dic -kfepindex /gensym/ut/g2-51r7/index.dic -kfepkojin /gensym/ut/g2-51r7/kojin.dic")
      ("5.1 (Rev. 6)" .
       "/gensym/ut/g2-51r6/g2 -name \"G2-51r6\" -fonts /gensym/ut/fonts-51r6/ -module-search-path /gensym/ut/kbs-51r6/utils -kfepmain /gensym/ut/g2-51r6/main.dic -kfepindex /gensym/ut/g2-51r6/index.dic -kfepkojin /gensym/ut/g2-51r6/kojin.dic")
      ("5.1 (Rev. 5)" .
       "/gensym/ut/g2-51r5/g2 -name \"G2-51r5\" -fonts /gensym/ut/fonts-51r5/ -module-search-path /gensym/ut/kbs-51r5/utils -kfepmain /gensym/ut/g2-51r5/main.dic -kfepindex /gensym/ut/g2-51r5/index.dic -kfepkojin /gensym/ut/g2-51r5/kojin.dic")
      ("5.1 (Rev. 4)" .
       "/gensym/ut/g2-51r4/g2 -name \"G2-51r4\" -fonts /gensym/ut/fonts-51r4/ -module-search-path /gensym/ut/kbs-51r4/utils -kfepmain /gensym/ut/g2-51r4/main.dic -kfepindex /gensym/ut/g2-51r4/index.dic -kfepkojin /gensym/ut/g2-51r4/kojin.dic")
      ("5.1 (Rev. 3)" .
       "/gensym/archives/g2-51r3/g2 -name \"G2-51r3\" -fonts /gensym/ut/fonts-51r3/ -kfepmain /gensym/archives/g2-51r3/main.dic -kfepindex /gensym/archives/g2-51r3/index.dic -kfepkojin /gensym/archives/g2-51r3/kojin.dic")
      ("5.1 (Rev. 2)" .
       "/gensym/archives/g2-51r2/g2 -name \"G2-51r2\" -fonts /gensym/ut/fonts-51r2/ -kfepmain /gensym/archives/g2-51r2/main.dic -kfepindex /gensym/archives/g2-51r2/index.dic -kfepkojin /gensym/archives/g2-51r2/kojin.dic")
      ("5.1 (Rev. 1)" .
       "/gensym/archives/g2-51r1/g2 -name \"G2-51r1\" -fonts /gensym/ut/fonts-51r1/ -kfepmain /gensym/archives/g2-51r1/main.dic -kfepindex /gensym/archives/g2-51r1/index.dic -kfepkojin /gensym/archives/g2-51r1/kojin.dic")
      ("5.1 (Rev. 0)" .
       "/gensym/archives/g2-51r0/g2 -name \"G2-51r0\" -fonts /gensym/ut/fonts-51r0/ -kfepmain /gensym/archives/g2-51r0/main.dic -kfepindex /gensym/archives/g2-51r0/index.dic -kfepkojin /gensym/archives/g2-51r0/kojin.dic")
      ("5.0 (Rev. 3)" .
       "/gensym/archives/g2-50r3/g2 -name \"G2-50r3\" -fonts /gensym/ut/fonts-50r3/ -kfepmain /gensym/archives/g2-50r3/main.dic -kfepindex /gensym/archives/g2-50r3/index.dic -kfepkojin /gensym/archives/g2-50r3/kojin.dic")
      ("5.0 (Rev. 2)" .
       "/gensym/archives/g2-50r2/g2 -name \"G2-50r2\" -fonts /gensym/ut/fonts-50r2/ -kfepmain /gensym/archives/g2-50r2/main.dic -kfepindex /gensym/archives/g2-50r2/index.dic -kfepkojin /gensym/archives/g2-50r2/kojin.dic")
      ("5.0 (Rev. 1)" .
       "/gensym/archives/g2-50r1/g2 -name \"G2-50r1\" -fonts /gensym/ut/fonts-50r1/ -kfepmain /gensym/archives/g2-50r1/main.dic -kfepindex /gensym/archives/g2-50r1/index.dic -kfepkojin /gensym/archives/g2-50r1/kojin.dic")
      ("5.0 (Rev. 0)" .
       "/gensym/archives/g2-50r0/g2 -name \"G2-50r0\" -fonts /gensym/ut/fonts-50r0/ -kfepmain /gensym/archives/g2-50r0/main.dic -kfepindex /gensym/archives/g2-50r0/index.dic -kfepkojin /gensym/archives/g2-50r0/kojin.dic")

      ("4.1 (Rev. 1)" .
       "/gensym/archives/g2-41r1/g2 -name \"G2-41r1\" -fonts /gensym/archives/g2-41r1/fonts/ -kfepmain /gensym/archives/g2-41r1/main.dic -kfepindex /gensym/archives/g2-41r1/index.dic -kfepkojin /gensym/archives/g2-41r1/kojin.dic")
      ("4.1 (Rev. 0)" .
       "/gensym/archives/g2-41r0/g2 -name \"G2-41r0\" -fonts /gensym/archives/g2-41r0/fonts/ -kfepmain /gensym/archives/g2-41r0/main.dic -kfepindex /gensym/archives/g2-41r0/index.dic -kfepkojin /gensym/archives/g2-41r0/kojin.dic")

      ("4.0 (Rev. 3, H23)" .
       "/gensym/ut/g2-40r3-H23/g2 -name \"G2-40r3\" -fonts /gensym/ut/g2-40r3-H23/fonts/ -kfepmain /gensym/ut/g2-40r3-H23/main.dic -kfepindex /gensym/ut/g2-40r3-H23/index.dic -kfepkojin /gensym/ut/g2-40r3-H23/kojin.dic")
      ("4.0 (Rev. 2, C26)" .
       "/gensym/ut/g2-40r2-C26/g2 -name \"G2-40r2\" -fonts /gensym/ut/g2-40r2-C26/fonts/ -kfepmain /gensym/ut/g2-40r2-C26/main.dic -kfepindex /gensym/ut/g2-40r2-C26/index.dic -kfepkojin /gensym/ut/g2-40r2-C26/kojin.dic")
      ("4.0 (Rev. 1)" .
       "/gensym/archives/g2-40r1/g2 -name \"G2-40r1\" -fonts /gensym/archives/g2-40r1/fonts/ -kfepmain /gensym/archives/g2-40r1/main.dic -kfepindex /gensym/archives/g2-40r1/index.dic -kfepkojin /gensym/archives/g2-40r1/kojin.dic")

;;These don't actually work at the moment.  Keeping them around in comments in
;;case we decide to figure out what's wrong with eship. --yduJ 9/13/04
;;      ("3.0 Rev. 9" .
;;       "/gensym/ut/g2-30r9/g2 -name \"G2-30r9\" -kfepmain /gensym/ut/g2-30r9/KFEP-MAIN.DIC -kfepindex /gensym/ut/g2-30r9/KFEP-INDEX.DIC -kfepkojin /gensym/ut/g2-30r9/KFEP-KOJIN.DIC")
;;      ("3.0 Rev. 3" .
;;       "/gensym/ut/g2-30r3/g2 -name \"G2-30r3\" -kfepmain /gensym/ut/g2-30r3/KFEP-MAIN.DIC -kfepindex /gensym/ut/g2-30r3/KFEP-INDEX.DIC -kfepkojin /gensym/ut/g2-30r3/KFEP-KOJIN.DIC")
      ))

;; Removed the command line args requesting that OK files in the local directories
;; be loaded.  These looked like
;;
;;    -ok /gensym/ut/g2-30r3/g2.ok
;;
;; These OK files are not good.  Using the environment variable G2_OK, which everyone
;; surely has by now, is much better.  If this fails to work out, at least change the
;; args to
;;
;;    -ok /home/ab/g2.ok
;;
;; This should be a superset of the OKs in the /gensym/ut/* release directories.
;; It's loadable in 3.0 Rev. 0 without any problems as far as I know.  (MHD
;; 8/30/94)


(defun run-some-g2 (version-vector &optional revision)
  "Spawn a released version of G2.  Defaults to the latest in the field, 3.0r0"
  (interactive (list (completing-read "G2 version: " released-g2-versions)))
  (if (null revision)
      (setq revision (car version-vector)))
  (let ((command (cdr (assoc revision version-vector))))
    (shell-command (format "nohup %s &" command))))

(defun run-released-g2 (&optional revision)
  (run-some-g2 released-g2-versions revision))

(defun run-older-g2 (&optional revision)
  (run-some-g2 older-g2-versions revision))



;;;; Gensym menu


(defun add-g2-versions-to-gensym-menu ()
  (let ((versions released-g2-versions)
	(version nil))
    (while (setq version (car versions))
      (setq versions (cdr versions))
      (let ((version-name (car version)))
	(add-menu-button '("Gensym" "Run Released G2")
			 (vector version-name
				 (list 'run-released-g2 version-name)
				 t))))))


(defun add-older-g2-versions-to-gensym-menu ()
  (let ((versions older-g2-versions)
	(version nil))
    (while (setq version (car versions))
      (setq versions (cdr versions))
      (let ((version-name (car version)))
	(add-menu-button '("Gensym" "Run Older Released G2")
			 (vector version-name
				 (list 'run-older-g2 version-name)
				 t))))))

(defun lisp-file-in-lisp-mode-p ()
  (and (eq major-mode 'lisp-mode)
       (string-match "\\.lisp\\'" (buffer-name (current-buffer)))))

(defvar helpdesk-password "gensym")
(defun run-telewindows-to-helpdesk ()
  "Spawn TW (latest version) connecting to the Helpdesk (host helpdesk at 1300)"
  (interactive)
  (shell-command 
    (format "nohup %s helpdesk 1300 -icon Bugsy -name HelpDesk -password %s -background /home/development/config/bug.xbm &"
	    tw-for-helpdesk helpdesk-password)))



(if (lucid-platform-p)
    (add-menu-button '("Gensym") (vector "Lucid" 'lucid t)))
(if (allegro-platform-p)
    (add-menu-button '("Gensym") (vector "Allegro" 'allegro t)))

(add-menu-button '("Gensym") (vector "Helpdesk" 'run-telewindows-to-helpdesk t))
(add-menu-button '("Gensym") (vector "Eternal Recompile" 'warnings-from-external-recompile t))
(add-menu-button '("Gensym") (vector "Find Translated C" 'find-translated-c '(lisp-file-in-lisp-mode-p)))
(add-menu-button '("Gensym" "GDB") (vector "current (ab build) G2" '(run-debuggable-image 'g2) t))
(add-menu-button '("Gensym" "GDB") (vector "current (ab build) TW" '(run-debuggable-image 'tw) t))
(add-menu-button '("Gensym" "GDB") (vector "eternal translate G2"
					   '(run-eternal-translate-debuggable-image 'g2) t))
(add-menu-button '("Gensym" "GDB") (vector "eternal translate TW"
					   '(run-eternal-translate-debuggable-image 'tw) t))
(add-g2-versions-to-gensym-menu)
(add-older-g2-versions-to-gensym-menu)

(cond ((not (boundp 'gensym-lisp-fontify-mode))
       (setq gensym-lisp-fontify-mode 'default)))

(defconst gensym-fontify-menu
    '(["None" gensym-no-lisp-highlighting
       :style radio
       :selected (eq gensym-lisp-fontify-mode 'none)]
      ["Default" gensym-default-lisp-highlighting
       :style radio
       :selected (eq gensym-lisp-fontify-mode 'default)]
      ["Control Structure" gensym-more-lisp-highlighting
       :style radio
       :selected (eq gensym-lisp-fontify-mode 'more)]))

(add-menu '("Gensym") "Syntax Highlighting" gensym-fontify-menu)

(add-menu-button '("Build") (vector "AB Build Summary" (list 'view-file-simple ab-build-summary-log) t))
(add-menu-button '("Build") (vector "AB Build Machines" (list 'view-file-simple ab-build-machines) t))
(add-menu-button '("Build") (vector "AB Regression Summary" (list 'view-file-simple ab-regression-summary-log) t))
(add-menu-button '("Build") (vector "AB commitlog" (list 'view-file-simple ab-repository-commitlog) t))
(add-menu-button '("Build") (vector "Eternal Translate Build Summary" (list 'view-file-simple et-build-summary-log) t))
(add-menu-button '("Build") (vector "Eternal Translate Regression Summary" (list 'view-file-simple et-regression-summary-log) t))
(add-menu-button '("Build") (vector "AB-9oct95  commitlog" (list 'view-file-simple ab9-repository-commitlog) t))


(add-hook 'activate-menubar-hook 'activate-gensym-menu-hook)

(defun activate-gensym-menu-hook ()
  (cond (current-menubar
	 (let ((places (car (find-menu-item current-menubar '("Places")))))
	   (cond (places
		  (build-places-menu places)))
	   nil))))


(defun add-places-menu ()
  (save-excursion
    (set-buffer "*scratch*")
    (add-menu-button '("Places") (vector "Empty" '(lambda ()) t))))

(add-places-menu)


(defun go-to-marker (marker)
  (let ((buffer (marker-buffer marker)))
    (cond (buffer
	   (switch-to-buffer buffer)
	   (goto-char (marker-position marker))))))


(defun trim-trailing-whitespace (string)
  (cond ((string-match "\\w" string)
	 (substring string (max 0 (1- (match-beginning 0)))))
	(t
	 string)))

(defun menu-of-places-to-go ()
  (let ((markers (mapcar 'cdr register-alist)) ; tag-mark-stack1
	(menu-items ()))
    (while markers
      (let* ((mrk (car markers))
	     buffer
	     start
	     end)
	(cond ((not (markerp mrk)))
	      ((null (setq buffer (marker-buffer mrk))))
	      ((or (string-match "\\` " (buffer-name buffer))
		   (string-match "\\`\\*" (buffer-name buffer))))
	      (t
	       (save-excursion
		 (set-buffer buffer)
		 (goto-char (marker-position mrk))
		 (beginning-of-line)
		 (setq start (point))
		 (end-of-line)
		 (setq end (point))
		 (if (> end start)
		     (let ((line (format "%s: %s"
					 (upcase (pathname-name (buffer-name buffer)))
					 (trim-trailing-whitespace
					   (buffer-substring start (min end (+ start 40)))))))

		       (setq menu-items
			     (cons (vector line (list 'go-to-marker mrk) t) menu-items))))))))
	(setq markers (cdr markers)))
    (nreverse menu-items)))


;; Better: a hierarchical menu, first on module names, then on places.  Each
;; place is the name of a function we compiled (or that we did some important
;; editor command upon, such as editing it).

(defun build-places-menu (places-menu)
  (let ((items (menu-of-places-to-go)))
    (cond ((equal items (cdr places-menu))
	   t)				; return t meaning "no change"
	  ((null places-menu)
	   t)
	  ((null items)
	   (setcdr places-menu (list (vector "Use point-to-register to add to this list"
					     '(point-to-register ?a) t)))
	   nil)
	  (t
	   (setcdr places-menu items)
	   nil))))
