;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module PRODUCTS: An enumeration of all Gensym Products Currently Shipping

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Authors: Ben Hyde




;;;; Introduction

;;; This file contains the enumeration of products that Gensym
;;; is currently shipping.  This file is used to generate data
;;; needed by the licensing server.





;;;; Additional Info appended to each and every authorization.

;#+obsolete
;(def-additional-info
;  ""
;  "Please fax or call Gensym Licensing if any problems arise."
;  "    Fax: 617-547-1962"
;  "    Phone: 617-547-2500"
;  ""
;  "The Hotline numbers for Gensym Customer Support are:"
;  "    Phone: 617-547-1534"
;  "    Fax: 617-547-1962")







;;;; G2

(def-product-authorization ("G2" "V2015")
  :authorization-method g2
  :description "G2 Real Time Expert System Version 2015"
  :g2-version-switch 12
  :default-process-count 2
  :default-tw-process-count 0
  :default-t2-process-count 0
  :process-count-spec (or (member unlimited) (integer 1 200))
  )

(def-product-authorization ("G2" "V2011")
  :authorization-method g2
  :description "G2 Real Time Expert System Version 2011"
  :g2-version-switch 11
  :default-process-count 2
  :default-tw-process-count 0
  :default-t2-process-count 0
  :process-count-spec (or (member unlimited) (integer 1 200))
  )

(def-product-authorization ("G2" "V9")
  :authorization-method g2
  :description "G2 Real Time Expert System Version 9.0"
  :g2-version-switch 9
  :default-process-count 2
  :default-tw-process-count 0
  :default-t2-process-count 0
  :process-count-spec (or (member unlimited) (integer 1 200))
  )

(def-product-authorization ("G2" "V83")
  :authorization-method g2
  :description "G2 Real Time Expert System Version 8.3"
  :g2-version-switch 83 
  :default-process-count 2
  :default-tw-process-count 0
  :default-t2-process-count 0
  :process-count-spec (or (member unlimited) (integer 1 200))
  )

(def-product-authorization ("G2" "V8")
  :authorization-method g2
  :description "G2 Real Time Expert System Version 8.0"
  :g2-version-switch 8 
  :default-process-count 2
  :default-tw-process-count 0
  :default-t2-process-count 0
  :process-count-spec (or (member unlimited) (integer 1 200))
  )

(def-product-authorization ("G2" "V6")
  :authorization-method g2
  :description "G2 Real Time Expert System Version 6.0 & 7.0"
  :g2-version-switch 6
  :default-process-count 2
  :default-tw-process-count 0
  :default-t2-process-count 0
  :process-count-spec (or (member unlimited) (integer 1 200))
  )

(def-product-authorization ("G2" "V5")
  :authorization-method g2
  :description "G2 Real Time Expert System Version 5.0"
  :g2-version-switch 5
  :default-process-count 2
  :default-tw-process-count 0
  :default-t2-process-count 0
  :process-count-spec (or (member unlimited) (integer 1 200))
  )

(def-product-authorization ("G2" "V4")
  :authorization-method g2
  :description "G2 Real Time Expert System Version 4.0"
  :g2-version-switch 4
  :default-process-count 2
  :default-tw-process-count 0
  :process-count-spec (or (member unlimited) (integer 1 200))
  )

(def-product-authorization ("G2" "V3")
  :authorization-method g2
  :description "G2 Real Time Expert System Version 3.0"
  :g2-version-switch 3
  :default-process-count 2
  :process-count-spec (or (member unlimited) (integer 1 200))
  )

(def-product-authorization ("G2" "V2")
  :authorization-method g2
  :description "G2 Real Time Expert System Version 2"
  :g2-version-switch t
  )

(Def-Product-Authorization ("G2" "V1.11B")
  :authorization-method g2
  :Description "G2 Real Time Expert System Version 1.11B"
  :G2-Version-Switch nil
  )




;;;;; Telewindows 2

(def-product-authorization ("Telewindows2" "V1")
  :authorization-method telewindows2
  :description "Telewindows 2 Toolkit Version 1"
  :tw2-version-number 1  )



;;;; Telewindows

(def-product-authorization ("Telewindows" "V2")
  :authorization-method telewindows
  :Description "Telewindows Version 2"
  :telewindows-version-number-as-float 2.0
  )

(def-product-authorization ("Telewindows" "V3")
  :authorization-method telewindows
  :Description "Telewindows Version 3"
  :telewindows-version-number-as-float 3.1
  :default-process-count 1
  :process-count-spec (or (member unlimited) (integer 1 200))
  )

(def-product-authorization ("Telewindows" "V3 alpha")
  :authorization-method telewindows
  :Description "Telewindows Version 3 alpha"
  :telewindows-version-number-as-float 3.0
  :default-process-count 1
  :process-count-spec (or (member unlimited) (integer 1 200))
  )

(def-product-authorization ("Telewindows" "V4")
  :authorization-method telewindows
  :Description "Telewindows Version 4"
  :telewindows-version-number-as-float 4.0
  :default-process-count 1
  :process-count-spec (or (member unlimited) (integer 1 200))
  )

(def-product-authorization ("Telewindows" "V5")
  :authorization-method telewindows
  :Description "Telewindows Version 5"
  :telewindows-version-number-as-float 5.0
  :default-process-count 1
  :process-count-spec (or (member unlimited) (integer 1 200))
  )

(def-product-authorization ("Telewindows" "V6")
  :authorization-method telewindows
  :Description "Telewindows Version 6 & 7"
  :telewindows-version-number-as-float 6.0
  :default-process-count 1
  :process-count-spec (or (member unlimited) (integer 1 200))
  )

(def-product-authorization ("Telewindows" "V8")
  :authorization-method telewindows
  :Description "Telewindows Version 8"
  :telewindows-version-number-as-float 8.0
  :default-process-count 1
  :process-count-spec (or (member unlimited) (integer 1 200))
  )

(def-product-authorization ("Telewindows" "V2011")
  :authorization-method telewindows
  :Description "Telewindows Version 2011"
  :telewindows-version-number-as-float 11.0
  :default-process-count 1
  :process-count-spec (or (member unlimited) (integer 1 200))
  )

(def-product-authorization ("Telewindows" "V2015")
  :authorization-method telewindows
  :Description "Telewindows Version 2015"
  :telewindows-version-number-as-float 12.0
  :default-process-count 1
  :process-count-spec (or (member unlimited) (integer 1 200))
  )



;;;; Bridges

(def-product-authorization ("G2-ODBC" "v5")
  :authorization-method bridge
  :description "G2-ODBC Bridge v5"
  :bridge-revision-switch revision-2)

(def-product-authorization ("G2-ODBC" "v6")
  :authorization-method bridge
  :description "G2-ODBC Bridge v6"
  :bridge-revision-switch revision-2)  ;; ddm 1/19/98

(def-product-authorization ("G2-ODBC" "v7")
  :authorization-method bridge
  :description "G2-ODBC Bridge v7"
  :bridge-revision-switch revision-2)

(def-product-authorization ("G2-ODBC" "V8")
  :authorization-method bridge
  :description "G2-ODBC Bridge V8"
  :bridge-revision-switch revision-2)  

(def-product-authorization ("G2-ODBC" "V11")
  :authorization-method bridge
  :description "G2-ODBC Bridge 2011"
  :bridge-revision-switch revision-1)

(def-product-authorization ("G2-ODBC" "V12")
  :authorization-method bridge
  :description "G2-ODBC Bridge 2015"
  :bridge-revision-switch revision-1)

(def-product-authorization ("SQLSVR" "v8")
  :authorization-method bridge
  :description "G2-SQL SERVER Bridge v8"
  :bridge-revision-switch revision-2)

(def-product-authorization ("G2-ABInterchange" "v5")
  :authorization-method bridge
  :description "G2-ABInterchange Bridge v5"
  :bridge-revision-switch revision-2)

(def-product-authorization ("G2-ABInterchange" "v4")
  :authorization-method bridge
  :description "G2-ABInterchange Bridge v4"
  :bridge-revision-switch revision-2)

(def-product-authorization ("GSI-ABNet-DTL" "v1")
  :authorization-method bridge
  :description "GSI-ABNet-DTL Bridge v1"
  :bridge-revision-switch revision-2) 

(def-product-authorization ("GSI-ABPLC" "v3")
  :authorization-method bridge
  :description "GSI-ABPLC Bridge v3"
  :bridge-revision-switch revision-2)

(def-product-authorization ("G2-AIM" "v2")
  :authorization-method bridge
  :description "G2-AIM Bridge v2"
  :bridge-revision-switch revision-2)

(def-product-authorization ("GSI-BASEstar" "v1")
  :authorization-method bridge
  :description "GSI-BASEstar Bridge v1"
  :bridge-revision-switch revision-2)

