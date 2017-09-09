/* -*- c-file-style:"stroustrup"; indent-tabs-mode: nil -*- */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "GoogleStyleTest.h"
#include "cppunit_assertion_trait_charp.hpp"


extern "C" {
#include "cprim.h"
}

/** Returns a mallocated G2 string copy of a given wide string @p src.
    G2 characters are a subset of UCS-2, but that subset is defined in
    Lisp. Keeping that in-sync here would be hard. So, we just do a
    simple "narrowing" here, and G2 Lisp code will figure out if the
    UCS-2 character it got is a valid G2 character. This implies that
    characters out of UCS-2 range (code point > 0xFFFF) will just have
    their "high-bits" removed.

    This is used when we want to "construct" a G2 string from a wide
    string. When C11 support matures, we will avoid use of wide
    characters/strings, and hopefully not need this function. 

    On platforms (i.e. Windows) where wide characters are 16-bits,
    this is a simple copy (like wcsdup()).
  */
g2chr16_t *g2pvt_wdups16(wchar_t const*src);

/** Returns a mallocated wide string copy of a given G2 string @p src.
    An inverse of g2pvt_wdups16();
*/
wchar_t *g2pvt_s16dupw(g2chr16_t const* src);

/// Unicode line separator
#define LS L"\u2028"

/// Unicode paragraph separator
#define PS L"\u2029"


#define EXPECT_chomp(input, chomped) {                             \
        char s_[] = input;                                         \
        CPPUNIT_ASSERT_EQUAL((char*)chomped, g2pvt_chomp(s_));     \
    }

#define EXPECT_dup_chomp_ex(input, to_chomp, chomped) {                 \
        char *s_ = g2pvt_dup_chomp_ex(input, sizeof input - 1, to_chomp); \
        CPPUNIT_ASSERT(s_ != NULL);                                     \
        CPPUNIT_ASSERT_EQUAL((char*)chomped, s_);                       \
        free(s_);                                                       \
    }

#define EXPECT_chomp_ex(input, to_chomp, chomped) {                     \
        char s_[] = input;                                              \
        CPPUNIT_ASSERT_EQUAL((char*)chomped, g2pvt_chomp_ex(s_, sizeof s_-1, to_chomp)); \
    }

#define EXPECT_chomps16(input, chomped) {                              \
        g2chr16_t *s_ = g2pvt_wdups16(input);                          \
        CPPUNIT_ASSERT(s_ != NULL);                                    \
        CPPUNIT_ASSERT(g2pvt_chomps16(s_) != NULL);                    \
        wchar_t *wcs_ = g2pvt_s16dupw(s_);                             \
        CPPUNIT_ASSERT_EQUAL((wchar_t*)chomped, wcs_);                 \
        free(wcs_);                                                    \
        free(s_);                                                      \
    }

#define EXPECT_chomps16_ex(input, to_chomp, chomped) {                  \
        g2chr16_t *s_ = g2pvt_wdups16(input);                           \
        CPPUNIT_ASSERT(s_ != NULL);                                     \
        g2chr16_t *g2_to_chomp_ = g2pvt_wdups16(to_chomp);              \
        CPPUNIT_ASSERT(g2_to_chomp_ != NULL);                           \
        CPPUNIT_ASSERT(g2pvt_chomps16_ex(s_, g2pvt_s16len(s_), g2_to_chomp_) != NULL); \
        wchar_t *wcs_ = g2pvt_s16dupw(s_);                             \
        CPPUNIT_ASSERT_EQUAL((wchar_t*)chomped, wcs_);                 \
        free(wcs_);                                                    \
        free(g2_to_chomp_);                                            \
        free(s_);                                                      \
    }

#define EXPECT_dup_chomps16_ex(input, to_chomp, chomped) {              \
        g2chr16_t *s_ = g2pvt_wdups16(input);                           \
        CPPUNIT_ASSERT(s_ != NULL);                                     \
        g2chr16_t *g2_to_chomp_ = g2pvt_wdups16(to_chomp);              \
        CPPUNIT_ASSERT(g2_to_chomp_ != NULL);                           \
        g2chr16_t *got_ = g2pvt_dup_chomps16_ex(s_, g2pvt_s16len(s_), g2_to_chomp_); \
        CPPUNIT_ASSERT(got_ != NULL);                                   \
        wchar_t *wcs_ = g2pvt_s16dupw(got_);                            \
        CPPUNIT_ASSERT_EQUAL((wchar_t*)chomped, wcs_);                  \
        free(wcs_);                                                     \
        free(got_);                                                     \
        free(g2_to_chomp_);                                             \
        free(s_);                                                       \
    }


