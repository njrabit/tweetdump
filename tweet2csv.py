import sys
import re
from pprint import pprint

hashtag = re.compile(r"(#+[a-zA-Z0-9(_)]{1,})")
username = re.compile(r"(@+[a-zA-Z0-9(_)]{1,})")


class Tweet:

    def __init__(self):
        self.time = ""
        self.user = ""
        self.tweet = ""
        self.hashtag = ""
        self.mention = ""

    def output(self):
        self.hashtag = hashtag.findall(self.tweet)
        self.mentions = username.findall(self.tweet)
        return (
            f"\"{self.time}\",\"{self.user}\",\"{self.tweet}\",\"{self.mention}\",\"{self.hashtag}\"")

    def postcode(self):
        self.time = strip(self.time).encode("utf-8")
        self.user = strip(self.user).encode("utf-8")
        self.tweet = strip(self.tweet).encode("utf-8")
        self.hashtag = strip(self.hashtag).encode("utf-8")
        self.mention = strip(self.mention).encode("utf-8")

    def strip(self, s):
        return (s.split("\t")[1].encode())

    def itime(self, s):
        self.time = self.strip(s.strip())

    def iuser(self, s):
        self.user = self.strip(s.strip().replace("http://twitter.com/", "@"))

    def itweet(self, s):
        self.tweet = self.strip(s.strip())

t = Tweet()

print("starting")

for l in sys.stdin:

    if '' == l.strip():
        print(t.output())
        t = Tweet()

    if l.startswith("T\t"):
        t.itime(l)

    if l.startswith("U\t"):
        t.iuser(l)

    if l.startswith("W\t"):
        t.itweet(l)

    # print(f'Input : {l}')
