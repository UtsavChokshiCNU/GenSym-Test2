import re

from pygments.lexer import Lexer, RegexLexer, bygroups, include, do_insertions
from pygments.token import Text, Comment, Operator, Keyword, Name, \
     Punctuation, String, Number, Punctuation, Literal, Generic, Error



__all__ = ['GensymLexer']


class GensymLexer(RegexLexer):
    """
    Lexer for Gensym KB language.(referenced from functional.py, CommonLispLexer
    """

    name = 'G2'
    aliases = ['kb']
    filenames = ['*.kb']
    mimetypes = ['application/x-kb', 'application/x-knownledgebase']

    flags = re.IGNORECASE | re.MULTILINE

    ### couple of useful regexes

    # characters that are not macro-characters and can be used to begin a symbol
    nonmacro = r'\\.|[a-zA-Z0-9!$%&*+-/<=>?@\[\]^_{}~]'
    constituent = nonmacro + '|[#.]'
    terminated = r'(?=[ "()\'\n,;`])' # whitespace or terminating macro characters

    ### symbol token, reverse-engineered from hyperspec
    # Take a deep breath...
    symbol = r'(\|[^|]+\||(?:%s)(?:%s)*)' % (nonmacro, constituent)

    # reserved words from lisp function (list-all-reserved-words)
    special_forms = [
        "a", "above", "across", "ago", "all", "an", "and", "any", "at", "available-frame-vector",
        "average", "be", "becomes", "begin", "below", "between", "by", "call", "case", "change",
        "checking", "collection", "color-pattern", "conclude", "connected", "could", "count",
        "current", "day", "days", "deviation", "do", "down", "during", "else", "end", "every",
        "everything", "exists", "exit", "expiration", "false", "first", "focus", "for", "format",
        "giving", "go", "has", "hour", "hours", "if", "in", "infer", "input", "integral", "interpolated",
        "invoke", "is", "last", "maximum", "minimum", "minute", "minutes", "moved", "name", "named", "nearest",
        "nil", "no", "none", "not", "nothing", "of", "on", "one", "or", "output", "over", "past", "per", "product",
        "rate", "repeat", "return", "rules", "same", "second", "seconds", "send", "set", "should", "simulated",
        "standard", "start", "subworkspace", "sum", "symbol", "that", "the", "then", "there", "this", "to", "true",
        "undefined", "unspecified", "until", "upon", "using", "value", "values", "via", "wait", "was",
        "week", "weeks", "were", "when", "will", "with", "workspace", "yes",
        ]
    builtin_types = [
        'truth-value', 'symbol', 'text', 'quantity', 'value', 'item-or-value', 'sequence', 'structure',
        'time-stamp', 'long', 'integer', 'float', 'class',
        ]

    def get_tokens_unprocessed(self, text):
        stack = ['root']
        for index, token, value in RegexLexer.get_tokens_unprocessed(self, text, stack):
            if token is Name.Variable:
                if value in self.special_forms:
                    yield index, Keyword, value
                    continue
                if value in self.builtin_types:
                    yield index, Keyword.Type, value
                    continue
            yield index, token, value

    tokens = {
        'root' : [
            ('', Text, 'body'),
        ],
        'multiline-comment' : [
            (r'{', Comment.Multiline, '#push'), # (cf. Hyperspec 2.4.8.19)
            (r'}', Comment.Multiline, '#pop'),
            (r'[^}]+', Comment.Multiline),
            (r'[}]', Comment.Multiline),
        ],
        'body' : [
            # whitespace
            (r'\s+', Text),
            # (r'[:;]', Punctuation),
            (r'[<>/+:{}"!#$%&\'()*,-.;=?@\[\\\]^_`|~]', Punctuation),

            # single-line comment
            (r'\/\/.*?$', Comment.Singleline),

            # multi-line comment
            (r'{', Comment.Multiline, 'multiline-comment'),

            # strings and characters
            (r'"(\\.|[^"\\])*"', String),

            # decimal numbers
            (r'[-+]?\d+\.?' + terminated, Number.Integer),
            (r'[-+]?\d+/\d+' + terminated, Number),
            (r'[-+]?(\d*\.\d+([defls][-+]?\d+)?|\d+(\.\d*)?[defls][-+]?\d+)' \
                + terminated, Number.Float),

            # functions and variables
            # (r'\*' + symbol + '\*', Name.Variable.Global),
            (symbol, Name.Variable),

            # #\ parentheses }
            # (r'\(', Punctuation, 'body'), }
            # (r'\)', Punctuation, '#\pop'), }

        ],
    }
