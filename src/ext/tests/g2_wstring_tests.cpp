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

#pragma execution_character_set("utf-8")

/* Since most compilers still don't support the C11 `char16_t` type
   and <uchar.t> header and `u""` and `U""` string literals, we'll
   use wide strings (literals) here (and convert to `g2chr16_t`
   "along the way").
*/
#include <wchar.h>
#include <assert.h>

g2chr16_t *g2pvt_wdups16(wchar_t const*src)
{
    size_t n;
    size_t i;
    g2chr16_t *rslt;

    assert(src != NULL);

    n = wcslen(src);
    rslt = (g2chr16_t*)malloc((n+1) * sizeof *rslt);
    if (NULL == rslt) {
        return NULL;
    }
    for (i = 0 ; i < n; ++i) {
        rslt[i] = (g2chr16_t)src[i];
    }
    rslt[i] = 0;

    return rslt;
}


wchar_t *g2pvt_s16dupw(g2chr16_t const* src)
{
    size_t n;
    size_t i;
    wchar_t *rslt;

    assert(src != NULL);

    n = g2pvt_s16len(src);
    rslt = (wchar_t*)malloc((n+1) * sizeof *rslt);
    if (NULL == rslt) {
        return NULL;
    }
    for (i = 0 ; i < n; ++i) {
        rslt[i] = src[i];
    }
    rslt[i] = L'\0';

    return rslt;
}


#define EXPECT_s16dup2mbs(output, input) {                              \
        g2chr16_t *g2s_ = g2pvt_wdups16(input);                         \
        CPPUNIT_ASSERT(g2s_ != NULL);                                   \
        char *s_ = g2_s16dup2mbs(g2s_);                                 \
        CPPUNIT_ASSERT(s_ != NULL);                                     \
        CPPUNIT_ASSERT_EQUAL((char*)output, s_);                        \
        free(s_);                                                       \
        free(g2s_);                                                     \
    }


TEST(g2_s16dup2mbsb_ascii)
{
    // This should work with any locale
    EXPECT_s16dup2mbs("narrow me", L"narrow me");
    EXPECT_s16dup2mbs("", L"");
    EXPECT_s16dup2mbs("1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890", L"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
}

#ifndef _WIN32
// Windows standard C library locale is broken, it doesn't handle UTF-8.
TEST(g2_s16dup2mbsb_cyrillic_en_US_UTF8)
{
    // This test assumes that the `en_US.UTF8` locale is supported,
    // which is the case on pretty much any modern system that is not Windows
    CPPUNIT_ASSERT(NULL != setlocale(LC_ALL, "en_US.UTF-8"));

    EXPECT_s16dup2mbs("Миле воли диско", L"Миле воли диско");
    EXPECT_s16dup2mbs("абвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџш", L"абвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџшабвгдђежзијклљмнњопрстћуфхцчџш");

    // We are _not_ restoring the old locale because we can't, there
    // is no portable way of doing it in C (setlocale returns the new
    // "state" - not the old). So, other tests that depend on using
    // some other locale will have to set the one they need. Until we
    // provide a wrapper over C locale with something like
    // push_locale() and pop_locale().
}
#else
// So, on Windows, let's go mediaval and use CP1251. It is not a multi-byte
// encoding, but, at least we'll check if decoding from wide-string works.
TEST(g2_wcsdup2mbsb_cyrillic_CP1251)
{
    // Here we just change the code-page of the locale to CP1251.
    // Since we don't care about other aspects of locale, it's OK.
    // OTOH, setting some "real" cyrillic locale may fail on a
    // particular machine.
    CPPUNIT_ASSERT(NULL != setlocale(LC_ALL, ".1251"));

    // Encoding of this file may get messed up, so let's just "spell
    // this out", character code by character code. This is cyrillic
    // transcription of "Mile":
    EXPECT_s16dup2mbs("\xCC\xE8\xEB\xE5", L"\u041C\u0438\u043B\u0435");

    // We are _not_ restoring the old locale for the reasons explained above
}
#endif


TEST(g2_s16dup2mbsb_cyrillic_C)
{
    // "C" locale has to exist and it doesn't support Cyrillic
    CPPUNIT_ASSERT(NULL != setlocale(LC_ALL, "C"));

    // With "C" locale, this must fail.
    g2chr16_t *mile = g2pvt_wdups16(L"Миле воли диско");
    CPPUNIT_ASSERT(mile != NULL);
    CPPUNIT_ASSERT(NULL == g2_s16dup2mbs(mile));
    free(mile);
    // We are _not_ restoring the old locale for the same reasons as
    // the `g2_s16dup2mbsb_cyrillic_en_US_UTF8` test.
}


#define EXPECT_wdups16(input) {                                         \
        g2chr16_t *s_ = g2pvt_wdups16(input);                           \
        int i;                                                          \
        size_t len;                                                     \
        CPPUNIT_ASSERT(s_ != NULL);                                     \
        len = g2pvt_s16len(s_);                                         \
        CPPUNIT_ASSERT_EQUAL(len, wcslen(input));                       \
        for (i = 0; i < len; ++i) {                                     \
            CPPUNIT_ASSERT_EQUAL((wchar_t)s_[i], input[i]);             \
        }                                                               \
        free(s_);                                                       \
    }

TEST(g2_wdups16)
{
    EXPECT_wdups16(L"Test");
    EXPECT_wdups16(L"Миле воли диско");
    EXPECT_wdups16(L"Test Миле воли диско");
    EXPECT_wdups16(L"");
}

