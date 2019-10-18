from tweepy.streaming import StreamListener
from tweepy import OAuthHandler
from tweepy import Stream

#Variables that contains the user credentials to access Twitter API 
access_token = "1175521961948135424-rFuPTB9yy199EqOOAD37WF4cdoMO23"
access_token_secret = "pMzfBBwazTBmrS208pmdm9RnR2eAmFa1bpysUQf9FJYSI"
consumer_key = "jUTnbqrmx6GeL76n4cEmmSukr"
consumer_secret = "KPdT15ZkflMpJxgwcRWmPP6HEWrL5hJ6XxrODMfOb2e3XmoOyR"


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
    #stream.filter(track='pro-security')
    stream.filter(track=['privacy', 'pro-privacy'])
