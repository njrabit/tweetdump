#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

regex_t hashtag;
regex_t username;

typedef struct Tweet {
  char* time;
  char* user;
  char* tweet;
  char* hashtags;
  char* mentions;
} Tweet;

void init_tweet(Tweet* t) {
  t->time = malloc(sizeof(char));
  t->time[0] = '\0';
  t->user = malloc(sizeof(char));
  t->user[0] = '\0';
  t->tweet = malloc(sizeof(char));
  t->tweet[0] = '\0';
  t->hashtags = malloc(sizeof(char));
  t->hashtags[0] = '\0';
  t->mentions = malloc(sizeof(char));
  t->mentions[0] = '\0';
}

void free_tweet(Tweet* t) {
  free(t->time);
  free(t->user);
  free(t->tweet);
  free(t->hashtags);
  free(t->mentions);
}

char* output(Tweet* t) {
  char* result = malloc(sizeof(char));
  result[0] = '\0';

  regmatch_t matches[10];
  if (regexec(&hashtag, t->tweet, 10, matches, 0) == 0) {
    char tmp[1000];
    for (int i = 0; i < 10; i++) {
      if (matches[i].rm_so == -1) break;
      int len = matches[i].rm_eo - matches[i].rm_so;
      memcpy(tmp, t->tweet + matches[i].rm_so, len);
      tmp[len] = '\0';
      strcat(t->hashtags, tmp);
    }
  }
  if (regexec(&username, t->tweet, 10, matches, 0) == 0) {
    char tmp[1000];
    for (int i = 0; i < 10; i++) {
      if (matches[i].rm_so == -1) break;
      int len = matches[i].rm_eo - matches[i].rm_so;
      memcpy(tmp, t->tweet + matches[i].rm_so, len);
      tmp[len] = '\0';
      strcat(t->mentions, tmp);
    }
  }

  char buffer[1000];
  sprintf(buffer, "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"", t->time, t->user, t->tweet, t->mentions, t->hashtags);
  strcat(result, buffer);

  return result;
}

char* strip(char* s) {
  char* result = malloc(sizeof(char));
  result[0] = '\0';

  char* token
