#!/usr/bin/env python3

from sys import argv, stderr, stdin
from os import getenv
from requests import get

from bs4 import BeautifulSoup as bs
from markdownify import MarkdownConverter

if __name__ == '__main__':

    base_url = 'https://adventofcode.com/2022'

    if len(argv) == 1:
        print('No argument', file=stderr)
        exit(1)

    day = argv[1]

    cookie = getenv('AOC_COOKIE')
    if not cookie or not len(cookie):
        print("AOC_COOKIE not found or empty", file=stderr)
        exit(1)

    url = f'{base_url}/day/{day}'

    head = { 'Cookie': f'session={cookie}' }

    resp = get(url, headers=head)
    if resp.status_code != 200:
        print(f'Error fetching description from {url}: Server returned {resp.status_code}')
        exit(1)

    parsed = bs(resp.content, 'html.parser')
    article = parsed.find_all('article')

    opts = {
            'wrap': True,
            'wrap_width': 80,
            'bullets': '+',
            }

    for art in article:
        md_data = MarkdownConverter(**opts).convert_soup(art)
        print(md_data, end='')
