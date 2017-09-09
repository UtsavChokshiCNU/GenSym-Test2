/* -*- c-file-style:"stroustrup"; indent-tabs-mode: nil -*- */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if !defined INC_CPPUNIT_ASSERTION_TRAIT_CHARP
#define      INC_CPPUNIT_ASSERTION_TRAIT_CHARP

namespace CppUnit {
    /** This trait class will enable nicer asserts for C strings.
        If you include this, your test can be written like this:
      
            char s[100] = "yes";
            CPPUNIT_ASSERT_EQUAL((char*)"yes, sir", strcat(s, ", sir"));

        and will give nicer output (printing both the expected and the
        actual string), instead of writing them like this:

            CPPUNIT_ASSERT_EQUAL(0, strcmp("yes, sir", strcat(s, ", sir")));

	which would only print the return of strcmp(), which isn't very
        useful.
    */
    template<> struct assertion_traits<char*> {
        static bool equal(char* const& x, char* const& y) {
            return strcmp(x,y) == 0;
        }
        
        static std::string toString(char* const& x) {
            return std::string("'") + x + "'";
        }
    };

    /** Ditto for C wide strings */
    template<> struct assertion_traits<wchar_t*> {
        static bool equal(wchar_t* const& x, wchar_t* const& y) {
            return wcscmp(x,y) == 0;
        }
        
        static std::string toString(wchar_t* const& wcs) {
            wchar_t const *converter;
            mbstate_t mbs;
            char *s;
            size_t length;
            
            memset(&mbs, 0, sizeof mbs);
            converter = wcs;
            length = wcsrtombs(NULL, &converter, 0, &mbs);
            printf("%ls, length=%zu, converter=%ls\n", wcs, length, converter);
            if (length == (size_t)-1) {
                return "Failed to convert";
            }
            s = (char*)malloc(length+1);
            if (NULL == s) {
                return "???";
            }
            converter = wcs;
            memset(&mbs, 0, sizeof mbs);
            wcsrtombs(s, &converter, length, &mbs);
            s[length] = '\0';

            std::string result("'");
            result += s;
            free(s);
            result += "'";
            return result;
        }
    };
}


#endif /* !defined INC_CPPUNIT_ASSERTION_TRAIT_CHARP */