(def-product-authorization ("GSI-CM50S" "v1")
  :authorization-method bridge
  :description "GSI-CM50S Bridge v1"
  :bridge-revision-switch revision-2)

(def-product-authorization ("G2-GEPLC" "v4")
  :authorization-method bridge
  :description "G2-GEPLC Bridge v4"
  :bridge-revision-switch revision-2)

(def-product-authorization ("GSI-Modbus" "v1")
  :authorization-method bridge
  :description "GSI-Modbus Bridge v1"
  :bridge-revision-switch revision-2)

(def-product-authorization ("GSI-Modbus-Plus" "v1")
  :authorization-method bridge
  :description "GSI-Modbus-Plus Bridge v1"
  :bridge-revision-switch revision-2)

;; G2-Oracle bridges

(def-product-authorization ("G2-ORACLE" "v3")
  :authorization-method bridge
  :description "G2-ORACLE Bridge v3"
  :bridge-revision-switch revision-2)

(def-product-authorization ("G2-ORACLE" "V5")
    :authorization-method bridge
    :description "G2-Oracle Bridge"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-ORACLE" "v6")
  :authorization-method bridge
  :description "G2-ORACLE Bridge v6 rev.2"
  :bridge-revision-switch revision-2)

(def-product-authorization ("G2-ORACLE" "v7")
  :authorization-method bridge
  :description "G2-ORACLE Bridge v7"
  :bridge-revision-switch revision-2)

(def-product-authorization ("G2-ORACLE" "V11")
  :authorization-method bridge
  :description "G2-ORACLE Bridge 2011"
  :bridge-revision-switch revision-1)

(def-product-authorization ("G2-ORACLE" "V12")
  :authorization-method bridge
  :description "G2-ORACLE Bridge 2015"
  :bridge-revision-switch revision-1)

(def-product-authorization ("G2-MSSQL" "V11")
  :authorization-method bridge
  :description "G2-MSSQL Bridge 2011"
  :bridge-revision-switch revision-1)

(def-product-authorization ("G2-OSIPI" "v1")
  :authorization-method bridge
  :description "G2-OSIPI Bridge v1"
  :bridge-revision-switch revision-2)

(def-product-authorization ("G2-Rdb" "v3")
  :authorization-method bridge
  :description "G2-Rdb Bridge v3"
  :bridge-revision-switch revision-2)

(def-product-authorization ("GSI-SETCON" "v1")
  :authorization-method bridge
  :description "GSI-SETCON Bridge v1"
  :bridge-revision-switch revision-2)


(def-product-authorization ("G2-SYBASE" "v3")
  :authorization-method bridge
  :description "G2-SYBASE Bridge v3"
  :bridge-revision-switch revision-2)

(def-product-authorization ("G2-SYBASE" "V5")
    :authorization-method bridge
    :description "G2-Sybase Bridge"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-SYBASE" "v6")
  :authorization-method bridge
  :description "G2-SYBASE Bridge v6 rev.2"
  :bridge-revision-switch revision-2)

(def-product-authorization ("G2-SYBASE" "v7")
  :authorization-method bridge
  :description "G2-SYBASE Bridge v7"
  :bridge-revision-switch revision-2)

(def-product-authorization ("G2-SYBASE" "V11")
  :authorization-method bridge
  :description "G2-SYBASE Bridge 2011"
  :bridge-revision-switch revision-1)

(def-product-authorization ("G2-SYBASE" "V12")
  :authorization-method bridge
  :description "G2-SYBASE Bridge 2015"
  :bridge-revision-switch revision-1)

(def-product-authorization ("GSI-TDC2000" "v1")
  :authorization-method bridge
  :description "GSI-TDC2000 Bridge v1"
  :bridge-revision-switch revision-2)

(def-product-authorization ("GSI-RTAP" "v1")
  :authorization-method bridge
  :description "GSI-RTAP Bridge v1"
  :bridge-revision-switch revision-2)

(def-product-authorization ("G2-SETCIM" "v1")
  :authorization-method bridge
  :description "G2-SETCIM Bridge v1"
  :bridge-revision-switch revision-2)

(def-product-authorization ("G2ABI_EI" "V4")
    :authorization-method bridge
    :description "G2-ABInterchange (EI) Bridge"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2ABI_EP" "V4")
    :authorization-method bridge
    :description "G2-ABInterchange (EP) Bridge"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2ABI_KT" "V4")
    :authorization-method bridge
    :description "G2-ABInterchange (KT)"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-ABPLC" "V3")
    :authorization-method bridge
    :description "G2-ABPLC Bridge"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-AIM" "V2")
    :authorization-method bridge
    :description "G2-Aim Bridge"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-AIM" "V2")
    :authorization-method bridge
    :description "G2-Aim Bridge"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-APRIL" "V5")
    :authorization-method bridge
    :description "G2-April Bridge"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-BASESTAR" "V3")
    :authorization-method bridge
    :description "G2-BASEstar Bridge"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-GEPLC" "V5")
    :authorization-method bridge
    :description "G2-GEPLC Bridge"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-GES6" "V4")
    :authorization-method bridge
    :description "G2-GES6 Bridge"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-INFORMIX" "V5")
    :authorization-method bridge
    :description "G2-Informix Bridge v5"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-INFORMIX" "V6")
    :authorization-method bridge
    :description "G2-Informix Bridge v6"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-MISTIC" "V4")
    :authorization-method bridge
    :description "G2-Mistic Bridge"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-MODBUS" "V5")
    :authorization-method bridge
    :description "G2-Modbus Bridge"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-MODBUS" "V5")
    :authorization-method bridge
    :description "G2-Modbus Bridge"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-MODBUSPLUS" "V5")
    :authorization-method bridge
    :description "G2-ModbusPlus"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-PI" "V1")
    :authorization-method bridge
    :description "G2-PI Bridge"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-PI" "V2")
    :authorization-method bridge
    :description "G2-PI Bridge"
    :bridge-revision-switch revision-2)

;; V3 for g2-pi was apparently skipped as far as requiring
;; new codes. (MHD 3/27/01)

(def-product-authorization ("G2-PI" "V4")
    :authorization-method bridge
    :description "G2-PI Bridge"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-PI" "V6")
    :authorization-method bridge
    :description "G2-PI Bridge"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-PI" "V11")
    :authorization-method bridge
    :description "G2-PI Bridge 2011"
    :bridge-revision-switch revision-1)

(def-product-authorization ("G2-PI" "V12")
    :authorization-method bridge
    :description "G2-PI Bridge 2015"
    :bridge-revision-switch revision-1)

(def-product-authorization ("G2-RDB" "V5")
    :authorization-method bridge
    :description "G2-Rdb Bridge"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-SQD" "V5")
    :authorization-method bridge
    :description "G2-SQD Bridge"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-TDC3000" "V1")
    :authorization-method bridge
    :description "G2-TDC3000 (S) Bridge"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-WESTINGHOUSE" "V4")
    :authorization-method bridge
    :description "G2-Westinghouse Bridge"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2ABI_EI" "V5")
    :authorization-method bridge
    :description "G2-ABInterchange (EI) Bridge"
    :bridge-revision-switch revision-2)

(def-product-authorization ("GSI-ABNET-DTL" "V1-0B")
    :authorization-method bridge
    :description "GSI-ABNet-DTL"
    :bridge-revision-switch revision-2)

(def-product-authorization ("GSI-RTAP" "V1-0B")
    :authorization-method bridge
    :description "GSI-RTAP Bridge"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-ABPLC" "V3.5")
    :authorization-method bridge
    :description "G2-ABPLC Bridge"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-WebLink" "V1")
    :authorization-method bridge
    :description "G2-WebLink Bridge"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-WebLink" "V2")   ;; added 6/26/98
    :authorization-method bridge
    :description "G2-WebLink Bridge"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-WebLink" "V11")
    :authorization-method bridge
    :description "G2-WebLink Bridge"
    :bridge-revision-switch revision-1)

(def-product-authorization ("G2-WebLink" "V12")
    :authorization-method bridge
    :description "G2-WebLink Bridge 2015"
    :bridge-revision-switch revision-1)

(def-product-authorization ("G2-JDBC" "V11")
    :authorization-method bridge
    :description "G2-JDBC Bridge"
    :bridge-revision-switch revision-1)

(def-product-authorization ("G2-JDBC" "V12")
    :authorization-method bridge
    :description "G2-JDBC Bridge"
    :bridge-revision-switch revision-1)

(def-product-authorization ("G2-WebMiner" "V1")
    :authorization-method bridge
    :description "G2-WebMiner Bridge"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-AAGSRVR" "V1")
    :authorization-method bridge
    :description "G2-AAGSRVR At a Glance Server"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-AAGCLNT" "V1")
    :authorization-method bridge
    :description "G2-AAGCLNT At a Glance Client"
    :bridge-revision-switch revision-2)


