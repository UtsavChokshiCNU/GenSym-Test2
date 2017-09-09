;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module PLATFORMS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark H. David

;;; This module contains X Windows machinery and some code to communicate with
;;; the host operating system.



;;;; Forward References in PLATFORMS


(declare-forward-references (:suppress-module-checks-for gsi)

  (reclaim-mouse-pointers-if-g2   function)
  (sync-graphics-on-native-window function windows1)

  (slave-gensym-window?           function windows1)
  #+development (pretty-type-of-gensym-window function windows1)

  (note-change-in-gensym-window function windows4)
  (handle-reshape-event function windows4)

  (reclaim-window-for-workstation function windows1)
  (workstation-dead-p             function windows1)
  (map-to-black-or-white          function windows1)

  (make-or-revise-window          function windows4)

  (refresh-window function panes)
  (lay-out-window function panes)

  (reclaim-workstation-context-stack-if-g2             function)
  (reclaim-workstation-event-queue-if-g2               function workstation)
  (reclaim-non-kb-workspaces-for-this-workstation-only-if-g2 function)
  (reclaim-workstation-tasks                           function telestubs)

  (current-workstation-native-window?     variable telestubs)
  (enqueue-local-paste-availability-event function telestubs)
  (local-clipboard-has-text-p             function telestubs)
  (reclaim-icp-object-map-for-workstation function telestubs)

  #-sbcl (original-icp-window-protocol-version variable platforms)
  (latest-icp-window-protocol-version variable platforms)
  (change-icp-window-protocol-version function windows1)
  (delete-corresponding-object? variable int1)
  (current-workstation                                           variable)
  (current-workstation-window                                   variable)
  (window-supports-request-for-paste-availability-function function)

  (make-block-near-mouse-cache-internal-1 function run)
  (reclaim-block-near-mouse-cache-1 function run)

  #+development (note-use-of-pixmap function WINDOWS1)

  (get-gensym-window-reshape-event-queue function) ; WINDOWS1
  (get-event-queue-of-native-window function)
  (get-reshape-event-queue-of-native-window function)

  (get-background-color-or-tiling-pattern function windows2)
  (get-local-machine-id-function function) ; SEQUENCES1

  (construct-local-event-plist function)   ; WINDOWS4

  (map-client-dialog-id-to-global-dialog-id function)
  (remove-dialog-given-client-id function)
  (charting-library-version? function)                ; NATIVE-TW
  )


;;; `Service-workstations' is an overloaded term.  It is both the
;;; name of the routine responsible for running the UI, and it is
;;; the name of the named extent which contains it's G2 process state.

(def-named-dynamic-extent service-workstations
  (module platforms))



;;; `Workstations-in-service' is a gensym-list of workstations.  It is
;;; the root of the workstation, and window hierarchy.

(declare-special-global workstations-in-service)
(defvar-of-named-dynamic-extent workstations-in-service service-workstations
  (process-binding nil))

(defvar-of-named-dynamic-extent last-workstation-serviced service-workstations
  (process-binding nil))

;;; `Last-session-id-for-g2' is a generator for the session id of each
;;; workstation.  See session-id.

(declare-special-global last-session-id-for-g2)
(defvar-of-named-dynamic-extent last-session-id-for-g2 service-workstations
    (process-binding 0))



;;; A `Session-id' is an integer.  Each time a user connects to G2 the
;;; workstation he connects via is given a fresh session ID.  This session id
;;; can then be used as a key for storing state associated with that session,
;;; for example the last position this user scrolled some object to.

(def-concept session-id)

;; There are not guards against wrap around, etc.  So there is a miniscule
;; chance of duplicate session-id, but frame serial numbers will wrap long
;; before that happens.

;; The fact these are ordered is not used, but I suspect that
;; workstation in service is actually maintained in reverse session-id order.






;;;; Standard Colors




;;; `Standard-gensym-color-alist' is a parameter alist of the form
;;;
;;;    ({(color red green blue alternative-name? not-in-x-color-database?
;;;       new-pastel-color?)})
;;;
;;; where red, green, and blue are the respective rgb assignments.  A variant
;;; spelling of a color may be specified by alternative-name?.  Entries in
;;; standard-gensym-color-alist are sorted alphabetically by color.

;;; The new-pastel-color?  flag signifies a color that was added (from the X11
;;; R5 rgb.txt file) in 3.1.  Only "pastel" colors, i.e., light colors that map
;;; to WHITE on monochrome monitors, were added.  This feature is now under
;;; review.  Note that new-pastel-color?  is now also a global symbol property,
;;; defined in WINDOWS1, and derived from this list.  See the function
;;; derive-standard-gensym-color-data in WINDOWS1.  (MHD 12/17/92)

;;; A `color value vector' is a managed array whose length is equal to the
;;; length of standard-gensym-color-alist.

;;; Standard-gensym-color-alist includes a subset of the colors documented in
;;; Appendix D (pages. 537-538) of the Xlib Reference Manual (1988, O'Reilly and
;;; Associates).  For purposes of mapping names in this alist to names in X, the
;;; hyphens are replaced with spaces and all the letters are changed to
;;; lowercase.  It may be updated to include additions to and reflect changes in
;;; the standard Xlib colors, insofar as that is practical.  Upcoming releases
;;; of X (in 1990 or 1991) may well support hundreds of colors, more than can
;;; typically be maintained at any one time in typical hardware color maps.

;;; The colors PURPLE and DARK-GRAY are also included, even though they are not
;;; part of the X set of colors; these colors were already supported in G2 prior
;;; to adoption of the X set of colors.

;;; Note that the real way to map in X Windows from colors to the "best"
;;; color values is via XParseColor.  The colors in standard-gensym-color-alist
;;; are likely to differ markedly in appearance on different monitors, unless
;;; the rgb values are "tuned" for each monitor in the X implementation.
;;; Implementers of X for specific monitors are both free and encouraged to
;;; "tune" the rgb values appropriately from what is specified in the standard
;;; X11 distribution.  XParseColor is the interface to those "tuned" values.

;;; Since vendors are free to delete any member of the advertised set of colors,
;;; we still need to default to something reasonable for our users, so this
;;; information will need to be present in some form.  (I.e. XParseColor cannot
;;; be guaranteed to return a non-null result for ANY color, even those in the
;;; published set.)

;;; NOTE: For MS Windows, we keep a data structure in C parallel to this.  See
;;; the function make-c-color-array-code, which automates coding of this
;;; parallel c data structure.  Note that this is always the master repository
;;; of name/rgb mapping information.  If this changes, update the C file.  See
;;; make-c-color-array-code for further info.

;;; 3/27/96, mpc: Discovered that the default color values taken from the
;;; Xlib Reference Manual are nowhere near the color they supposedly
;;; represent.  (They're actually for a DEC VR290 display.) This was the
;;; source of our color woes on the Windows platforms, since color names
;;; mean nothing to a PC these rgb pairs were used.  Discovered a table of
;;; color values defined by Netscape/Sun for JavaScript color mapping.
;;; Will use these values rather than the ones from the X manual.
;;; NOTE: I've only fixed values for the colors we use. In the list below,
;;; any color which is commented out should be confirmed before put into
;;; action.

(defvar standard-gensym-color-alist
  ;; If you add to this list, also add to the color-hierarchy parameter
  (optimize-constant
  '((aquamarine 127 255 212)
    (black 0 0 0)
    (blue 0 0 255)
;    (blue-violet 159 95 159)
    (brown 165 42 42)
    (cadet-blue 95 158 160)
    (coral 255 127 80)
;    (cornflower-blue 66 66 111)
    (cyan 0 255 255)
    (dark-gray                                        ; not in X, was introduced in
      128 128 128 dark-grey t)                        ;   post 1.11B G2
;    (dark-green 47 79 47)
;    (dark-olive-green 79 79 47)
;    (dark-orchid 153 50 204)
    (dark-slate-blue 72 61 139)
;    (dark-slate-gray 47 79 79 dark-slate-grey)
;    (dark-turquoise 112 147 219)
    (dim-gray 105 105 105 dim-grey)
;    (firebrick 142 35 35)
    (forest-green 34 139 34)
    (gold 255 215 0)
    (goldenrod 218 165 32)
    (gray 169 169 169 grey)
    (green 0 255 0)
    (green-yellow 173 255 47)
    (indian-red 205 92 92)
    (khaki 240 230 140)
    (light-blue 173 216 230)
    (light-gray 211 211 211 light-grey)                ; was 168 168 168 in Xlib
                                                ;   Programming Manual, but
                                                ;   that was obviously a bug --
                                                ;   notice what gray is!  These
                                                ;   numbers are those used by
                                                ;   our sun (California), and
                                                ;   they're nice because they
                                                ;   map to white
;    (light-steel-blue 143 143 188)
    (lime-green 50 205 50)
    (magenta 255 0 255)
    (maroon 128 0 0)
    (medium-aquamarine 102 205 170)
    (medium-blue 0 0 205)
;    (medium-forest-green 107 142 35)
    (medium-goldenrod 234 234 173)
    (medium-orchid 186 85 211)
;    (medium-sea-green 66 111 66)
;    (medium-slate-blue 127 0 255)
;    (medium-spring-green 127 255 0)
;    (medium-turquoise 112 219 219)
;    (medium-violet-red 219 112 147)
;    (midnight-blue 47 47 79)
;    (navy-blue 35 35 142 navy)
    (orange 255 165 0)
    (pale-green 152 251 152)
    (pink 255 192 203)
    (plum 221 160 221)
    (purple                                        ; not in X, was always in G2;
      128 0 128 nil t)                                ;   same rgb's as blue-violet
    (red 255 0 0)
    (salmon 250 128 114)
;    (sea-green 35 142 107)
    (sienna 160 82 45)
    (sky-blue 135 206 235)
    (slate-blue 106 90 205)
;    (spring-green 0 255 127)
;    (steel-blue 35 107 142)
    (tan 210 180 140)
    (thistle 216 191 216)
    (turquoise 64 224 208)
    (violet 238 130 238)
    (violet-red 204 50 153)
    (wheat 245 222 179)
    (white 255 255 255)                                ; was 252 252 252 in Xlib
                                                ;   Programming Manual, but
                                                ;   that was obviously a bug --
                                                ;   the immediate need to change this
                                                ;   was because it messed up color printing,
                                                ;   forcing there to be a dirty-looking
                                                ;   "off-white" instead of just the white
                                                ;   of the paper.  These
                                                ;   numbers are those used by
                                                ;   our Sun (California), by the
                                                ;   way.

    (yellow 255 255 0)
;    (yellow-green 153 204 50)


    ;; WHAT FOLLOWS: The following colors add new pastels (light colors)
    ;; to G2.  This is being done for version 3.1.  The following is the
    ;; X11R5 new rgb.txt, minus colors that appear above, alternate
    ;; color names for compound names with no hyphens (e.g., GhostWhite
    ;; for ghost-white).  (Note that the rgb values for several of the
    ;; previously defined colors changed in this version.  We'll stick
    ;; to the old values for now.) Then, the "dark" colors are commented
    ;; out, and the "numbered" color variations (e.g., snow1, snow2),
    ;; are commented out.

    ;; Micro notes: New set distributed with X11R5: (MHD 12/15/92) NOTE:
    ;; The sixth element, not-in-x-color-name-database?, is not really
    ;; relevant at this point.  Most of these colors are not in that
    ;; database in X11r4, but they are in the distribution in R5.
    ;; However, I don't believe they're documented.  NOTE 2: the rgb
    ;; values in the x11r5 distribution rgb.txt differ in many cases
    ;; from those given in the x11r4 distribution.  Don't know what to
    ;; do about this.  Note 3: purple was added to the x11r5 rgb.txt
    ;; file; it had been missing in the r4 version, as flagged above.
    ;; (MHD 12/15/92)

    ;; THESE ARE NOW IN REVIEW -- THESE SHOULD NOT BE PUT INTO KBS.  We
    ;; will decide which colors to add, what to do to make them more
    ;; uniform across platforms, review implementation details, and how
    ;; to document this change.  (Implementation issues include handling
    ;; the difference between old rgb values, which have been in G2 and
    ;; were (mostly) published in the X Users Manual, and the new ones
    ;; that appear in the R5 rgb.text file; the current limit of 4
    ;; columns on color menus; what happens if colors get into KBs
    ;; during the review phase and then get removed; is printing SW
    ;; impacted by this; whether 82 (the new total number of different
    ;; colors) too high a number; how to deal with old version of Telewindows,
    ;; which will be unable to display the new colors, and will actually
    ;; end up displaying them as black; etc.) (MHD 12/17/92)

    ;; After review with Ben, Dave, and Lowell, we decided that if names
    ;; are too silly, we couldn't use them.  Then we thought if we could
    ;; get by with just the non-silly names, we might still be able to
    ;; make use of this.  So, I have attempted to judge which names were
    ;; to silly and which were OK below.  So, of the colors that would
    ;; qualify if not for their silly names, I have so marked them and
    ;; commented them out if silly.  (MHD 12/17/92)

    ;; Stats:
    ;;
    ;;        2.0 through 3.0 (previous) number of colors: 44
    ;;       number of light colors, including silly ones: 81
    ;;     new (current) number of non-silly light colors: 63
    ;;
    ;; (MHD 12/17/92)

;    (snow 255 250 250 nil nil t)                ; light - silly
;    (ghost-white 248 248 255 nil nil t)        ; light - silly
    (smoke 245 245 245 white-smoke nil t)        ; light - ok
;    (gainsboro 220 220 220 nil nil t)                ; light - silly
    (Floral-White 255 250 240 nil nil t)        ; light - ok
;    (old-lace 253 245 230 nil nil t)                ; light - silly
    (linen 250 240 230 nil nil t)                ; light - ok
    (antique-white 250 235 215 nil nil t)        ; light - ok
;    (papaya-whip 255 239 213 nil nil t)        ; light - silly
;    (blanched-almond 255 235 205 nil nil t)        ; light - silly
;    (bisque 255 228 196 nil nil t)                ; light - silly
;    (peach-puff 255 218 185 nil nil t)                ; light - silly
;    (navajo-white 255 222 173 nil nil t)        ; light - silly
;    (moccasin 255 228 181 nil nil t)                ; light - silly
;    (cornsilk 255 248 220 nil nil t)                ; light - silly
    (ivory 255 255 240 nil nil t)                ; light - ok
;    (lemon-chiffon 255 250 205 nil nil t)        ; light - silly
;    (seashell 255 245 238 nil nil t)                ; light - silly
;    (honeydew 240 255 240 nil nil t)                ; light - silly
;    (mint-cream 245 255 250 nil nil t)                ; light - silly
    (azure 240 255 255 nil nil t)                ; light - ok
;    (alice-blue 240 248 255 nil nil t)                ; light - silly
    (lavender 230 230 250 nil nil t)                ; light - ok
;    (lavender-blush 255 240 245 nil nil t)        ; light - silly
;    (misty-rose 255 228 225 nil nil t)                ; light - silly
;    (slate-gray 112 128 144)                        ; dark
;    (light-slate-gray 119 136 153)                ; dark
;    (dark-slate-blue 72  61 139)                ; dark
;    (slate-blue 106  90 205)                        ; dark
;    (medium-slate-blue 123 104 238)                ; dark
;    (light-slate-blue 132 112 255)                ; dark
;    (medium-blue 0   0 205)                        ; dark
;    (royal-blue 65 105 225)                        ; dark
;    (dodger-blue 30 144 255)                        ; dark
;    (deep-sky-blue 0 191 255)                        ; dark
;    (sky-blue 135 206 235)                        ; dark
;    (light-sky-blue 135 206 250)                ; dark
;    (steel-blue 70 130 180)                        ; dark
    (light-steel-blue 176 196 222 nil nil t)        ; light - ok
    (powder-blue 176 224 230 nil nil t)                ; light - ok
    (pale-turquoise 175 238 238 nil nil t)        ; light - ok
;    (dark-turquoise 0 206 209)                        ; dark
;    (medium-turquoise 72 209 204)                ; dark
;    (turquoise 64 224 208)                        ; dark
;    (cyan 0 255 255)                                ; dark
    (light-cyan 224 255 255 nil nil t)                ; light - ok
;    (light-sea-green 32 178 170)                ; dark
;    (lawn-green 124 252   0)                        ; dark
;    (chartreuse 127 255   0)                        ; dark
;    (medium-spring-green 0 250 154)                ; dark
;    (lime-green 50 205  50)                        ; dark
;    (yellow-green 154 205  50)                        ; dark
;    (olive-drab 107 142  35)                        ; dark
;    (dark-khaki 189 183 107)                        ; dark
    (pale-goldenrod 238 232 170 nil nil t)        ; light - ok
    (light-goldenrod-yellow 250 250 210 nil nil t)        ; light -ok
    (light-yellow 255 255 224 nil nil t)        ; light - ok
    (light-goldenrod 238 221 130 nil nil t)        ; light - ok
;    (dark-goldenrod 184 134  11)                ; dark
;    (rosy-brown 188 143 143)                        ; dark
;    (saddle-brown 139  69  19)                        ; dark
;    (peru 205 133  63)                                ; dark
;    (burlywood 222 184 135)                        ; dark
    (beige 245 245 220 nil nil t)                ; light - ok
;    (sandy-brown 244 164  96)                        ; dark
;    (chocolate 210 105  30)                        ; dark
;    (dark-salmon 233 150 122)                        ; dark
;    (light-salmon 255 160 122)                        ; dark
;    (dark-orange 255 140   0)                        ; dark
;    (light-coral 240 128 128)                        ; dark
;    (tomato 255  99  71)                        ; dark
;    (orange-red 255  69   0)                        ; dark
;    (hot-pink 255 105 180)                        ; dark
;    (deep-pink 255  20 147)                        ; dark
    (light-pink 255 182 193 nil nil t)                ; light - ok
;    (pale-violet-red 219 112 147)                ; dark
;    (orchid 218 112 214)                        ; dark
;    (dark-violet 148   0 211)                        ; dark
;    (medium-purple 147 112 219)                ; dark
;    (snow1 255 250 250)
;    (snow2 238 233 233)
;    (snow3 205 201 201)
;    (snow4 139 137 137)
;    (seashell1 255 245 238)
;    (seashell2 238 229 222)
;    (seashell3 205 197 191)
;    (seashell4 139 134 130)
;    (AntiqueWhite1 255 239 219)
;    (AntiqueWhite2 238 223 204)
;    (AntiqueWhite3 205 192 176)
;    (AntiqueWhite4 139 131 120)
;    (bisque1 255 228 196)
;    (bisque2 238 213 183)
;    (bisque3 205 183 158)
;    (bisque4 139 125 107)
;    (PeachPuff1 255 218 185)
;    (PeachPuff2 238 203 173)
;    (PeachPuff3 205 175 149)
;    (PeachPuff4 139 119 101)
;    (NavajoWhite1 255 222 173)
;    (NavajoWhite2 238 207 161)
;    (NavajoWhite3 205 179 139)
;    (NavajoWhite4 139 121         94)
;    (LemonChiffon1 255 250 205)
;    (LemonChiffon2 238 233 191)
;    (LemonChiffon3 205 201 165)
;    (LemonChiffon4 139 137 112)
;    (cornsilk1 255 248 220)
;    (cornsilk2 238 232 205)
;    (cornsilk3 205 200 177)
;    (cornsilk4 139 136 120)
;    (ivory1 255 255 240)
;    (ivory2 238 238 224)
;    (ivory3 205 205 193)
;    (ivory4 139 139 131)
;    (honeydew1 240 255 240)
;    (honeydew2 224 238 224)
;    (honeydew3 193 205 193)
;    (honeydew4 131 139 131)
;    (LavenderBlush1 255 240 245)
;    (LavenderBlush2 238 224 229)
;    (LavenderBlush3 205 193 197)
;    (LavenderBlush4 139 131 134)
;    (MistyRose1 255 228 225)
;    (MistyRose2 238 213 210)
;    (MistyRose3 205 183 181)
;    (MistyRose4 139 125 123)
;    (azure1 240 255 255)
;    (azure2 224 238 238)
;    (azure3 193 205 205)
;    (azure4 131 139 139)
;    (SlateBlue1 131 111 255)
;    (SlateBlue2 122 103 238)
;    (SlateBlue3 105  89 205)
;    (SlateBlue4 71  60 139)
;    (RoyalBlue1 72 118 255)
;    (RoyalBlue2 67 110 238)
;    (RoyalBlue3 58  95 205)
;    (RoyalBlue4 39  64 139)
;    (blue1 0   0 255)
;    (blue2 0   0 238)
;    (blue3 0   0 205)
;    (blue4 0   0 139)
;    (DodgerBlue1 30 144 255)
;    (DodgerBlue2 28 134 238)
;    (DodgerBlue3 24 116 205)
;    (DodgerBlue4 16  78 139)
;    (SteelBlue1 99 184 255)
;    (SteelBlue2 92 172 238)
;    (SteelBlue3 79 148 205)
;    (SteelBlue4 54 100 139)
;    (DeepSkyBlue1 0 191 255)
;    (DeepSkyBlue2 0 178 238)
;    (DeepSkyBlue3 0 154 205)
;    (DeepSkyBlue4 0 104 139)
;    (SkyBlue1 135 206 255)
;    (SkyBlue2 126 192 238)
;    (SkyBlue3 108 166 205)
;    (SkyBlue4 74 112 139)
;    (LightSkyBlue1 176 226 255)
;    (LightSkyBlue2 164 211 238)
;    (LightSkyBlue3 141 182 205)
;    (LightSkyBlue4 96 123 139)
;    (SlateGray1 198 226 255)
;    (SlateGray2 185 211 238)
;    (SlateGray3 159 182 205)
;    (SlateGray4 108 123 139)
;    (LightSteelBlue1 202 225 255)
;    (LightSteelBlue2 188 210 238)
;    (LightSteelBlue3 162 181 205)
;    (LightSteelBlue4 110 123 139)
;    (LightBlue1 191 239 255)
;    (LightBlue2 178 223 238)
;    (LightBlue3 154 192 205)
;    (LightBlue4 104 131 139)
;    (LightCyan1 224 255 255)
;    (LightCyan2 209 238 238)
;    (LightCyan3 180 205 205)
;    (LightCyan4 122 139 139)
;    (PaleTurquoise1 187 255 255)
;    (PaleTurquoise2 174 238 238)
;    (PaleTurquoise3 150 205 205)
;    (PaleTurquoise4 102 139 139)
;    (CadetBlue1 152 245 255)
;    (CadetBlue2 142 229 238)
;    (CadetBlue3 122 197 205)
;    (CadetBlue4 83 134 139)
;    (turquoise1 0 245 255)
;    (turquoise2 0 229 238)
;    (turquoise3 0 197 205)
;    (turquoise4 0 134 139)
;    (cyan1 0 255 255)
;    (cyan2 0 238 238)
;    (cyan3 0 205 205)
;    (cyan4 0 139 139)
;    (DarkSlateGray1 151 255 255)
;    (DarkSlateGray2 141 238 238)
;    (DarkSlateGray3 121 205 205)
;    (DarkSlateGray4 82 139 139)
;    (aquamarine1 127 255 212)
;    (aquamarine2 118 238 198)
;    (aquamarine3 102 205 170)
;    (aquamarine4 69 139 116)
;    (DarkSeaGreen1 193 255 193)
;    (DarkSeaGreen2 180 238 180)
;    (DarkSeaGreen3 155 205 155)
;    (DarkSeaGreen4 105 139 105)
;    (SeaGreen1 84 255 159)
;    (SeaGreen2 78 238 148)
;    (SeaGreen3 67 205 128)
;    (SeaGreen4 46 139         87)
;    (PaleGreen1 154 255 154)
;    (PaleGreen2 144 238 144)
;    (PaleGreen3 124 205 124)
;    (PaleGreen4 84 139         84)
;    (SpringGreen1 0 255 127)
;    (SpringGreen2 0 238 118)
;    (SpringGreen3 0 205 102)
;    (SpringGreen4 0 139         69)
;    (green1 0 255          0)
;    (green2 0 238          0)
;    (green3 0 205          0)
;    (green4 0 139          0)
;    (chartreuse1 127 255   0)
;    (chartreuse2 118 238   0)
;    (chartreuse3 102 205   0)
;    (chartreuse4 69 139   0)
;    (OliveDrab1 192 255  62)
;    (OliveDrab2 179 238         58)
;    (OliveDrab3 154 205         50)
;    (OliveDrab4 105 139         34)
;    (DarkOliveGreen1 202 255 112)
;    (DarkOliveGreen2 188 238 104)
;    (DarkOliveGreen3 162 205         90)
;    (DarkOliveGreen4 110 139         61)
;    (khaki1 255 246 143)
;    (khaki2 238 230 133)
;    (khaki3 205 198 115)
;    (khaki4 139 134         78)
;    (LightGoldenrod1 255 236 139)
;    (LightGoldenrod2 238 220 130)
;    (LightGoldenrod3 205 190 112)
;    (LightGoldenrod4 139 129         76)
;    (LightYellow1 255 255 224)
;    (LightYellow2 238 238 209)
;    (LightYellow3 205 205 180)
;    (LightYellow4 139 139 122)
;    (yellow1 255 255          0)
;    (yellow2 238 238          0)
;    (yellow3 205 205          0)
;    (yellow4 139 139          0)
;    (gold1 255 215          0)
;    (gold2 238 201          0)
;    (gold3 205 173          0)
;    (gold4 139 117          0)
;    (goldenrod1 255 193         37)
;    (goldenrod2 238 180         34)
;    (goldenrod3 205 155         29)
;    (goldenrod4 139 105         20)
;    (DarkGoldenrod1 255 185         15)
;    (DarkGoldenrod2 238 173         14)
;    (DarkGoldenrod3 205 149         12)
;    (DarkGoldenrod4 139 101          8)
;    (RosyBrown1 255 193 193)
;    (RosyBrown2 238 180 180)
;    (RosyBrown3 205 155 155)
;    (RosyBrown4 139 105 105)
;    (IndianRed1 255 106 106)
;    (IndianRed2 238  99         99)
;    (IndianRed3 205  85         85)
;    (IndianRed4 139  58         58)
;    (sienna1 255 130         71)
;    (sienna2 238 121         66)
;    (sienna3 205 104         57)
;    (sienna4 139  71         38)
;    (burlywood1 255 211 155)
;    (burlywood2 238 197 145)
;    (burlywood3 205 170 125)
;    (burlywood4 139 115         85)
;    (wheat1 255 231 186)
;    (wheat2 238 216 174)
;    (wheat3 205 186 150)
;    (wheat4 139 126 102)
;    (tan1 255 165         79)
;    (tan2 238 154         73)
;    (tan3 205 133         63)
;    (tan4 139  90         43)
;    (chocolate1 255 127         36)
;    (chocolate2 238 118         33)
;    (chocolate3 205 102         29)
;    (chocolate4 139  69         19)
;    (firebrick1 255  48         48)
;    (firebrick2 238  44         44)
;    (firebrick3 205  38         38)
;    (firebrick4 139  26         26)
;    (brown1 255  64         64)
;    (brown2 238  59         59)
;    (brown3 205  51         51)
;    (brown4 139  35         35)
;    (salmon1 255 140 105)
;    (salmon2 238 130         98)
;    (salmon3 205 112         84)
;    (salmon4 139  76         57)
;    (LightSalmon1 255 160 122)
;    (LightSalmon2 238 149 114)
;    (LightSalmon3 205 129         98)
;    (LightSalmon4 139  87         66)
;    (orange1 255 165          0)
;    (orange2 238 154          0)
;    (orange3 205 133          0)
;    (orange4 139  90          0)
;    (DarkOrange1 255 127          0)
;    (DarkOrange2 238 118          0)
;    (DarkOrange3 205 102          0)
;    (DarkOrange4 139  69          0)
;    (coral1 255 114         86)
;    (coral2 238 106         80)
;    (coral3 205  91         69)
;    (coral4 139  62         47)
;    (tomato1 255  99         71)
;    (tomato2 238  92         66)
;    (tomato3 205  79         57)
;    (tomato4 139  54         38)
;    (OrangeRed1 255  69          0)
;    (OrangeRed2 238  64          0)
;    (OrangeRed3 205  55          0)
;    (OrangeRed4 139  37          0)
;    (red1 255   0          0)
;    (red2 238   0          0)
;    (red3 205   0          0)
;    (red4 139   0          0)
;    (DeepPink1 255  20 147)
;    (DeepPink2 238  18 137)
;    (DeepPink3 205  16 118)
;    (DeepPink4 139  10         80)
;    (HotPink1 255 110 180)
;    (HotPink2 238 106 167)
;    (HotPink3 205  96 144)
;    (HotPink4 139  58  98)
;    (pink1 255 181 197)
;    (pink2 238 169 184)
;    (pink3 205 145 158)
;    (pink4 139  99 108)
;    (LightPink1 255 174 185)
;    (LightPink2 238 162 173)
;    (LightPink3 205 140 149)
;    (LightPink4 139  95 101)
;    (PaleVioletRed1 255 130 171)
;    (PaleVioletRed2 238 121 159)
;    (PaleVioletRed3 205 104 137)
;    (PaleVioletRed4 139  71         93)
;    (maroon1 255  52 179)
;    (maroon2 238  48 167)
;    (maroon3 205  41 144)
;    (maroon4 139  28         98)
;    (VioletRed1 255  62 150)
;    (VioletRed2 238  58 140)
;    (VioletRed3 205  50 120)
;    (VioletRed4 139  34         82)
;    (magenta1 255   0 255)
;    (magenta2 238   0 238)
;    (magenta3 205   0 205)
;    (magenta4 139   0 139)
;    (orchid1 255 131 250)
;    (orchid2 238 122 233)
;    (orchid3 205 105 201)
;    (orchid4 139  71 137)
;    (plum1 255 187 255)
;    (plum2 238 174 238)
;    (plum3 205 150 205)
;    (plum4 139 102 139)
;    (MediumOrchid1 224 102 255)
;    (MediumOrchid2 209  95 238)
;    (MediumOrchid3 180  82 205)
;    (MediumOrchid4 122  55 139)
;    (DarkOrchid1 191  62 255)
;    (DarkOrchid2 178  58 238)
;    (DarkOrchid3 154  50 205)
;    (DarkOrchid4 104  34 139)
;    (purple1 155  48 255)
;    (purple2 145  44 238)
;    (purple3 125  38 205)
;    (purple4 85  26 139)
;    (MediumPurple1 171 130 255)
;    (MediumPurple2 159 121 238)
;    (MediumPurple3 137 104 205)
;    (MediumPurple4 93  71 139)
;    (thistle1 255 225 255)
;    (thistle2 238 210 238)
;    (thistle3 205 181 205)
;    (thistle4 139 123 139)
;    (gray0 0   0   0)
;    (grey0 0   0   0)
;    (gray1 3   3   3)
;    (grey1 3   3   3)
;    (gray2 5   5   5)
;    (grey2 5   5   5)
;    (gray3 8   8   8)
;    (grey3 8   8   8)
;    (gray4 10  10  10)
;    (grey4 10  10  10)
;    (gray5 13  13  13)
;    (grey5 13  13  13)
;    (gray6 15  15  15)
;    (grey6 15  15  15)
;    (gray7 18  18  18)
;    (grey7 18  18  18)
;    (gray8 20  20  20)
;    (grey8 20  20  20)
;    (gray9 23  23  23)
;    (grey9 23  23  23)
;    (gray10 26  26  26)
;    (grey10 26  26  26)
;    (gray11 28  28  28)
;    (grey11 28  28  28)
;    (gray12 31  31  31)
;    (grey12 31  31  31)
;    (gray13 33  33  33)
;    (grey13 33  33  33)
;    (gray14 36  36  36)
;    (grey14 36  36  36)
;    (gray15 38  38  38)
;    (grey15 38  38  38)
;    (gray16 41  41  41)
;    (grey16 41  41  41)
;    (gray17 43  43  43)
;    (grey17 43  43  43)
;    (gray18 46  46  46)
;    (grey18 46  46  46)
;    (gray19 48  48  48)
;    (grey19 48  48  48)
;    (gray20 51  51  51)
;    (grey20 51  51  51)
;    (gray21 54  54  54)
;    (grey21 54  54  54)
;    (gray22 56  56  56)
;    (grey22 56  56  56)
;    (gray23 59  59  59)
;    (grey23 59  59  59)
;    (gray24 61  61  61)
;    (grey24 61  61  61)
;    (gray25 64  64  64)
;    (grey25 64  64  64)
;    (gray26 66  66  66)
;    (grey26 66  66  66)
;    (gray27 69  69  69)
;    (grey27 69  69  69)
;    (gray28 71  71  71)
;    (grey28 71  71  71)
;    (gray29 74  74  74)
;    (grey29 74  74  74)
;    (gray30 77  77  77)
;    (grey30 77  77  77)
;    (gray31 79  79  79)
;    (grey31 79  79  79)
;    (gray32 82  82  82)
;    (grey32 82  82  82)
;    (gray33 84  84  84)
;    (grey33 84  84  84)
;    (gray34 87  87  87)
;    (grey34 87  87  87)
;    (gray35 89  89  89)
;    (grey35 89  89  89)
;    (gray36 92  92  92)
;    (grey36 92  92  92)
;    (gray37 94  94  94)
;    (grey37 94  94  94)
;    (gray38 97  97  97)
;    (grey38 97  97  97)
;    (gray39 99  99  99)
;    (grey39 99  99  99)
;    (gray40 102 102 102)
;    (grey40 102 102 102)
;    (gray41 105 105 105)
;    (grey41 105 105 105)
;    (gray42 107 107 107)
;    (grey42 107 107 107)
;    (gray43 110 110 110)
;    (grey43 110 110 110)
;    (gray44 112 112 112)
;    (grey44 112 112 112)
;    (gray45 115 115 115)
;    (grey45 115 115 115)
;    (gray46 117 117 117)
;    (grey46 117 117 117)
;    (gray47 120 120 120)
;    (grey47 120 120 120)
;    (gray48 122 122 122)
;    (grey48 122 122 122)
;    (gray49 125 125 125)
;    (grey49 125 125 125)
;    (gray50 127 127 127)
;    (grey50 127 127 127)
;    (gray51 130 130 130)
;    (grey51 130 130 130)
;    (gray52 133 133 133)
;    (grey52 133 133 133)
;    (gray53 135 135 135)
;    (grey53 135 135 135)
;    (gray54 138 138 138)
;    (grey54 138 138 138)
;    (gray55 140 140 140)
;    (grey55 140 140 140)
;    (gray56 143 143 143)
;    (grey56 143 143 143)
;    (gray57 145 145 145)
;    (grey57 145 145 145)
;    (gray58 148 148 148)
;    (grey58 148 148 148)
;    (gray59 150 150 150)
;    (grey59 150 150 150)
;    (gray60 153 153 153)
;    (grey60 153 153 153)
;    (gray61 156 156 156)
;    (grey61 156 156 156)
;    (gray62 158 158 158)
;    (grey62 158 158 158)
;    (gray63 161 161 161)
;    (grey63 161 161 161)
;    (gray64 163 163 163)
;    (grey64 163 163 163)
;    (gray65 166 166 166)
;    (grey65 166 166 166)
;    (gray66 168 168 168)
;    (grey66 168 168 168)
;    (gray67 171 171 171)
;    (grey67 171 171 171)
;    (gray68 173 173 173)
;    (grey68 173 173 173)
;    (gray69 176 176 176)
;    (grey69 176 176 176)
;    (gray70 179 179 179)
;    (grey70 179 179 179)
;    (gray71 181 181 181)
;    (grey71 181 181 181)
;    (gray72 184 184 184)
;    (grey72 184 184 184)
;    (gray73 186 186 186)
;    (grey73 186 186 186)
;    (gray74 189 189 189)
;    (grey74 189 189 189)
;    (gray75 191 191 191)
;    (grey75 191 191 191)
;    (gray76 194 194 194)
;    (grey76 194 194 194)
;    (gray77 196 196 196)
;    (grey77 196 196 196)
;    (gray78 199 199 199)
;    (grey78 199 199 199)
;    (gray79 201 201 201)
;    (grey79 201 201 201)
;    (gray80 204 204 204)
;    (grey80 204 204 204)
;    (gray81 207 207 207)
;    (grey81 207 207 207)
;    (gray82 209 209 209)
;    (grey82 209 209 209)
;    (gray83 212 212 212)
;    (grey83 212 212 212)
;    (gray84 214 214 214)
;    (grey84 214 214 214)
;    (gray85 217 217 217)
;    (grey85 217 217 217)
;    (gray86 219 219 219)
;    (grey86 219 219 219)
;    (gray87 222 222 222)
;    (grey87 222 222 222)
;    (gray88 224 224 224)
;    (grey88 224 224 224)
;    (gray89 227 227 227)
;    (grey89 227 227 227)
;    (gray90 229 229 229)
;    (grey90 229 229 229)
    (extra-light-gray 229 229 229 extra-light-grey nil t)        ; NOT IN X, R4 or R5; same as gray90
;    (gray91 232 232 232)
;    (grey91 232 232 232)
;    (gray92 235 235 235)
;    (grey92 235 235 235)
;    (gray93 237 237 237)
;    (grey93 237 237 237)
;    (gray94 240 240 240)
;    (grey94 240 240 240)
;    (gray95 242 242 242)
;    (grey95 242 242 242)
;    (gray96 245 245 245)
;    (grey96 245 245 245)
;    (gray97 247 247 247)
;    (grey97 247 247 247)
;    (gray98 250 250 250)
;    (grey98 250 250 250)
;    (gray99 252 252 252)
;    (grey99 252 252 252)
;    (gray100 255 255 255)
;    (grey100 255 255 255)


    )))

