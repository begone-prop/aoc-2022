#!/usr/bin/env python3

from sys import argv, stderr, stdin

from bs4 import BeautifulSoup as bs
from markdownify import MarkdownConverter

if __name__ == '__main__':

    html_data = None
    if len(argv) > 1:
        with open(argv[1]) as f:
            html_data = f.read()
    else:
        html_data = stdin.read()

    parsed = bs(html_data, 'html.parser')
    article = parsed.find('article')

    opts = {
            'wrap': True,
            'wrap_width': 80,
            'bullets': '+',
            }

    md_data = MarkdownConverter(**opts).convert_soup(article)

    print(md_data, end='')