TEST(chomp_regular)
{
    EXPECT_chomp("chomp me\n", "chomp me");
    EXPECT_chomp("chomp me\r", "chomp me");
    EXPECT_chomp("chomp me\r\n", "chomp me");
    EXPECT_chomp("chomp me\n\r", "chomp me");
    EXPECT_chomp("chomp me", "chomp me");
}


TEST(chomp_corner_cases)
{
    EXPECT_chomp("\n", "");
    EXPECT_chomp("\r", "");
    EXPECT_chomp("\r\n", "");
    EXPECT_chomp("", "");
}


TEST(chomp_cyrillic)
{
    // Using UTF-8 encoding here
    EXPECT_chomp("Миле воли диско\n", "Миле воли диско");
    EXPECT_chomp("Миле воли диско\r", "Миле воли диско");
    EXPECT_chomp("Миле воли диско\r\n", "Миле воли диско");
    EXPECT_chomp("Миле воли диско", "Миле воли диско");
}


TEST(chomps16_regular)
{
    EXPECT_chomps16(L"chomp this\n", L"chomp this");
    EXPECT_chomps16(L"chomp this\n"PS, L"chomp this");
    EXPECT_chomps16(L"chomp this\n"PS LS, L"chomp this");
    EXPECT_chomps16(L"chomp this\r"LS, L"chomp this");
    EXPECT_chomps16(L"chomp this\r\n"LS PS, L"chomp this");
    EXPECT_chomps16(L"chomp this\n\r", L"chomp this");
    EXPECT_chomps16(L"chomp this", L"chomp this");
}


TEST(chompw_corner_cases)
{
    EXPECT_chomps16(L"\n", L"");
    EXPECT_chomps16(L"\r", L"");
    EXPECT_chomps16(L"\r\n", L"");
    EXPECT_chomps16(L"", L"");
}


TEST(chompw_cyrillic)
{
    // Using UTF-8 encoding here
    EXPECT_chomps16(L"Миле воли диско\n", L"Миле воли диско");
    EXPECT_chomps16(L"Миле воли диско\r", L"Миле воли диско");
    EXPECT_chomps16(L"Миле воли диско\r\n", L"Миле воли диско");
    EXPECT_chomps16(L"Миле воли диско", L"Миле воли диско");
}

TEST(chomp_ex_regular)
{
    EXPECT_chomp_ex("chomp me\n", "\n", "chomp me");
    EXPECT_chomp_ex("chomp me\n", "\r\n", "chomp me");
    EXPECT_chomp_ex("chomp me\n", "\n\r", "chomp me");
    EXPECT_chomp_ex("chomp me\n", "\r", "chomp me\n");
    EXPECT_chomp_ex("chomp me\r", "\r", "chomp me");
    EXPECT_chomp_ex("chomp me\r\n", "\r\n", "chomp me");
    EXPECT_chomp_ex("chomp me\r\n", "\n", "chomp me\r");
    EXPECT_chomp_ex("chomp me\n\r", "\r\n", "chomp me");
    EXPECT_chomp_ex("chomp me", "\r\n", "chomp me");
    EXPECT_chomp_ex("chomp me", "m", "chomp me");
    EXPECT_chomp_ex("chomp me", "", "chomp me");
    EXPECT_chomp_ex("chomp me", "e", "chomp m");
    EXPECT_chomp_ex("chomp me", "me", "chomp ");
    EXPECT_chomp_ex("chomp me", "m e", "chomp");
}