;;; http://en.wikipedia.org/wiki/YIQ
;;; Y = (0.299, 0.587, 0.144) (R,G,B) gives pure black & white translation for RGB
(defun-simple rgb2gray (r g b)
  (round (+e (*e (coerce-fixnum-to-gensym-float r) 0.299d0)
             (*e (coerce-fixnum-to-gensym-float g) 0.587d0)
             (*e (coerce-fixnum-to-gensym-float b) 0.114d0))))

;;; This parameter is used by `emit-printing-color-map' to generate the `gray-color-map'.
(defparameter gray-gensym-color-alist
  (loop for (color r g b) in standard-gensym-color-alist
        for c = (rgb2gray r g b)
        collect (list color c c c)))

;; To do: put the new colors into "color-hierarchy", below! (MHD 3/19/93)
;; Here are the new colors:
;;
;;  (smoke floral-white linen antique-white ivory azure lavender
;;   light-steel-blue powder-blue pale-turquoise light-cyan
;;   pale-goldenrod light-goldenrod-yellow light-yellow
;;   light-goldenrod beige light-pink)

#+development
(defun print-report-of-gensym-rgb-values ()
  (format t "~25,S~5,S~5,S~5,S~%" "Color" "Red" "Green" "Blue")
  (loop for (name r g b) in standard-gensym-color-alist
        do
    (format t "~25,A~5,A~5,A~5,A~%" name r g b)))


;;; `Color-hierarchy' is a parameter which holds a tree of the standard
;;; Gensym colors.  If the allocation of the non-root colors fail, then
;;; an attempt will be made to allocate the color of parent of the non-root
;;; node to the node.  The two root colors are black and white.

(defvar color-hierarchy
  (optimize-constant
    '(root
      (black
       (red
        (orange
          (gold
            khaki
            sienna
            tan)
          coral)
        (brown
          (magenta
            thistle
            violet-red
            pink)
          (maroon
            salmon
            indian-red)))
       (blue
        (purple
          (light-blue
            medium-blue
            sky-blue)
          (cadet-blue
            slate-blue
            dark-slate-blue)
          (violet
            medium-orchid
            plum))
        gray
        (dark-gray
          dim-gray)))
      (white
       (yellow
        (goldenrod
          wheat
          ;; new pastels:   (MHD 4/22/93)
          light-goldenrod-yellow light-yellow light-goldenrod
          )
        medium-goldenrod)
       (green
        (pale-green
          lime-green
          green-yellow
          cyan)
        (forest-green
          medium-aquamarine
          aquamarine
          turquoise))
       light-gray
       ;; new grays:     (MHD 4/25/93)
       extra-light-gray
       ;; new pastels:   (MHD 4/22/93)
       smoke floral-white linen antique-white ivory
       azure lavender light-steel-blue powder-blue
       pale-turquoise light-cyan pale-goldenrod
       beige light-pink
       ))))



;;; `Standard-gensym-color-subset' ...

(defparameter standard-gensym-color-subset
  '(black white
    red orange
    yellow green blue
                purple brown
                light-gray gray
                dark-gray))

;; Standard-gensym-color-subset started as the local variable standard-color-subset
;; in the function post-color-choice-menu in FACILITIES.

;; Remember to touch GRAMMAR2 for recompilation when this changes, since macro
;; def-semi-open-category-color there uses this list at macroexpansion time.

;; Specs for Colors in G2 Prior to 2.0 Beta 2:
;;
;; Color                     X Windows              Mac                        TI Explorer
;; -----------------------------------------------------------------------------
;; white                "white"                (1.0 1.0 1.0)                w::white
;; black                 "black"                (0.0 0.0 0.0)                w::black
;; light gray            "#cccccc"        (0.8 0.8 0.8)                w::25%-gray-color
;; gray                        "#9999b3"        (0.6 0.6 0.7)                w::50%-gray-color
;; dark gray                "#808080"        (0.5 0.5 0.5)                w::75%-gray-color
;; red                        "#dd0000"        (1.0 0.0 0.0)                w::red
;; green                "#00dd00"        (0.0 1.0 0.0)                w::green
;; blue                        "#0000dd"        (0.0 0.0 1.0)                w::blue
;; yellow                "yellow"        (1.0 0.9 0.0)                w::yellow
;; purple                "blue violet"        (1.0 0.0 1.0)                w::purple
;; brown                "brown"                (0.7 0.4 0.4)                w::light-brown
;; orange                "coral"                (1.0 0.44 0.0)                w::orange
;; aquamarine                "#0da4ab"        (0.05 0.64 0.67)        w::blue-green
;;
;; Note that specs are idiosyncratic to the particular implementation in question.






;;; `Make-c-color-array-code' is a development-only function.  It writes
;;; to standard output C code that looks like this:
;;;
;;;   #define NUM_COLORS 69   /* There are 69 colors defined in the X windows system. */
;;;   XCOLOR XColorArray[NUM_COLORS] =
;;;   {
;;;    "antique white", RGB( 250, 235, 215),
;;;    "aquamarine", RGB( 127, 255, 212),
;;;    "azure", RGB( 240, 255, 255),
;;;    .
;;;    .
;;;    .
;;;   };
;;;
;;;  This is the code that should be in the ext (C) file g2.h.  Whenever
;;;  standard-gensym-color-alist changes, this function should be run, and
;;;  its output text used to replace the appropriate code in g2.h.

#+development
(defun make-c-color-array-code ()
  (loop for (color red green blue alternative-name?)
            in standard-gensym-color-alist
        collect (format nil "\"~a\", RGB(~d, ~d, ~d);"
                        (copy-symbol-name color nil t)
                        red green blue)
        into all-entries
        count t into number-of-entries
        when alternative-name?
          collect (format nil "\"~a\", RGB(~d, ~d, ~d)"
                          (copy-symbol-name alternative-name? nil t)
                          red green blue)
          into all-entries
          and count t into number-of-entries
        finally
          (format t "~
                     ~%#define NUM_COLORS ~d    /* There are ~d colors ~
                     defined in the X windows system. */~
                     ~%XCOLOR XColorArray[NUM_COLORS] =~%{~%"
                  number-of-entries number-of-entries)
          (loop for entry in all-entries do
            (format t "   ~a~%" entry))
          (format t "};~%")))














(defvar native-window-notices-enter-and-leave-events-p nil)

#+development
(defun decode-x11-event-code (code)
  (declare (type fixnum code))
  (case (logandf code x11-event-codes-mask)
    (#.x11-no-more-events        "x11-no-more-events")
    (#.x11-nullevent                "x11-nullevent")
    (#.x11-keypress                "x11-keypress")
    (#.x11-button-press                "x11-button-press")
    (#.x11-button-release        "x11-button-release")
    (#.x11-pointer-motion        "x11-pointer-motion")
    (#.x11-exposure                "x11-exposure")
    (#.x11-reshape                "x11-reshape")
    (#.x11-enter                "x11-enter-window")
    (#.x11-leave                "x11-leave-window")
    (#.x11-focus-in                "x11-focus-in")
    (#.x11-focus-out                "x11-focus-out")
    (#.x11-control                "x11-control")
    ))




#+development
(defun describe-event (event-code)
  (let ((key-code (ashf event-code (- x11-number-of-bits-in-event-codes))))
    (format t "Event type is ~a~%" (decode-x11-event-code event-code))
    (format t "Key, if any,  is ~a~%" (key-name key-code))
    event-code))




;;; The function `x11-display-specified-p' will return t if the X windows
;;; display is specified (typically by the "-display" command-line keyword
;;; argument) or if the window system on the current platform does not need such
;;; a specification.  Otherwise, this function returns nil.  This function might
;;; cons.

(def-substitution-macro platform-does-not-need-x11-display-p ()
  (windows-platform-p))

