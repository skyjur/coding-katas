#!/usr/bin/env python3
import requests
import sys
import os
import lxml.html as html

LANGUAGES = [
    ('javascript', 'js'),
]
URL = 'https://www.hackerrank.com/rest/contests/master/challenges/{challenge_id}'


def get_challenge(challenge_id):
    resp = requests.get(URL.format(challenge_id=challenge_id))
    resp.raise_for_status()
    data = resp.json()
    os.makedirs(challenge_id)
    for lang, extension in LANGUAGES:
        codepath = os.path.join(challenge_id, 'main.' + extension)
        with open(codepath, 'w') as f:
            f.write(data['model']['%s_template' % lang])
        etree = html.fromstring(data['model']['body_html'])
        for i, block in enumerate(etree.cssselect('.challenge_sample_input_body pre')):
            sample = ''.join(block.xpath('.//text()'))
            samplepath = os.path.join(challenge_id, 'sample%d.in' % i)
            with open(samplepath, 'w') as f:
                f.write(sample.strip())


if __name__ == '__main__':
    get_challenge(sys.argv[1])