TEST(chomp_ex_corner_cases)
{
    EXPECT_chomp_ex("\n", "\n", "");
    EXPECT_chomp_ex("\n", "\r\n", "");
    EXPECT_chomp_ex("\n", "\n\r", "");
    EXPECT_chomp_ex("\n", "\r", "\n");
    EXPECT_chomp_ex("\r", "\r", "");
    EXPECT_chomp_ex("\r\n", "\r\n", "");
    EXPECT_chomp_ex("\r\n", "\n\r", "");
    EXPECT_chomp_ex("", "\r", "");
    EXPECT_chomp_ex("", "\r\n", "");
    EXPECT_chomp_ex("", "", "");
}


TEST(chomp_ex_cyrillic)
{
    // Using UTF-8 encoding here
    EXPECT_chomp_ex("А ја коло Шумадијско\n", "\n\r", "А ја коло Шумадијско");
    EXPECT_chomp_ex("А ја коло Шумадијско\r", "\r\n", "А ја коло Шумадијско");
    EXPECT_chomp_ex("А ја коло Шумадијско\r\n", "\r\n", "А ја коло Шумадијско");
    EXPECT_chomp_ex("А ја коло Шумадијско", "\r\n", "А ја коло Шумадијско");
    EXPECT_chomp_ex("А ја коло Шумадијско", "о", "А ја коло Шумадијск");
    EXPECT_chomp_ex("А ја коло Шумадијско", "ја", "А ја коло Шумадијско");
    EXPECT_chomp_ex("А ја коло Шумадијско", "ок", "А ја коло Шумадијс");
}


TEST(chompw_ex_regular)
{
    EXPECT_chomps16_ex(L"chomp me\n", L"\n", L"chomp me");
    EXPECT_chomps16_ex(L"chomp me\n", L"\r\n", L"chomp me");
    EXPECT_chomps16_ex(L"chomp me\n", L"\n\r", L"chomp me");
    EXPECT_chomps16_ex(L"chomp me\n", L"\r", L"chomp me\n");
    EXPECT_chomps16_ex(L"chomp me\r", L"\r", L"chomp me");
    EXPECT_chomps16_ex(L"chomp me\r"PS, L"\r"PS, L"chomp me");
    EXPECT_chomps16_ex(L"chomp me\r"LS, L"\r"PS, L"chomp me\r"LS);
    EXPECT_chomps16_ex(L"chomp me\r\n", L"\r\n", L"chomp me");
    EXPECT_chomps16_ex(L"chomp me\r\n", L"\n", L"chomp me\r");
    EXPECT_chomps16_ex(L"chomp me\n\r", L"\r\n", L"chomp me");
    EXPECT_chomps16_ex(L"chomp me", L"\r\n", L"chomp me");
    EXPECT_chomps16_ex(L"chomp me", L"m", L"chomp me");
    EXPECT_chomps16_ex(L"chomp me", L"", L"chomp me");
    EXPECT_chomps16_ex(L"chomp me", L"e", L"chomp m");
    EXPECT_chomps16_ex(L"chomp me", L"me", L"chomp ");
    EXPECT_chomps16_ex(L"chomp me", L"m e", L"chomp");
}


TEST(chompw_ex_corner_cases)
{
    EXPECT_chomps16_ex(L"\n", L"\n", L"");
    EXPECT_chomps16_ex(L"\n", L"\r\n", L"");
    EXPECT_chomps16_ex(L"\n", L"\n\r", L"");
    EXPECT_chomps16_ex(L"\n", L"\r", L"\n");
    EXPECT_chomps16_ex(L"\r", L"\r", L"");
    EXPECT_chomps16_ex(L"\r\n", L"\r\n", L"");
    EXPECT_chomps16_ex(L"\r\n", L"\n\r", L"");
    EXPECT_chomps16_ex(L"", L"\r", L"");
    EXPECT_chomps16_ex(L"", L"\r\n", L"");
    EXPECT_chomps16_ex(L"", L"", L"");
}


TEST(chompw_ex_cyrillic)
{
    // Using UTF-8 encoding here
    EXPECT_chomps16_ex(L"А ја коло Шумадијско\n", L"\n\r", L"А ја коло Шумадијско");
    EXPECT_chomps16_ex(L"А ја коло Шумадијско\r", L"\r\n", L"А ја коло Шумадијско");
    EXPECT_chomps16_ex(L"А ја коло Шумадијско\r\n", L"\r\n", L"А ја коло Шумадијско");
    EXPECT_chomps16_ex(L"А ја коло Шумадијско", L"\r\n", L"А ја коло Шумадијско");
    EXPECT_chomps16_ex(L"А ја коло Шумадијско", L"о", L"А ја коло Шумадијск");
    EXPECT_chomps16_ex(L"А ја коло Шумадијско", L"ја", L"А ја коло Шумадијско");
    EXPECT_chomps16_ex(L"А ја коло Шумадијско", L"ок", L"А ја коло Шумадијс");
}


