"""
Gensym syntax highlighting for Pygments.
"""

from setuptools import setup

entry_points = """
[pygments.lexers]
gensym-kb = gensymlexer.gensymlexer:GensymLexer
"""

setup(
    name         = 'gensymlexer',
    version      = '0.1',
    description  = __doc__,
    author       = "Xu Jingtao (jingtaozf@gmail.com)",
    packages     = ['gensymlexer'],
    entry_points = entry_points
)
