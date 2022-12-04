import sys
import re
from pprint import pprint

dehash = re.compile(r"(#+[a-zA-Z0-9(_)]{1,})")
demention = re.compile(r"(@+[a-zA-Z0-9(_)]{1,})")

class Tweet:

    def __init__(self):
        self.time = ""
        self.user = ""
        self.tweet = ""
        self.hashtag = []
        self.mention = []

    def output(self):
        return (
            f"\"{self.time}\",\"{self.user}\",\"{self.tweet}\",\"{self.mention}\",\"{self.hashtag}\""
            )
    
    def trim(self, s):
        return (s.strip().split("\t")[1])

    def postcode(self, s):
        return(s.encode("utf-8"))
    
    def postencode(self):
        self.hashtag = dehash.findall(self.tweet)
        self.mentions = demention.findall(self.tweet)
        self.time = self.postcode(self.time)
        self.user = self.postcode(self.user)
        self.tweet = self.postcode(self.tweet)


    def itime(self, s):
        self.time = self.trim(s)

    def iuser(self, s):
        self.user = self.trim(s).replace("http://twitter.com/", "@")

    def itweet(self, s):
        self.tweet = self.trim(s)

    def ihashtag(self, s):
        self.hashtag = set(dehash.findall(self.tweet).sort())

t = Tweet()

for l in sys.stdin:

    if '' == l.strip():
        t.postencode()
        print(t.output())
        t = Tweet()

    if l.startswith("T\t"):
        t.itime(l)

    if l.startswith("U\t"):
        t.iuser(l)

    if l.startswith("W\t"):
        t.itweet(l)