(defun-simple x11-display-specified-p ()
  (if (or (platform-does-not-need-x11-display-p)
          (get-command-line-keyword-argument '#.(stringw "display")))
      t
      nil))

;; Q: Why was this specified to return T? (MHD)
;; A: So callers don't try to get the actual command-line argument from it (jh,
;; 6/14/94).



;;; The function `no-local-window-p' will return non-nil if the command line has
;;; indicated that G2 should run without a local window.  This is expressed by
;;; suppling the "-no-window" flag.  (That flag had been known as "-nowindow"
;;; prior to 8.1r0 and we still support that, but we prefer "-no-window", with
;;; the hyphen.)  As of 8.1r0, however, we document the "-local-window" flag,
;;; and this may give us an opportunity to change the default setting, and make
;;; G2 run headless UNLESS -local-window is found on the Unix command line.  For
;;; now, we don't actually pay any attention to the presence or absence of
;;; "-local-window" on the command line.  -jv, 1/24/05

#-mtg2 (defparameter no-local-window-p-cached nil)
#-mtg2 (defvar-of-special-global no-local-window-p) ; a cache

#+mtg2 (defvar no-local-window-p-cached nil)
#+mtg2 (defvar no-local-window-p nil) ; a cache

(defun-simple no-local-window-p ()
  ;; Some day?
  ;; (not (get-command-line-flag-argument '#.(stringw "local-window")))
  (if no-local-window-p-cached
      no-local-window-p
    (prog1 (setq no-local-window-p
                 (or (get-command-line-flag-argument '#.(stringw "no-window"))
                     (get-command-line-flag-argument '#.(stringw "nowindow"))))
      (setq no-local-window-p-cached t))))

;;; The function/macro `c-x11-initialize-after-connection' initializes the
;;; native window for the latest G2 connection (i.e., including reroutes).  See
;;; windows.c, msmain.c, and TELEWINDOWS for further information.

(def-gensym-c-function c-x11-initialize-after-connection
  (:void "g2ext_x11_initialize_after_connection")
  ((:pointer gensym-x-window)
   (:fixnum-int icp-window-protocol-version)
   (:fixnum-int unicode-character-events-ok-p)
   (:fixnum-int xclip-p)))


(def-gensym-c-function c-x11-set-window-is-connected
  (:fixnum-int "g2ext_x11_set_window_is_connected")
  ((:pointer gensym-x-window)))


;;; `x-events-pending?' checks if anything is waiting in the X queue

(def-gensym-c-function x-events-pending?
                       (:fixnum-int "g2ext_is_XPendingp")
  ())


;;; The function/macro `c-x11-screen-depth' returns the size of screen
;;; pixels in bits.

(def-gensym-c-function c-x11-screen-depth (:fixnum-int "g2ext_x11_screen_depth")
  ((:pointer gensym-x-window)))


;;; `c-x11-raise-window' raises a gensym X window above any other X windows
;;; on the screen (strictly above any on its superior window, which is currently
;;; the root window).  -fmw, 9/15/93

#+development
(def-gensym-c-function c-x11-raise-window (:fixnum-int "g2ext_x11_raise_window")
  ((:pointer gensym-x-window)))


;;; The function `raise-application-window' brings G2 to the top of the stack in
;;; the native window system.
;; -fmw, 9/15/93

;; Currently used only by the development-only `break' command. -fmw, 11/11/03

#+development
(defun raise-application-window (gensym-x-window)
  (c-x11-raise-window gensym-x-window))




;;;; Cut and Paste functions

;; Historical and explanatory note: The first cut and paste functions involved
;; use of the X11 cut buffers, which are meant only for text. Later, the X11
;; clipboard came into use, along with the MS Windows Clipboard. Thus, many
;; functions and variables are still called ...x11-cut-buffer-..., even though
;; they work with the clipboard on either the MS Windows NT or any X windows
;; platform. (LGibson 7-31-97).

;;; The function `current-selection-in-native-window-system?' returns the
;;; current X selection on local X display, or nil.  The string is a newly
;;; allocated simple gensym string, and should be liberated with
;;; `reclaim-simple-text-string'.

(defparameter maximum-x11-cut-buffer-length (expt 2 15))

;; The max in X is 2^15; seems adequate for our purposes, but
;; consider increasing this at some later point. (MHD 4/10/97)

;(defun current-selection-in-native-window-system? (&optional native-window?)
;  (when native-window?                        ; should be an integer
;    (read-x-window-cut-buffer native-window?)))

;;; `Read-x-window-cut-buffer' reads in the contents of text-string to the X cut
;;; buffer.  The result is returned as a new text string.  Note that at present,
;;; this may return a zero-length string, and it can never return a value other
;;; than a string.

(defun read-x-window-cut-buffer (gensym-x-window)
  (let ((cut-buffer-string
          (obtain-simple-gensym-string
            maximum-x11-cut-buffer-length)))
    (let ((length
            (c-x11-read-cut-buffer
              gensym-x-window cut-buffer-string
              ;; room for null byte:  (nec?!)
              (-f maximum-x11-cut-buffer-length 1))))
      (prog1 (if (>f length 0)
                 (import-text-string cut-buffer-string 'x-cut-buffer 0 length)
                 (obtain-text-string 0)) ; return a 0-length string if nothing
        (reclaim-gensym-string cut-buffer-string)))))



;;; `c-x11-read-cut-buffer' copies the contents of X cut buffer 0 into STRING.
;;; and returns the number of bytes copied, up to a maximum of MAX-SIZE.

(def-gensym-c-function c-x11-read-cut-buffer
    (:fixnum-int "g2ext_x11_read_cut_buffer")
  ((:pointer gensym-x-window)
   (:string string)
   (:fixnum-int max-size)))



;;; `Write-x-window-cut-buffer' writes out the contents of text-string to the X
;;; cut buffer.  This translates unicode characters as necessary to the
;;; character encoding used for the cut buffer. The plan is to write to the
;;; buffer under as many formats as possible (UNICODE and text at this
;;; point). Note that it may not be possible for all characters to be exported
;;; properly.  This does the best that it can.

(defun write-x-window-cut-buffer (gensym-x-window text-string)
  (let ((string (export-text-string text-string 'x-cut-buffer)))
    (c-x11-write-cut-buffer gensym-x-window string (length string))
    (reclaim-gensym-string string)))



;;; The def-gensym-c-function `c-x11-write-cut-buffer' copies the first length
;;; characters of string, a Gensym (Lisp) string, into the X cut buffer.

(def-gensym-c-function c-x11-write-cut-buffer
    (:fixnum-int "g2ext_x11_write_cut_buffer")
  ((:pointer gensym-x-window)
   (:string string)
   (:fixnum-int length)))



;;; The def-gensym-c-function `c-x11-clipboard-has-text' returns zero (0) if
;;; pasted text is available.  Otherwise, it returns a non-zero integer.

(def-gensym-c-function c-x11-clipboard-has-text
    (:fixnum-int "g2ext_x11_clipboard_has_text")
  ((:pointer gensym-x-window)))


;;; The def-gensym-c-function `c-x11-clipboard-x-targets-p' returns 1 (1) if X
;;; targets should be use.  Otherwise, it returns 0, and MS windows targets
;;; should be used.  `X targets' are string, x compound text, and (Gensym's)
;;; Unicode.  `MS Windows targets' are cf-text and cf-unicode.

(def-gensym-c-function c-x11-clipboard-x-targets-p
    (:fixnum-int "g2ext_x11_clipboard_x_targets_p")
  ((:pointer gensym-x-window)))



;;; `Write-clipboard', `read-clipboard', `c-write-clipboard', `c-read-clipboard'
;;;
;;; This calls the C foreign function with clipboard text args in the following
;;; formats for X:
;;;
;;;   (1) Latin-1-string: Latin-1 with LF characters between lines;
;;;   (2) X-compound-text-string: X compound text with LF characters
;;;       between lines;
;;;   (3) Unicode-text-string: Unicode text with Gensym's native
;;;       linebreak character (Unicode Line Separator)
;;;
;;; Otherwise, this is presumably MS Windows, and these formats are supplied:
;;;
;;;   (1) Latin-1-string: CF_TEXT format, i.e., Latin-1 with CR/LF
;;;       character pairs between lines;
;;;   (2) X-compound-text-string: an empty string (which is then
;;;       not used on the C side);
;;;   (3) Unicode-text-string: CF_UNICODE_TEXT format, i.e., Unicode
;;;       text with CR/LF character pairs between lines

(defun write-clipboard (gensym-x-window text-string)
  (let* ((x-targets-p (c-x11-clipboard-x-targets-p gensym-x-window))
         (latin-1-string
           (export-text-string
             text-string
             (if x-targets-p
                 'x-string
                 'cf-text)))
         (latin-1-string-length
           (gensym-string-length latin-1-string))
         (x-compound-text-string
           (if x-targets-p
               (export-text-string text-string 'x-compound-text-string)
               (obtain-gensym-string 0)))
         (x-compound-text-string-length
           (gensym-string-length x-compound-text-string))
         (unicode-text-string
           (export-text-string
             text-string
             (if x-targets-p
                 'unicode
                 'cf-unicode-text)))
         (unicode-text-string-length
           (wide-string-length unicode-text-string)))
    (prog1 (c-write-clipboard
             gensym-x-window
             latin-1-string latin-1-string-length
             x-compound-text-string x-compound-text-string-length
             unicode-text-string unicode-text-string-length)
      (reclaim-gensym-string latin-1-string)
      (reclaim-gensym-string x-compound-text-string)
      (reclaim-wide-string unicode-text-string))))

(def-gensym-c-function c-write-clipboard
    (:fixnum-int "g2ext_write_clipboards")
  ((:pointer gensym-x-window)
   (:string latin-1-string)
   (:fixnum-int latin-1-string-length)
   (:string x-compound-text-string)
   (:fixnum-int x-compound-text-string-length)
   (:byte-vector-16 unicode-text-string)
   (:fixnum-int unicode-text-string-length)))



(defun read-clipboard (gensym-x-window)
  (let* ((latin-1-string
           (obtain-simple-gensym-string allocated-clipboard-text-length))
         (x-compound-text-string
           (obtain-simple-gensym-string allocated-clipboard-text-length))
         (unicode-text-string
           (obtain-text-string allocated-clipboard-text-length))
         (clipboard-reading-results-vector
           (make-wide-string clipboard-reading-results-vector-length)))
    (c-read-clipboard
      gensym-x-window
      latin-1-string specified-max-clipboard-text-length 1
      x-compound-text-string specified-max-clipboard-text-length 1
      unicode-text-string specified-max-clipboard-text-length 1
      clipboard-reading-results-vector)
    (let* ((latin-1-result
             (wide-character-code
               (charw
                 clipboard-reading-results-vector
                 latin-1-clipboard-read-results-entry)))
           (x-compound-text-result
             (wide-character-code
               (charw
                 clipboard-reading-results-vector
                 x-compound-text-clipboard-read-results-entry)))
           (unicode-text-result
             (wide-character-code
               (charw
                 clipboard-reading-results-vector
                 unicode-text-clipboard-read-results-entry))))
      (prog1
          (cond
            ((/=f unicode-text-result
                  clipboard-read-results-failure-code)
             (import-text-string
               unicode-text-string 'unicode 0 unicode-text-result))
            ((/=f x-compound-text-result
                  clipboard-read-results-failure-code)
             (import-text-string
               x-compound-text-string 'x-compound-text-string 0 x-compound-text-result))
            ((/=f latin-1-result
                  clipboard-read-results-failure-code)
             (import-text-string
               latin-1-string 'iso-8859-1-gensym-string 0 latin-1-result))
            (t
             (copy-constant-wide-string #w"")))
        (reclaim-wide-string clipboard-reading-results-vector)
        (reclaim-gensym-string latin-1-string)
        (reclaim-gensym-string x-compound-text-string)
        (reclaim-text-string unicode-text-string)))))


(def-gensym-c-function c-read-clipboard
    (:fixnum-int "g2ext_read_clipboards")
  ((:pointer gensym-x-window)
   (:string latin-1-string)
   (:fixnum-int latin-1-string-max-length)
   (:fixnum-int latin-1-string-desired_p)
   (:string x-compound-text-string)
   (:fixnum-int x-compound-text-string-max-length)
   (:fixnum-int x-compound-text-string-desired_p)
   (:byte-vector-16 unicode-text-string)
   (:fixnum-int unicode-text-string-max-length)
   (:fixnum-int unicode-text-string-desired_p)
   (:byte-vector-16 result-vector)))



;;;; More functions


;;; The def-gensym-c-function `c-x11-file-descriptor-for-window' returns the
;;; file descriptor of the stream on which incoming events for the given Gensym
;;; window index arrive.  G2 assumes that a select() on the returned file
;;; descriptor will return whenever there is a pending event on the window.  If
;;; no file descriptor which satisfies this property can be found, then -1 is
;;; returned.
;; -fmw, 11/3/93

(def-gensym-c-function c-x11-file-descriptor-for-window
    (:fixnum-int "g2ext_x11_file_descriptor_for_window")
  ((:pointer gensym-x-window)))


(defun file-descriptor-for-native-window (gensym-x-window)
  (c-x11-file-descriptor-for-window gensym-x-window))

;; I'm not sure that this stub is needed.




;; jh, 7/12/91.  We now use x11-preinitialized-p to help with the authorization
;; checks for embedded G2.  Thus it is 1 when windows have been supressed and 0
;; otherwise, rather than a simple t.  We might consider changing its name to
;; something more devious.

(defvar x11-preinitialized-p nil)

(defmacro g2-running-without-local-window-p ()
  `(and x11-preinitialized-p
        (=f x11-preinitialized-p 1)))

(defmacro g2-running-in-window-mode-p ()
  `(and x11-preinitialized-p
        (=f x11-preinitialized-p 0)))


;;; `print-display-error' prints an error message
;;; indicating that the X11 window display is missing, so
;;; no window can be created and the startup must be
;;; aborted.


(defun print-display-error ()
  (format t "~&The X11 window display has not been specified in either")
  (format t "~%the command line or the environment variable DISPLAY.")
  (format t "~%Aborting ")
  (format t (current-system-case
                   (ab "G2 ")
                   (telewindows "TW ")
                   (t "")))
  (format t "startup.~%"))


;; jh, 8/15/91.  Changed local-gensym-x11-display to determine the operating
;; system at runtime and react differently.  This maintains backward
;; compatability to the days when we compiled on the same platform we ran on.

(defvar cached-local-gensym-x11-display #+chestnut-3 nil #-chestnut-3 ":0.0") ;SS_G2L

(defun local-gensym-x11-display ()
  (or cached-local-gensym-x11-display
      (setq cached-local-gensym-x11-display
            (get-gensym-environment-variable "DISPLAY"))))


;;; The function `get-default-x11-display' ...  attempts to get the display name
;;; from the command line and then the environment variable DISPLAY.  If no
;;; display name is found and the window system on the current platform needs a
;;; display name, this function calls exit-lisp-process to exit the system.

(defun-simple get-default-x11-display ()
  (cond ((or (g2-running-without-local-window-p)
             (platform-does-not-need-x11-display-p))
         ":0")                                                    ; Never used (jh,2/10/92)
        (t
         (let ((x11-display?
                 (get-command-line-keyword-argument '#.(stringw "display"))))
           (or x11-display?
               (local-gensym-x11-display)
               (progn
                 (print-display-error)
                 #-development
                 (exit-lisp-process)))))))

;; jh, 2/10/92.  Changed get-default-x11-display to check if G2 is running
;; without a local window before looking for an X11 display.  G2 does not need a
;; display in headless mode, and it shouldn't quit if it doesn't find one.




;;; The function `get-window-name-from-command-line-if-any' gets the value for
;;; the user-specified -name command line keyword arg.  [As of the release
;;; pending 10/15/00, and also prior to 5.0, i.e., 4.1 & earlier:] the text is
;;; to undergo no import, i.e., stays a Lisp string, and undergoes no character
;;; set translation, but is passed straight through to the window system for
;;; display in the current window system's locale.

(defun get-window-name-from-command-line-if-any ()
  (get-command-line-keyword-argument '#.(stringw "name") 1 t))





;;; The function `get-icon-name-from-command-line-if-any' is similar to the
;;; above function, but specifies just the text to be shown in an iconic view
;;; of the application.  It follows the same conventions for import.

;; jh, 5/19/92.  Added.

(defun get-icon-name-from-command-line-if-any ()
  (get-command-line-keyword-argument '#.(stringw "icon") 1 t))

;; The handling of character set (no import) is being done to fix the bug "-name
;; startup parameter does not display Japanese names correct" (HQ-2133884).  In
;; 5.0, we started importing command line args as ISO Latin-1, which caused a
;; perceived regression for Japanese customers, who previously enjoyed G2's
;; passing its name text (in Shift-JIS character set, say) intact from the
;; command line to Windows for display as the title bar text for the G2
;; window. (MHD 10/15/00)




;;; The function `get-default-scale-from-command-line-if-any' returns either nil
;;; or two values, the default x scale and the default y scale.  Checking and
;;; filtering is done here so that this produces only legal, and reasonable,
;;; values when it returns non-nil.
;;;
;;; A user can specify on the command line any one of the following sets of
;;; commands:
;;;
;;;     -x-res[olution] <resolution-spec>
;;;     -y-res[olution] <resolution-spec>
;;;
;;;     -res[olution] <resolution-spec>
;;;
;;;
;;;     -x-mag[nification] <ratio>
;;;     -y-mag[nification] <ratio>
;;;
;;;     -mag[nification] <ratio>
;;;
;;; where <resolution-spec> can be one of the following
;;;
;;;    query-device
;;;    <number-of-dots-per-inch>[<units>]
;;;
;;;     NOTE: the query-device kind of resolution spec is not yet supported.
;;;
;;; where <units> can be only dpi, dots per inch, (at present), and defaults to
;;; dpi; where number-of-dots-per-inch is an integer in the range [50..200]; and
;;; where <ratio> is an integer or floating point number in the range
;;; [.67..2.66] giving the number of pixels per workspace unit at "full scale",
;;; i.e., when G2 displays a workspace at what the user should perceive as "full
;;; scale".
;;;
;;; These args are intended as "hints" to G2 as to what the device resolution
;;; is.  Presumably, G2 should know this itself, but for various reasons, it's
;;; better for it to be a soft parameter that users can specify.
;;;
;;; When none of these args are specified, the result is effectively the same
;;; as if the user specified
;;;
;;;    -magnification 1 -resolution 75
;;;
;;; When both magnification and resolution are specified, they combine.  For
;;; example, the user can specify
;;;
;;;   - magnification .5 -resolution 150
;;;
;;; This would turn out to be equivalent the the default.
;;;
;;;   NOTE: the combination of magnification and resolution is not yet
;;;   implemented; just use one or the other for now.
;;;
;;; Combinations of args that don't make sense, e.g., say -x-res AND -res, is
;;; undefined, except to say that a legal default (x/y) scale will be chosen,
;;; and it _might_ seem reasonable.  The same applies for cases where an illegal
;;; spec is supplied, as well as a combination of these two situations.
;;;
;;; All of these command line args end up setting the default scale for
;;; workspaces to be shown in this window.  (I.e., this applies to Telewindows
;;; processes, as well as to the (one) local window of a G2 process.)
;;;
;;; Once inside of G2, a user cannot control the ratio of workspace units to
;;; pixels.  [We might support access to this information, and perhaps setting
;;; of it on a window-by-window basis at some point in the future.]
;;;
;;; Note that we may support G2-wide per-workpace scaling at some future point,
;;; perhaps even in release 4.0.  This would be a specification along the lines
;;; of the number of workspace units per inch, or the workspace default scale
;;; (here, a magnification of the internal default scale).
;;;
;;; [Consider dropping "default-(x/y-)scale", since it's not really related to
;;; the workspace unit scaling that's in the product, and can be easily confused
;;; with it. (MHD 4/16/94)]
;;;
;;; [Consider including the word "device" in the names of the command line args,
;;; e.g., "-device-x-resolution", ..., "-device-x-scale", ...]
;;;
;;; The number 75 is the DPI for which fonts licensed from Adobe were tuned.
;;; Secondarily, -- and this we can maybe document -- it's a good (almost)
;;; lowest common denominator.
;;;
;;; Note that once we advertise that our HM14 really is 14 point, we are stuck
;;; with 75 as the "default" dpi.  Until then, we aren't really committed,
;;; though presumably we'd either have to get new new tuned bitmaps, or not use
;;; tuned bitmaps, or use bitmaps tuned for different resolutions than we're
;;; really using.  Note also that the default workspace-unit-per-inch setting in
;;; the printer-setup system table is 100.  I think that's not completely
;;; orthogonal, but we can live with it.

(defun get-default-x-and-y-scale-from-command-line-if-any (&optional silent?)
  (values
    (get-default-scale-from-command-line-1 'x silent?)
    (get-default-scale-from-command-line-1 'y silent?)))


(defun get-default-scale-from-command-line-1 (goal-dimension silent?)
  (loop for command-string
            in (getf '(x ("x-res" "x-resolution"
                          "res" "resolution"
                          "x-mag" "x-magnification"
                          "mag" "magnification")
                       y ("y-res" "y-resolution"
                          "res" "resolution"
                          "y-mag" "y-magnification"
                          "mag" "magnification"))
                     goal-dimension)
        thereis
          (if (search "res" command-string)
              (process-command-line-resolution-arg command-string silent?)
              (process-command-line-scale-arg command-string silent?))))






(defun process-command-line-resolution-arg (name &optional silent?)
  (let* ((resolution-spec? (get-command-line-keyword-argument name))
         (resolution-in-dpi?
           (when resolution-spec?
             (read-fixnum-from-string        ; "dpi" allowed at end, not required;
               resolution-spec? 0        ; (allow any other junk)
               (lengthw resolution-spec?)))))
    (or (if resolution-in-dpi?
            (if (<= gensym-windows-minimum-supported-dpi
                    resolution-in-dpi?
                    gensym-windows-maximum-supported-dpi)
                ;; (< lcd-dpi dpi state-of-art-dpi)
                (scale-scale
                  (normalized-scale) resolution-in-dpi? gensym-windows-standard-dpi)))
        (if resolution-spec?
            (unless silent?
              (notify-user-at-console
                       "~%Illegal ~a arg: ~a; it must be an integer ~
                         between ~a and ~a (expressing dots per inch).~%"
                      name
                      (or resolution-spec? "(none)")
                      gensym-windows-minimum-supported-dpi
                      gensym-windows-maximum-supported-dpi))))))



(defun process-command-line-scale-arg (name &optional silent?)
  (with-temporary-gensym-float-creation scale
    (let* ((scale-spec? (get-command-line-keyword-argument name))
           (scale?
             (if scale-spec?
                 (read-number-from-string scale-spec? 0 (lengthw scale-spec?)))))
      (or (if scale?
              (let ((scale-as-number
                      (if (managed-float-p scale?)
                          (managed-float-value scale?)
                          scale?)))
                (if (<= gensym-windows-minimum-supported-scale
                        scale-as-number
                        gensym-windows-maximum-supported-scale)
                    (round (* (normalized-scale) scale-as-number)))))
          (if scale-spec?
              (unless silent?
                (notify-user-at-console
                        "~%Illegal ~a arg: ~a; it must be a number ~
                         between ~f and ~f (expressing a magnification factor).~%"
                        name
                        (or scale-spec? "(none)")
                        gensym-windows-minimum-supported-scale
                        gensym-windows-maximum-supported-scale)))))))


;; Extension: handle default-x-scale and default-y-scale separately on the
;; command line.  Some devices don't have square pixels.

;; Be able to get the resolution from the screen.  If it were the default, users
;; would always get points sizes that are exact for the display they're using by
;; default.  However, then they would not get crisp, tuned bitmaps by default.
;; So I'm not sure it's wise just yet.  Our font scaling is improved, but still
;; poor compared to hand-tuned.  Maybe if we had better hinting in our fonts,
;; or yet better scaling, or a bit of both, or if had a lot more tuned bitmaps,
;; we could get away with it.  If it's not the default, an easy command line
;; option, say
;;
;;    -true-point-sizes
;;
;; would be sufficient.
;;
;; The X details are:
;;
;;    XWidthMMOfScreen (screen)
;;    XHeightMMOfScreen (screen)
;;
;; These return the width and height of the screen in milimeters.
;;
;;    XWidthOfScreen (screen)
;;    XHeightOfScreen (screen)
;;
;; These return the width and height of the screen in milimeters.
;;
;;    1 mm = .0394 in
;;
;; Thus, the dpi (dots per inch) in x for a screen S is
;;
;;    (XWidthMMOfScreen (S) / XWidthOfScreen (S)) * (1 / .0394)
;;
;; Similarly for height.
;;
;; (MHD 3/3/94)




;;; The function `c-x11-preinitialize' ...

(def-gensym-c-function c-x11-preinitialize
    (:void "g2ext_x11_preinitialize")
  ((:fixnum-int run-without-local-window-p)
   (:string windowhandle)))




;;; The function `x11-preinitialize-if-necessary' ...

(defun x11-preinitialize-if-necessary ()
  (unless x11-preinitialized-p
    (let ((preinitialization-option
            (current-system-case
              (ab (if (no-local-window-p) 1 0))
              (telewindows 0))))
      (c-x11-preinitialize preinitialization-option
                           (get-parent-windowhandle))
      (setq x11-preinitialized-p preinitialization-option))))




;;; The function `c-x11-initialize' initializes the X11 toolkit, brings
;;; up a top level window,and returns that window
;;; (as the "native local window").

(def-gensym-c-function c-x11-initialize
                       (:pointer "g2ext_x11_initialize")
  ((:string display-spec)
   (:string window-name)
   (:string icon-name)
   (:fixnum-int window-width)                        ; or -2 for fullscreen, -1 for normal (90%)
   (:fixnum-int window-height)                        ; or -2 for fullscreen, -1 for normal
   (:fixnum-int x-offset)                        ; or -1 if unsupplied
   (:fixnum-int y-offset)                        ; or -1 if unsupplied
   (:fixnum-int backing_store_p)                ; 1 if using backing store, 0 otherwise
   (:fixnum-int private_colormap_p)                ; 1 if using private color map, 0 otherwise
   (:fixnum-int frame_type)))                        ; frame-type-mdi, etc.


;; jh, 5/19/92.  Changed c-x11-initialize to take an extra argument, icon-name,
;; so we can differentiate it from window-name.  In some cases (e.g.,
;; Telewindows), we want a smaller icon-name than window-name.






;;; The function `c-x11-make-xwindow-visible' ...

(def-gensym-c-function c-x11-make-xwindow-visible
                       (:void "g2ext_x11_make_xwindow_visible")
  ((:pointer gensym-x-window-index)))




;;; The function `c-x11-close' closes the X11 window.

(def-gensym-c-function c-x11-close
                       (:void "g2ext_x11_close")
  ((:pointer gensym-x-window-index)))



;;; The gensym-c-function `c-x11-sync' flushes the X output
;;; buffers and then waits until all requests have been
;;; received and processed by the X server.

(def-gensym-c-function c-x11-sync
    (:void "g2ext_x11_sync")
  ((:pointer gensym-x-window)))


;; I saw a note go by in the change log about potentially replacing a call to
;; c-x11-sync with c-x11-flush.  I seem to remember that this was added to push
;; back onto the G2 process so that when it was incessantly attempting to draw more
;; than the X server could keep up with we would not have unbounded expansions of
;; the X11 output event queue.  I must admit to my ignorance about X11 Flush, and
;; whether it would prevent this problem itself, but I do remember that we inserted
;; this in specific response to some crashes experienced by customers.



;;; The gensym-c-function `c-x11-flush' flushes X output buffers
;;; to the X server.  It is rumored to have some problems on
;;; HP machines.

(def-gensym-c-function c-x11-flush
    (:void "g2ext_x11_flush")
  ((:pointer gensym-x-window)))

;; On the HP, XSync is able to NOT get wedged when lots of events are queued.
;; XFlush can get wedged on some occasions.  We should get HP to fix this bug
;; and revert to using XFlush.  -pto 08feb89

;; I think that it will be safe to call flush as long as we periodically call
;; sync, too.  I would like to flush on each call to service-workstation, so
;; that graphics updated whenever the user does an allow other processing.
;; But, calling XSync that often would be much too slow, since XSync must wait
;; for a full round-trip-time to the server.






;;; The function `c-x11-get-pixel-value' allocates an X11 pixel value
;;; for the named color.

(def-gensym-c-function c-x11-get-pixel-value
    (:fixnum-int "g2ext_get_pixel")
  ((:pointer gensym-x-window)
   (:string gensym-color-string)
   (:fixnum-int extended-color-p)))                            ; Boolean.


;;; The function `get-pixel-value' returns a pixel value for the given named
;;; color, or NIL if no pixel could be allocated.  It should be the used
;;; instead of calls to the raw C routine.  It ensures that pixel values are
;;; always fixnums in the range [0,255], a requirement for background images
;;; (for now).  Extended-color-p must be NIL if this color is one of G2's basic
;;; set, or T if this is a new color for images.

;;;   02-29-96, mpc: In the let statement of get-pixel-value below, I've
;;; removed the following bit of code and replaced it with the if.
;;; We believe the slam to 8 bits was the only limiting factor in
;;; supporting >8bit color. Now we simply return the value passed back
;;; from the C function.
;;;
;;;    (when (>=f raw-pixel-value 0)
;;;      ;; Paranoically force the returned value to be in the range [0,255].
;;;      (logandf raw-pixel-value 255 ))))

(defun get-pixel-value (native-window string extended-color-p)
  (let ((raw-pixel-value
          (c-x11-get-pixel-value
            native-window
            string
            (if extended-color-p 1 0))))
    (if (>=f raw-pixel-value 0)
        raw-pixel-value
        nil)))


;;; The gensym-c-function `c-x11-free-extended-colors' frees all the of pixels
;;; associated with extended colors, that is, those allocated by get-pixel with
;;; extended-color-p = T.

(def-gensym-c-function c-x11-free-extended-colors
    (:fixnum-int "g2ext_free_extended_colors")
  ((:pointer gensym-x-window)))






;;; The function/macro `c-x11-last-mouse-x-position' and `c-x11-last-mouse-y-position' ...

(def-gensym-c-function c-x11-last-mouse-x-position
                       (:fixnum-int "g2ext_x11_last_mouse_x_position")
  ((:pointer gensym-x-window)))


(def-gensym-c-function c-x11-last-mouse-y-position
                       (:fixnum-int "g2ext_x11_last_mouse_y_position")
  ((:pointer gensym-x-window)))



;;; The gensym-c-function `c-x11-last-event-bits' returns the state of
;;; the G2 modifier bits for the last event.

(def-gensym-c-function c-x11-last-event-bits
                       (:fixnum-int "g2ext_x11_last_event_bits")
  ((:pointer gensym-x-window)))



;;; The gensym-c-function `c-x11-last-event-time' returns the time of
;;; the last event, in milliseconds, with a wrap size of 28bits.

(def-gensym-c-function c-x11-last-event-time
                       (:fixnum-int "g2ext_x11_last_event_time")
  ((:pointer gensym-x-window)))


;;; The gensym-c-function `c-x11-last-event-window-name' returns the handle of
;;; the native window associated with the last event. The handle is not the same
;;; as the index (the g2pointer), and is assigned by G2.

(def-gensym-c-function c-x11-last-event-window-handle
                       (:fixnum-int "g2ext_x11_last_event_window_handle")
  ((:pointer gensym-x-window)))


;;; The gensym-c-function `c-x11-last-event-value' fills a text buffer with a
;;; string associated with the last event, if any. Returns -1 if no value..

(def-gensym-c-function c-x11-last-event-value
    (:fixnum-int "g2ext_x11_last_event_value")
  ((:pointer gensym-x-window)
   (:wide-string buffer)
   (:fixnum-int buffer-size)))



;;; The function/macro `c-x11-last-window-x' and `c-x11-last-window-y' ...

(def-gensym-c-function c-x11-last-window-x
                       (:fixnum-int "g2ext_x11_last_window_x")
  ((:pointer gensym-x-window)))

(def-gensym-c-function c-x11-last-window-y
                       (:fixnum-int "g2ext_x11_last_window_y")
  ((:pointer gensym-x-window)))


;;; The function/macro `c-x11-last-window-width' and `c-x11-last-window-height' ...

(def-gensym-c-function c-x11-last-window-width
                       (:fixnum-int "g2ext_x11_last_window_width")
  ((:pointer gensym-x-window)))

(def-gensym-c-function c-x11-last-window-height
                       (:fixnum-int "g2ext_x11_last_window_height")
  ((:pointer gensym-x-window)))







;;; The function/macro `c-x11-last-expose-x-position' and `c-x11-last-expose-y-position' ...

(def-gensym-c-function c-x11-last-expose-x-position
                       (:fixnum-int "g2ext_x11_last_expose_x_position")
  ((:pointer gensym-x-window)))





(def-gensym-c-function c-x11-last-expose-y-position
                       (:fixnum-int "g2ext_x11_last_expose_y_position")
  ((:pointer gensym-x-window)))






;;; The function/macro `c-x11-last-expose-width' and `c-x11-last-expose-height' ...

(def-gensym-c-function c-x11-last-expose-width
                       (:fixnum-int "g2ext_x11_last_expose_width")
  ((:pointer gensym-x-window)))






(def-gensym-c-function c-x11-last-expose-height
                       (:fixnum-int "g2ext_x11_last_expose_height")
  ((:pointer gensym-x-window)))






;;; The function `c-x11-start-mouse-tracking' ...

(def-gensym-c-function c-x11-start-mouse-tracking
                       (:void "g2ext_start_tracking_mouse")
  ((:pointer gensym-x-window)))





;;; The function `c-x11-stop-mouse-tracking' ...

(def-gensym-c-function c-x11-stop-mouse-tracking
                       (:void "g2ext_stop_tracking_mouse")
  ((:pointer gensym-x-window)))





;;; The function `c-x11-window-width' ...

(def-gensym-c-function c-x11-window-width
                       (:fixnum-int "g2ext_window_width")
  ((:pointer gensym-x-window)))





;;; The function `c-x11-window-height' ...

(def-gensym-c-function c-x11-window-height
                       (:fixnum-int "g2ext_window_height")
  ((:pointer gensym-x-window)))





;;; The function `c-x11-get-mouse-x-position' returns the X coordinate of
;;; the present mouse position.  To get the Y coordinate, call
;;; c-x11-last-mouse-y-position.

(def-gensym-c-function c-x11-get-mouse-x-position
                       (:fixnum-int "g2ext_x11_get_mouse_x_position")
  ((:pointer gensym-x-window)))





;;; The function `c-x11-copy-pixmap' is used to bitblt icon layers and graph
;;; ring rasters to the screen. Icon layers currently specify a function-index
;;; of x11-stippled or x11-xor, and only graph ring rasters ever use x11-copy.

(def-gensym-c-function c-x11-copy-pixmap
                       (:void "g2ext_copy_pixmap_to_window")
  ((:pointer pixmap-structure-pointer)
   (:pointer gensym-x-window)
   (:fixnum-int x-offset)
   (:fixnum-int y-offset)
   (:fixnum-int x)
   (:fixnum-int y)
   (:fixnum-int width)
   (:fixnum-int height)
   (:fixnum-int foreground-xcolor)
   (:fixnum-int background-xcolor)
   (:fixnum-int function-index)))

;; Called by add-from-stored-raster-to-current-window and
;; add-from-graph-ring-raster-to-current-window-2.

;; Note: added 2nd argument (:pointer gensym-x-window) today. (MHD 11/20/01)



;;; The function `x11-copy-bitmap-to-bitmap'

(def-gensym-c-function c-x11-copy-bitmap-to-bitmap
                       (:void "g2ext_copy_bitmap_to_bitmap")
  ((:pointer pixmap-structure1-pointer)
   (:pointer pixmap-structure2-pointer)
   (:fixnum-int x-offset)
   (:fixnum-int y-offset)
   (:fixnum-int x)
   (:fixnum-int y)
   (:fixnum-int width)
   (:fixnum-int height)
   (:fixnum-int foreground-color)))


(def-gensym-c-function c-x11-set-debugging-mode
                       (:void "g2ext_x11_set_debug_mode")
  ((:pointer gensym-x-window)))

(def-gensym-c-function c-x11-clear-debugging-mode
                       (:void "g2ext_x11_clear_debug_mode")
  ((:pointer gensym-x-window)))



;;; The function `c-x11-copy-polychrome-pixmap' ... is incomplete

(def-gensym-c-function c-x11-copy-polychrome-pixmap
                       (:void "g2ext_copy_polychrome_pixmap_to_window")
  ((:pointer pixmap-structure-pointer)
   (:pointer gensym-x-window)
   (:fixnum-int x-offset)
   (:fixnum-int y-offset)
   (:fixnum-int x)
   (:fixnum-int y)
   (:fixnum-int width)
   (:fixnum-int height)
   (:fixnum-int function-index)))

;; Note: added 2nd argument (:pointer gensym-x-window) today. (MHD 11/20/01)




;;; The function `x11-create-pixmap' allocates a new pixmap in the native window
;;; system.  If it fails, then if
;;; `do-not-error-in-x11-create-pixmap-on-failed-allocation' is bound to a
;;; non-nil value, it returns the failing result returned from the call to C.
;;; Otherwise, (still in the failing case), it calls
;;; `handle-no-solution-to-raster-allocation-failure', at present is implemented
;;; to make TW/G2 abort.  [MHD: it should maybe abort TW, but for G2 it should
;;; only turn G2 windowless, allowing it to continue functioning as a server!]

(defvar do-not-error-in-x11-create-pixmap-on-failed-allocation nil) ; new (MHD 8/16/98)

(defun-substitution-macro x11-create-pixmap (gensym-x-window width height depth irregular-size-p)
  (let ((pixmap-or-error-flag                        ; a pointer to a "pixmap" or -1
          (c-x11-create-pixmap-1 gensym-x-window width height depth
                                 (if irregular-size-p 1 0))))
    (cond ((<f pixmap-or-error-flag 0)
           (unless do-not-error-in-x11-create-pixmap-on-failed-allocation
             (handle-no-solution-to-raster-allocation-failure
               gensym-x-window width height))
           ;; Not nec. X windows.
           pixmap-or-error-flag)
          (t
           #+development
           (note-use-of-pixmap pixmap-or-error-flag width height depth)
           pixmap-or-error-flag))))

;; Note that this is the only place we do error checking.  xwindows.c was
;; changed to return -1 from create_pixmap when it had allocation problems.
;; This was put in as a last minute patch for the release of 2.0 Beta-3.0.
;; This has to all be reworked for consistent and rigorous error handling.
;; Consider, for the release, making this a macro!  (MHD/BAH 4/9/90)

(defun handle-no-solution-to-raster-allocation-failure ; NEW (MHD 8/16/98)
    (gensym-window width height)
  (notify-user-at-console-and-on-logbook "Unable to allocate a ~dx~d pixmap!" width height))

;; Change this to just make the G2 run without a local window!!!! (MHD 8/16/98)

(def-gensym-c-function c-x11-create-pixmap-1
                       (:pointer "g2ext_create_pixmap")        ; returns pointer or -1.
  ((:pointer gensym-x-window)
   (:fixnum-int width)
   (:fixnum-int height)
   (:fixnum-int depth)
   (:fixnum-int irregular)))



;;; The function `c-x11-reclaim-pixmap' returns a pixmap to the O.S.

(def-gensym-c-function c-x11-reclaim-pixmap
                       (:void "g2ext_reclaim_pixmap")
  ((:pointer pixmap-structure-pointer)))





;;; The function `c-x11-move-pointer' ...

(def-gensym-c-function c-x11-move-pointer
                       (:fixnum-int "g2ext_x11_move_pointer")
  ((:pointer gensym-x-window)
   (:fixnum-int dest-x)
   (:fixnum-int dest-y)))





;;; The function `c-x11-get-event' returns the G2 code for
;;; the next keyboard, mouse, or random window system event,
;;; if any.  If no events are available, it returns null-event.

(def-gensym-c-function c-x11-get-event
                       (:fixnum-int "g2ext_get_event")
  ((:pointer gensym-x-window)))





;;; The function `c-x11-set-line-pattern' ...

#+unused
(def-gensym-c-function c-x11-set-line-pattern
                       (:void "g2ext_set_line_pattern")
  ((:pointer pixmap-structure-pointer)
   (:fixnum-int pattern)))





;;;; Pixmap drawing primitives



;;; The function `c-x11-pdraw-point' ...

(def-gensym-c-function c-x11-pdraw-point
                       (:void "g2ext_p_draw_point")
  ((:pointer pixmap-structure-pointer)
   (:fixnum-int x)
   (:fixnum-int y)
   (:fixnum-int xcolor)))





;;; The function `c-x11-pdraw-line' ...

(def-gensym-c-function c-x11-pdraw-line
                       (:void "g2ext_p_draw_line")
  ((:pointer pixmap-structure-pointer)
   (:fixnum-int x1)
   (:fixnum-int y1)
   (:fixnum-int x2)
   (:fixnum-int y2)
   (:fixnum-int xcolor)))





(def-gensym-c-function c-x11-pdraw-wide-line
                       (:void "g2ext_p_draw_wide_line")
  ((:pointer pixmap-structure-pointer)
   (:fixnum-int x1)
   (:fixnum-int y1)
   (:fixnum-int x2)
   (:fixnum-int y2)
   (:fixnum-int xcolor)
   (:fixnum-int line-width)))






;;; The functions `c-x11-stipple-rectangle' ...

(def-gensym-c-function c-x11-stipple-rectangle
                       (:void "g2ext_p_stipple_rect")
  ((:pointer pixmap-structure-pointer)
   (:fixnum-int stipple)
   (:fixnum-int x)
   (:fixnum-int y)
   (:fixnum-int width)
   (:fixnum-int height)))





;;; The function `c-x11-pfill-rectangle' ...

(def-gensym-c-function c-x11-pfill-rectangle
                       (:void "g2ext_p_fill_rect")
  ((:pointer pixmap-structure-pointer)
   (:fixnum-int x)
   (:fixnum-int y)
   (:fixnum-int width)
   (:fixnum-int height)
   (:fixnum-int xcolor)))






;;; The function `c-x11-pfill-triangle' ...

(def-gensym-c-function c-x11-pfill-triangle
                       (:void "g2ext_p_fill_triangle")
  ((:pointer pixmap-structure-pointer)
   (:fixnum-int x1)
   (:fixnum-int y1)
   (:fixnum-int x2)
   (:fixnum-int y2)
   (:fixnum-int x3)
   (:fixnum-int y3)
   (:fixnum-int xcolor)))



(defconstant maximum-polygon-coordinates (*f maximum-polygon-points 2))
;;; The function `c-x11-pfill-clipped-polygon' ...

(def-gensym-c-function c-x11-pfill-clipped-polygon
                       (:void "g2ext_p_fill_clipped_polygon")
  ((:pointer pixmap-structure-pointer)
   (:string point_data) ; encoded coordinates in byte vector
   (:fixnum-int number-points)
   (:fixnum-int left)
   (:fixnum-int top)
   (:fixnum-int right)
   (:fixnum-int bottom)
   (:fixnum-int xcolor)))






;;; The function `c-x11-pdraw-arc' ...

(def-gensym-c-function c-x11-pdraw-arc
                       (:void "g2ext_p_draw_arc")
  ((:pointer pixmap-structure-pointer)
   (:fixnum-int x)
   (:fixnum-int y)
   (:fixnum-int width)
   (:fixnum-int height)
   (:fixnum-int start-angle)
   (:fixnum-int displacement-angle)
   (:fixnum-int xcolor)))






;;; The function `c-x11-pfill-arc' ...

(def-gensym-c-function c-x11-pfill-arc
                       (:void "g2ext_p_fill_arc")
  ((:pointer pixmap-structure-pointer)
   (:fixnum-int x)
   (:fixnum-int y)
   (:fixnum-int width)
   (:fixnum-int height)
   (:fixnum-int start-angle)
   (:fixnum-int displacement-angle)
   (:fixnum-int xcolor)))



;;; The gensym-c-function `c-x11-draw-offscreen' enters and leaves off-screen
;;; drawing mode.  The offscreen bitmap to use must be supplied if enable-p is
;;; true.

(def-gensym-c-function c-x11-draw-offscreen
    (:void "g2ext_offscreen")
  ((:pointer gensym-x-window)
   (:pointer pixmap-structure-pointer)        ; Pixmap to use if on.
   (:fixnum-int enable-p)))                ; Boolean On/off




;;;; Window drawing primitives



;; TILING


;;; The function `c-x11-initialize-tile' ...

(def-gensym-c-function c-x11-initialize-tile
                       (:void "g2ext_x11_initialize_tile")
  ((:pointer gensym-x-window)
   (:pointer pixmap-structure-pointer)
   (:fixnum-int foreground-xcolor)
   (:fixnum-int background-xcolor)))


;;; The function `c-x11-draw-tiling-pattern' ...

(def-gensym-c-function c-x11-draw-tiling-pattern
    (:void "g2ext_x11_tile")
  ((:pointer gensym-x-window)
; Someday
;   (:fixnum-int pattern)                                    ; Pixmap or -1
   (:fixnum-int left)
   (:fixnum-int top)
   (:fixnum-int width)
   (:fixnum-int height)))


(def-gensym-c-function c-x11-scroll-rectangle
    (:void "g2ext_scroll_rectangle")
  ((:pointer gensym-x-window)
   (:fixnum-int source-left)
   (:fixnum-int source-top)
   (:fixnum-int width)
   (:fixnum-int height)
   (:fixnum-int destination-left)
   (:fixnum-int destination-top)))



(def-gensym-c-function c-x11-draw-string (:void "g2ext_w_draw_string")
  ((:pointer window)
   (:fixnum-int left)
   (:fixnum-int top)
   (:fixnum-int right)
   (:fixnum-int bottom)
   (:fixnum-int x)
   (:fixnum-int y)
   (:fixnum-int color)
   (:fixnum-int point-size)
   (:fixnum-int angle)                        ; CCW degrees
   (:fixnum-int flags)                        ; Flags: bit-0 = reflect-left-right-p
   (:fixnum-int x-scale)
   (:fixnum-int y-scale)
   (:fixnum-int word-spacing)
   (:wide-string string)
   (:fixnum-int length)))



(def-gensym-c-function c-x11-draw-string-with-clipping
                       (:fixnum-int "g2ext_w_draw_string_with_clipping")
  ((:pointer gensym-x-window)
   (:fixnum-int x)                                            ; Left edge
   (:fixnum-int y)                                            ; Baseline

   (:fixnum-int left-edge)
   (:fixnum-int top-edge)
   (:fixnum-int right-edge)
   (:fixnum-int bottom-edge)

   (:fixnum-int xcolor)
   (:fixnum-int function-index)
   (:string font-name)
   (:string ascii-text)
   (:fixnum-int length)))



(def-gensym-c-function c-x11-draw-string-in-font
                       (:fixnum-int "g2ext_draw_string_in_font")
  ((:pointer gensym-x-window)
   (:fixnum-int x)                                            ; Left edge
   (:fixnum-int y)                                            ; Baseline

   (:fixnum-int xcolor)
   (:fixnum-int function-index)
   (:pointer font)
   (:string ascii-text)
   (:fixnum-int length)))

(def-gensym-c-function c-x11-draw-string-in-font-with-clipping
                       (:fixnum-int "g2ext_draw_string_in_font_with_clipping")
  ((:pointer gensym-x-window)
   (:fixnum-int x)                                            ; Left edge
   (:fixnum-int y)                                            ; Baseline

   (:fixnum-int left-edge)
   (:fixnum-int top-edge)
   (:fixnum-int right-edge)
   (:fixnum-int bottom-edge)

   (:fixnum-int xcolor)
   (:fixnum-int function-index)
   (:pointer font)
   (:string ascii-text)
   (:fixnum-int length)))


(def-gensym-c-function c-x11-get-character-set-width
    (:fixnum-int "g2ext_get_character_set_width")
  ((:fixnum-int character-code)
   (:pointer font)))


(def-gensym-c-function c-x11-allocate-x-font
    (:pointer "g2ext_allocate_x_font")
  ((:pointer gensym-x-window)
   (:string font-name)))


#+unused
(def-gensym-c-function c-x11-draw-line
    (:void "g2ext_w_draw_line")
  ((:pointer gensym-x-window)
   (:fixnum-int x1)
   (:fixnum-int y1)
   (:fixnum-int x2)
   (:fixnum-int y2)
   (:fixnum-int xcolor)
   (:fixnum-int function-index)))

;; Unused (we always need the native clipping).



(def-gensym-c-function c-x11-draw-line-with-clipping
  (:void "g2ext_w_draw_line_with_clipping")
  ((:pointer gensym-x-window)
   (:fixnum-int x1)
   (:fixnum-int y1)
   (:fixnum-int x2)
   (:fixnum-int y2)
   (:fixnum-int left-edge)
   (:fixnum-int top-edge)
   (:fixnum-int right-edge)
   (:fixnum-int bottom-edge)
   (:fixnum-int xcolor)
   (:fixnum-int function-index)))

;; Used by add-upward-sloping-line-to-current-window and
;; add-downward-sloping-line-to-current-window


;;; The gensym-c-function `c-x11-draw-wide-polyline' draws a continuous wide
;;; polyline on the native window in given color and using given raster op,
;;; possibly dashed with on/off lengths given by pattern (0 means solid).

(def-gensym-c-function c-x11-draw-wide-polyline
  (:void "g2ext_w_draw_wide_polyline")
  ((:pointer gensym-x-window)
   (:wide-string points)                ; Interpreted as an array of signed shorts.
   (:fixnum-int npoints)
   (:fixnum-int left-edge)                ; Clipping region.
   (:fixnum-int top-edge)
   (:fixnum-int right-edge)
   (:fixnum-int bottom-edge)
   (:fixnum-int color)
   (:fixnum-int width)                        ; 0 means to use fast (cosmetic) lines
   (:fixnum-int style)                        ; Cap,join style, stock dash patterns
   (:wide-string dashes)                ; Custom dot/dash pattern
   (:fixnum-int ndashes)
   (:fixnum-int function-index)))


(def-gensym-c-function c-x11-draw-rectangle
    (:void "g2ext_w_fill_rect")
  ((:pointer gensym-x-window)
   (:fixnum-int x)
   (:fixnum-int y)
   (:fixnum-int width)
   (:fixnum-int height)
   (:fixnum-int xcolor)
   (:fixnum-int function-index)))


(def-gensym-c-function c-x11-draw-tiles
    (:void "g2ext_w_draw_tiles")
  ((:pointer gensym-x-window)
   (:pointer pixmap)
   (:fixnum-int x-origin)                ; Tiling origin (in window)
   (:fixnum-int y-origin)
   (:fixnum-int left)                        ; Rectangle to fill
   (:fixnum-int top)
   (:fixnum-int width)
   (:fixnum-int height)
   (:fixnum-int foreground)                ; fg/bg for 1-bit pixmaps
   (:fixnum-int background)))

(def-gensym-c-function c-x11-draw-polygon
    (:void "g2ext_w_draw_polygon")
  ((:pointer gensym-x-window)
   (:fixnum-int left-edge)                ; Clipping region.
   (:fixnum-int top-edge)
   (:fixnum-int right-edge)
   (:fixnum-int bottom-edge)
   (:fixnum-int line-color)                ; Graphics context
   (:fixnum-int line-width)
   (:fixnum-int fill-color)
   (:fixnum-int fill-pattern)
   (:fixnum-int function-index)
   (:wide-string points)                ; Interpreted as an array of signed shorts.
   (:fixnum-int npoints)))

(def-gensym-c-function c-x11-draw-ellipse
    (:void "g2ext_w_draw_ellipse")
  ((:pointer gensym-x-window)
   (:fixnum-int left-edge)                ; Clipping region.
   (:fixnum-int top-edge)
   (:fixnum-int right-edge)
   (:fixnum-int bottom-edge)
   (:fixnum-int line-color)                ; Graphics context
   (:fixnum-int line-width)
   (:fixnum-int fill-color)
   (:fixnum-int fill-pattern)
   (:fixnum-int function-index)
   (:fixnum-int x1)                        ; Bounding box of the ellipse.
   (:fixnum-int y1)
   (:fixnum-int x2)
   (:fixnum-int y2)))


;;; The gensym-c-function `c-x11-bell' rings the bell on the remote window.

(def-gensym-c-function c-x11-bell (:fixnum-int "g2ext_x11_bell")
  ((:pointer gensym-x-window)
   (:fixnum-int percent)))



(defun get-values-from-x11-parse-geometry (parsestring)
  (c-x11-parse-geometry parsestring)
  ;; This how we get multiple values from our FF interface.
  (values
    (c-x11-parse-geometry-x)
    (c-x11-parse-geometry-y)
    (c-x11-parse-geometry-width)
    (c-x11-parse-geometry-height)))


;;; The function `c-x11-parse-geometry' takes the string received with the command
;;; line argument "-geometry" and calls XParseGeometry which will return the
;;; x,y,width and height given in the string.

(def-gensym-c-function c-x11-parse-geometry (:void "g2ext_x11_parse_geometry")
  ((:string parsestring)))

;; Unspcified values are -1.  Negative x and y values are truevalue - 2 .
(def-gensym-c-function c-x11-parse-geometry-x (:fixnum-int "g2ext_x11_parse_geometry_x")
  ())

(def-gensym-c-function c-x11-parse-geometry-y (:fixnum-int "g2ext_x11_parse_geometry_y")
  ())

(def-gensym-c-function c-x11-parse-geometry-width (:fixnum-int "g2ext_x11_parse_geometry_width")
  ())

(def-gensym-c-function c-x11-parse-geometry-height (:fixnum-int "g2ext_x11_parse_geometry_height")
  ())



(defun make-block-near-mouse-cache ()
  (current-system-case
    (ab (make-block-near-mouse-cache-internal-1))
    (t  nil)))

(defun-void reclaim-block-near-mouse-cache-function (cache)
  (current-system-case
    (ab (reclaim-block-near-mouse-cache-1 cache))
    (t  cache)))


;;;; The Workstation Structure




;; Slots need to be accessed before WORKSTATIONS is loaded.  See about moving
;; other things in here.  See about merging "workstation event queues" and "local
;; event queues"!! (MHD 7/17/89)



;;; The `workstation' structure is the root of a data structure used to manage
;;; user workstations.  This data structure can persist over KB clear.  The set
;;; of all workstations is maintained in the variable `workstations-in-service',
;;; that variable forms the root of the workstation/window hierarchy.

;;; The `window-for-workstation' slot holds the window that plays the role of
;;; standard output of this workstation.  The dynamic extent `on-window' is
;;; established when doing output to the window.

;;; A substantail number of slots implement input handling, for example
;;; g2-user-mode-for-this-workstation?, workstation-event-queue,
;;; workstation-context-stack, mouse-tracking?, etc., etc.  The dynamic extent
;;; `for-workstation' is established when working on input processing.

;;; All mouse pointers are allocated and reclaimed in the module WORKSTATIONS.
;;; All current mouse-pointer instances are recorded in the two slots
;;; `recent-mouse-pointers-{1,2}'.  When ever `recent-mouse-pointer-countdown'
;;; reachs zero those in recent-mouse-pointers-2 are reclaimed if there
;;; reference count is zero, and those in recent-mouse-pointers-1 are shifted
;;; over into recent-mouse-pointers-2.  The act of incrementing/decrementing
;;; the reference count is known as registering/releasing.  Any slot that
;;; holds a mouse pointer should register it, and then release it when done.

;;; A number of slots hold information, mouse pointers, etc., that together
;;; provides a model of what is going on in the event stream.  A kind of
;;; lexical analysis.

;;; `Mouse-pointer-of-latest-event' and `Mouse-pointer-of-previous-event' the
;;; last two mouse pointers seen by service workstation.  A non zero value in
;;; `Mouse-button-model' indicates that some number of mouse buttons are currently
;;; depressed.  When one or more buttons are depressed then
;;; `mouse-pointer-of-last-down'  is bound to the mouse pointer of the first
;;; button that was depressed.

;;; The flag `tracking-mouse?' indicates that mouse motion events are currently
;;; being posted by workstation.

;;; For documentation of `image-plane-with-selection-focus-of-workstation?' and
;;; `block-with-selection-focus-of-workstation' see the
;;; `x-in-workspace-of-selection-focus'.

;;; The slot `image-plane-to-continue-refreshing?'  is used to put an
;;; image-plane's drawing on hold withing the workstation.

;;; The slot `search-states-in-this-workstation' is used to the state of a inspect
;;; command in progress requested by this user.

;;; The slot `non-kb-workspaces-for-this-workstation-only' holds a partition of the
;;; temporary KB that are private to this workstation, e.g. it's clipboard.

;;; Few of these slots are maintained on the Telewindow's side of the connection.

;;; A model of the currently logged in user is maintained that is sufficent
;;; to: manage that user correctly, to allow him to change modes, without
;;; resubmitting his password.  See below.  The password is the md5 hash
;;; of the username and passowrd (see md5-encoded-password).

;; - ben 2/23/93

(def-structure (workstation
                 (:reclaimer reclaim-workstation-internal)
                 (:print-function print-workstation)
                 (:constructor
                   make-workstation
                   (window-for-workstation)))

  (window-for-workstation                        ; nil only transiently -- a
    nil                                                ;   gensym window -- always filled
    :reclaimer reclaim-window-for-workstation)        ;   in (in set-up-workstation)
                                                ; reclaimer in WINDOWS1
  (workstation-event-queue
    (make-queue) :reclaimer reclaim-workstation-event-queue-if-g2)

  (corresponding-icp-object-map-for-workstation nil)

  ;; State of the Lexical Analysis of the Event Stream.
  (tracking-mouse? nil)                 ; Enable/disable of mouse motion events.
  (x-in-window-of-mouse? 0)                ; The latest mouse-x,y available. NEVER nil.
  (y-in-window-of-mouse? 0)
  image-plane-with-selection-focus-of-workstation?
  block-with-selection-focus-of-workstation

  (mouse-button-model 0)          ; Which buttons are down right now.
  (mouse-button-of-last-activity 'none)        ; A symbol, left, middle, right, or none.
  mouse-pointer-of-latest-event   ;  initialized
  mouse-pointer-of-previous-event ;    by set-up-workstation
  mouse-pointer-of-last-down      ;    via make-an-initial-mouse-pointer.



  ;; Memory management for mouse-pointers.
  (recent-mouse-pointers-1 nil :reclaimer reclaim-mouse-pointers-if-g2)
  (recent-mouse-pointers-2 nil :reclaimer reclaim-mouse-pointers-if-g2)
  (recent-mouse-pointer-countdown 2)

  ;; Workstation Contexts
  (workstation-context-stack                        ; nil only transiently
    nil :reclaimer reclaim-workstation-context-stack-if-g2)
  (type-of-modal-context? nil)                        ; a type-of-workstation-context for
                                                ;   a context at this level or lower
                                                ;   in the stack; if true, digressions
                                                ;   not pertinent to this context are
                                                ;   disallowed and special handling may
                                                ;   be required in certain subcontexts

  ;; Model of the current logged in user.
  (g2-user-mode-for-this-workstation? nil) ; NOTE: tried once (11/22/94) to have
                                           ; this default to ADMINISTRATOR, but
                                           ; that broke
                                           ; enter-user-settings-editor, q.v.
                                           ; for explanation. (MHD 1/12/95)
  (g2-user-name-for-this-workstation? nil)      ; login name
  (g2-user-password-for-this-workstation? nil)  ; password (or null text-string)
  (g2-user-discard-user-settings-for-this-workstation-p nil)  ; t/nil
  (g2-window-name-or-class-for-this-workstation        ; name or class for g2 window
    'g2-window)                                        ; defaults to class g2 window
  (time-of-telewindows-connection? nil        ; a unix-time time stamp; the value of
                                   :reclaimer reclaim-if-managed-float)
                                        ;   current-real-time at the time
                                        ;   of the connection; or nil

  (g2-window-for-this-workstation? nil)
                                                ; nil => not connected; else,
                                                ;    a g2 window instance
  (g2-window-init-string? nil                        ; nil or a arb. user text data in string
                          :reclaimer reclaim-if-text-string)
                                                ;   form; however, only legal Gensym text
                                                ;   string characters are allowed
  (specific-language-for-this-workstation? nil)        ; nil or a language (symbol)

  (workstation-login-state 'logged-out)                ; one of LOGGED-IN, LOGGING-IN,
                                                ;   LOGGED-OUT, or CHANGING-KBS

  (g2-user-in-this-workstation-has-backdoor-privileges? nil) ; G2 Side Only
  ;; End of model


  ;; Misc
  (image-plane-to-continue-refreshing? nil) ; See maybe-defer-refreshing-image-plane
  (search-states-in-this-workstation nil)        ; a gensym tree (usu. empty) of the form
                                                ;    ({(kb-search-state
                                                ;       . frame-serial-number)})

  (non-kb-workspaces-for-this-workstation-only        ; a gensym list (usu. empty) of the form
    nil                                                ;    ({non-kb-workspace})
    :reclaimer                                        ; non-kb workpaces point back here
      reclaim-non-kb-workspaces-for-this-workstation-only-if-g2)

  ;; Return values from workstation contexts:
  (workstation-context-first-return-value nil :reclaimer reclaim-gensym-tree-with-text-strings)
  (workstation-context-second-return-value nil :reclaimer reclaim-gensym-tree-with-text-strings)
  (workstation-context-third-return-value nil :reclaimer reclaim-gensym-tree-with-text-strings)

  ;; The heartbeat used in some workstation contexts.
  (heartbeat-task-of-workstation? nil)

  ;; Session-id-of-workstation is used only in G2, and is
  ;; read only.  It is analagous to frame serial number and
  ;; used as a key for storing per workstation session specifics
  ;; in unsaved slots, for example were we last had this
  ;; scrolled to.
  (session-id-of-workstation (incf last-session-id-for-g2))

  ;; `workstation-network-host-name?' and `workstation-os-user-name?' come
  ;; from the (telewindows) plist.
  (workstation-network-host-name? nil        ; move up later!
                                  :reclaimer reclaim-if-text-string)
  (workstation-os-user-name? nil        ; move up later!
                             :reclaimer reclaim-if-text-string)
  (workstation-reroute-problem-report? nil) ; if this is the G2 side
                                            ;   of a Telewindows connection,
                                            ;   and a reroute failed, this
                                            ;   holds the failure string
                                            ; move up later!
  ;; See mouse-tracking.
  (consider-synthetic-motion-event? nil) ;; Should be next to mouse-tracking?

  ;; Used to cache the nearest object to a mouse click.
  (workstation-block-near-mouse-cache
    (make-block-near-mouse-cache)
    :reclaimer reclaim-block-near-mouse-cache-function)

  (workstation-os-type? nil)

  (workstation-paste-request-id 0)        ; incremented when a paste is requested to
                                        ;   keep requests in synch with replies
  (workstation-clipboard-has-text-p nil) ; polled periodically; kept in synch
                                             ;   in G2/TW; when it changes, a paste
                                             ;    event is generated (across TW/G2)

  (notify-if-clipboard-has-text-p t)        ; enable/disable "tracking" of available
                                        ;   text to be pasted; only used by 5.0+
                                        ;   G2/TW
  (current-task-to-run-service-workstation nil)
  (future-task-to-run-service-workstation nil)

  (cjk-typeface-preference-for-this-workstation? ; Japanese, Korean, Chinese (= chinese-simplified),
    nil)                                         ;   chinese-Simplified, or Chinese-Traditional
                                                 ;   (= chinese at present, but subject to future
                                                 ;   revision)  (MHD 4/9/99)
                                                 ; New! (MHD 4/9/99)
  (style-specifically-for-this-workstation? ; nil (default), g2-5.x, standard, standard-large
    nil)

  ;; The selected image-plane. Doesn't necessarily have keyboard focus.
  (selected-image-plane nil)
  (selection-callbacks-task nil)

  ;; Handle of selected/focussed native window, if any. May be stale.
  (handle-of-selected-native-window? nil)

  ;; For g2-last-input-event -fmw, 2/23/07
  mouse-pointer-of-last-interesting-event
  ;;This slot is used to avoid recursive workstation flush
  workstation-flush-in-progress?
)

;; These slots could be reordered.


(defun window-for-workstation-function (workstation)
  (window-for-workstation workstation))


;;; `Reclaim-workstation' removes from service and destroys workstation along
;;; with all its related substructure and submappings.

(defun reclaim-workstation (workstation)
  (when (eq last-workstation-serviced workstation)
    (setq last-workstation-serviced nil))
  (setq workstations-in-service
        (delete-gensym-element workstation workstations-in-service))
  (let ((delete-corresponding-object? nil))
    (reclaim-icp-object-map-for-workstation workstation))
  (reclaim-workstation-tasks workstation)
  (setf (workstation-flush-in-progress? workstation) nil)
  (reclaim-workstation-internal workstation))


#+development
(defun print-workstation (workstation stream depth)
  (declare (ignore depth))
  (printing-random-object (workstation stream)
    (format stream "WORKSTATION~@[ ~a~]"
            (cond ((workstation-dead-p workstation)
                   "Dead")
                  ((window-for-workstation workstation)
                   (pretty-type-of-gensym-window
                     (window-for-workstation workstation)))))))



;;;; Event Details


;;; An `event plist' is to be used in a local event (or as the "event detail" of
;;; a workstation event) for extra detailed information associated with the
;;; event. An event plist's contents is determined by the type of event and
;;; other particulars of the event, e.g., the event code.
;;;
;;; An event plist is to be constructed by users of events as a list (possibly
;;; null) of gensym conses, the top level elements of which are of the following
;;; types (a) text-string, (b) symbol, (c) integer (a gensym fixnum).

;;; The following operations are defined for event details.
;;;
;;; `Reclaim-event-plist' reclaims an event plist.
;;;
;;; `Copy-event-plist' copies an event plist, including the top-level conses
;;; (using gensym-cons) and text strings.

(defun reclaim-event-plist (plist)
  (unless (null plist)
    (loop for (nil v) on plist by #'cddr
          do (if (text-string-p v)
                 (reclaim-text-string v)))
    (reclaim-gensym-list plist)))


(defun copy-event-plist (plist)
  (unless (null plist)
    (loop for (p v) on plist by #'cddr
          nconc (gensym-list p (if (text-string-p v) (copy-text-string v) v)))))




;;;; Local Events



;;; A `local event queue' is a queue of the "local events" from a "local
;;; window", that is a (Gensym) window that is not of type ICP.

;;; For a standard workstation local event, the elements are:
;;;
;;;    event-code x y timestamp
;;;
;;; where timestamp is usually the "current fixnum time", but can be implemented
;;; as any fixnum representation of "ticks" which always increase for at least
;;; 24 hours.

;;; For a reshape event, the elements are:
;;;
;;;    RESHAPE

;;; For a refresh event, the elements are:
;;;
;;;    REFRESH [left-edge-of-area top-edge-of-area
;;;                right-edge-of-area bottom-edge-of-area]
;;;
;;; The edges are optional.  If they are provided, then just the area specified
;;; will be refreshed.  Otherwise, the entire gensym window must be refreshed.

;;; Event codes are as defined in module KEYBOARDS.

;;; X is the x position of the mouse in native window coordinates.  Y is the y
;;; position of the mouse in window coordinates; timestamp is the closest
;;; possible approximation to the time at which the mouse input occurred; and
;;; native-window is the local (non-ICP) window (as defined in module WINDOWS)
;;; to which this input was directed.


#+development
(defvar trace-local-events nil)

#+development
(defun trace-local-events ()
  (setq trace-local-events t))

#+development
(defun untrace-local-events ()
  (setq trace-local-events nil))


#+development
(defun trace-local-event (type key-code x y timestamp &optional plist?)
  (format t "~2a ~9d ~4d ~4d ~12a(~d)~@[ ~s~]~%"
          type timestamp x y (key-name key-code) key-code plist?))



(def-structure (local-event
                 (:reclaimer reclaim-local-event-1)
                 (:print-function print-local-event))
  local-event-key-code                        ; Including window-reshape
  local-event-timestamp
  local-event-cursor-x                        ; left-edge-of-area
  local-event-cursor-y                        ; top
  local-event-right                        ; right
  local-event-bottom                        ; bottom
  (local-event-plist                          ; Other info; automatic reclamation of top-level
    nil :reclaimer reclaim-event-plist)) ;   gensym conses & text strings



;;; `Reclaim-local-event' is the standard function that should be used to
;;; reclaim a local event. It reclaims the top-level conses of the plist slot
;;; (local-event-plist?) as gensym conses.  Text strings that occur as values
;;; are reclaimed using reclaim-text-string. Other slots (besides the plist) are
;;; immediate Lisp values, and therefore need no reclamation.  The local-event
;;; structure spine is itself reclaimed in the conventional way structures.

(defun reclaim-local-event (local-event)
  (reclaim-local-event-1 local-event))



#+development
(defun print-local-event (local-event stream depth)
  (declare (ignore depth))
  (printing-random-object (local-event stream)
    (let ((key-code (local-event-key-code local-event)))
      (format stream "~a ~a ~d,~d"
              'local-event
              (if key-code (key-name key-code))
              (local-event-cursor-x local-event)
              (local-event-cursor-y local-event)))))


;;; `Copy-local-event' copies an event.  The plist's spine is copied using fresh
;;; gensym conses, and creating copies of text strings or gensym strings that
;;; appear as values.  No other substructure of the plist is copied.

(defun copy-local-event (event)
  (let ((new-event (make-local-event)))
    (setf (local-event-key-code new-event) (local-event-key-code event)
          (local-event-timestamp new-event) (local-event-timestamp event)
          (local-event-cursor-x new-event) (local-event-cursor-x event)
          (local-event-cursor-y new-event) (local-event-cursor-y event)
          (local-event-right new-event) (local-event-right event)
          (local-event-bottom new-event) (local-event-bottom event)
          (local-event-plist new-event) (copy-event-plist (local-event-plist event)))
    new-event))

(declare-special-global local-event-queue)
(def-system-variable local-event-queue
    platforms
  (:funcall make-queue) nil t)



;;; The macro `local-event-queue' is intended to be used in an environment
;;; having possibly many gensym windows per Lisp process.  Gensym software
;;; currently does not have to support such platforms.  (They were last needed
;;; on the "tv windows" window system of the lisp machine.  For the current set
;;; of cases, this just expands to the variable local-event-queue.
;;;
;;; Similar comments apply to `local-reshape-event-queue', the macro and
;;; variable, respectively, which are defined below, as well as to
;;; `local-paste-event-queue'.

(defmacro local-event-queue (native-window?)
  `(or (get-event-queue-of-native-window ,native-window?)
       local-event-queue))



;;; The function `reclaim-local-event-queue' reclaims a local event queue,
;;; including its events.  This can be used to reclaim any queue that holds
;;; structures of type local-event, inluding not only the local event queue of a
;;; Gensym window, but also the reshape event queue and paste event queue.

(defun reclaim-local-event-queue (queue)
  (loop while (queue-non-empty-p queue)
        do (reclaim-local-event (queue-pop queue)))
  (reclaim-queue queue))



;;; The function `enqueue-local-event' enqueues a local event.  The optional
;;; plist is should either be nil or a plist, to be incorporated directly (i.e.,
;;; with no copying) into the local event plist slot.  The event elements are
;;; reclaimed via reclaim-local-event, q.v.

(defun enqueue-local-event (native-window? key-code x y timestamp &optional plist?)
  (let ((event (make-local-event)))
    (setf (local-event-key-code event) key-code
          (local-event-timestamp event) timestamp
          (local-event-cursor-x event) x
          (local-event-cursor-y event) y
          (local-event-right event) x                            ; Ignored.
          (local-event-bottom event) y
          (local-event-plist event) plist?)
    (queue-insert (local-event-queue native-window?) event)
    event))

;; Called from get-all-x11-events and player.



;;; `Dequeue-local-event-if-any' returns the next event available from the local event
;;; merge, if it has any, or from the listed local event queue, if it has any.

(defmacro dequeue-local-event-if-any (native-window)
  `(queue-pop (local-event-queue ,native-window)))



;;; `Peek-at-local-event-if-any' is like dequeue-local-event-if-any except that calling
;;; it does not invalidate the previously dequeued local event.

(defmacro peek-at-local-event-if-any (native-window)
  `(queue-peek (local-event-queue ,native-window)))



;;; The macro `requeue-local-event' pushes the given local event onto
;;; the local event queue for the given window.

(defmacro requeue-local-event (native-window local-event)
  `(queue-push (local-event-queue ,native-window) ,local-event))



;;; The function `get-last-such-local-event' is used to merge mouse-motion
;;; events in the local event queue.

(defun get-last-local-mouse-motion-event (native-window?)
  (loop with last-one? = nil
        as local-event? = (peek-at-local-event-if-any native-window?)
        while (and local-event? (mouse-motion-event-p (local-event-key-code local-event?)))
        do (when last-one?
             (reclaim-local-event last-one?))
           (setq last-one? (dequeue-local-event-if-any native-window?))
        finally
          (return last-one?)))

;; This no longer ignores shift (or other) bits in the event codes. (MHD 10/1/99)

;; Consider (maybe optionally) giving up after some number of iterations, so that it
;; doesn't, say, overly compress mouse motion events.




;;;; Reshape event queue

(declare-special-global local-reshape-event-queue)
(def-system-variable local-reshape-event-queue platforms
  (:funcall make-queue))


(defmacro local-reshape-event-queue (native-window?)
  `(or (get-reshape-event-queue-of-native-window ,native-window?)
       local-reshape-event-queue))




;;; `Enqueue-window-reshape-event' enqueues a refresh or reshape event in a
;;; special `local reshape event queue'.  This is check at frequent intervals
;;; by G2 in order to react to changes in the appearance of a G2 window caused
;;; by interaction by the user with the native window system's window manager.
;;; For example, on Lisp machines, the user can reshape a G2 window using Edit
;;; Screen off of the Lisp machine's main menu.  Another example is when the
;;; user exposes part of a G2 window using the Macintosh interface.  In these
;;; cases, this function, along with handle-reshape-event (in WINDOWS) should
;;; work to fix up G2's image on the screen as well as its internal
;;; representation of the G2 window's size.

;;; Key-code may be the key-code for either WINDOW-RESHAPE or WINDOW-REFRESH.

(defun enqueue-window-reshape-event
    (native-window key-code timestamp
                   &optional
                   left-edge-of-area? top-edge-of-area?
                   right-edge-of-area? bottom-edge-of-area?
                   window-handle?)
  (let ((local-event (make-local-event)))
    (setf (local-event-key-code local-event) key-code
          (local-event-timestamp local-event) timestamp
          (local-event-cursor-x local-event) left-edge-of-area?
          (local-event-cursor-y local-event) top-edge-of-area?
          (local-event-right local-event) right-edge-of-area?
          (local-event-bottom local-event) bottom-edge-of-area?)
    (when window-handle?
      (setf (local-event-plist local-event) (gensym-list 'window window-handle?)))
    (queue-insert (local-reshape-event-queue native-window)
                  local-event)))

;; In the past, key-code might have been some Macintosh data structure.



;;;; Window reshapes



;;; `Check-shape-of-window-without-lookahead' is intended as a very efficient
;;; check on whether the window has been reshaped or refreshed by the user (via
;;; the host window system) or by the system (e.g. due to pop-up messages,
;;; dialog boxes, or menus).  It is intended to be called by on-window in each
;;; implementation where that is appropriate, e.g. systems with window managers
;;; that allow users to reshape windows.  Support is needed within G2 for this.
;;; Namely, a "local reshape event" must be enqueued for the local window.  If a
;;; reshape event happens, it calls the function reshape-native-window.  We
;;; return T iff some work was done.

(defun-simple check-shape-of-window-without-lookahead (gensym-window native-window)
  (with-backtrace-for-internal-error 'check-shape-of-window-without-lookahead
    (let ((work-was-done? nil))

      (loop with queue = (get-gensym-window-reshape-event-queue gensym-window)
            for count from 1 to 20        ; do only a reasonable number of times
            while (queue-peek queue)
            doing
        (handle-reshape-event gensym-window native-window)
        (setq work-was-done? t))

      work-was-done?)))

;; Forward-referencing problems made having this be a macro unwieldy.  It seems
;; unnecessary.  (MHD 1/30/95)

;; In X Windows, get-all-x11-events must be called to poll for refresh/reshape
;; events.  In all others, these go into the refresh/reshape event queue
;; asynchronously.  (MHD 11/27/89)

;; When a telewindow is reshaped, we get a bunch of refresh events in
;; succession, which sometimes the remote G2 can merge into one and sometimes
;; not.  It might be useful to merge them here, on the telewindows side.  The
;; also happens in Windows 3.5.




;;; `Reshape-native-g2-window' is called by the user interface manager in G2
;;; when it receives a WINDOW-RESHAPE event for a native window. ...

(defun reshape-native-g2-window (gensym-window native-window)
  (make-or-revise-window-per-native-window gensym-window native-window)
  (lay-out-window gensym-window)
  (progn                                ; see note -mhd, 1/22/01
    (flush-window-reshape-local-event-queue native-window)
    (refresh-window gensym-window)))

;; Consider adjusting each pane cursor that is being used to resize or relocate
;; an image plane so as to maintain its offset from that image plane.

;; Note: in order to avoid this full refresh, we must enable bit gravity in
;; ext/c/windows.c (so that the the minimal exposure event comes in, i.e.,
;; define (enable) BIT_GRAVITY in ext/c/windows.c), and then invalidate the
;; regions that are no longer valid (i.e., the interior of image planes with
;; same gravity as we use in windows.c) but were previously inside the old
;; window and are still inside the new window, so they are refreshed.  I.e.,
;; with our usual single pane configuration, if growing on right and bottom,
;; have to invalidate old the right and bottom window pane borders so they get
;; redrawn.  A little project.  Oh, also have to fix things up to work
;; reasonably with old G2's, which won't handle partial exposure events at
;; all. -mhd, 1/22/01



;;; `Get-width-of-native-window' and `get-height-of-native-window' determine
;;; the width and height of the specified native-window in an
;;; implementation-dependent way.
;;;
;;; This may be called with a "native window" that is not even yet linked to a
;;; gensym window, but is about to become so linked.
;;;
;;; Notes for the X Window System implementation:
;;;
;;; We are using x11-last-window-width and x11-last-window-height as the width
;;; and the height are always guaranteed to be set in xwindows.c to the value
;;; associated with the real window.  x11-window-width and x11-window-height
;;; might not retrun the actual value during a resize.
;;;
;;; G2 croaks when the window size is less than 22.  Here we pretend that it is
;;; always at least 22.  -pto & mhd 17jul90

(defun-simple get-x-position-of-native-window (native-window)
  (c-x11-last-window-x native-window))

(defun-simple get-y-position-of-native-window (native-window)
  (c-x11-last-window-y native-window))

(defun-simple get-width-of-native-window (native-window)
  (maxr (c-x11-last-window-width native-window)
        22))

(defun-simple get-height-of-native-window (native-window)
  (maxr (c-x11-last-window-height native-window)
        22))

;; Called from TELEWINDOWS, and from the function below.  Abstracted out of
;; inline code in these callers today. (MHD 5/16/94)



;;; `Make-or-revise-window-per-native-window' makes a new, or revises an old,
;;; gensym window having native-window as the value for its native-window? slot
;;; in an implementation-dependent way.  In either case, it calls
;;; make-or-revise-window.

;;; If gensym-window? is null, a new gensym window is created and returned;
;;; otherwise, gensym-window? is simply revised.  Note that a new window
;;; parameters plist is created only when a new gensym window is created;
;;; otherwise the old one is used.  When an new one is created, it is done via a
;;; call to make-window-parameters-plist.

;;; This is called, for example, when creating a new gensym window for the first
;;; time at the start of a G2 process or when revising an existing gensym window
;;; in response to revisions to the native window by the user through the host
;;; operating system.

;;; See make-window-parameters-plist and make-or-revise-window for further
;;; details.

(defun-simple make-or-revise-window-per-native-window (gensym-window? native-window)
  (let* ((gensym-window
           (make-or-revise-window
             gensym-window?
             0 0
             (get-width-of-native-window native-window)
             (get-height-of-native-window native-window)
             native-window
             nil
             (unless gensym-window?
               (make-window-parameters-plist native-window)))))

    (note-change-in-gensym-window gensym-window)

    (unless gensym-window?
      ;; Creating a new native gensym-window?
      ;;
      ;; Note that at the time this window is created in TW, we do not yet have
      ;; an ICP connection, so it would be bad to attempt to send notice of
      ;; this change over the wire.
      (change-icp-window-protocol-version
        gensym-window
        (if (slave-gensym-window? gensym-window)
            original-icp-window-protocol-version
            latest-icp-window-protocol-version)))
    gensym-window))

;; Note: this no longer supports a raster-for-native-window? to be kept in the
;; gensym window structure.  It always passes in NIL for that slot.  It used to
;; pass in something for some tv-windows (lispm) implmentations.  Now, that
;; concept may be completely obsolete.  (MHD 5/16/94)

;; This does not look at the type of native-window, which is bad!! (MHD 1/9/91)
;; Move elsewhere?




;;;; Local Events in X11



;;; The defparameter `fixnum-time-interval-for-automatic-xsync' is the interval
;;; a which we call XSync, whether we need to or not.  Calling XSync
;;; periodically seems to be necessary in order to see error events from the
;;; server. For example, when our X window is deleted out from under us.  Here
;;; we default to once a second.

(defparameter fixnum-time-interval-for-automatic-xsync (*f 1 fixnum-time-units-per-second))

(defvar fixnum-time-of-last-xsync 0)



;;; The substitution-macro `decode-local-event' decodes single local event,
;;; which may be from either X or MS windows, and returns two values, the
;;; event-type and the key-code..  We canonicalize the key code for keyboard
;;; events in various ways.

(defun-substitution-macro decode-local-event (event-code)
  (let* ((event-type (logandf event-code x11-event-codes-mask))
         (key-code (ashf event-code x11-key-code-shift)))

    (cond ((=f event-code x11-no-more-events)
           (values event-code 0))

          ((=f event-type x11-keypress)
           (values event-type (canonicalize-gensym-key-code key-code)))

          ((or (=f event-type x11-button-press)
               (=f event-type x11-button-release)
               (=f event-type x11-pointer-motion))
           (values event-type (clear-bit key-code caps-lock-bit)))

          (t
           (values event-type key-code)))))

;; This is nearly, and should become, a no-op.



;;; The parameter `scrollbar-code-names' must be kept in sync with Win32
;;; winuser.h.

(defparameter scrollbar-code-names
  #(lineup linedown pageup pagedown thumbposition thumbtrack top bottom endscroll))

(defun-simple scrollbar-code-name (code)
  (when (<f -1 code (length scrollbar-code-names))
    (svref scrollbar-code-names code)))

;; Unpacks string produced by pack_root_and_path in ext/c/twpro.c
(defun unpack-list-directory-request-value (value)
  (let ((pos? (position-in-wide-string (code-charw 1) value)))
    (cond (pos?
           (prog1
               (gensym-list 'root (wide-string-substring value 0 pos?)
                            'directory (wide-string-substring value (1+f pos?) nil))
             (reclaim-wide-string value)))
          (t
           (gensym-list 'directory value)))))


;;; The function `decode-native-control-event' unpacks event data in the x, y,
;;; width and height parms into a more user-friendly plist of information.

(defun-simple decode-native-control-event (key-code x y width height window-handle? value?)
  (case (convert-key-code-to-key-symbol key-code)
    ((hscroll vscroll)                        ; See GENSYM_HSCROLL, GENSYM_VSCROLL in mdi.c
     (nconc (gensym-list 'code (scrollbar-code-name x) 'thumb y 'id width)
            (and window-handle? (gensym-list 'window window-handle?))))

    (menu-choice                        ; See GENSYM_MENU_CHOICE in graphics.h
     (gensym-list 'choice x 'menu y))

    (menu-bar                                ; See GENSYM_MENUBAR in graphics.h
     ;; TODO: Include the menu-bar handle in the message.
     nil)

    (dialog-update
     (gensym-list 'dialog-id (map-client-dialog-id-to-global-dialog-id x)
                  'control-id y 'initiator width 'new-value value?))

    (dialog-dismissed
     (gensym-list 'dialog-id (remove-dialog-given-client-id x)
                  'dialog-response-code y))

    (dialog-miscellaneous-communication
     (gensym-list 'dialog-id (map-client-dialog-id-to-global-dialog-id x)
                  'control-id y
                  'message-type width 'info value?))

    (dialog-user-gesture
     (nconc
       (gensym-list 'control-id width
                    'key height)
       (if (>=f x 0) (gensym-list 'row x))
       (if (>=f y 0) (gensym-list 'column y))
       (if value? (gensym-list 'value value?))
       (if window-handle? (gensym-list 'window window-handle?))))

    (nms-menu-posted                        ; See GENSYM_MENU_POSTED in graphics.h
     (gensym-list 'nms-menu-handle x 'item y))

    (nms-menu-unposted                        ; New for 8.1b0
     (gensym-list 'nms-menu-handle x))

    (nms-menu-item-selected                ; New for 8.0r1
     (gensym-list 'nms-menu-handle x 'item y
                  'previous-nms-menu-handle width 'previous-item height))

    ;; New for 8.0. See g2pvt_send_nms_control_event and nms-execute-menu-choice
    (nms-control                        ; Msg from NMS edit or combo box
     (nconc (gensym-list 'control-id x        ; Cmd ID of control object
                         'selection y)        ; If combo-box, index of selection, else -1.
            (if value? (gensym-list 'value value?))
            (if window-handle? (gensym-list 'window window-handle?))))

    (tree-view
     (nconc (gensym-list 'handle width)        ; Handle of the tree-view FIXME: redundant.
            (gensym-list 'event height)        ; Event type
            (gensym-list 'item x)        ; Handle of item (if relevant)
            (if (>f y 0) (gensym-list 'key y))        ; Keycode (if relevant)
            (if value? (gensym-list 'value value?)) ; Label of item
            (if window-handle? (gensym-list 'window window-handle?))))

    (prop-grid
     (nconc (gensym-list 'event x)        ; Event code
            (gensym-list 'item y)        ; Item ID (if relevant)
            (if (/=f width most-negative-fixnum) ; Integer value (if relevant)
                (gensym-list 'ivalue width))
            (if value? (gensym-list 'value value?)) ; Item value as string (if relevant)
            (if window-handle? (gensym-list 'window window-handle?))))

    (grid-view
     (nconc (gensym-list 'event x)        ; Event code
            (gensym-list 'control-id y)        ; TODO: Only if is in a dialog.
            (gensym-list 'row width)
            (gensym-list 'column height)
            (if value? (gensym-list 'value value?))
            (if window-handle? (gensym-list 'window window-handle?))))

    (tabular-view
     (nconc (gensym-list 'event x)        ; Event code
            (gensym-list 'row y)        ; Row ID
            (if (>=f height 0) (gensym-list 'column height)) ; Column (physical)
            (if (>f width 0) (gensym-list 'key width))        ; Keycode (if relevant)
            (if value? (gensym-list 'value value?)) ; Label of item
            (if window-handle? (gensym-list 'window window-handle?))))

    (chart-view
     (nconc (gensym-list 'x x 'y y)        ; subset, point OR menu, submenu
            (gensym-list 'handle width)        ; unused
            (gensym-list 'event height)        ; event code
            (if value? (gensym-list 'value value?)) ; Coordinates, other info.
            (if window-handle? (gensym-list 'window window-handle?))))

    (shortcut-bar
     (nconc (gensym-list 'event x)        ; Event type
            (gensym-list 'drag-to y)        ; Destination item index
            (gensym-list 'folder width)        ; Folder index, if relevant.
            (gensym-list 'item height)        ; Item index, if relevant.
            (if value? (gensym-list 'value value?)) ; Label of item
            (if window-handle? (gensym-list 'window window-handle?))))

    (html-view
     (nconc (gensym-list 'x x 'y y)        ; Mouse position
            (gensym-list 'handle width)        ; control handle
            (gensym-list 'event height)        ; event code
            (if value? (gensym-list 'value value?))
            (if window-handle? (gensym-list 'window window-handle?))))

    (logbook-view
     (nconc (gensym-list 'x x 'y y)        ; Mouse position
            (gensym-list 'msg width)        ; Message serial number
            (gensym-list 'event height)        ; event code
            (if value? (gensym-list 'value value?))
            (if window-handle? (gensym-list 'window window-handle?))))

    (status-bar
     (nconc (gensym-list 'event x)
            (gensym-list 'pane y)
            (gensym-list 'bits width)
            (if value? (gensym-list 'value value?))
            (if window-handle? (gensym-list 'window window-handle?))))

    (debugger-dialog
     (nconc (gensym-list 'opcode x 'line y)
            (if window-handle? (gensym-list 'window window-handle?))))

    (editor
     (nconc (gensym-list 'opcode x)
             (gensym-list 'caret y)
            (if (>=f width 0) (gensym-list 'end width))
            (if value? (gensym-list 'text value?))
            (if window-handle? (gensym-list 'window window-handle?))))

    (list-directory                        ; Request from choose-file/directory dialogs
     (nconc (gensym-list 'handle x)
            (if (>=f y 0) (gensym-list 'opcode y))
            (when value?
              (unpack-list-directory-request-value value?))
            (if window-handle? (gensym-list 'window window-handle?))))

    ;; New for 8.0
    (window-refresh
     (nconc (gensym-list 'x x 'y y 'width width 'height height)
            (and window-handle? (gensym-list 'window window-handle?))))

    ;; Possible status values: size-restored, size-minimized, size-maximized,
    ;; and maybe for window-size, size-maxshow, size-maxhide.
    (window-moved
     (nconc (gensym-list 'x x 'y y 'status width)
            (and window-handle? (gensym-list 'window window-handle?))))
    (window-sized
     (nconc (gensym-list 'width width 'height height 'status x)
            (and window-handle? (gensym-list 'window window-handle?))))

    (t
     (when window-handle?
       (gensym-list 'window window-handle?)))))


;;; The function `native-window-handle-for-last-event?' returns the handle of the
;;; native-window associated with the last event, or NIL if none.

(defun native-window-handle-for-last-event? (native-window)
  (let ((handle (c-x11-last-event-window-handle native-window)))
    (if (>=f handle 0) handle)))        ; handle of 0 means main G2-WINDOW


;;; The function `string-value-for-last-event?' returns a newly consed
;;; wide-string associated with the last event, or NIL if none.

(defun string-value-for-last-event? (native-window)
  (let ((length (c-x11-last-event-value native-window #w"" 0)))
    (when (>=f length 0)
      (let ((string (obtain-text-string length)))
        (c-x11-last-event-value native-window string length)
        string))))

;;; The function `get-all-x11-events' is the connection between a local
;;; X window and the our local event queues.  It discards null-events.
;;; Reshape and expose events are passed on to enqueue-window-reshape-event
;;; all others passed on via enqueue-local-event.

;;; At present, all events received within a given call to get-all-x11-events
;;; have the exact same timestamp.  This could probably be remedied,
;;; especially since X keeps timestamps with its own internal events, but
;;; we would have to understand the mapping from those time base into the
;;; our timebase.

(defun get-all-x11-events (native-window)

  (let ((fixnum-time (get-fixnum-time))
        (event-code 0))

    (loop
      ;; Periodically do an XSync, which allows us to notice that, for example,
      ;; our X window has been destroyed.
      ;; The "correct" way to do this is via XNoOp(display).
      (when (>f (fixnum-time-difference fixnum-time fixnum-time-of-last-xsync)
                fixnum-time-interval-for-automatic-xsync)
        (setq fixnum-time-of-last-xsync fixnum-time)
        (sync-graphics-on-native-window native-window))

      (multiple-value-bind (event-type key-code)
          (decode-local-event (setq event-code (c-x11-get-event native-window)))

        ;; Chestnut mistranslates CASE with negative arms, which is why this
        ;; is a COND.
        (cond ((=f event-type #.x11-no-more-events)
               (loop-finish))
              ((=f event-type #.x11-nullevent)
               nil)
              ((=f event-type #.x11-focus-in)
               ;; New for 8.0: send focus-in events explicitly.
               (when (native-window-handle-for-last-event? native-window)
                 (enqueue-local-event
                   native-window (key-code 'window-activated)
                   (c-x11-last-mouse-x-position native-window)
                   (c-x11-last-mouse-y-position native-window)
                   (c-x11-last-event-time native-window)
                   (gensym-list 'window
                                (native-window-handle-for-last-event? native-window))))

               ;; Did another app copy into clipboard? Tell G2 status
               (when (and (notify-if-clipboard-has-text-p current-workstation)
                          (window-supports-request-for-paste-availability-function
                            current-workstation-window))
                 (enqueue-local-paste-availability-event
                   native-window
                   (local-clipboard-has-text-p current-workstation-window)
                   1))) ; don't care for paste-availability-event

              ;; These are OLE-only and could be removed.
               ((=f event-type #.x11-enter)
                (when native-window-notices-enter-and-leave-events-p
                  (enqueue-local-event
                    native-window
                    (key-code 'enter-window)
                    (c-x11-last-mouse-x-position native-window)
                    (c-x11-last-mouse-y-position native-window)
                    (c-x11-last-event-time native-window))))
               ((=f event-type #.x11-leave)
                (when native-window-notices-enter-and-leave-events-p
                  (enqueue-local-event
                    native-window
                    (key-code 'leave-window)
                    (c-x11-last-mouse-x-position native-window)
                    (c-x11-last-mouse-y-position native-window)
                    (c-x11-last-event-time native-window))))

              ((=f event-type #.x11-reshape)
               (let* ((last-window-x
                        (c-x11-last-window-x native-window))
                      (last-window-y
                        (c-x11-last-window-y native-window))
                      (last-window-width
                        (c-x11-last-window-width native-window))
                      (last-window-height
                        (c-x11-last-window-height native-window)))
                 (enqueue-window-reshape-event
                   native-window
                   (key-code 'window-reshape)
                   (c-x11-last-event-time native-window)
                   last-window-x
                   last-window-y
                   (+r last-window-x last-window-width) ; right
                   (+r last-window-y last-window-height)  ; bottom
                   (native-window-handle-for-last-event? native-window))))

              ((=f event-type #.x11-exposure)
               (unless (last-exposure-event-already-queued-p native-window)
                 (let* ((last-expose-x
                          (c-x11-last-expose-x-position native-window))
                        (last-expose-y
                          (c-x11-last-expose-y-position native-window))
                        (last-expose-width
                          (c-x11-last-expose-width native-window))
                        (last-expose-height
                          (c-x11-last-expose-height native-window)))
                   (enqueue-window-reshape-event
                     native-window
                     (key-code 'window-refresh)
                     (c-x11-last-event-time native-window)
                     last-expose-x
                     last-expose-y
                     (+r last-expose-x last-expose-width) ; right
                     (+r last-expose-y last-expose-height)  ; bottom
                     (native-window-handle-for-last-event? native-window)))))

              ((=f event-type #.x11-control)
               ;; Message from some arbitrary native control, window, or widget.
               ;; The keycode encodes the class of control (GENSYM_HSCROLL,
               ;; GENSYM_VSCROLL, etc), and the last-expose-x,y,width,height
               ;; encode additional arbitrary parameters, overloaded in the same
               ;; way that Win32 overloads wparam and lparam. Here is where we
               ;; unpack them into a plist. See g2ext_get_event in
               ;; ext/c/events.c
               (let ((plist (decode-native-control-event
                              key-code
                              (c-x11-last-expose-x-position native-window)
                              (c-x11-last-expose-y-position native-window)
                              (c-x11-last-expose-width native-window)
                              (c-x11-last-expose-height native-window)
                              (native-window-handle-for-last-event? native-window)
                              (string-value-for-last-event? native-window))))
                 (enqueue-local-event
                   native-window key-code
                   (c-x11-last-mouse-x-position native-window)
                   (c-x11-last-mouse-y-position native-window)
                   (c-x11-last-event-time native-window)
                   plist)))

              (t
               ;; All the rest: keyboard, mouse.
               (enqueue-local-event
                 native-window key-code
                 (c-x11-last-mouse-x-position native-window)
                 (c-x11-last-mouse-y-position native-window)
                 (c-x11-last-event-time native-window)
                 (construct-local-event-plist native-window))))))))

;; This routine is called in Telewindows, and so you can't munge the event
;; in a manner that will make the Telewindow's incompatible with older
;; G2 processes.  - ben 10/22/93

;; Note: it is tempting to use the time tags which Xlib supplies here.  They
;; more accurately reflect what the user really did (double click, etc).  But
;; careful: If we do, then the mouse-tracking procedure and get-last-event user
;; procs must convert back to G2 time for the user!  -bah, fmw, 2/25/94

;; This now uses the timetag from Xlib. -fmw, 10/12/94



;;; `Last-exposure-event-already-queued-p' peeks at every element of the local
;;; event queue of native window that holds exposure events
;;; (local-reshape-event-queue), and returns true iff the last exposure event is
;;; queued there.  The coordinates of the last exposure event are taken into
;;; account, but the timestamp is not, when making the comparison.  This has a
;;; maximum number of events to check, but it's very high (100), and it should
;;; be very rarely if ever this high.  Meanwhile, it's no problem for duplicate
;;; exposure events to be in the queue, just a bit less optimal.

(defun last-exposure-event-already-queued-p (native-window)
  (find-local-reshape-event
    native-window
    (key-code 'window-refresh)
    (c-x11-last-expose-x-position native-window)
    (c-x11-last-expose-y-position native-window)
    (c-x11-last-expose-width native-window)
    (c-x11-last-expose-height native-window)))

;; Why this was added: it remains a mystery why (at some point early in 6.0),
;; there are clearly now three exposure type refresh events at startup.  When
;; these happen, and they're all the same, it is fine in general to just have
;; one.  This is implemented for now by just peeking at the queue and not adding
;; the subsequent events when it's already at the head of the queue.  A more
;; complicated filtering could be done, but this accomplishes the primary goal:
;; getting rid of the flash at startup, very noticeable with slower connections.
;; -mhd, 1/23/01





;;; Flush-window-reshape-local-event-queue ... One place this is intended to be
;;; used: when handling a reshape event, where we decide to respond with a full
;;; refresh and reshape to up-to-date window coordinates, obviating the need for
;;; any further reshape or refresh events.

(defun flush-window-reshape-local-event-queue (native-window)
  (loop with e
        while (setq e (queue-pop (local-reshape-event-queue native-window)))
        do (reclaim-local-event e)))






#+unused
(defun-simple reshape-events-equal-p (event-1 event-2)
  (and
    (eql (local-event-key-code event-1) (local-event-key-code event-2))
    (eql (local-event-cursor-x event-1) (local-event-cursor-x event-2))
    (eql (local-event-cursor-y event-1) (local-event-cursor-y event-2))
    (eql (local-event-right event-1) (local-event-right event-2))
    (eql (local-event-bottom event-1) (local-event-bottom event-2))))

#+unused
(defun-void remove-similar-local-reshape-events (native-window reshape-event)
  (queue-delete-macro
    (local-reshape-event-queue native-window)
    reshape-event
    :test reshape-events-equal-p))


(defun find-local-reshape-event (native-window event-code x y width height)
  (loop for e being each queue-element
          of (local-reshape-event-queue native-window)
        if (and
             (eql (local-event-key-code e) event-code)
             (eql (local-event-cursor-x e) x)
             (eql (local-event-cursor-y e) y)
             (eql (local-event-right e) width)
             (eql (local-event-bottom e) height))
          return e))

;; Despite their names (no ?), the slots of these structures do not reliably
;; hold fixnum integers, so no type-specific arithmetic is applied.




;;; Describe-local-reshape-event-queue is a development-only function.  It
;;; prints a description of each event in the local-reshape-event-queue of
;;; native-window.

#+development
(defun describe-local-reshape-event-queue (native-window)
  (loop for e being each queue-element
          of (local-reshape-event-queue native-window)
        do (d e)))








;;;; Mouse Positions




;;; `set-position-of-mouse-1' is a subfunction of the icp message handler for
;;; set-position-of-mouse, which should be the only function that uses it.
;;; (See TELESTUBS).  It should return the x and y local of the mouse after the
;;; move.

(defun set-position-of-mouse-1 (x y)
  (c-x11-move-pointer current-workstation-native-window? x y)
  (values x y))



;;; `Shift-position-of-mouse-1' is a subfunction of the icp message handler for
;;; shift-position-of-mouse, which should be the only function that uses it.
;;; (See TELESTUBS.)

(defun shift-position-of-mouse-1 (delta-x delta-y)
  (multiple-value-bind (mouse-x mouse-y)
      (get-position-of-mouse)
    (set-position-of-mouse-1
      (+ mouse-x delta-x) (+ mouse-y delta-y))))



;;; The function `get-position-of-mouse' queries the native window system
;;; to retrieve the current mouse position.

(defun get-position-of-mouse ()
  (cond ((null current-workstation-native-window?)
         (values 10 10))
        (t
         (let* ((mouse-x
                  (c-x11-get-mouse-x-position current-workstation-native-window?))
                (mouse-y
                  (c-x11-last-mouse-y-position current-workstation-native-window?)))
           (values mouse-x mouse-y)))))




;;; `Native-window-polling-interval' is a system variable used to effect the
;;; rate at which we must poll the native window.  The value is in units
;;; of milliseconds.  The default, 1 second, arises (we believe) because of
;;; race conditions that allow events to arrive just before we go to sleep.
;;; These events hide in the client side of the server while we block on the
;;; handle that the client side uses to talk to server.

;; We now believe that the scenario outlined above is extremely unlikely, and so
;; we will up the maximum sleep to 1 hour.  -jra 11/4/96

;;; See `mouse-tracking' for a dicussion of why this is sometimes bound to
;;; a smaller value.

;;; In Telewindows it passed in the call to idle-process, so there it's really
;;; the napping interval.

;;; In G2 is is used to configure a scheduled task that generates a heartbeat,
;;; that in turn awakens the scheduler, and hence kicks service-workstations.

(declare-special-global native-window-polling-interval-default
                        native-window-polling-interval-fast
                        native-window-polling-interval)

(def-system-variable native-window-polling-interval-default platforms 3600000)
(def-system-variable native-window-polling-interval-fast    platforms #+development 3600000 #-development 250)
(def-system-variable native-window-polling-interval         platforms 3600000)


;;; `Start-mouse-tracking' and `stop-mouse-tracking enables' toggle interrupt style
;;; enqueueing of mouse motion events.

(defun start-mouse-tracking (native-window)
  (setf native-window-polling-interval
        native-window-polling-interval-fast)
  (c-x11-start-mouse-tracking native-window)
  t)


(defun stop-mouse-tracking (native-window)
  (setf native-window-polling-interval
        native-window-polling-interval-default)
  (c-x11-stop-mouse-tracking native-window)
  t)





;;;; For-Workstation-Context a Named Dynamic Extent

(def-named-dynamic-extent for-workstation-context
  (module telestubs)
  (unwind? t))

(defvar-of-named-dynamic-extent specific-structure-for-current-workstation-context
    for-workstation-context)

#+obsolete
(defvar-of-named-dynamic-extent track-mouse-in-current-workstation-context?
    for-workstation-context)

(defvar-of-named-dynamic-extent type-of-current-workstation-context
    for-workstation-context)

(defvar-of-named-dynamic-extent current-workstation-context
    for-workstation-context)







;;;; For-Workstation-Polling a Named Dynamic Extent




;;; For-workstation-polling allows its body to call poll-workstation
;;; and get-position-of-mouse by binding the required special variables
;;; needed for that function (based on workstation).

;;; It binds a subset of the variables bound by for-workstation.  Specifically,
;;; it binds current-workstation, current-workstation-window, type-of-
;;; current-workstation-window, and current-workstation-native-window?.


(def-named-dynamic-extent for-workstation-polling
  (module platforms)
  (unwind? t))

(defvar-of-named-dynamic-extent current-workstation for-workstation-polling)
(defvar-of-named-dynamic-extent current-workstation-window for-workstation-polling)
(defvar-of-named-dynamic-extent type-of-current-workstation-window
    for-workstation-polling)
(defvar-of-named-dynamic-extent current-workstation-native-window?
    for-workstation-polling)

(defmacro for-workstation-polling ((workstation) &body body)
  `(with-named-dynamic-extent* for-workstation-polling
                               ((current-workstation
                                  ,workstation)
                                (current-workstation-window
                                  (window-for-workstation current-workstation))
                                (current-workstation-native-window?
                                  (native-window? current-workstation-window))
                                (type-of-current-workstation-window
                                  (type-of-gensym-window current-workstation-window)))
     ,@body))






;;;; Misc Color and Pixel Operations




;;; The function `get-x11-pixel-value-from-rgb' allocates a new X11 pixel for
;;; the given rgb color.  It returns NIL if one could not be allocated.

(defun get-x11-pixel-value-from-rgb (native-x11-window red green blue extended-color-p)
  (let* ((string
           (twith-output-to-text-string
             (twrite-string "#")
             (if (< red 16) (twrite-string "0"))
             (twrite-positive-fixnum-in-radix red 16)
             (if (< green 16) (twrite-string "0"))
             (twrite-positive-fixnum-in-radix green 16)
             (if (< blue 16) (twrite-string "0"))
             (twrite-positive-fixnum-in-radix blue 16)))
         (pixel?
           (get-pixel-value native-x11-window string extended-color-p)))
    (reclaim-text-string string)
    pixel?))

;; The MS windows code is depending on the format being exactly #rrggbb.
;; We should instead pass the RGB values directly to the C layer.




;;; `Allocate-x11-pixel-value' returns the X11 pixel value of a color, given
;;; its symbol.  It first trys a textual mapping, then it goes for the RGB
;;; value of the color.  It returns nil if both attempts fail.

(defun allocate-x11-pixel-value (x11-window color-symbol)
  (let* ((color-name-text-string
           (copy-symbol-name color-symbol nil t))
         (pixel?
           (get-pixel-value x11-window color-name-text-string nil)))
    (reclaim-text-string color-name-text-string)
    (when (null pixel?)
      (let ((color-r-g-b? (assoc color-symbol standard-gensym-color-alist)))
        (when color-r-g-b?
          (setq pixel? (get-x11-pixel-value-from-rgb x11-window
                                                     (second color-r-g-b?)
                                                     (third color-r-g-b?)
                                                     (fourth color-r-g-b?)
                                                     nil)))))
    pixel?))



;;; `Create-x11-color-plist-from-color-hierarchy' returns a plist of colors.
;;; The plist consists entirely of new gensym conses.

;;; Note function argument 'color-hierarchy' has been changed to c-hierarchy to
;;; prevent name conflict with another global variable, because we think it's 
;;; no need to specially bind that variable. -- binghe, 2011/12/10, Glority

(defun create-x11-color-plist-from-color-hierarchy
    (x11-window c-hierarchy
                &optional
                (default-pixel-value 0)
                (number-of-colors-left nil))

    (when (null number-of-colors-left)
      (setq number-of-colors-left        ; see note (MHD 3/28/01)
            (maxf
              (-f (expt 2 (min 24 (c-x11-screen-depth x11-window)))
                  2)                        ; 2 is a magic number
              2)))
    (loop with queue = (make-queue)
          as entry
             = (gensym-cons default-pixel-value c-hierarchy)
             then (queue-pop queue)
          as entry-default-pixel = (car entry)
          as entry-name = (if (symbolp (cdr entry)) (cdr entry) (second entry))
          as pixel-value
             = (or (when (and (>f number-of-colors-left 0)
                              (not (eq entry-name 'root)))
                     (decff number-of-colors-left)
                     (allocate-x11-pixel-value x11-window entry-name))
                   entry-default-pixel)
          when (not (eq entry-name 'root))
            nconc (gensym-list entry-name (gensym-list pixel-value))
              into plist
          when (consp (cdr entry))
            do (loop for sub-entry in (cddr entry)
                     do (queue-insert queue (gensym-cons pixel-value sub-entry)))
          do (reclaim-gensym-cons entry)
          while (queue-non-empty-p-macro queue)
          finally
            (reclaim-queue queue)
            (return plist)))

;; Note: we compute number of colors left as the minimum of 2^24 colors or the
;; actual number, presumed to be 2 to the power given by the screen depth.  In
;; practice, a screen depth is rarely higher than 24, but if it is, it's
;; generally >= 36.  Our fixnum size is assumed to be 30 bits.  The purpose of
;; the min is to keep from going into bignums if the depth is, say, 36, and this
;; is fine, since would never need a number any higher than 2^24, since we so
;; few colors to handle in G2. (MHD 3/28/01)

;; To see that the consing here is under control, run this test:
;;
;; (compare-memory-allocation nil t)  ; reset count
;; (gensym-cons nil nil)        ; optional test
;; (compare-memory-allocation)  ; see what happens when one cons is loose, something like:
;;   Pool Name                     Type                    Count      Out  D Count    D Out
;;   Gensym-Conses                 Cons                     1595     1395        0        1
;; (reclaim-gensym-tree (create-x11-color-plist-from-color-hierarchy (native-window? system-window) color-hierarchy))  ; run it
;; (compare-memory-allocation)  ; see that delta (D Out) is zero (or that nothing prints out)




;;; `Allocate-x11-colors' returns a plist which maps color name symbols to
;;; X pixel values.  It does this for both color and monochrome systems.

(defun allocate-x11-colors (x11-window)
  (let ((screen-depth
          (c-x11-screen-depth x11-window)))
    (if (>f screen-depth 1)
        (create-x11-color-plist-from-color-hierarchy
          x11-window color-hierarchy 0)
        (make-monochrome-color-description-plist
          (get-pixel-value x11-window "#000000" nil)              ; black
          (get-pixel-value x11-window "#ffffff" nil)))))      ; white

;; The list is a mixture of Gensym and static conses!

;; Would (create-x11-color-plist-from-color-hierarchy
;; x11-window color-hierarchy 0 2) be better?  - mhd





;;; `Make-monochrome-color-description-plist' returns a color description plist
;;; in which every standard Gensym color is given either black-pixel-value, if
;;; the color maps to black, and white-pixel-value, if the color maps to white.

;;; For example,
;;;
;;;    (make-monochrome-color-description-plist 1 0)
;;;
;;; returns a color description plist for typical monochrome monitors, on which 1 is
;;; black and 0 is white.

;;; The result is made up of gensym conses.

(defun make-monochrome-color-description-plist
    (black-pixel-value white-pixel-value)
  (loop for (color) in standard-gensym-color-alist
        collect color using gensym-cons
        collect
        (gensym-list                                                    ; Was just list.
          (if (eq (map-to-black-or-white color) 'white)
              white-pixel-value
              black-pixel-value))
          using gensym-cons))

;; If this was allocating its memory in some reasonable pool, then life would be
;; better.  The window description plist is apparently built out of gensym
;; conses, so maybe that is where these should be taken from.  On the whole it
;; looks like this and the data structures it is incorporated into are all
;; leaking.  This is a problem because this is now called below the print
;; action, which could easily happen hundreds of times during a session of G2.
;; - ben 11/07/91

;; I fixed this to create its result out of gensym conses.  Note that
;; make-color-map creates its "color value plist" out of gensym conses as well.
;; Also, make-or-revise-window was fixed to reclaim an old color map, if any.
;; (MHD 11/14/91)







#+development
(defun ordered-list-of-colors ()
  (let* ((standard-gensym-color-alist-ordered-by-preference
           (nconc                                ; reclaim this list of gensym conses at end
             (loop for entry in standard-gensym-color-alist
                   when (memq (car entry) standard-gensym-color-subset)
                     collect entry using gensym-cons)
             (loop for entry in standard-gensym-color-alist
                   unless (memq (car entry) standard-gensym-color-subset)
                     collect entry using gensym-cons))))
    standard-gensym-color-alist-ordered-by-preference))

;; Old code for the "Then" case of allocate-x11-colors
;        (loop with standard-gensym-color-alist-ordered-by-preference
;                = (nconc                        ; reclaim this list of gensym conses at end
;                    (loop for entry in standard-gensym-color-alist
;                          when (memq (car entry) standard-gensym-color-subset)
;                            collect entry using gensym-cons)
;                    (loop for entry in standard-gensym-color-alist
;                          unless (memq (car entry) standard-gensym-color-subset)
;                            collect entry using gensym-cons))
;              for (color r g b)
;                  in standard-gensym-color-alist-ordered-by-preference
;              as color-name-text-string                ; all lowercase, hyphens => spaces
;                 = (copy-symbol-name color nil t)
;              collect color into result
;              collect
;                (list
;                  (let ((result
;                          (c-x11-get-pixel-value
;                            x11-window
;                            color-name-text-string)))
;                    (cond
;                      ((<f result 0)                ; failed  (use minuspf?)
;                       (reclaim-text-string color-name-text-string)
;                       (setq color-name-text-string
;                             ;; A small leak! -- in practice, usu.
;                             ;;   the two specs for purple & dark-dray
;                             ;;   (MHD 1/8/90)
;                             (with-dynamic-creation
;                               (format
;                                 nil "#~2,'0x~2,'0x~2,'0x"        ; RRGGBB in Hex
;                                 r g b)))
;                       (when (array-has-fill-pointer-p color-name-text-string)
;                         (setq color-name-text-string
;                               (copy-text-string color-name-text-string)))
;                       (setq result
;                             (c-x11-get-pixel-value
;                               x11-window
;                               color-name-text-string))
;                       (cond
;                         ((<f result 0)                ; punt
;                          (setq result
;                                (if (eq (map-to-black-or-white-function color) 'white)
;                                    white-pixel-value
;                                    black-pixel-value))
;                          (cond
;                            ((<f result 0)        ; really punt!
;                             #+development
;                             (cerror
;                               "Continue"
;                               "X11 not allocating colors properly")
;                             (setq result 0)))))))
;                    result))
;                into result
;              do
;          (when (not (array-has-fill-pointer-p
;                       color-name-text-string))
;            (reclaim-text-string color-name-text-string))
;              finally
;                (reclaim-gensym-list
;                  standard-gensym-color-alist-ordered-by-preference)
;                (return result))

(progn) ; ends long comment







;;;; ICP Window Protocol Version



;;; An `ICP window protocol version' is a fixnum used to enumerate various
;;; versions of the ICP window protocol.  This protocol is used for
;;; communication between: G2 and Telewindows; G2 and itself; and G2 and
;;; the print job generator.  Each new version is a superset of the previous
;;; version.

;;; It is a design rule that any G2 can connect to any Telewindows.  When a
;;; connection is first opened the protocol defaults to the lowest level, and
;;; then if both parties can manage it they can negotiate an improved protocol.

;;; Whenever the protocol changes (i.e. a message is: introduced, removed, or
;;; an interface changes) the parameter `latest-icp-window-protocol-version' is
;;; incremented to a new value.  A constant is defined at the new value to
;;; name the protocol version.  That constant is then used to switch between
;;; code that uses the new message and code that works around the missing new
;;; message using older messages.

;;; The indicator `icp-window-protocol-version' in a window parameters plist
;;; gives each window's maximum ICP window protocol version.  This indicator
;;; can be absent indicating version zero.  This value is the window's
;;; opening bid for it's prefered protocol-version.

;;; When a window is first created by make-or-revise-window this bid is ignored,
;;; and the window's protocol-version is set to zero.  For the G2 to self
;;; connection the protocol-version is immediately promoted to the lastest
;;; protocol-version.  The same is done for a printing window.

;;; When Telewindows connects to G2, it sends the window parameters plist in the
;;; initial cluster of messages, i.e., define-telewindows-workstation,
;;; define-gensym-window, and initialize-telewindows-workstation.  If the G2
;;; is capable of noticing the Telewindow's request for a higher
;;; protocol-version it will then notify the Telewindows that it may use the
;;; maximum of the Telewindow's bid, and the G2's latest protocol version.

;;; Don't forget PRINTING when adding new window protocol message types.


#+development
(defvar map-of-icp-protocol-features '())


#+development
(defun output-icp-protocol-features-for-c (&optional filename?)
  (let ((filename (or filename?
                      (format nil "~A/~A" source-directory-name "ext/c/lispicp.h"))))
    (setq map-of-icp-protocol-features (sort map-of-icp-protocol-features #'< :key #'car))
    (with-open-file (stream filename :direction :output)
      (format stream "/* Auto-generated via Lisp function output-icp-protocol-features-for-c */~%")
      (format stream "/* Hand-editing is probably not advised. */~%~%")
      (loop for (icp-number feature-name) in map-of-icp-protocol-features
            do
        (format stream "#define ~30a ~d~%" feature-name icp-number)))))




;;; The macro `def-icp-window-protocol-version' simplifies somewhat the bumping
;;; of the ICP window protocol version. Plan to use it to build up a features
;;; list for a window, some fine day.

(defmacro def-icp-window-protocol-version (feature number &key (printing 'dont-care))
  (let* ((const-name (intern (format nil "ICP-WINDOW-PROTOCOL-SUPPORTS-~a" feature)))
         (macro-name-1 (intern (format nil "WINDOW-SUPPORTS-~a" feature)))
         (macro-name-2 (intern (format nil "CURRENT-WINDOW-SUPPORTS-~a" feature)))
         #+development
         (c-feature-name (substitute #\_ #\- (format nil "ICP-~a" feature)))
         (form ``(current-window-supports-this-icp-window-protocol-p
                   ,',const-name ,gensym-window)))
    (cond ((eq printing nil)
           (setq form ``(and (not (printing-window-p ,gensym-window)) ,,form)))
          ((eq printing t)
           (setq form ``(or (printing-window-p ,gensym-window) ,,form))))
    (setq form `(avoiding-variable-capture (gensym-window) ,form))
    `(progn
       (defconstant ,const-name ,number)
       #+development
       (gensym-push (gensym-list ,number ,c-feature-name) map-of-icp-protocol-features)
       (defmacro ,macro-name-1 (&optional (gensym-window 'current-window)) ,form)
       (defmacro ,macro-name-2 (&optional (gensym-window 'current-window)) ,form)
       ',feature)))



;;; `Current-window-supports-this-icp-window-protocol-p' is a macro usable only
;;; within a basic-on-window dynamic extent.  It takes one of the constants
;;; naming an ICP window protocol version (defined above) and checks that the
;;; window supports that protocol.
;;;
;;; `Window-supports-this-icp-window-protocol-p' is similar but can be used in
;;; any context and checks its argument gensym-window rather than
;;; current-window.

(defmacro window-supports-this-icp-window-protocol-p
    (desired-icp-window-protocol-version gensym-window)
  `(<f ,desired-icp-window-protocol-version
       (icp-window-protocol-version ,gensym-window)))

;; I changed the <= test to <.  Why? Whenever a given desired feature has been
;; added, latest-icp-window-protocol-version has been made one greater than
;; that.  Thus, to see if a peer has that desired feature, your want to know
;; that your peer has at least one greater than that desired feature's version
;; number.  E.g., for some feature at version 6, you have to have at least
;; latest-icp-window-protocol-version = 7.  (MHD 2/3/95)


(defmacro current-window-supports-this-icp-window-protocol-p
    (desired-icp-window-protocol-version
      &optional (gensym-window 'current-window)) ; eliminate arg?!
  `(window-supports-this-icp-window-protocol-p
     ,desired-icp-window-protocol-version
     ,gensym-window))

;; Added new submacro, that could be used in any context, not just a
;; basic-on-window.  Eliminate the optional arg in the old function?  (MHD
;; 2/1/95)








;;; The macro `current-window-supports-image-painting' returns T if we can
;;; paint on the current window.  Ben's scrolling messages were added at the
;;; same time as our image-painting messages, so we use their version number.

(defmacro current-window-supports-image-painting (&optional (gensym-window 'current-window))
  `(or (printing-window-p ,gensym-window)
       (current-window-supports-this-icp-window-protocol-p
         icp-window-protocol-supports-scrolling
         ,gensym-window)))



(defmacro current-window-supports-v4-mouse-messages (gensym-window)
  `(or (printing-window-p ,gensym-window)
       (current-window-supports-this-icp-window-protocol-p
         icp-window-protocol-supports-v4-mouse-messages
         ,gensym-window)))

(defmacro window-supports-paint-icon-onto-graph-raster (gensym-window)
  `(current-window-supports-v4-mouse-messages ,gensym-window))



(defmacro current-window-supports-force-graphics (&optional (gensym-window 'current-window))
  `(and (not (printing-window-p ,gensym-window))
        (current-window-supports-this-icp-window-protocol-p
          icp-window-protocol-supports-force-graphics
          ,gensym-window)))



(defmacro icp-window-protocol-supports-saving-user-settings-p (gensym-window)
  `(window-supports-this-icp-window-protocol-p
     icp-window-protocol-supports-saving-user-settings
     ,gensym-window))





(defmacro window-supports-icon-image-painting (gensym-window)
  `(or (printing-window-p ,gensym-window)
       (current-window-supports-this-icp-window-protocol-p
         icp-window-protocol-supports-polychrome-icon-images
         ,gensym-window)))




(defmacro window-supports-un-decomposed-polygons-in-scratchpad-rasters
    (gensym-window)
    `(or (printing-window-p ,gensym-window)
         (current-window-supports-this-icp-window-protocol-p
           icp-window-protocol-supports-un-decomposed-polygons
           ,gensym-window)))



;;; Telewindow protocol version 16 passes the user's password (taken off
;;; the command line) as a string.  Older versions passed it via a fixnum.

;;; G2's capable of this protocol level demand it.  In other words an old
;;; TW (preversion 15) can not talk to an new G2 (version 15 or greater).

;;; TW's capable of this protocol can talk to old G2.  They will pass the
;;; encrypted password in the older style when the sense that the channel
;;; is running that way.

;;; The macro `window-supports-native-cut-and-paste' returns true if
;;; gensym-window is capable of implementing the native clipboard ("cut and
;;; paste") protocol, and does not have this feature suppressed.  Otherwise, it
;;; returns nil, indicating that G2 should simply use its scrapbook to implement
;;; an internal version of cut and paste, as was done in G2 versions through
;;; 4.0.
;;;
;;; It tests both for this flag, and, in addition, for the existence of
;;; NO-NATIVE-CLIPBOARD = true in gensym-window's parameters plist, which can be
;;; set via the G2/TW command line argument no-native-clipboard, see
;;; UTILITIES3.  Setting this to true is done in order to disable the native
;;; clipboard feature.



(defmacro window-supports-native-cut-and-paste (gensym-window)
  (avoiding-variable-capture (gensym-window)
    `(and (current-window-supports-this-icp-window-protocol-p
            icp-window-protocol-supports-native-cut-and-paste
            ,gensym-window)
          (not (get-gensym-window-parameter
                 ,gensym-window 'no-native-clipboard)))))

;; (MHD 3/28/97)


;;; `window-supports-request-for-paste-availability' needed to make sure G2
;;; does not send older TWs a new ICP message,
;;; request-paste-availability-status.



(defmacro window-supports-request-for-paste-availability (gensym-window)
  (avoiding-variable-capture (gensym-window)
    `(and (current-window-supports-this-icp-window-protocol-p
            icp-window-protocol-supports-request-for-paste-availability
            ,gensym-window)
          (not (get-gensym-window-parameter
                 ,gensym-window 'no-native-clipboard)))))




;;; `Window-supports-unicode-character-events' needed to make sure G2
;;; can understand new Unicode character events.  If not, only
;;; traditional, but limited, mostly ASCII, character events can be
;;; handled, and Telewindows 6.0 endeavors only to send such events to
;;; represent users typing in characters.  If Unicode events are
;;; handled, Telewindows 6.0 supports users switching keyboards to
;;; non-English keyboard layouts in Windows, and use of built-in
;;; Windows IME's (e.g., the built-in Windows Japanese front-end
;;; processor).  The support for Unicode events is limited, and at
;;; this time non-Windows versions of Telewindows continue to send the
;;; "traditional" events and lack support for most non-ASCII character
;;; input, Asian front-end processors, foreign character composition,
;;; and the like.



(defmacro window-supports-unicode-character-events (gensym-window)
  (avoiding-variable-capture (gensym-window)
    `(current-window-supports-this-icp-window-protocol-p
      icp-window-protocol-supports-unicode-character-events
      ,gensym-window)))

;; (MHD 12/3/99)



;;; `Window-supports-raster-stipples' needed to support dithering of graphics in
;;; rasters, in particular the ICP message
;;; initialize-scratchpad-raster-with-stipple.



(defmacro window-supports-raster-stipples (gensym-window)
  (avoiding-variable-capture (gensym-window)
    `(current-window-supports-this-icp-window-protocol-p
      icp-window-protocol-supports-raster-stipples
      ,gensym-window)))

;; (MHD 3/2/01)


;; Renumbered ICP versions to place the ones used in 6.2 first, and removed an
;; already obsolete one.  The result is that now G2/TW 7.0p0's must be a matched
;; pair -- TW 7.0p0's compiled previous to this commit will no longer work with
;; G2 7.0p0's compiled after this commit. The policy now is that a prototype G2
;; must be used with a matching TW ("matching" means compiled from the same
;; sources), or else with a previous *released* TW. It is undefined what happens
;; if you connect with a non-matching prototype TW.  This is so that we can be
;; free to modify or discard ICP versions during prototyping.  -fmw, 6/6/02

;;; `current-window-supports-24bit-image-painting' is true if paint-image-data
;;; supports 24bit images.  This version was previously shared with native widgets.



(defmacro current-window-supports-24bit-image-painting
    (&optional (gensym-window 'current-window))
  (avoiding-variable-capture (gensym-window)
    `(current-window-supports-this-icp-window-protocol-p
       icp-window-protocol-supports-24bit-image-painting
      ,gensym-window)))


;;; `current-window-supports-wide-polyline' is true for printing windows and for
;;; TW's with the new add-wide-polyline-to-current-window message, which
;;; includes a dashes[] argument.



(defmacro current-window-supports-wide-polyline
    (&optional (gensym-window 'current-window))
  (avoiding-variable-capture (gensym-window)
    `(or (printing-window-p ,gensym-window)
         (current-window-supports-this-icp-window-protocol-p
           icp-window-protocol-supports-wide-polyline
           ,gensym-window))))


;;; The macro `window-supports-offscreen-drawing' is true if the window supports
;;; offscreen drawing via the single `draw-offscreen' ICP message.



(defmacro window-supports-offscreen-drawing (gensym-window)
  (avoiding-variable-capture (gensym-window)
    `(current-window-supports-this-icp-window-protocol-p
       icp-window-protocol-supports-offscreen-drawing
      ,gensym-window)))


;;; `Current-window-supports-event-plists' is true if
;;; send-telewindows-workstation-event supports putting the plist that may be
;;; found in a local event (as of G2 7.0, 2/5/02) into the workstation event
;;; being sent over to G2 (where it becomes the workstation event "detail").

;;; We lump this version in with native widgets.  This is first being used as
;;; part of the native simple dialog facility.



(defmacro current-window-supports-event-plists
    (&optional (gensym-window 'current-window))
  `(current-window-supports-this-icp-window-protocol-p
     icp-window-protocol-supports-event-plists
     ,gensym-window))


;;; `window-supports-native-widgets' needed to the posting of native popup
;;; menus, native menu bars, and any other native stuff we may dream up later.
;;; Here "widget" is a generic term for any native control, widget, gadget, or
;;; whatever, and should not be interpreted as a Xt widget.



(defmacro window-supports-native-widgets (gensym-window)
  (avoiding-variable-capture (gensym-window)
    `(current-window-supports-this-icp-window-protocol-p
       icp-window-protocol-supports-native-widgets
      ,gensym-window)))


;;; `current-window-supports-image-tiling' is true for TW's which handle a
;;; quality of TILED in paint-image-in-current-window.



(defmacro current-window-supports-image-tiling
    (&optional (gensym-window 'current-window))
  (avoiding-variable-capture (gensym-window)
    `(and (not (printing-window-p ,gensym-window)) ; Only Postscript Level 2 would work.
          (current-window-supports-this-icp-window-protocol-p
            icp-window-protocol-supports-image-tiling
            ,gensym-window))))


;;; `current-window-supports-nms-menus' is true if given telewindow supports NMS
;;; (Native Menu System) menus



(defmacro current-window-supports-nms-menus (&optional (gensym-window 'current-window))
  (avoiding-variable-capture (gensym-window)
    `(current-window-supports-this-icp-window-protocol-p
       icp-window-protocol-supports-nms-menus
      ,gensym-window)))


;;; `Current-window-icp-window-protocol-70r0-p' is true if Telewindows is at
;;; least from a 7.0r0 release or later.



;;; `Current-window-icp-window-protocol-70-prerelease-p' is true if Telewindows
;;; is a prerelease of 7.0, i.e., 7.0 alpha, beta, or an unofficial (candidate)
;;; prerelease of 7.0r0 prior to the official 7.0r0 release.


(defmacro current-window-icp-window-protocol-70r0-p (&optional (gensym-window 'current-window))
  (avoiding-variable-capture (gensym-window)
    `(current-window-supports-this-icp-window-protocol-p
       icp-window-protocol-70r0
      ,gensym-window)))

(defmacro current-window-icp-window-protocol-70-prerelease-p (&optional (gensym-window 'current-window))
  (avoiding-variable-capture (gensym-window)
    `(and (current-window-supports-this-icp-window-protocol-p
            icp-window-protocol-70-prerelease
            ,gensym-window)
          (not (current-window-supports-this-icp-window-protocol-p
                 icp-window-protocol-70r0
                 ,gensym-window)))))


;;; The macro `window-supports-native-printing' is true if the window supports
;;; the new ICP messages for drawing to a client-side printer.



(defmacro window-supports-native-printing (&optional (gensym-window 'current-window))
  (avoiding-variable-capture (gensym-window)
    `(current-window-supports-this-icp-window-protocol-p
       icp-window-protocol-supports-native-printing
      ,gensym-window)))


;;; `current-window-supports-nms-posting-callbacks' is true if given telewindow
;;; supports NMS posting callbacks, which are used to implement dynamic menus.



(defmacro window-supports-nms-posting-callbacks (&optional (gensym-window 'current-window))
  (avoiding-variable-capture (gensym-window)
    `(current-window-supports-this-icp-window-protocol-p
       icp-window-protocol-supports-nms-posting-callbacks
      ,gensym-window)))


;;; `current-window-supports-native-icons' is true if given telewindow supports
;;; icons in native menus and elsewhere.



(defmacro current-window-supports-native-icons (&optional (gensym-window 'current-window))
  (avoiding-variable-capture (gensym-window)
    `(current-window-supports-this-icp-window-protocol-p
       icp-window-protocol-supports-native-icons
      ,gensym-window)))


;;; `Current-window-supports-move-telewindow' is true if given telewindow
;;; supports sending information about moves, i.e., changes to the (x, y)
;;; position of the windows it's managing.



(defmacro window-supports-move-telewindow (&optional (gensym-window 'current-window))
  (avoiding-variable-capture (gensym-window)
    `(current-window-supports-this-icp-window-protocol-p
       icp-window-protocol-supports-move-telewindow
      ,gensym-window)))


;;; `current-window-supports-native-progress-bar' is true if given telewindow
;;; supports the manage-progress-bar ICP message.



(defmacro current-window-supports-native-progress-bar
    (&optional (gensym-window 'current-window))
  (avoiding-variable-capture (gensym-window)
    `(current-window-supports-this-icp-window-protocol-p
       icp-window-protocol-supports-native-progress-bar
      ,gensym-window)))


;;; `current-window-supports-basic-dialogs' is true if given telewindow supports
;;; the basic dialogs, including the animation control.



(defmacro current-window-supports-basic-dialogs
    (&optional (gensym-window 'current-window))
  (avoiding-variable-capture (gensym-window)
    `(current-window-supports-this-icp-window-protocol-p
       icp-window-protocol-supports-basic-dialogs
      ,gensym-window)))


;;;; 8.0r0

(def-icp-window-protocol-version mdi 37) ; The new MDI for NIP, that is.

(def-icp-window-protocol-version custom-dialogs 38)

(def-icp-window-protocol-version nms-controls 39) ; Just supports the ICP messages.

(def-icp-window-protocol-version list-directory 40) ; 8.0b0


;;;; 8.0r1

;; ICP set-window-title has actually been around since 70r0, but the handler on
;; the TW side was buggy until 80r1. -fmw, 7/20/04

(def-icp-window-protocol-version set-window-title 41)

(def-icp-window-protocol-version nms-modify-control 42)

(def-icp-window-protocol-version manage-status-bar 43)

(def-icp-window-protocol-version nms-selection-callbacks 44)


;;;; 8.1a0

(def-icp-window-protocol-version file-dialog-ex 45)

(def-icp-window-protocol-version tree-views 46)

(def-icp-window-protocol-version html-views 47)

(def-icp-window-protocol-version debugger-dialog 48)

(def-icp-window-protocol-version native-editor 49)


;;;; 8.1b0

(def-icp-window-protocol-version native-printing-ex 50)

(def-icp-window-protocol-version nms-unposting-callbacks 51)

(def-icp-window-protocol-version shortcut-bars 52)

(def-icp-window-protocol-version polyarcs 53 :printing t)

(def-icp-window-protocol-version chart-views 54)

(def-icp-window-protocol-version grid-views 55)


;;;; 8.1r0

(def-icp-window-protocol-version tabular-view-selected-rows 56)

(def-icp-window-protocol-version zorder-native-window 57)

(def-icp-window-protocol-version dialog-panes 58) ; ICP show-custom-dialog-ex

(def-icp-window-protocol-version new-grid-views 59)

(def-icp-window-protocol-version manage-pane 60) ; ICP manage-pane


;;;; 8.1r1

(def-icp-window-protocol-version scroll-while-minimized-fix 61)

(def-icp-window-protocol-version nms-set-theme 62) ; Set UI theme

(def-icp-window-protocol-version toolbar-docking 63)

(def-icp-window-protocol-version simple-dialog-ex 64)


;;;; 8.2a0

(def-icp-window-protocol-version tree-views-ex 65)

(def-icp-window-protocol-version views-api 66) ; Enhanced manage-pane, etc.


;;;; 8.2r0

(def-icp-window-protocol-version html-help-ex 67)

(def-icp-window-protocol-version manage-ui-properties 68)

(def-icp-window-protocol-version manage-logbook 69)

(def-icp-window-protocol-version grid-view-small-chunks 70)

(def-icp-window-protocol-version tabbed-mdi-mode 71)

(def-icp-window-protocol-version manage-dialog 72)


;;;; 8.2r1

(def-icp-window-protocol-version modify-node 73) ; Tree view modify-node

(def-icp-window-protocol-version views-in-dialogs 74)

(def-icp-window-protocol-version hide-toolbar 75) ; Show/hide toolbar

(def-icp-window-protocol-version extended-dialog-text-boxes 76)

(def-icp-window-protocol-version property-grid 77)

(def-icp-window-protocol-version append-control-ex 78)


;;;; 8.3a0

(def-icp-window-protocol-version chart-views-in-panes 79)

(def-icp-window-protocol-version incremental-editor-updates 80)

(def-icp-window-protocol-version native-editor-ex 81)

(def-icp-window-protocol-version nip-rescale-window 82)

(def-icp-window-protocol-version manage-status-bar-ex 83)

(def-icp-window-protocol-version choose-directory 84)

(def-icp-window-protocol-version tabular-views 85) ; The new implementation


;;;; 8.3b0

(def-icp-window-protocol-version views-in-listbars 86)

(def-icp-window-protocol-version choose-directory-on-server 87)


;;;; 8.3b1

(def-icp-window-protocol-version tabular-view-selection-changed-events 88)


;;;; 8.3r0

(def-icp-window-protocol-version grid-view-delimiter-fix 89)


;;;; 8.4r0

(def-icp-window-protocol-version set-background-color 90)

(defparameter latest-icp-window-protocol-version 91)        ; increment when you add
                                        ; keep 1 + highest version constant




;; If you want to get down and dirty, and infer the Telewindows version number
;; from the plist before there was this facility, you can.  (The bad news is, we
;; have to -- it's my fault -- more on that below. -mhd)
;;
;; 1.11B (the earliest stable 1.0 version)  (ref. "MA:>AB-1-11B>PRIMITIVES.LISP")
;; -> 2.0 (ref. "MA:>AB-BETA4>PLATFORMS.LISP")
;;
;; The property
;;
;;      minimum-line-height-of-text-to-draw 6
;;
;; first appears in 2.0
;;
;; This is where BEEP was added as a message (and it was added as a
;; system procedure later, in 3.0).
;;
;; It is therefore a happy outcome that we can discern this from 1.11b.
;; (I.e., we can now fix 3.1 not to send BEEP messages across to 1.11b
;; Telewindows.)
;;
;;
;;
;;
;; 2.0 (ref. "MA:>AB-BETA4>PLATFORMS.LISP")
;; -> 2.1 (ref. "MA:>AB-2-1>PLATFORMS.LISP")
;;
;; No changes are discernable.  No known problems with this are known.
;;
;;
;; 2.1 (ref. "MA:>AB-BETA4>PLATFORMS.LISP")
;; -> 3.0 Rev. 0 (ref. "MA:>AB-7SEP92-OBSOLETE>PLATFORMS.LISP")
;;
;; No changes are discernable.  No known problems with this are known.
;;
;;
;;
;; (MHD 12/29/92)




;;;; System Metrics



;; TODO: Update these on WM_DISPLAYCHANGED.

(defun get-system-metrics-for-local-window ()
  (when (windows-platform-p)                ; Only Win32 has them at the moment.
    (gensym-list 'system-metrics
                 (loop for i below number-of-system-metrics
                       collect (c-get-system-metric i) using gensym-cons))))

(def-gensym-c-function c-get-system-metric
  (:fixnum-int "g2ext_get_system_metric") ;SS_ERROR: was :void
  ((:fixnum-int which-metric)))


;;;; Gensym Window Parameters


#+development
(defun property-list-p (list)
  (and (listp list)
       (or (null list) (null (cdr (last list))))
       (evenp (length list))
       (loop for (indicator value) on list by 'cddr
             always (symbolp indicator))))



(defparameter default-width-of-window-border 6)



;;; The function `make-window-parameters-plist' returns a window parameters
;;; plist as a tree of unshared gensym conses.

;;; Native-window?, if non-nil, is the native window (i.e., for X, a C pointer
;;; to an X window).  This is used at present for deriving the color map.

;;; A gensym window is created in a G2 process to correspond to a gensym window in
;;; a Telewindows process by passing the latter as an icp object argument in an icp
;;; message (sent from the Telewindows to the G2).  This causes a define-gensym-window
;;; message to be sent from the Telewindows process to the G2 process, which includes,
;;; as an argument, an appropriately modified copy of the window parameters plist of
;;; the gensym window in the Telewindows process.

(defun make-window-parameters-plist (native-window?)
  (let* ((constant-plist
           '(pane-layout (detail-pane)                            ; see note 1.
             allow-user-notifications? t                    ; see function notify-all-users
             allow-panic-messages? t                            ; see function panic, a vestigial organ.
             bits-per-pixel 1                                    ; Entirely bogus, a vestigial organ.
             minimum-line-height-of-text-to-draw 6
             width-of-space-between-panes 2 ; 1986 - 1999: was 6! (MHD 10/26/99)
             default-minimum-width-for-pane 10                    ; fix these later!
             default-minimum-height-for-pane 10
             pane-borders-color black
             default-image-border-width 3
             default-image-border-color black
             minimum-scale  #.(round (normalized-scale) 128)
             maximum-scale #.(* (normalized-scale) 4)            ; ok to exceed normalized scale

             use-xor-for-addition? t        ; Passed around, but never used.

             ;; Begin block of obsolete entries.
             ;; These must remain so connecting to G2s works out.
             default-workspace-area-background-color white
             default-workspace-area-foreground-color black
             image-plane-border-outline-width 2
             image-plane-minimum-border-width 3
             image-plane-border-color black
             image-plane-top-bar-width 28
             image-plane-title-color white
             image-plane-title-font-map (hm18)
             image-plane-title-baseline-position 21
             image-plane-hide-button-color white            ; green?
             image-plane-hide-button-width 18
             image-plane-hide-button-height 18
             image-plane-hide-button-position 12
             image-plane-scroll-bar-width 28
             image-plane-scroll-bar-background-color white
             image-plane-scroll-bar-rail-width 8
             image-plane-scroll-bar-rail-color black
             image-plane-scroll-bar-thumb-width 20
             image-plane-scroll-bar-thumb-color black
             ;; End of block of obsolete features.

             type-of-gensym-window x11-window
             scratchpad-raster-type-for-window x11-pixmap
             stored-raster-type-for-window x11-pixmap))

         (varying-plist
           (gensym-list
             'width-of-window-border default-width-of-window-border

             ;; New. Now allow max 4X scaling. (MHD 5/19/93)
             ;; Now based on command line: . (MHD 3/3/94)
             'default-x-scale (or (get-default-x-and-y-scale-from-command-line-if-any)
                                  #.(normalized-scale))
             'default-y-scale (or (nth-value
                                    1 (get-default-x-and-y-scale-from-command-line-if-any t))
                                  #.(normalized-scale))


             ;; Notes on color-description-plist?
             ;;
             ;; Prior to 3.0, it was for this parameter to be nil; thus, for
             ;; compatibility with older Telewindows, it will remain legal
             ;; to transmit nil for this parameter to indicate that only
             ;; two colors (1 - black and 0 - white) are available.
             ;; But that is no longer permitted in 3.0 or later versions
             ;; of the system.
             ;;
             ;; Note that color-description-plist? could be transmitted by old
             ;; (prior to 3.0) Telewindows, so we won't change its name (to
             ;; remove the "?").  Also, make-or-revise-gensym-windowa now uses
             ;;   (make-monochrome-color-description-plist 1 0)
             ;; to create the color map for a gensym window if color-description-
             ;; plist? does come in as nil (from an old Telewindow).
             ;;
             ;; (MHD 11/2/90)

             ;; should NEVER be nil EVEN if B&W
             'color-description-plist? (or (if native-window?
                                               (allocate-x11-colors native-window?))
                                           (make-monochrome-color-description-plist 1 0))

             ;; New for 7.1
             'window-x-in-parent
             (if native-window? (get-x-position-of-native-window native-window?) 0)
             'window-y-in-parent
             (if native-window? (get-y-position-of-native-window native-window?) 0)

             'default-pane-background-color-or-tiling-pattern-rows
             (get-background-color-or-tiling-pattern)

             ;; New in version 3.1, see section "ICP Window Protocol Version"
             'icp-window-protocol-version latest-icp-window-protocol-version))

         (result
           (nconc (copy-tree-using-gensym-conses constant-plist)
                  varying-plist
                  ;; New for 8.1: screen depth, chart info
                  (and native-window?
                       (gensym-list 'window-screen-depth (c-x11-screen-depth native-window?)
                                    'charting-library-version? (charting-library-version?)))
                  ;; New for 8.0: Win32 system metrics
                  (and native-window? (get-system-metrics-for-local-window)))))

    #+development (assert (property-list-p result))

    result))

;; Note 1: Example of a "tiled" pane layout:
;;    '((bottom .35 overview-pane)
;;        (left .35 (top .15 title-pane) menu-pane)
;;        detail-pane).



;;;; UUIDs for G2 and Telewindows

;; Note: this section moved here from TYPES in order to support UUIDs in
;; Telewindows. This is not needed for GSI at present, so this module is a good
;; place due to its load order position and the fact that it's not included in
;; GSI. (MHD 11/5/02)





;;; The function `make-uuid' makes and returns an 8 character long wide string
;;; representing a newly created UUID.  The string becomes a `uuid string', or
;;; `uuid' for short, the value of the uuid slot of blocks.

(def-concept uuid)

;;; The UUIDs created by G2 use the OSF/Open Group DCE UUID format, as documented in
;;; CAE Specification, DCE 1.1: Remote Procedure Call, Universal Unique Identifier
;;; http://www.opengroup.org/onlinepubs/9629399/apdxa.htm#tagcjh_20

;;; UPDATE, 12/24/01: On Win32 Platforms (IntelNT and AlphaNT) we now interface
;;; to the Win32 library function UuidCreate to get the UUID.  Note that on
;;; Windows 2000 and Windows XP, and presumably later versions of Windows, this
;;; UUID does not appear to reveal any identifying information, i.e., the MAC
;;; address, of the computer.  (Possibly this is also true of WinNT 4.0 SP6a,
;;; but we haven't checked.) This was done for privacy/security reasons on
;;; Windows. Earlier versions of Windows show the MAC address of the computer.
;;; G2 should has made no claims either way, so this should not be a problem.
;;; The code that gets the MAC address under Windows is therefore mostly dead:
;;; although there is still an attempt made to get node information for the
;;; machine we're on at startup, it's not used.

;; See ftp://ftp.digital.com/pub/DEC/DCE/PD-DCE-RPC.tar.Z (./src/rpc/runtime/uuid.c).
;; There is a local copy in /home/rh/DCE/src/rpc/runtime/uuid.c
;; An older specification is in http://www.ietf.org/internet-drafts/draft-leach-uuids-guids-01.txt

;; Variant #1: OSF 1.0 DCE RPC

;; The lowest addressed octet contains the global/local bit and the
;; unicast/multicast bit, and is the first octet of the address transmitted
;; on an 802.3 LAN.
;;
;; The adjusted time stamp is split into three fields, and the clockSeq
;; is split into two fields.
;;
;; |<------------------------- 32 bits -------------------------->|
;;
;; +--------------------------------------------------------------+
;; |                     low 32 bits of time                      |  0-3  .time_low
;; +-------------------------------+-------------------------------
;; |     mid 16 bits of time       |  4-5               .time_mid
;; +-------+-----------------------+
;; | vers. |   hi 12 bits of time  |  6-7               .time_hi_and_version
;; +-------+-------+---------------+
;; |Res|  clkSeqHi |  8                                 .clock_seq_hi_and_reserved
;; +---------------+
;; |   clkSeqLow   |  9                                 .clock_seq_low
;; +---------------+----------...-----+
;; |            node ID               |  8-16           .node
;; +--------------------------...-----+
;;
;; --------------------------------------------------------------------------
;;
;; The structure layout of all three UUID variants is fixed for all time.
;; I.e., the layout consists of a 32 bit int, 2 16 bit ints, and 8 8
;; bit ints.  The current form version field does NOT determine/affect
;; the layout.  This enables us to do certain operations safely on the
;; variants of UUIDs without regard to variant; this increases the utility
;; of this code even as the version number changes (i.e., this code does
;; NOT need to check the version field).
;;
;; The "Res" field in the octet #8 is the so-called "reserved" bit-field
;; and determines whether or not the uuid is a old, current or other
;; UUID as follows:
;;
;;      MS-bit  2MS-bit  3MS-bit      Variant
;;      ---------------------------------------------
;;         0       x        x       0 (NCS 1.5)
;;         1       0        x       1 (DCE 1.0 RPC)
;;         1       1        0       2 (Microsoft)
;;         1       1        1       unspecified
;;
;; --------------------------------------------------------------------------

;; The DCE spec says to use the Ethernet card number (IEEE 802), but in some cases,
;; we use something else unique to our licensing.
;; This is potentially a problem in site licensing, but the timestamp will
;; have to pull us through there.

(defvar node-id-for-uuid nil)
(defvar node-id-for-uuid-uses-ethernet-address-p nil)

(def-substitution-macro get-node-id-for-uuid ()
  (or node-id-for-uuid
      (get-node-id-for-uuid-1)))

;VAX uses ethernet address
;note that the ethernet addresses need to be in a "canonical bit ordering"
(defparameter extract-ethernet-script
  "/bin/grep '[0-9a-z][0-9a-z]:..:..:..:..:..' | /bin/sed -e 's/^\\(.*\\)/\\1 /' -e 's/^.*[ \\t]\\([0-9a-z][0-9a-z]:[0-9a-z:]*\\) .*$/\\1/'")

(defun get-ethernet-address-if-possible (uuid-machine-id)
  (case g2-operating-system
    (unix
     (multiple-value-bind (buffer start end)
         (if (memq g2-machine-type '(vax alphavms))
             (let ((string (wide-string-to-gensym-string (get-local-machine-id-function))))
               (values string 0 (length string)))
             (get-ethernet-address-if-possible-for-unix))
       (when buffer
         (prog1 (extract-ethernet-address-from-string buffer start end uuid-machine-id)
           (reclaim-gensym-string buffer)))))
    (t nil)))

(defun get-ethernet-address-if-possible-for-unix ()
  (multiple-value-bind (command type)
      (case g2-machine-type
        (hp9000s700 (values "lanscan -a" 'skip-two-characters)) ; HP-UX B.10.01
        (alphaosf   (values "netstat -i -I ln0 | grep '<Link>'" 'extract-ethernet)) ; OSF1 V3.2
        (sgi        (values "netstat -ia"                       'extract-ethernet)) ; IRIX 5.2
        (sparcsol   (values "ndd /dev/arp arp_cache_report | grep PUBLISH"
                                                                'extract-ethernet)) ; SunOS 5.5-5.11
        (intelsol   (values "ndd /dev/arp arp_cache_report | grep PUBLISH"
                                                                'extract-ethernet)) ; SunOS 5.9-5.11
        ;;(intelnt    (values "net config workstation | grep 'Workstation active'")) ; no 'grep'
        ;;(rs6000 (values "???" nil)) ; AIX 4
        ;;(sun4   (values "???" nil)) ; SunOS 4.1.4
        )
    (unless command (return-from get-ethernet-address-if-possible-for-unix nil))
    (when (eq type 'extract-ethernet)
      (setq command (tformat-gensym-string "~A | ~A" command extract-ethernet-script)))
    (let* ((successful-command-output? (unix-command-output-as-string command)))
      (reclaim-gensym-string command)
      (when successful-command-output?
        (let ((number-of-characters (lengthw successful-command-output?)))
          (if (<=f 12 number-of-characters)
              (values (prog1
                          (wide-string-to-gensym-string successful-command-output?)
                        (reclaim-text-string successful-command-output?))
                      (if (eq type 'skip-two-characters)
                          2
                          0)
                      number-of-characters)
              (progn
                (reclaim-text-string successful-command-output?)
                nil)))))))


(defun extract-ethernet-address-from-string (buffer start end result)
  (loop for result-index from 0 below 3
        do (setf (charw result result-index) (code-wide-character 0)))
  (loop with all-zeros-p = t
        with result-index = 0
        with current-bit-count = 0
        while (<f result-index 3)
        for index from start below end
        for char = (char buffer index)
        for digit = (digit-char-p char 16)
        when digit
          do (incff (charw-bv16 result result-index)
                    (left-shiftf digit current-bit-count))
             (incff current-bit-count 4)
             (when (=f current-bit-count 16)
               (setq current-bit-count 0)
               (incff result-index))
            (unless (=f 0 digit)
              (setq all-zeros-p nil))
        finally (return (if (and (=f 3 result-index)
                                 (not all-zeros-p))
                            result
                            nil))))

(defun get-node-id-for-uuid-1 ()
  (let* ((uuid-machine-id (make-wide-string 3))
         (ethernet-address (get-ethernet-address-if-possible uuid-machine-id))
         (machine-id-string
           (or ethernet-address
               ;;see nsleep() in ext/c/nsleep.c
               ;;sun4: hostid command, gethostid system call (32 bits)
               (get-local-machine-id-function)))
         (machine-id-length (wide-string-length machine-id-string)))
    (declare (type fixnum machine-id-length))
    (if (<=f machine-id-length 3)
        (loop for index from 0 below 3 do
          (setf (charw uuid-machine-id index)
                (if (<f index machine-id-length)
                    (charw machine-id-string index)
                    (code-charw 0))))
        ;; To compute a hash of the host name, we have 6 bytes worth of storage in 3
        ;; wide characters.  Host names are returned as text strings, but we know that
        ;; only the lowest 8 bits of any character in the name can have any significant
        ;; data in it, since the original host name came from an 8-bit character string
        ;; function.  We will compute 3 16-bit hash numbers from the string by treating
        ;; it as three separate hashing operations on successive thirds of the string.
        ;; If the length doesn't divide evenly, we'll put the extra characters into the
        ;; last hash.  If the host name is three characters or shorter, then we will
        ;; just place those into the wide-string locations, filling with null
        ;; characters as needed.
        (loop with clump-size = (floorf-positive machine-id-length 3)
              for index from 0 below 3
              for start-char = (*f index clump-size)
              for limit = (if (=f index 2)
                              machine-id-length
                              (+f start-char clump-size))
              do
          (setf (charw uuid-machine-id index)
                (code-charw (hash-wide-string-portion
                              machine-id-string start-char limit)))))
    (setq node-id-for-uuid-uses-ethernet-address-p (not (null ethernet-address)))
    (setq node-id-for-uuid uuid-machine-id)))

(def-system-variable time-of-last-uuid platforms nil)

(defvar always-use-current-time-for-uuid nil) ; when NIL, allows for better compaction
(def-system-variable use-current-time-for-next-uuid platforms t)

(def-system-variable clock-sequence-for-uuid platforms nil)
(def-substitution-macro get-clock-sequence-for-uuid ()
  (or clock-sequence-for-uuid
      (setq clock-sequence-for-uuid (get-clock-sequence-for-uuid-1))))



(defun-simple get-clock-sequence-for-uuid-1 ()
  (let* ((pid-low-bits
           (floor (mod (c-get-process-identifier) #.(- (expt 2 18) 1d0))))
         (unique-bits-for-uuid-clock-sequence
           (logandf 8191 pid-low-bits)))
    (loop for i from 0 below (right-shiftf pid-low-bits 13)
          do (random 8192))
    (+f (if node-id-for-uuid-uses-ethernet-address-p
            #x8000  ;; Add the marker for "DCE" UUID variant.
            #xE000) ;; Add the marker for "other" UUID variant.
        (logxorf (random 8192) unique-bits-for-uuid-clock-sequence))))

(defun-simple reset-clock-sequence-for-uuid ()
  (setq clock-sequence-for-uuid
        (+f (if node-id-for-uuid-uses-ethernet-address-p
                #x8000  ;; Add the marker for "DCE" UUID variant.
                #xE000) ;; Add the marker for "other" UUID variant.
            (logandf 8191 (1+ clock-sequence-for-uuid)))))

(def-system-variable uuid-time-b0 platforms 0)
(def-system-variable uuid-time-b1 platforms 0)
(def-system-variable uuid-time-b2 platforms 0)
(def-system-variable uuid-time-b3 platforms 0)

;; The above seven (7) def-system-variable forms had been originally coded (for
;; G2 6.0) as DEFVAR's. A cursory glance at the uses of these variables,
;; however, showed that they were (a) subject to mutation, (b) had their global,
;; as opposed to their let-bound, bindings changed, and (c) could not be
;; reasonably shared between processes, concurrent or sequential. Thus, they
;; obviously should have been system variables. The programmer (Richard Harris)
;; was either given the questionable advice not to use def-system-variable for
;; situations in which it was called for, or decided that upon his own
;; initiative. Changing now to be def-system-variable forms. A more
;; comprehensive review of DEFVAR, both in this module and elsewhere throughout
;; the sources, is probably in order at a later time! Note that we currently
;; utilize multiple sequential G2 processes (e.g., run G2, then abort Lisp to
;; top level, then run G2 again). Note that we do not currently utilize multiple
;; concurrent processes, since we got off Lisp machines, but we may choose to do
;; so at some point, as it is supported by all of our current development Lisp
;; implementations (Lucid, Harlequin, Franz). (MHD 1/2/01)


(defmacro increment-unsigned-byte-16-variables (b0 b1 b2 b3) ; b0 is lsb
  `(progn
     (incff ,b0)
     (when (=f ,b0 65536)
       (setq ,b0 0)
       (incff ,b1)
       (when (=f ,b1 65536)
         (setq ,b1 0)
         (incff ,b2)
         (when (=f ,b2 65536)
           (setq ,b2 0)
           (incff ,b3)
           (when (=f ,b3 65536)
             (setq ,b3 0)))))
     (values ,b3 ,b2 ,b1 ,b0)))

(defun get-time-for-uuid-internal (time-managed-float)
  ;; This timestamp is a 60 bit value, represented in UTC in 100 nanosecond intervals
  ;; since 1582-10-15 00:00:00.00 (The date of Gregorian reform to the Christian calendar).
  ;; At the Unix base time (January 1, 1970), the timestamp was 01B21DD213814000.
  (let ((current-unix-time (managed-float-value time-managed-float)))
    (multiple-value-bind (time-b3 remainder-b3)
        (floor (+e (*e current-unix-time #.(* 1d7 (expt 2 -48)))
                   #.(* 1d0 (* #x1DD213814000 (expt 2 -48)))))
      (incff time-b3 #.(+ #x01B2 #x1000)) ; #x1000 is DCE version 1.
      (multiple-value-bind (time-b2 remainder-b2)
          (floor (*e remainder-b3 #.(* 1d0 (expt 2 16))))
        (multiple-value-bind (time-b1 remainder-b1)
            (floor (*e remainder-b2 #.(* 1d0 (expt 2 16))))
          (multiple-value-bind (time-b0)
              (floor (*e remainder-b1 #.(* 1d0 (expt 2 16))))
            ;; This next line improves repeatability of consing traces
            (setq time-b0 (logandf time-b0 #xff00)) ; This line is the reason for the following test.
            (if (and (=f uuid-time-b3 time-b3)  ; This test is only really necessary on
                     (=f uuid-time-b2 time-b2)  ; machines that have high resolution clocks,
                     (=f uuid-time-b1 time-b1)  ; and even then only when items are being
                     (=f uuid-time-b0 time-b0)) ; created very frequently.
                (increment-unsigned-byte-16-variables
                  uuid-time-b0 uuid-time-b1 uuid-time-b2 uuid-time-b3)
                (values
                  (setq uuid-time-b3 time-b3)
                  (setq uuid-time-b2 time-b2)
                  (setq uuid-time-b1 time-b1)
                  (setq uuid-time-b0 time-b0)))))))))



(defun get-time-for-uuid ()
  (unless time-of-last-uuid
    (setq time-of-last-uuid (allocate-managed-float 0.0)))
  (let* ((last-unix-time (managed-float-value time-of-last-uuid))
         (current-unix-time 0.0)
         (uuid-unix-time
           (if (or (=e 0.0 last-unix-time)
                   always-use-current-time-for-uuid
                   use-current-time-for-next-uuid
                   (and check-time-on-next-uuid
                        (>e (-e (progn
                                  #-development
                                  (progn
                                    (setq check-time-on-next-uuid nil)
                                    (get-fixnum-time))
                                  (setq current-unix-time (gensym-get-unix-time)))
                                last-unix-time)
                            maximum-interval-between-new-time-for-uuid))
                   (=f (logandf uuid-offset-mask uuid-time-b0) uuid-offset-mask))
               (if (=e 0.0 current-unix-time)
                   (gensym-get-unix-time)
                   current-unix-time)
               last-unix-time)))
    (declare (type double-float last-unix-time current-unix-time uuid-unix-time))
    (setq use-current-time-for-next-uuid nil)
    (cond ((=e uuid-unix-time last-unix-time)
           ;; add "1" to the time.  This allows for 100000 UUIDs per 10 msec clock tick.
           (increment-unsigned-byte-16-variables
             uuid-time-b0 uuid-time-b1 uuid-time-b2 uuid-time-b3)) ; lsb ... msb
          (t
           (when (<e uuid-unix-time last-unix-time)
             (reset-clock-sequence-for-uuid))
           (setf (managed-float-value time-of-last-uuid) uuid-unix-time)
           (get-time-for-uuid-internal time-of-last-uuid)))))



;;; The function `get-win32-uuid' fills uuid-string via a call to win32 function
;;; c-uuid-create.  The only types of problems this expects to encounter are
;;; those that concern uniqueness, or lack thereof. In such cases, this will
;;; still generate an ID, that is in all probability unique, though it may have
;;; a small chance of not being universally unique. In the case of G2 objects,
;;; this is a relatively minor concern for most applications. If there is a
;;; problem, we put out a message the first time it occurs giving a general
;;; statement of the problem, and also a specific message that is one of those
;;; suggested by the Win32 Header file.

(def-system-variable user-notified-of-uuid-uniqueness-problem-p platforms nil)

(defun get-win32-uuid (uuid-string)
  (let ((code (c-uuid-create uuid-string)))
    (cond
      ((=f code 0)
       t)
      (t
       (unless user-notified-of-uuid-uniqueness-problem-p
         (let* ((message-string?
                 (cond
                   ((=f code rpc_s_uuid_local_only)
                    rpc_s_uuid_local_only-message)
                   ((=f code rpc_s_uuid_no_address)
                    rpc_s_uuid_no_address-message)))
                (message-string
                  (tformat-text-string
                    "~a~a"
                    (or message-string? "Unrecognized error code: ")
                    (if message-string? "" code))))
           (notify-user-at-console-and-on-logbook
             "This computer's operating system cannot generate a universal unique ID (UUID).~
              ~%~a" message-string)
           (setq user-notified-of-uuid-uniqueness-problem-p t)
           (reclaim-text-string message-string)))
       nil))))



(defun-simple make-uuid ()
  (let ((uuid-string (make-wide-string 8)))
    (case g2-machine-type
      ((intelnt alphant)
       (get-win32-uuid uuid-string))
      (t
       (multiple-value-bind (b3 b2 b1 b0)
           (get-time-for-uuid)
         (let ((machine-id-string (get-node-id-for-uuid)))
           ;; Note that the call to get-node-id-for-uuid must precede
           ;; the call to get-clock-sequence-for-uuid.
           (setf (charw uuid-string 0) (code-wide-character b0))
           (setf (charw uuid-string 1) (code-wide-character b1))
           (setf (charw uuid-string 2) (code-wide-character b2))
           (setf (charw uuid-string 3) (code-wide-character b3))
           (setf (charw uuid-string 4) (code-wide-character (get-clock-sequence-for-uuid)))
           (loop for index from 0 below 3
                 do (setf (charw uuid-string (+f index 5))
                          (charw machine-id-string index)))))))
    (mark-wide-string-as-binary uuid-string)
    uuid-string))





;;; The function `twrite-uuid-printed-representation' writes uuid's printed
;;; representation to the current output string as a string of hex digits.
;;; There should be 8 wide (16-bit) characters in UUID, and so, with 4 digits
;;; per UUID character, the resulting hex string will be exactly 32 in length.

(defun-simple twrite-uuid-printed-representation (uuid)
  (twrite-binary-string-printed-representation uuid))

(defun-simple twrite-binary-string-printed-representation (binary-string)
  (let* ((write-strings-parsably? nil)
         (string
          (twith-output-to-text-string
            (loop for i from 0 below (lengthw binary-string)
                  as character-code = (wide-character-code (charw binary-string i))
                  do (twrite-string
                      (if (<=f character-code #xf)
                          "000"
                          (if (<=f character-code #xff)
                              "00"
                              (if (<=f character-code #xfff)
                                  "0"
                                  ""))))
                     (twrite-positive-fixnum-in-radix character-code 16)))))
    (downcase-text-string-in-place string)
    (twrite-string string)
    (reclaim-text-string string)))





;;; The function `hash-wide-string-portion' takes a text-string, a start index,
;;; and an end index (which is the last char to be hashed plus one).  This
;;; function computes and returns a 16-bit unsigned hash of that portion of the
;;; string.  The hash is incrementally computed by rotating the 16-bit left by
;;; one (wrapping the topmost bit back to the bottom) and then XORing the next
;;; character into the hash.

(defun-simple hash-wide-string-portion (wide-string start end)
  (declare (type fixnum start end))
  (cond
    ((=f start end)
     0)
    ((=f start (-f end 1))
     (char-codew (charw wide-string start)))
    (t
     (loop with hash fixnum = (char-codew (charw wide-string start))
           for index from (+f start 1) below end
           for char-code fixnum = (char-codew (charw wide-string index))
           do
       (setq hash
             (logxorf (+f (logandf (ashf hash 1) #xffff)
                          (ashf hash -15))
                      char-code))
           finally (return hash)))))