TEST(dup_chomp_ex_regular)
{
    EXPECT_dup_chomp_ex("chomp me\n", "\n", "chomp me");
    EXPECT_dup_chomp_ex("chomp me\n", "\r\n", "chomp me");
    EXPECT_dup_chomp_ex("chomp me\n", "\n\r", "chomp me");
    EXPECT_dup_chomp_ex("chomp me\n", "\r", "chomp me\n");
    EXPECT_dup_chomp_ex("chomp me\r", "\r", "chomp me");
    EXPECT_dup_chomp_ex("chomp me\r\n", "\r\n", "chomp me");
    EXPECT_dup_chomp_ex("chomp me\r\n", "\n", "chomp me\r");
    EXPECT_dup_chomp_ex("chomp me\n\r", "\r\n", "chomp me");
    EXPECT_dup_chomp_ex("chomp me", "\r\n", "chomp me");
    EXPECT_dup_chomp_ex("chomp me", "m", "chomp me");
    EXPECT_dup_chomp_ex("chomp me", "", "chomp me");
    EXPECT_dup_chomp_ex("chomp me", "e", "chomp m");
    EXPECT_dup_chomp_ex("chomp me", "me", "chomp ");
    EXPECT_dup_chomp_ex("chomp me", "m e", "chomp");
}


TEST(dup_chomp_ex_corner_cases)
{
    EXPECT_dup_chomp_ex("\n", "\n", "");
    EXPECT_dup_chomp_ex("\n", "\r\n", "");
    EXPECT_dup_chomp_ex("\n", "\n\r", "");
    EXPECT_dup_chomp_ex("\n", "\r", "\n");
    EXPECT_dup_chomp_ex("\r", "\r", "");
    EXPECT_dup_chomp_ex("\r\n", "\r\n", "");
    EXPECT_dup_chomp_ex("\r\n", "\n\r", "");
    EXPECT_dup_chomp_ex("", "\r", "");
    EXPECT_dup_chomp_ex("", "\r\n", "");
    EXPECT_dup_chomp_ex("", "", "");
}


TEST(dup_chomp_ex_cyrillic)
{
    // Using UTF-8 encoding here
    EXPECT_dup_chomp_ex("А ја коло Шумадијско\n", "\n\r", "А ја коло Шумадијско");
    EXPECT_dup_chomp_ex("А ја коло Шумадијско\r", "\r\n", "А ја коло Шумадијско");
    EXPECT_dup_chomp_ex("А ја коло Шумадијско\r\n", "\r\n", "А ја коло Шумадијско");
    EXPECT_dup_chomp_ex("А ја коло Шумадијско", "\r\n", "А ја коло Шумадијско");
    EXPECT_dup_chomp_ex("А ја коло Шумадијско", "о", "А ја коло Шумадијск");
    EXPECT_dup_chomp_ex("А ја коло Шумадијско", "ја", "А ја коло Шумадијско");
    EXPECT_dup_chomp_ex("А ја коло Шумадијско", "ок", "А ја коло Шумадијс");
}