(def-product-authorization ("G2-NV6K-SNMP" "V2")
    :authorization-method bridge
    :description "G2-SNMP IBM NetView Bridge"
    ;; from Hank Streeter
    ;; formerly described as "G2-NV6K-SNMP SNMP bridge"
    ;; updated ddm 7/28/97 as per HQ-1383325
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-HPOV-SNMP" "V2")
    :authorization-method bridge
    :description "G2-SNMP HP OpenView Bridge"
    ;; Release form can't be found just now, ddm 7/28/97
    ;; updated as per HQ-1383325
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-GNRC-SNMP" "V1")
    :authorization-method bridge
    :description "G2-SNMP Generic Bridge"
    ;; from William Moris
    ;; via Ticket HQ-2684042
    ;; ddm 2/26/99
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-GNRC-SNMP" "V2")
    :authorization-method bridge
    :description "G2-SNMP Generic Bridge"
    ;; from Hank Streeter
    ;; Release Form dated 1/9/97
    ;; updated as per HQ-1383325
    ;; ddm 7/28/97
    :bridge-revision-switch revision-2)


(def-product-authorization ("G2-APPLICOM" "V1")
    :authorization-method bridge
    :description "G2 Applicom"
    ;; from Peter Fandel
    ;; Release Form dated 8/26/97
    ;; updated as per HQ-1546218
    ;; ddm 9/22/97
    :bridge-revision-switch revision-1)


(def-product-authorization ("GENSYM-PMGR" "V1")
    :authorization-method bridge
    :description "Ping Manager"
    ;; ddm 2/9/98
    :bridge-revision-switch revision-1)


(def-product-authorization ("NOL-STUDIO" "V4B")
    :authorization-method bridge
    :description "Gensym NeurOn-Line Studio version 4.0 beta"
    ;; ddm 10/16/98 for Mark Kramer
    :bridge-revision-switch revision-2)

;; n.b. The beta above will clash with a v4 of the production
;; version. It should be cleared out as soon as the two versions
;; below ship. 

(def-product-authorization ("NOL-STUDIO" "V2")
    :authorization-method bridge
    :description "Gensym NeurOn-Line Studio development version 2"
    ;; ddm 1/19/99 for Ellen Gerlovin (for Mark Kramer)
    :bridge-revision-switch revision-2)

(def-product-authorization ("NOL-ONLINE" "V2")
    :authorization-method bridge
    :description "Gensym NeurOn-Line Studio deployment version 2"
    ;; ddm 1/19/99 for Ellen Gerlovin (for Mark Kramer)
    :bridge-revision-switch revision-2)


(def-product-authorization ("G2-SERIALLINK" "B1")
    :authorization-method bridge
    :description "G2 SerialLink version beta 1"
    ;; ddm 2/22/98
    :bridge-revision-switch revision-2)


(def-product-authorization ("G2-HLA" "V1")
    :authorization-method bridge
    :description "G2-HLA 1.3r0"
    ;; ddm 3/12/99 For Philippe Printz
    :bridge-revision-switch revision-2)


(def-product-authorization ("G2-OPCLINK" "V1")
    :authorization-method bridge
    :description "G2 OPCLink Bridge 1.0r0"
    ;; New information: (from around 2002) Contact: Gensym, Samy Achour
    ;; (sachour@gensym.com) -- Gensym salesperson AND owner of company that
    ;; developed replacement product. -- mhd, 12/1/03
    ;; 
    ;; Older information -- supplier relationship ended circa 2002:
    ;; ;; ddm 6/3/99 for Chistine McCarty as the intermediary
    ;; ;; for Matrikon Consulting, 2950 Parsons Road, 2d floor,
    ;; ;; Edmonton, Canada T6N1A3
    ;; ;; contact: Jeff Caulfield (403) 448 1010
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-OPCLINK" "V3")
    :authorization-method bridge
    :description "G2 OPCLink Bridge 3.0r0"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-OPCLINK" "V8")
    :authorization-method bridge
    :description "G2 OPCLink Bridge 8.3r0"
    ;; Requested in Bug HQ-5459201. - jpg 2/23/07
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-OPCLINK" "V11")
    :authorization-method bridge
    :description "G2 OPCLink Bridge 2011"
    :bridge-revision-switch revision-1)

(def-product-authorization ("G2-OPCLINK" "V12")
    :authorization-method bridge
    :description "G2 OPCLink Bridge 2015"
    :bridge-revision-switch revision-1)

(def-product-authorization ("G2-OPCHDALINK" "V1")
    :authorization-method bridge
    :description "G2 OPCHDALink Bridge 1.0r0"
    ;; Contact: Gensym, Samy Achour (sachour@gensym.com) -- Gensym salesperson
    ;; AND owner of company that produced this product. -- mhd, 12/1/03

    ;; Related Helpdesk Ticket: HQ-4632993 "add G2-OPCHDALink to the Product
    ;; field in HL/HD"
    :bridge-revision-switch revision-2)

(def-product-authorization ("G2-OPCHDALINK" "V2")
    :authorization-method bridge
    :description "G2 OPCHDALink Bridge 2.0r0"
    :bridge-revision-switch revision-2)


(def-product-authorization ("G2-PAGER" "V1")
    :authorization-method bridge
    :description "G2-Pager"
    ;; Don Wilkey, Gensym
    ;; G.P.O. Box 904, Brisbane QLD 4001, Australia
    ;; 462 (7) 3210 2685
    ;; -- ddm 7/30/99
    :bridge-revision-switch revision-2)


(def-product-authorization ("G2-RV" "V1")
    :authorization-method bridge
    :description "G2-Rendezvous Bridge"
    ;; Don Wilkey, Gensym
    ;; G.P.O. Box 904, Brisbane QLD 4001, Australia
    ;; 462 (7) 3210 2685
    ;; ddm 11/22/99
    :bridge-revision-switch revision-2)


(def-product-authorization ("JYC" "V1")
    :authorization-method bridge
    :description "G2-JYC -- Johnson Yokogawa Distributed Control Bridge"
    ;; Requested by Matthew Farris via Ticket HQ-3284970
    ;; ddm 1/5/00
    :bridge-revision-switch revision-2)


(def-product-authorization ("G2-MAIL" "V1")
    :authorization-method bridge
    :description "G2-Mail Bridge"
    ;; Don Wilkey (see above)
    ;; ddm 1/20/00
    :bridge-revision-switch revision-2)


;(def-product-authorization ("" "V1")
;    :authorization-method bridge
;    :description ""
;    ;; ddm 1/5/00
;    :bridge-revision-switch revision-2)











;;;; Packages (aka Tool Kits)

(def-product-authorization ("gensym-gda" "any")
  :authorization-method g2-package
  :description "Gensym Diagnostic Assistant, Version 1"
  :package-authorization-codes (207069 492886 107838 518886)
                      ; formally: (295778 459396 22238 71614)
  :package-name-for-ok-object gensym-gda
)

(def-product-authorization ("gensym-gda2" "any")
  :authorization-method g2-package
  :description "Gensym Diagnostic Assistant, Version 2"
  :package-authorization-codes (510167 388613 243339 160470) 
  :package-name-for-ok-object gensym-gda2
)

(def-product-authorization ("gensym-gda4" "any")
  :authorization-method g2-package
  :description "Gensym Diagnostic Assistant, Version 4"
  :package-authorization-codes (251193 54680 285373 495123)
  :package-name-for-ok-object gensym-gda4
  ;; For Mike Nelson 3/23/99
)

(def-product-authorization ("gensym-gda-v5" "any")
  :authorization-method g2-package
  :description "Gensym Diagnostic Assistant, Version 5"
  :package-authorization-codes (470427 366512 66851 389453)
  :package-name-for-ok-object gensym-gda-v5
  ;; Requested in Ticket HQ-5016328. - jpg 8/1/05
)


(def-product-authorization ("gensym-optegrity-v4" "any")
  :authorization-method g2-package
  :description "Gensym Optegrity, Version 4"
  :package-authorization-codes (25882 249579 433575 316799)
  :package-name-for-ok-object gensym-optegrity-v4
  ;; Per Gensym order services request through ticket HQ-4657642. product
  ;; contacts are Philippe Printz and William Morris. -mhd, 10/7/03
)

(def-product-authorization ("gensym-optegrity-v5" "any")
  :authorization-method g2-package
  :description "Gensym Optegrity, Version 5"
  :package-authorization-codes (148299 260187 463070 243285)
  :package-name-for-ok-object gensym-optegrity-v5
  ;; Requested in Ticket HQ-5016328 by William Morris. - jpg 5/13/05
)

