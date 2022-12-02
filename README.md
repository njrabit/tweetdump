# tweetdump
Converts the 476m tweet data dump on Internet Archive to CSV ready to import into a database

# tweetdump according to OpenAI Chatbot
This Python program processes tweet data from the standard input and outputs the tweet time, user, tweet text, mentions, and hashtags as a comma-separated string on a single line. It does this by creating a Tweet object and using the Tweet class's methods to process each line of the input. When a line of input is empty, it indicates that the current tweet is finished, so the program outputs the processed tweet data and creates a new Tweet object to process the next tweet.
