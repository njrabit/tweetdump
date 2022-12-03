#include <iostream>
#include <regex>
#include <string>

std::regex hashtag("(#+[a-zA-Z0-9(_)]{1,})");
std::regex username("(@+[a-zA-Z0-9(_)]{1,})");

class Tweet {
 public:
  std::string time;
  std::string user;
  std::string tweet;
  std::string hashtags;
  std::string mentions;

  Tweet() : time(""), user(""), tweet(""), hashtags(""), mentions("") {}

  std::string output() {
    hashtags = std::regex_replace(tweet, hashtag, "$1");
    mentions = std::regex_replace(tweet, username, "$1");
    return "\"" + time + "\",\"" + user + "\",\"" + tweet + "\",\"" + mentions + "\",\"" + hashtags + "\"";
  }

  std::string strip(const std::string& s) {
    return s.substr(s.find_first_of('\t') + 1);
  }

  void itime(const std::string& s) {
    time = strip(s);
  }

  void iuser(const std::string& s) {
    user = strip(s).replace("http://twitter.com/", "@");
  }

  void itweet(const std::string& s) {
    tweet = strip(s);
  }
};

int main() {
  Tweet t;
  std::cout << "starting" << std::endl;

  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      std::cout << t.output() << std::endl;
      t = Tweet();
    }

    if (line.find("T\t") == 0) {
      t.itime(line);
    }

    if (line.find("U\t") == 0) {
      t.iuser(line);
    }

    if (line.find("W\t") == 0) {
      t.itweet(line);
    }
  }

  return 0;
}
