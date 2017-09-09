/* -*- c-file-style:"stroustrup"; indent-tabs-mode: nil -*- */

/** This file is self-sufficient, you just need a C++11 compiler to build it */
#include <fstream>
#include <sstream>
#include <cstring>
#include <iostream>


std::string erase_between(std::string s, char const* start_tag, char const* end_tag)
{
    auto start = s.find(start_tag);
    if (s.npos == start) {
        return s;
    }
    auto end = s.find(end_tag);
    if (s.npos == start) {
        return s;
    }
    end += strlen(end_tag);
    s.erase(start, end - start);

    return s;
}


std::string erase_between_global(std::string s, char const* start_tag, char const* end_tag)
{
    for (;;) {
        std::string handled = erase_between(s, start_tag, end_tag);
        if (s == handled) {
            break;
        }
        s = handled;
    }
    return s;
}


bool all_whitespace(std::string s)
{
    for (auto i = s.begin(); i != s.end(); ++i) {
        switch (*i) {
        case ' ':
        case '\t':
        case '\r':
        case '\n':
            break;
        default:
            return false;
        }
    }
    return true;
}

std::string erase_all_empty_tags(std::string s)
{
    size_t start = 0;
    for (;;) {
        start = s.find("<", start);
        auto end = s.find_first_of(" >", start);
        auto tag_end = s.find(">", end);
        auto next_start = s.find("</", tag_end);
        if (s.npos == next_start) {
            break;
        }
        bool erased = false;
        if (all_whitespace(s.substr(tag_end + 1, next_start - tag_end - 1))) {
            auto next_end = s.find(">", next_start);
            if (s.npos == end) {
                break;
            }
            if (s.substr(start + 1, end - start -1) == s.substr(next_start + 2, next_end - next_start - 2)) {
                s.erase(start, next_end - start + 1);
                erased = true;
            }
        }

        if (!erased) {
            start = end;
        }
    }

    return s;
}


std::string cleanup_system_tables(std::string s)
{
    s = erase_between_global(s, "<g2:a.ICON-VARIABLES>", "</g2:a.ICON-VARIABLES>");
    // this gets rid of empty parameters
    s = erase_all_empty_tags(s);
    // this gets rid of empty <rdf:li>
    s = erase_all_empty_tags(s);
    return s;
}


int doit(std::istream &in, std::ostream &out)
{
    std::stringstream buffer;
    buffer << in.rdbuf();
    auto s = erase_between(buffer.str(), "<g2:externaldefinitions>", "</g2:externaldefinitions>");
    s = erase_between(s, "<g2:checksums>", "</g2:checksums>");
    s = erase_between_global(s, "<g2:a.AUTHORS>", "</g2:a.AUTHORS>");
    auto system_tables_start = s.find("<g2:systemtables>");
    if (s.npos == system_tables_start) {
        std::cout << "Can't find systemtables start" << std::endl;
        return -1;
    }
    auto system_tables_end = s.find("</g2:systemtables>");
    if (s.npos == system_tables_end) {
        std::cout << "Can't find systemtables end" << std::endl;
        return -1;
    }
    auto system_tables = cleanup_system_tables(s.substr(system_tables_start, system_tables_end - system_tables_start + strlen("</g2:systemtables>")));
    s.replace(system_tables_start, system_tables_end - system_tables_start + strlen("</g2:systemtables>"), system_tables);

    out << s;

    return 0;
}


int main(int argc, char *argv[])
{
    switch (argc) {
    case 1:
        return doit(std::cin, std::cout);
    case 2:
    {
        std::ifstream in(argv[1]);
        return doit(in, std::cout);
    }
    case 3:
    {
        std::ifstream in(argv[1]);
        std::ofstream out(argv[2]);
        return doit(in, out);
    }
    default:
        std::cout << "(C) IgniteTech 2017\nUtility that removes unneeded XML tags from a G2 (regression) test XML KB.\n\n"
            "    parameters: [input_file [output_file]]\n\n"
            "If not given in parameters, standard input and standard output are defaults.\n";
        return -1;
    }
}