(def-product-authorization ("gensym-integrity-v5" "any")
  :authorization-method g2-package
  :description "Gensym Integrity, Version 5"
  :package-authorization-codes (355941 233395 469277 5583)
  :package-name-for-ok-object gensym-integrity-v5
  ;; Requested in Ticket HQ-5016328. - jpg 8/1/05
)


(def-product-authorization ("gensym-gmm" "any")
  :authorization-method g2-package
  :description "Gensym G2 Message Manager"
  :package-authorization-codes (297923 227822 133861 402818)
  :package-name-for-ok-object gensym-gmm
)

;; Archtypical entry, with comments!
(def-product-authorization ("gensym-dsp" "any")
  :authorization-method g2-package
  ;; Used in the authorization utilities menu.

     ;; Used in the authorization printout.
  :description "Gensym Dynamic Scheduler Package"

  ;; Disables the menu entry in the utility.

   ;; Codes, as computed by ML.
  :package-authorization-codes (289594 110002 275266 191943)

  ;; What is entered in the ok object.
  :package-name-for-ok-object gensym-dsp)


(def-product-authorization ("orsi-pms" "any")
  :authorization-method g2-package
  :description "Orsi PMS"
  :package-authorization-codes (413115 467114 379289 369924)
  :package-name-for-ok-object orsi-pms
  )