#define EXPECT_s16dupw(input) {                                         \
        g2chr16_t *s_ = g2pvt_wdups16(input);                           \
        CPPUNIT_ASSERT(s_ != NULL);                                     \
        wchar_t *wcs_ = g2pvt_s16dupw(s_);                              \
        CPPUNIT_ASSERT_EQUAL(wcs_, (wchar_t*)input);                    \
        free(s_);                                                       \
        free(wcs_);                                                     \
    }

TEST(g2_s16dupw)
{
    EXPECT_s16dupw(L"Test");
    EXPECT_s16dupw(L"Миле воли диско");
    EXPECT_s16dupw(L"Test Миле воли диско");
    EXPECT_s16dupw(L"");
}


#define EXPECT_s16len(input) {                                          \
        g2chr16_t *s_ = g2pvt_wdups16(input);                           \
        size_t len;                                                     \
        CPPUNIT_ASSERT(s_ != NULL);                                     \
        len = g2pvt_s16len(s_);                                         \
        CPPUNIT_ASSERT_EQUAL(len, wcslen(input));                       \
        free(s_);                                                       \
    }

TEST(g2_s16len)
{
    EXPECT_s16len(L"Test");
    EXPECT_s16len(L"Миле воли диско");
    EXPECT_s16len(L"Test Миле воли диско");
    EXPECT_s16len(L"");
}

g2chr16_t *g2pvt_s16chr(g2chr16_t const*str, int character);


#define EXPECT_s16chr(input, chr) {                                     \
		wchar_t *wcs_ = input;											\
        g2chr16_t *s_ = g2pvt_wdups16(wcs_);                            \
        CPPUNIT_ASSERT(s_ != NULL);                                     \
        wchar_t const *wcsres_ = wcschr(wcs_, chr);						\
        CPPUNIT_ASSERT(wcsres_ != NULL);                                \
        g2chr16_t *g2res_ = g2pvt_s16chr(s_, chr);                      \
        CPPUNIT_ASSERT(g2res_ != NULL);                                 \
        CPPUNIT_ASSERT_EQUAL(g2res_ - s_, wcsres_ - wcs_);				\
        free(s_);                                                       \
    }

#define EXPECT_NULL_s16chr(input, chr) {                                \
        g2chr16_t *s_ = g2pvt_wdups16(input);                           \
        CPPUNIT_ASSERT(s_ != NULL);                                     \
        wchar_t const* wcsres_ = wcschr(input, chr);                    \
        CPPUNIT_ASSERT(wcsres_ == NULL);                                \
        g2chr16_t *g2res_ = g2pvt_s16chr(s_, chr);                      \
        CPPUNIT_ASSERT(g2res_ == NULL);                                 \
        free(s_);                                                       \
    }


TEST(g2_s16chr)
{
    EXPECT_s16chr(L"123", '1');
    EXPECT_s16chr(L"123", '2');
    EXPECT_s16chr(L"123", '3');
    EXPECT_NULL_s16chr(L"123", '4');

    EXPECT_s16chr(L"Миле воли диско", L'М');
    EXPECT_s16chr(L"Миле воли диско", L'и');
    EXPECT_s16chr(L"Миле воли диско", L'л');
    EXPECT_s16chr(L"Миле воли диско", L'е');
    EXPECT_s16chr(L"Миле воли диско", L' ');
    EXPECT_s16chr(L"Миле воли диско", L'в');
    EXPECT_s16chr(L"Миле воли диско", L'о');
    EXPECT_s16chr(L"Миле воли диско", L'д');
    EXPECT_s16chr(L"Миле воли диско", L'с');
    EXPECT_s16chr(L"Миле воли диско", L'к');
    EXPECT_NULL_s16chr(L"Миле воли диско", L'ш');

    EXPECT_NULL_s16chr(L"", 'g');
}


#define EXPECT_s16cmp(input, input_2) {                                 \
        g2chr16_t *s_ = g2pvt_wdups16(input);                           \
        CPPUNIT_ASSERT(s_ != NULL);                                     \
        g2chr16_t *s_2_ = g2pvt_wdups16(input_2);                       \
        CPPUNIT_ASSERT(s_2_ != NULL);                                   \
        int wc_diff = wcscmp(input, input_2);                           \
        int g2_diff = g2pvt_s16cmp(s_, s_2_);                           \
        CPPUNIT_ASSERT((wc_diff == g2_diff) || (wc_diff * g2_diff > 0)); \
        free(s_);                                                       \
        free(s_2_);                                                     \
    }

TEST(g2_s16cmp)
{
    EXPECT_s16cmp(L"", L"");
    EXPECT_s16cmp(L"Eh", L"");
    EXPECT_s16cmp(L"", L"He");
    EXPECT_s16cmp(L"Eh", L"Eh");
    EXPECT_s16cmp(L"He", L"He");
    EXPECT_s16cmp(L"Ehe", L"Eh");
    EXPECT_s16cmp(L"Eh", L"Ehe");
    EXPECT_s16cmp(L"Миле", L"Миле");
    EXPECT_s16cmp(L"Мил", L"Миле");
    EXPECT_s16cmp(L"Миле", L"Мил");
    EXPECT_s16cmp(L"иле", L"Миле");
    EXPECT_s16cmp(L"Миле", L"иле");
    EXPECT_s16cmp(L"Миле", L"Миве");
    EXPECT_s16cmp(L"Миве", L"Миле");
    EXPECT_s16cmp(L"Миле", L"");
    EXPECT_s16cmp(L"", L"Миле");
}