TEST(dup_chompw_ex_regular)
{
    EXPECT_dup_chomps16_ex(L"chomp me\n", L"\n", L"chomp me");
    EXPECT_dup_chomps16_ex(L"chomp me\n", L"\r\n", L"chomp me");
    EXPECT_dup_chomps16_ex(L"chomp me\n", L"\n\r", L"chomp me");
    EXPECT_dup_chomps16_ex(L"chomp me\n", L"\r", L"chomp me\n");
    EXPECT_dup_chomps16_ex(L"chomp me\r", L"\r", L"chomp me");
    EXPECT_dup_chomps16_ex(L"chomp me\r"PS, L"\r"PS, L"chomp me");
    EXPECT_dup_chomps16_ex(L"chomp me\r"LS, L"\r"PS, L"chomp me\r"LS);
    EXPECT_dup_chomps16_ex(L"chomp me\r\n", L"\r\n", L"chomp me");
    EXPECT_dup_chomps16_ex(L"chomp me\r\n", L"\n", L"chomp me\r");
    EXPECT_dup_chomps16_ex(L"chomp me\n\r", L"\r\n", L"chomp me");
    EXPECT_dup_chomps16_ex(L"chomp me", L"\r\n", L"chomp me");
    EXPECT_dup_chomps16_ex(L"chomp me", L"m", L"chomp me");
    EXPECT_dup_chomps16_ex(L"chomp me", L"", L"chomp me");
    EXPECT_dup_chomps16_ex(L"chomp me", L"e", L"chomp m");
    EXPECT_dup_chomps16_ex(L"chomp me", L"me", L"chomp ");
    EXPECT_dup_chomps16_ex(L"chomp me", L"m e", L"chomp");
}


TEST(dup_chompw_ex_corner_cases)
{
    EXPECT_dup_chomps16_ex(L"\n", L"\n", L"");
    EXPECT_dup_chomps16_ex(L"\n", L"\r\n", L"");
    EXPECT_dup_chomps16_ex(L"\n", L"\n\r", L"");
    EXPECT_dup_chomps16_ex(L"\n", L"\r", L"\n");
    EXPECT_dup_chomps16_ex(L"\r", L"\r", L"");
    EXPECT_dup_chomps16_ex(L"\r\n", L"\r\n", L"");
    EXPECT_dup_chomps16_ex(L"\r\n", L"\n\r", L"");
    EXPECT_dup_chomps16_ex(L"", L"\r", L"");
    EXPECT_dup_chomps16_ex(L"", L"\r\n", L"");
    EXPECT_dup_chomps16_ex(L"", L"", L"");
}


TEST(dup_chompw_ex_cyrillic)
{
    // Using UTF-8 encoding here
    EXPECT_dup_chomps16_ex(L"да будемо блиско\n", L"\n\r", L"да будемо блиско");
    EXPECT_dup_chomps16_ex(L"блиско\r", L"\r\n", L"блиско");
    EXPECT_dup_chomps16_ex(L"хармоника\r\n", L"\r\n", L"хармоника");
    EXPECT_dup_chomps16_ex(L"свира", L"\r\n", L"свира");
    EXPECT_dup_chomps16_ex(L"диско", L"о", L"диск");
    EXPECT_dup_chomps16_ex(L"ајде Миле", L"је", L"ајде Мил");
    EXPECT_dup_chomps16_ex(L"буди друг", L"гду", L"буди др");
}


TEST(chomp_ex_not_complete_string)
{
    char s[] = "chomp";
    CPPUNIT_ASSERT_EQUAL((char*)"cho", g2pvt_chomp_ex(s, strlen(s)-1, "m"));
    CPPUNIT_ASSERT_EQUAL((char*)"cho", g2pvt_chomp_ex(s, 1, "mo"));
    CPPUNIT_ASSERT_EQUAL((char*)"", g2pvt_chomp_ex(s, 1, "mco"));
}


TEST(chompw_ex_not_complete_string)
{
    g2chr16_t s[] = { 'c', 'h', 'o', 'm', 'p', 0 };
    g2chr16_t m[] = { 'm', 0 };
    g2chr16_t mo[] = { 'm', 'o', 0 };
    g2chr16_t mco[] = { 'm', 'c', 'o', 0 };
    g2chr16_t cho[] = { 'c', 'h', 'o', 0 };
    g2chr16_t empty[] = {  0 };
    CPPUNIT_ASSERT_EQUAL(0, g2pvt_s16cmp(cho, g2pvt_chomps16_ex(s, g2pvt_s16len(s)-1, m)));
    CPPUNIT_ASSERT_EQUAL(0, g2pvt_s16cmp(cho, g2pvt_chomps16_ex(s, 1, mo)));
    CPPUNIT_ASSERT_EQUAL(0, g2pvt_s16cmp(empty, g2pvt_chomps16_ex(s, 1, mco)));
}