(def-product-authorization ("test-package" "any")
  :authorization-method g2-package
  :description "Gensym's Test Toolkit Package"
  :package-authorization-codes (20553 462801 416679 183376)
  :package-name-for-ok-object test-package
  :additional-information  (""
                            "Note:"
                            "  This is not a shipping product."
                            "  This is intended only in house for testing
purposes.")
  )

(def-product-authorization ("gensym-test-1" "any")
  :authorization-method g2-package
  :description "Gensym Test Package 1"
  :package-authorization-codes (196522 429095 219061 30352)
  :package-name-for-ok-object gensym-test-1
  :additional-information
  (""
    "Note:"
    "  This is not a shipping product."
    "  This is intended only in house for testing purposes."))

(def-product-authorization ("gensym-test-2" "any")
  :authorization-method g2-package
  :description "Gensym Test Package 2"
  :package-authorization-codes (465721 397944 186902 66513)
  :package-name-for-ok-object gensym-test-2
  :additional-information
  (""
    "Note:"
    "  This is not a shipping product."
    "  This is intended only in house for testing purposes."))

(def-product-authorization ("Johnson JPS" "any")
  :authorization-method g2-package
  :description "Johnson JPS"
  :package-authorization-codes (487757 285038 509903 12087)
  :package-name-for-ok-object johnson-jps
  :additional-information  ("")
  )

(def-product-authorization ("ORSI EXAD" "any")
  :authorization-method g2-package
  :description "ORSI EXAD"
  :package-authorization-codes (482526  268201  407973  310406)
  :package-name-for-ok-object orsi-exad
  :additional-information  ("")
  )

(def-product-authorization ("Lafarge LISE" "any")
  :authorization-method g2-package
  :description "Lafarge LISE"
  :package-authorization-codes (271979 404674 29960 177631)
  :package-name-for-ok-object lafarge-lise
  :additional-information  ("Lafarge Informatique Systeme Expert")
  )

(def-product-authorization ("Gensym Basic" "any")
  :authorization-method g2-package
  :description "Gensym Basic Course"
  :package-authorization-codes (57430 360878 347114 262957)
  :package-name-for-ok-object gensym-basic
  :additional-information  ("Gensym Basic Course")
  )

(def-product-authorization ("Gensym Intermediate" "any")
  :authorization-method g2-package
  :description "Gensym Intermediate Course"
  :package-authorization-codes (29942 247067 266576 64736)
  :package-name-for-ok-object gensym-Intermediate
  :additional-information  ("Gensym Intermediate Course")
  )

(def-product-authorization ("Gensym NeurOn-Line" "any")
  :authorization-method g2-package
  :description "Gensym NeurOn-Line"
  :package-authorization-codes (385682 286522 62640 25364)
  :package-name-for-ok-object gensym-nol
  :additional-information  ("Gensym NeurOn-Line")
  )

(def-product-authorization ("Gensym Energy Manager" "any")
  :authorization-method g2-package
  :description "Gensym Energy Manager"
  :package-authorization-codes (154246 209778 439854 417657)
  :package-name-for-ok-object gensym-em
  :additional-information  ("Gensym Energy Manager")
  )


(def-product-authorization ("Gensym Help Desk" "any")
  :authorization-method g2-package
  :description "Gensym Help Desk"
  :package-authorization-codes (267101 214075 38853 164706)
  :package-name-for-ok-object gensym-hd
  :additional-information  ("Gensym Help Desk")
  )

(def-product-authorization ("ESIA Flownet" "any")
  :authorization-method g2-package
  :description "ESIA Flownet"
  :package-authorization-codes (500235 401632 308551 341284)
  :package-name-for-ok-object ESIA-Fnet
  :additional-information  ("ESIA Flownet")
  )


(def-product-authorization ("Coopers & Lybrand SPARKS" "any")
  :authorization-method g2-package
  :description "Coopers & Lybrand SPARKS"
  :package-authorization-codes (489308 51349 366575 141188)
  :package-name-for-ok-object cl-sparks
  :additional-information  ("Coopers & Lybrand SPARKS")
  )

(def-product-authorization ("Gensym GMQ" "any")
  :authorization-method g2-package
  :description "Gensym G2 Message Queues"
  :package-authorization-codes (368056 19975 506190 367912)
  :package-name-for-ok-object gensym-gmq
  :additional-information  ("Gensym's G2 Message Queues")
  )

(def-product-authorization ("Gensym PO" "any")
  :authorization-method g2-package
  :description "Gensym Parallel Optimizer"
  :package-authorization-codes (332058 32606 262166 407707)
  :package-name-for-ok-object gensym-po
  :additional-information  ("Gensym's Parallel Optimizer")
  )

(def-product-authorization ("ORSI Secure XP" "any")
  :authorization-method g2-package
  :description "ORSI Secure XP"
  :package-authorization-codes (412791 515896 220084 392897)
  :package-name-for-ok-object ORSI-SecureXP
  :additional-information  ("ORSI's Secure XP")
  )

(def-product-authorization ("Biotech Design Simulator" "any")
  :authorization-method g2-package
  :description "Biotech Design Simulator"
  :package-authorization-codes (476705 200620 178196 3634)
  :package-name-for-ok-object lsc-bds
  :additional-information  ("Biotech Design Simulator")
  )

(def-product-authorization ("Gensym Operator's Assistant" "any")
  :authorization-method g2-package
  :description "Gensym Operator's Assistant"
  :package-authorization-codes (83866 40706 2765 383424)
  :package-name-for-ok-object gensym-opa
  :additional-information  ("Gensym Operator's Assistant")
  )

(def-product-authorization ("Gensym STK1" "any")
  :authorization-method g2-package
  :description "Gensym Scheduling Toolkit 1"
  :package-authorization-codes (268995 351269 198972 498557)
  :package-name-for-ok-object gensym-stk1
  :additional-information  ("Gensym -- Scheduling Toolkit 1")
  ;; Bill Morrow
  )

(def-product-authorization ("Gensym STK2" "any")
  :authorization-method g2-package
  :description "Gensym Scheduling Toolkit 2"
  :package-authorization-codes (129759 90737 465714 251961)
  :package-name-for-ok-object gensym-stk2
  :additional-information  ("Gensym -- Scheduling Toolkit 2")
  ;; Bill Morrow
  )

(def-product-authorization ("Gensym Rethink" "any")
  :authorization-method g2-package
  :description "Gensym Rethink"
  :package-authorization-codes (292477 240738 418955 19185)
  :package-name-for-ok-object gensym-rethink
  :additional-information  ("Gensym -- Rethink")
  ;; Tom Foley
  )

(def-product-authorization ("gensym-rethink-v5" "any")
  :authorization-method g2-package
  :description "Gensym Rethink, Version 5"
  :package-authorization-codes (133352 275290 328499 253388)
  :package-name-for-ok-object gensym-rethink-v5
  :additional-information  ("")
  ;; Requested in Ticket HQ-5016328. - jpg 8/1/05
  )


(def-product-authorization ("EASE SPT" "any")
  :authorization-method g2-package
  :description
  "Schematic Programming Tool, EASE Software Engineering GmbH SPT"
  :package-authorization-codes (238728 188230 54838 17043)
  :package-name-for-ok-object ease-spt
  :additional-information
  ("Schematic Programming Tool, EASE Software Engineering GmbH SPT")
  ;; ??
  )


(def-product-authorization ("HBS APMD" "any")
  :authorization-method g2-package
  :description "Advanced Process Monitor & Diagnostics, HBS Computers"
  :package-authorization-codes (315494 333830 397142 113081)
  :package-name-for-ok-object hbs-apmd
  :additional-information
  ("Advanced Process Monitor & Diagnostics, HBS Computers")
  ;; Joe Harrington
  )

(def-product-authorization ("HBS CUA" "any")
  :authorization-method g2-package
  :description "Crude Unit Advisor, HBS Computers"
  :package-authorization-codes (466848 65369 187378 315236)
  :package-name-for-ok-object hbs-cua
  :additional-information  ("Crude Unit Advisor, HBS Computers")
  ;; Joe Harrington
  )

(def-product-authorization ("ABB Simcon GMB" "any")
  :authorization-method g2-package
  :description "Graphical Model Builder, ABB SIMCON(tm)"
  :package-authorization-codes (309558 280252 257202 279674)
  :package-name-for-ok-object simcon-gmb
  :additional-information  ("Graphical Model Builder, ABB SIMCON(tm)")
  ;; Phil Morrow
  )

(def-product-authorization ("Gensym GSPC" "any")
  :authorization-method g2-package
  :description "G2 Statistical Process Control Package"
  :package-authorization-codes (177460 399028 220529 18484)
  :package-name-for-ok-object gensym-gspc
  :additional-information  ("G2 Statistical Process Control Package")
  ;; Jere Beasley
  )

(def-product-authorization ("Gensym Bayes-Online" "any")
  :authorization-method g2-package
  :description "Bayes' Rule Network Modeling Package"
  :package-authorization-codes (210115 424352 186797 372242)
  :package-name-for-ok-object gensym-bayes-online
  :additional-information  ("Bayes' Rule Network Modeling Package")
  ;; Jere Beasley
  )

(def-product-authorization ("Gensym Space-Planner" "any")
  :authorization-method g2-package
  :description "2-D and 3-D Spacial Layout Planner"
  :package-authorization-codes (132591 245190 320020 262687)
  :package-name-for-ok-object gensym-space-planner
  :additional-information  ("")
  ;; Jere Beasley
  )

(def-product-authorization ("Gensym Visual Basic Bridge" "any")
  :authorization-method g2-package
  :description "Gensym's Visual Basic Bridge (an Asset) - Unlimited number of connections"
  :package-authorization-codes (303561 121553 255965 173781)
  :package-name-for-ok-object gensym-vb-bridge
  :additional-information  ("")
  ;; Last Known Contact: John Joyce, Gensym Advanced Development Group
  ;; Registration Date (Person): 7/27/95 (MHD)
  )

(def-product-authorization ("Gensym Visual Basic Bridge - 5" "any")
  :authorization-method g2-package
  :description "Gensym's Visual Basic Bridge (an Asset) - 5 connections"
  :package-authorization-codes (392441 16949 392843 357268)
  :package-name-for-ok-object gensym-vb-bridge-5
  :additional-information  ("")
  ;; John Joyce, Gensym Advanced Development Group
  ;; Registration Date (Person): 10/19/95 (MHD)
  )

(def-product-authorization ("Gensym Visual Basic Bridge - 10" "any")
  :authorization-method g2-package
  :description "Gensym's Visual Basic Bridge (an Asset) - 10 connections"
  :package-authorization-codes (477236 340023 275543 363820)
  :package-name-for-ok-object gensym-vb-bridge-10
  :additional-information  ("")
  ;; John Joyce, Gensym Advanced Development Group
  ;; Registration Date (Person): 10/19/95 (MHD)
  )

(def-product-authorization ("Gensym Visual Basic Bridge - 20" "any")
  :authorization-method g2-package
  :description "Gensym's Visual Basic Bridge (an Asset) - 20 connections"
  :package-authorization-codes (259181 20231 298111 276649)
  :package-name-for-ok-object gensym-vb-bridge-20
  :additional-information  ("")
  ;; John Joyce, Gensym Advanced Development Group
  ;; Registration Date (Person): 10/19/95 (MHD)
  )

(def-product-authorization ("Gensym Visual Basic Bridge - 40" "any")
  :authorization-method g2-package
  :description "Gensym's Visual Basic Bridge (an Asset) - 40 connections"
  :package-authorization-codes (64791 267584 237146 349452)
  :package-name-for-ok-object gensym-vb-bridge-40
  :additional-information  ("")
  ;; John Joyce, Gensym Advanced Development Group
  ;; Registration Date (Person): 10/19/95 (MHD)
  )

(def-product-authorization ("Batch Design Kit" "any")
  :authorization-method g2-package
  :description "MIT Batch Design Kit"
  :package-authorization-codes (392601 396467 441106 478849)
  :package-name-for-ok-object MIT-BDK
  :additional-information  ("")
  ;; Steven Fraleigh, at Gensym Corporation, working with MIT
  ;; -- mhd, 8/4/95
  )

(def-product-authorization ("EuriWare G2MATLAB" "any")
  :authorization-method g2-package
  :description "EuriWare G2MATLAB"
  :package-authorization-codes (266826 436690 379774 395051)
  :package-name-for-ok-object EW-G2MATLAB
  :additional-information  ("")
  ;; J.L. DelCovellerrie -- Euriware
  ;; phone: 33130145639 fax: 331301415660
  ;; -- ben, 1/29/96
  )

(def-product-authorization ("Gensym GAS" "any")
  :authorization-method g2-package
  :description "EuriWare Genetic Algorithm Solver (GENSYM-GAS)"
  :package-authorization-codes (197179 318861 226953 338425)
  :package-name-for-ok-object GENSYM-GAS
  :additional-information  ("")
  ;; Bill Morrow - Gensym Consulting
  ;; -- ben, 4/16/96
  )

(def-product-authorization ("Gensym Infi90" "any")
  :authorization-method g2-package
  :description "GENSYM-INFI90"
  :package-authorization-codes (311636 234462 427459 342740)
  :package-name-for-ok-object GENSYM-INFI90
  :additional-information  ("")
  ;; David Hickey
  ;; -- ben, 4/29/96
  )

(def-product-authorization ("Gensym GOLD" "any")
  :authorization-method g2-package
  :description "GENSYM-GOLD"
  :package-authorization-codes (435067 143618 103468 106054)
  :package-name-for-ok-object GENSYM-GOLD
  :additional-information  ("")
  ;; Vikram Pillam
  ;; -- ben, 9/10/96
  )

(def-product-authorization ("Gensym GDA3" "any")
  :authorization-method g2-package
  :description "GENSYM-GDA3"
  :package-authorization-codes (225089 334864 146714 211923)
  :package-name-for-ok-object GENSYM-GDA3
  :additional-information  ("")
  ;; Brian Seaworth, Ann Bark
  ;; -- ben, 9/10/96
  )

(def-product-authorization ("Gensym NOL3" "any")
  :authorization-method g2-package
  :description "GENSYM-NOL3"
  :package-authorization-codes (276665 103893 73341 82332)
  :package-name-for-ok-object GENSYM-NOL3
  :additional-information  ("")
  ;; Brian Seaworth, Ann Bark
  ;; -- ben, 9/10/96
  )

(def-product-authorization ("Gensym NOL4" "any")
  :authorization-method g2-package
  :description "GENSYM-NOL4"
  :package-authorization-codes (16705 36869 318138 112676)
  :package-name-for-ok-object GENSYM-NOL4
  :additional-information  ("")
  ;; Mike Nielson
  ;; -- ddm 4/5/99
  )

(def-product-authorization ("gensym-nol-v5" "any")
  :authorization-method g2-package
  :description "Gensym NOL, Version 5"
  :package-authorization-codes (491598 340639 136706 303097)
  :package-name-for-ok-object gensym-nol-v5 
  :additional-information  ("")
  ;; Requested in Ticket HQ-5016328. - jpg 8/1/05
  )

(def-product-authorization ("Gensym GSPC3" "any")
  :authorization-method g2-package
  :description "GENSYM-GSPC3"
  :package-authorization-codes (416746 209365 20011 463605)
  :package-name-for-ok-object GENSYM-GSPC3
  :additional-information  ("")
  ;; Brian Seaworth, Ann Bark
  ;; -- ben, 9/10/96
  )

(def-product-authorization ("Gensym ORBI" "any")
  :authorization-method g2-package
  :description "GENSYM G2 ORBLink Interface"
  :package-authorization-codes (38137 179255 114093 264316)
  :package-name-for-ok-object GENSYM-ORBI
  :additional-information  ("")
  ;; Peter Fandel
  )







(def-product-authorization ("Gensym Fault Expert" "any")
  :authorization-method g2-package
  :description "GENSYM Fault Expert"
  :package-authorization-codes (212982 32689 383087 313516)
  :package-name-for-ok-object GENSYM-FE
  :additional-information  ("")
  ;; Contact: David Green
  ;; Manager: Greg Stanley
  ;; Date: 2/5/97
  ;; Version: 2.0 Alpha Rev. 0
  )

(def-product-authorization ("Gensym CDG" "any")
  :authorization-method g2-package
  :description "GENSYM CDG"
  :package-authorization-codes (347024 239057 36836 255499)
  :package-name-for-ok-object GENSYM-CDG
  :additional-information  ("")
  ;; Contact: David Green
  ;; Manager: Greg Stanley
  ;; Date: 2/5/97
  ;; Version: 2.0 Alpha Rev. 0
  )

(def-product-authorization ("Gensym OPAC" "any")
  :authorization-method g2-package
  :description "GENSYM OPAC"
  :package-authorization-codes (400059 279913 222567 42222)
  :package-name-for-ok-object GENSYM-OPAC
  :additional-information  ("")
  ;; Contact: David Green
  ;; Manager: Greg Stanley
  ;; Date: 2/5/97
  ;; Version: 2.0 Alpha Rev. 0
  )

(def-product-authorization ("Gensym OPCS" "any")
  :authorization-method g2-package
  :description "GENSYM OPCS"
  :package-authorization-codes (260052 277479 127844 240830)
  :package-name-for-ok-object GENSYM-OPCS
  :additional-information  ("")
  ;; Contact: David Green
  ;; Manager: Greg Stanley
  ;; Date: 2/5/97
  ;; Version: 2.0 Alpha Rev. 0
  )

(def-product-authorization ("Gensym OXS" "any")
  :authorization-method g2-package
  :description "Gensym OXS"
  :package-authorization-codes (305388 207927 486716 44942)
  :package-name-for-ok-object GENSYM-OXS
  :additional-information  ("")
  ;; Input from Elizabeth Lang, 2/12/97:
  ;; Product Manager: David Green
  ;; Product Name: OXS
  ;; Manager: David Green
  ;; Authorization token: GENSYM-OXS
  ;; Version: 2.0 Alpha Rev. 0
  )

(def-product-authorization ("DBS-CABE-RM1" "any")
   :authorization-method g2-package
  :description "DBS CABE.repository"
  :package-authorization-codes (495189 412587 234522 69968)
  :package-name-for-ok-object DBS-CABE-RM1
  :additional-information  ("")
  ;; product name: CABE.repository
  ;; Company: Dynamic BioSimulations, Inc., Framingham, MA
  ;; Customer Name: Cristina Thalhammer-Reyero
  ;; Authorization token: dbs-cabe-rm1
  ;; Note: per customer, rm1 means "repository modeller 1"
  ;; Note: DBS stands for Dynamic BioSimulations
  ;; Note: I don't know what CABE stands for. (MHD)
  ;; Version: 1.0 rev.0
  ;; By: Mark H. David, 3/10/97
  )

(def-product-authorization ("GENSYM-GQS4" "any")
  :authorization-method g2-package
  :description "G2 Queue System"
  :package-authorization-codes (194876 286590 365601 3431)
  :package-name-for-ok-object GENSYM-GQS4
  :additional-information  ("")
  ;; Mark Kramer
  ;; -- ddm 7/25/97
  )

(def-product-authorization ("GENSYM-GQS5" "any")
  :authorization-method g2-package
  :description "G2 Queue System"
  :package-authorization-codes (254672 102714 110562 389280)
  :package-name-for-ok-object GENSYM-GQS5
  :additional-information  ("")
  ;; Mark Kramer
  ;; -- ddm 7/25/97
  )

(def-product-authorization ("GENSYM-DEVTOOLS5" "any")
  :authorization-method g2-package
  :description "G2 Developer Tools"
  :package-authorization-codes (516649 508237 43298 247980)
  :package-name-for-ok-object GENSYM-DEVTOOLS5
  :additional-information  ("")
  ;; Mark Kramer
  ;; -- ddm 7/25/97
  )

(def-product-authorization ("GENSYM-PROTOOLS5" "any")
  :authorization-method g2-package
  :description "G2 ProTools"
  :package-authorization-codes (520375 304183 500529 513878)
  :package-name-for-ok-object GENSYM-PROTOOLS5
  :additional-information  ("")
  ;; Mark Kramer
  ;; -- This is a renaming of GENSYM-DEVTOOLS !!
  ;;    flush the old version once the change has promulgated through
  ;;    the site ok file. ddm 11/18/97
  )



(def-product-authorization ("GENSYM-CORBA-DEV-V1-BETA" "any")
  :authorization-method g2-package
  :description "G2-CORBALink Development"
  :package-authorization-codes (279061 371678 346440 96903)
  :package-name-for-ok-object GENSYM-CORBA-DEV-V1-BETA
  :additional-information  ("")
  ;; Doug Loyer
  ;; -- ddm 8/19/97
  )

(def-product-authorization ("GENSYM-CORBA-RUNTIME-V1-BETA" "any")
  :authorization-method g2-package
  :description "G2-CORBALink RUNTIME"
  :package-authorization-codes (134443 325889 390655 316131)
  :package-name-for-ok-object GENSYM-CORBA-RUNTIME-V1-BETA
  :additional-information  ("")
  ;; Doug Loyer
  ;; -- ddm 8/19/97
  )

(def-product-authorization ("GENSYM-CORBALINK-DEV-V1" "any")
  :authorization-method g2-package
  :description "G2-CORBALink Development"
  :package-authorization-codes (298321 485534 233407 502554)
  :package-name-for-ok-object GENSYM-CORBALINK-DEV-V1
  :additional-information  ("")
  ;; Doug Loyer
  ;; -- ddm 9/22/97
  )

(def-product-authorization ("GENSYM-CORBALINK-RUNTIME-V1" "any")
  :authorization-method g2-package
  :description "G2-CORBALink RUNTIME"
  :package-authorization-codes (219616 206034 461749 362633)
  :package-name-for-ok-object GENSYM-CORBALINK-RUNTIME-V1
  :additional-information  ("")
  ;; Doug Loyer
  ;; -- ddm 9/22/97
  )

(def-product-authorization ("GENSYM-CORBALINK" "any")
  :authorization-method g2-package
  :description "G2-CORBALink"
  :package-authorization-codes (339165 241776 488004 415988)
  :package-name-for-ok-object GENSYM-CORBALINK 
  :additional-information  ("")
  ;; There's movement afoot (see Suggestion HQ-3677382) to possibly
  ;; replace the DEV and RUNTIME CORBALink authorizations above by
  ;; one CORBALink authorization.  This would be it.
  ;; -- jpg 7/29/04
  )



(def-product-authorization ("N-R-VMESA-V2" "any")
  :authorization-method g2-package
  :description "Visual Mesa"
  :package-authorization-codes (14558 302635 495684 469299)
  :package-name-for-ok-object N-R-VMESA-V2
  :additional-information  ("")
  ;; David Nelson
  ;; Nelson & Roseme
  ;; 5237 James Ave
  ;; Oalkand, CA 94618
  ;; Phone: 510 654-3536  Fax: 510 452-4410
  ;; -- ddm 9/22/97   Redone without the "&" 10/22
  )



(def-product-authorization ("STEL-NETCOACH-FAULT" "any")
  :authorization-method g2-package
  :description "stel-netcoach-fault"
  :package-authorization-codes (486643 60996 69017 378760)
  :package-name-for-ok-object STEL-NETCOACH-FAULT
  :additional-information  ("")
  ;; Registered by Steven J. Wiles,
  ;; Stanford Telecom, Inc.
  ;; 1761 Business Center Drive
  ;; Reston, Virginia, 20190
  ;; (703) 438-8023,  fax: (703) 438-8112
  ;; Product Manager: Wayne Fuller
  ;; -- ddm 10/23/97.  Revised 11/12 for different choice of auth. token
  )

(def-product-authorization ("STEL-NETCOACH-PERFORMANCE" "any")
  :authorization-method g2-package
  :description "stel-netcoach-performance"
  :package-authorization-codes (53753 231097 369610 162468)
  :package-name-for-ok-object STEL-NETCOACH-PERFORMANCE
  :additional-information  ("")
  ;;  Stanford Telecom, Inc. (as above)
  ;; -- ddm 10/23/97.  Revised 11/12 for different choice of auth. token
  )

(def-product-authorization ("STEL-NETCOACH-DISTRIBUTION" "any")
  :authorization-method g2-package
  :description "stel-netcoach-distribution"
  :package-authorization-codes (294435 217290 57715 118491)
  :package-name-for-ok-object STEL-NETCOACH-DISTRIBUTION
  :additional-information  ("")
  ;;   Stanford Telecom, Inc. (as above)
  ;; -- ddm 10/23/97.  Revised 11/12 for different choice of auth. token
  )

(def-product-authorization ("STEL-NETCOACH-SIMULATION" "any")
  :authorization-method g2-package
  :description "stel-netcoach-simulation"
  :package-authorization-codes (187093 135925 104536 456427)
  :package-name-for-ok-object STEL-NETCOACH-SIMULATION
  :additional-information  ("")
  ;;   Stanford Telecom, Inc. (as above)
  ;; -- ddm 10/23/97.  Revised 11/12 for different choice of auth. token
  )

(def-product-authorization ("GENSYM-SPT" "any")
  :authorization-method g2-package
  :description "Schematic Programming Tool"
  :package-authorization-codes (449128 359045 154954 267812)
  :package-name-for-ok-object GENSYM-SPT
  :additional-information  ("")
  ;; Gensym, for
  ;; Jean-Marie Foret
  ;; +32 3 384 93 70  (though that country code is suspect)
  ;; -- ddm 1/12/98
  )


(def-product-authorization ("GENSYM-ACTIVEXLINK" "any")
  :authorization-method g2-package
  :description "Gensym ActiveXLink"
  :package-authorization-codes (46066 511208 142696 47965)
  :package-name-for-ok-object GENSYM-ACTIVEXLINK
  :additional-information  ("")
  ;; from Doug Loyer
  ;; -- ddm 1/19/98
  )


(def-product-authorization ("GENSYM-ORA" "any")
  :authorization-method g2-package
  :description "OpEx Reachability Analyzer (ORA) v1.0"
  :package-authorization-codes (237678 179172 261544 189023)
  :package-name-for-ok-object GENSYM-ORA
  :additional-information  ("")
  ;; Tim Hill,  Gensym
  ;; 1776 Yorktown, Suite 700, Houston TX 77056
  ;; (713) 623-8000 x232   fax: (713) 623-4004
  ;; -- ddm 2/9/98
  )


(def-product-authorization ("GENSYM-IPRA" "any")
  :authorization-method g2-package
  :description "IP Reachability Analyzer (IPRA) v1.0"
  :package-authorization-codes (507869 327313 41003 35730)
  :package-name-for-ok-object GENSYM-IPRA
  :additional-information  ("")
  ;; Tim Hill,  Gensym
  ;; 1776 Yorktown, Suite 700, Houston TX 77056
  ;; (713) 623-8000 x232   fax: (713) 623-4004
  ;; -- ddm 2/9/98
  )


(def-product-authorization ("GENSYM-DXIOV" "any")
  :authorization-method g2-package
  :description "DxI OpenView v2.0"
  :package-authorization-codes (472770 494542 504796 148973)
  :package-name-for-ok-object GENSYM-DXIOV
  :additional-information  ("")
  ;; Tim Hill,  Gensym
  ;; 1776 Yorktown, Suite 700, Houston TX 77056
  ;; (713) 623-8000 x232   fax: (713) 623-4004
  ;; -- ddm 2/9/98
  )


(def-product-authorization ("GENSYM-OPWEB" "any")
  :authorization-method g2-package
  :description "OpEx Web Interface"
  :package-authorization-codes (408927 257546 39176 303653)
  :package-name-for-ok-object GENSYM-OPWEB
  :additional-information  ("")
  ;; Tim Hill,  Gensym
  ;; 1776 Yorktown, Suite 700, Houston TX 77056
  ;; (713) 623-8000 x232   fax: (713) 623-4004
  ;; -- ddm 2/17/98
  )


(def-product-authorization ("OPMAX" "any")
  :authorization-method g2-package
  :description "3otechnology-opmax"
  :package-authorization-codes (302576 490580 188217 55539)
  :package-name-for-ok-object OPMAX
  :additional-information  ("")
  ;; John Chang,  3o Technology, Inc.
  ;; 3324 Willits, 10-B, Philadelphia PA 19136
  ;; (215) 708-2307  fax: (215) 708-5073
  ;; -- ddm 7/27/98
  )


(def-product-authorization ("GENSYM-FERMENTATION-EXPERT" "any")
  :authorization-method g2-package
  :description "Gensym Fermentation Expert"
  :package-authorization-codes (398313 512100 464355 193234)
  :package-name-for-ok-object GENSYM-FERMENTATION-EXPERT
  :additional-information  ("")
  ;; Mike Wagner, Gensym Chicago office
  ;; -- ddm 7/31/98
  )


(def-product-authorization ("GENSYM-MESSAGE-PARSING-ENGINE" "any")
  :authorization-method g2-package
  :description "Gensym Message Parsing Engine"
  :package-authorization-codes ( 277685 139123 362434 171275 )
  :package-name-for-ok-object GENSYM-MESSAGE-PARSING-ENGINE
  :additional-information  ("")
  ;; Kevin Bolton, Gensym Washington office
  ;; (703)0 266-0203
  ;; -- ddm 2/16/99
  )


(def-product-authorization ("ITE-SDK1" "any")
  :authorization-method g2-package
  :description "ITE Scheduling Development Kit"
  :package-authorization-codes ( 344886 228088 46243 378381 )
  :package-name-for-ok-object ITE-SDK1
  :additional-information  ("")
  ;; Brendan Mitchell, Integrated Technologies Engineering
  ;; P.O. Box 1941, Richards Bay 3900, South Africa
  ;; +27 35 789 2710
  ;; -- ddm 4/23/99
  )


(def-product-authorization ("ACE-TOOLKIT1" "any")
  :authorization-method g2-package
  :description "Ahlstrom ACE Toolkit"
  :package-authorization-codes ( 460164 250997 339986 438731 )
  :package-name-for-ok-object ACE-TOOLKIT1
  :additional-information  ("")
  ;; Pierre Castonguay, Ahlstrom Machinery
  ;; 101 Ridge St., Glen Falls, NY 12801
  ;; (518) 745-2724
  ;; -- ddm 5/5/99
  )


(def-product-authorization ("SMS" "any")
  :authorization-method g2-package
  :description "Startup Management System"
  :package-authorization-codes ( 510700 240627 289027 412475 )
  :package-name-for-ok-object SMS
  :additional-information  ("")
  ;; Alan Fricker, National Power plc
  ;; Windmill Hill Business Park, Whitehill Way, Swindon
  ;; Witshire, UK SN5 6PB  +44 (0)1793 89019
  ;; -- ddm 5/17/99
  )


(def-product-authorization ("IAF" "any")
  :authorization-method g2-package
  :description "Integrated Application Framework"
  :package-authorization-codes ( 488086 241409 467937 471276 )
  :package-name-for-ok-object IAF
  :additional-information  ("")
  ;; Alan Fricker, National Power plc
  ;; Windmill Hill Business Park, Whitehill Way, Swindon
  ;; Witshire, UK SN5 6PB  +44 (0)1793 89019
  ;; -- ddm 5/17/99
  )


(def-product-authorization ("G2PLAYER" "any")
  :authorization-method g2-package
  :description "G2 Player"
  :package-authorization-codes ( 476613 200296 201247 3079 )
  :package-name-for-ok-object G2PLAYER
  :additional-information  ("")
  ;; 
  ;; -- ddm 6/28/99
  )


(def-product-authorization ("NEM" "any")
  :authorization-method g2-package
  :description "Market Trading Decision Support System version 1.0"
  :package-authorization-codes ( 241536 343008 70417 446376 )
  :package-name-for-ok-object NEM
  ;; Don Wilkey, Gensym
  ;; G.P.O. Box 904, Brisbane QLD 4001, Australia
  ;; 462 (7) 3210 2685
  ;; -- ddm 7/30/99
  :additional-information  (""))


(def-product-authorization ("ISIS" "any")
  :authorization-method g2-package
  :description "Incident Simulation System"
  :package-authorization-codes ( 177208 130906 341528 434018 )
  :package-name-for-ok-object ISIS
  ;; Dr. Ludwig Hub, Safety Consulting Institute
  ;; Holeeholzweg 75, Binningen CH 4102, Switzerland
  ;; +41 61 421 8842  sci@onthenet.ch
  ;; -- ddm 8/20/99
  :additional-information  (""))


(def-product-authorization ("GENSYM-E-SCOR" "any")
    :authorization-method g2-package
    :description "Gensym e-SCOR"
    :package-authorization-codes ( 136847 213359 286420 214740 )
    :package-name-for-ok-object GENSYM-E-SCOR
    ;; 
    ;; -- ddm 4/9/99
    :additional-information  (""))


(def-product-authorization ("ABB-PDW-V4" "any")
  :authorization-method g2-package
  :description "ABB-PDW-V4"
  :package-authorization-codes ( 286023 97914 104141 278447 )
  :package-name-for-ok-object ABB-PDW-V4
  ;; From Ticket HQ-3409803
  ;; -- ddm 4/4/00 
  :additional-information  (""))

(def-product-authorization ("ABB-PDE-LIGHT-V4" "any")
  :authorization-method g2-package
  :description "ABB-PDE-V4-LIGHT"
  :package-authorization-codes ( 166031 147205 235247 399939 )
  :package-name-for-ok-object ABB-PDE-LIGHT-V4
  ;; From an email message via Carol Huff (11/3) that's eventually gettin
  ;; to where it needs to go from what looks like the original request
  ;; on 10/27 from Heinz-Dieter.Conradi@de.abb.com
  ;; -- ddm 11/6/00
  :additional-information  (""))


(def-product-authorization ("GENSYM-OPEXPKG1-V3" "any")
  :authorization-method g2-package
  :description "OPEX version 3 package one"
  :package-authorization-codes ( 392511 396330 215039 114427 )
  :package-name-for-ok-object GENSYM-OPEXPKG1-V3
  ;; From Ticket HQ-3533188, msg #15
  ;; -- ddm 7/6/00
  :additional-information  (""))

(def-product-authorization ("GENSYM-OPEXPKG2-V3" "any")
  :authorization-method g2-package
  :description "OPEX version 3 package two"
  :package-authorization-codes ( 375019 432249 257383 487216 )
  :package-name-for-ok-object GENSYM-OPEXPKG2-V3
  ;; From Ticket HQ-3533188, msg #15
  ;; -- ddm 7/6/00
  :additional-information  (""))

(def-product-authorization ("GENSYM-OPEXPKG3-V3" "any")
  :authorization-method g2-package
  :description "OPEX version 3 package three"
  :package-authorization-codes (204096 206553 48602 166818  )
  :package-name-for-ok-object GENSYM-OPEXPKG3-V3
  ;; From Ticket HQ-3533188, msg #15
  ;; -- ddm 7/6/00
  :additional-information  (""))

(def-product-authorization ("GENSYM-OPEXPKG4-V3" "any")
  :authorization-method g2-package
  :description "OPEX version 3 package four"
  :package-authorization-codes ( 202062 115627 15952 49341 )
  :package-name-for-ok-object GENSYM-OPEXPKG4-V3
  ;; From Ticket HQ-3533188, msg #15
  ;; -- ddm 7/6/00
  :additional-information  (""))

(def-product-authorization ("GENSYM-ORBC" "any")
  :authorization-method g2-package
  :description "Orblink Compiler"
  :package-authorization-codes ( 137762 205471 437125 118312 )
  :package-name-for-ok-object GENSYM-ORBC
  ;; Mark Starns jumped up and down -- there's email.
  ;; -- ddm 7/21/00
  :additional-information  (""))

(def-product-authorization ("GENSYM-E-SCOR-ANALYST" "any")
  :authorization-method g2-package
  :description "e-SCOR-ANALYST"
  :package-authorization-codes ( 96122 334481 245963 266601 )
  :package-name-for-ok-object GENSYM-E-SCOR-ANALYST
  ;; Philippe needs these for e-SCOR 2.0
  ;; -- ddm 10/13/00 (Friday the 13th)
  :additional-information  (""))
;; Renamed -- keeping the old version in case we ever
;; have to debug against it. 
(def-product-authorization ("GENSYM-E-SCOR-STANDARD" "any")
  :authorization-method g2-package
  :description "e-SCOR-STANDARD"
  :package-authorization-codes ( 154166 482060 272864 482061 )
  :package-name-for-ok-object GENSYM-E-SCOR-STANDARD
  ;; For Philippe 12/19/00
  :additional-information  (""))

(def-product-authorization ("GENSYM-E-SCOR-DESIGNER" "any")
  :authorization-method g2-package
  :description "e-SCOR-DESIGNER"
  :package-authorization-codes ( 483726 92268 338374 81149 )
  :package-name-for-ok-object GENSYM-E-SCOR-DESIGNER
  ;; Philippe needs these for e-SCOR 2.0
  ;; -- ddm 10/13/00 (Friday the 13th)
  :additional-information  (""))
;; Renamed -- keeping the old version in case we ever
;; have to debug against it. 
(def-product-authorization ("GENSYM-E-SCOR-PROFESSIONAL" "any")
  :authorization-method g2-package
  :description "e-SCOR-PROFESSIONAL"
  :package-authorization-codes ( 435090 461684 185596 287883 )
  :package-name-for-ok-object GENSYM-E-SCOR-PROFESSIONAL
  ;; For Philippe 12/19/00
  :additional-information  (""))

(def-product-authorization ("GENSYM-E-SCOR-MANAGER" "any")
  :authorization-method g2-package
  :description "e-SCOR-MANAGER"
  :package-authorization-codes ( 50127 442013 188193 146267 )
  :package-name-for-ok-object GENSYM-E-SCOR-MANAGER
  ;; Philippe needs these for e-SCOR 2.0
  ;; -- ddm 10/13/00 (Friday the 13th)
  :additional-information  (""))

(def-product-authorization ("GENSYM-E-SCOR-PROFESSIONAL-TEAM" "any")
  :authorization-method g2-package
  :description "e-SCOR-PROFESSIONAL-TEAM"
  :package-authorization-codes (177400 291171 471385 114511)
  :package-name-for-ok-object GENSYM-E-SCOR-PROFESSIONAL-TEAM
  ;; Contact: Philippe Printz
  ;; Registration by MHD, 7/18/01
  :additional-information  (""))

(def-product-authorization ("gensym-escor-v5" "any")
  :authorization-method g2-package
  :description "Gensym e-SCOR, Version 5"
  :package-authorization-codes (336289 149640 473496 450663)
  :package-name-for-ok-object gensym-escor-v5 
  ;; Requested in Ticket HQ-5016328. - jpg 8/1/05
  :additional-information  (""))


(def-product-authorization ("POWERIT-PAX" "any")
  :authorization-method g2-package
  :description "PAX"
  :package-authorization-codes ( 229339 197201 12144 168799 )
  :package-name-for-ok-object POWERIT-PAX
  ;; For Tor Rundstrom, Powerit Generation AB
  ;; P.O. Box 1010, SE-149 25 Nynashahn
  ;; +46 8 520 665 21
  ;; -- ddm 12/19/00
  :additional-information  (""))

(def-product-authorization ("COMPUTAS-IMSPC" "any")
  :authorization-method g2-package
  :description "Computas iMSPC Toolkit version 2.1"
  :package-authorization-codes ( 96239 204184 303908 369029 )
  :package-name-for-ok-object COMPUTAS-IMSPC
  ;; For Stian Aase, saa@computas.com, Computas AS
  ;; P.P. Box 482, 1327 Lysaker, Norway
  ;; +47 67 83 10 00
  ;; -- ddm 12/19/00
  :additional-information  (""))

(def-product-authorization ("SIEMENS-NV-SA_ISCP-FV5" "any")
  :authorization-method g2-package
  :description "ISCP Intelligent Simulation and Controlling Platform"
  :package-authorization-codes (165760 457796 400630 22196)
  :package-name-for-ok-object SIEMENS-NV-SA-ISCP-FV5
  ;; Contact: Peter de Wit
  ;; Requested for:
  ;; Piet Polfliet
  ;; Siemens NV
  ;; Demeurslaan 132 Huizingen
  ;; Belgium
  ;; Requested in Ticket HQ-5290004. - jpg 5/24/06
  :additional-information  (""))

(def-product-authorization ("gensym-jmace-v2" "any")
  :authorization-method g2-package
  :description "Joint Military Art of Command Environment"
  :package-authorization-codes (139475 157347 510380 459482)
  :package-name-for-ok-object gensym-jmace-v2
  ;; Contact: Kim Wilkins
  ;; Requested in Ticket HQ-5371002. - jpg 10/13/06
  :additional-information  (""))

(def-product-authorization ("ANGLO-APET-V1" "any")
  :authorization-method g2-package
  :description "APET (AngloPlatinum)"
  :package-authorization-codes (236903 336350 207415 141442)
  :package-name-for-ok-object anglo-apet-v1
  ;; Contact: Jamie Reid (support team)
  ;; Requested for: AngloPlatinum
  ;; Requested in Ticket #121825 (GENSYMCID-1396). -binghe, 4Mar2015
  :additional-information  (""))

(def-product-authorization ("D2K-TF-V1" "any")
  :authorization-method g2-package
  :description "D2K Technologies"
  :package-authorization-codes (437140 8149 480644 327701)
  :package-name-for-ok-object d2k-tf-v1
  ;; Contact: Madalin Rauch (support team)
  ;; Requested for: D2K Technologies
  ;; Requested in Ticket #21942 (GENSYMCID-1649). -aj, 11Feb2016
  :additional-information  (""))

;(def-product-authorization ("" "any")
;  :authorization-method g2-package
;  :description ""
;  :package-authorization-codes (  )
;  :package-name-for-ok-object xxxxxxxxxx
;  ;; 
;  ;; -- ddm 2/1/00
;  :additional-information  (""))
