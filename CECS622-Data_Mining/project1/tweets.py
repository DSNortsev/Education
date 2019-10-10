from tweepy.streaming import StreamListener
from tweepy import OAuthHandler
from tweepy import Stream

#Variables that contains the user credentials to access Twitter API 
access_token = "1175521961948135424-7J6fY5ppFoBE3fCsGnkUml0LOivEdx"
access_token_secret = "ngb49DaTf8hZAZPM9VgwEuEyuq8MiLGbfQGqYrY6zrBy9"
consumer_key = "hPmKN3N4HgoHHYEtHD7FTNmBh"
consumer_secret = "iJEIJY7yFu44fzWJAOVpemaKOHHetjpCmHAwrBz4UBS25YlUx4"


#This is a basic listener that just prints received tweets to stdout.
class StdOutListener(StreamListener):

    def on_data(self, data):
        print(data)
        return True

    def on_error(self, status):
        print(status)


if __name__ == '__main__':

    #This handles Twitter authetification and the connection to Twitter Streaming API
    l = StdOutListener()
    auth = OAuthHandler(consumer_key, consumer_secret)
    auth.set_access_token(access_token, access_token_secret)
    stream = Stream(auth, l)

    # #This line filter Twitter Streams to capture data by the keywords: 'python', 'javascript', 'ruby'
 #   stream.filter(track='privacy')
    # stream.filter(track=['privacy rights groups', 'advocate for privacy rights' ,'privacy and security concerns','personal privacy', 'governments surveillance', 'pro-privacy', 'data collection'])
#    stream.filter(track=['privacy rights groups', 'advocate for privacy rights' ,'privacy and security concerns','personal privacy', 'data collection'])
    #stream.filter(track=['pro-security', 'public safety', 'national security'])
    stream.filter(track=['pro-privacy', 'data collection', 'surveillance'])
