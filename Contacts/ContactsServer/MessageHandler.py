#
#   Hello World server in Python
#   Binds REP socket to tcp://*:5555
#   Expects b"Hello" from client, replies with b"World"
#

#import time
import zmq, queue, threading  

class MessageHandler():

    def __init__(self, event):
        self.event = event
        self.messageQueue = queue.Queue()
        self.responseQueue = queue.Queue()

        # TODO - start a thread
        t = threading.Thread(target=self.messageThread,)
        t.start()
        #self.messageThread()

    def messageThread(self):
        self.context = zmq.Context()
        self.socket = self.context.socket(zmq.REP)
        self.socket.bind("tcp://*:5555")

        

        while True:

            # Wait for next request from client
            #Debug
            #print ('Waiting for request message')
            message = self.socket.recv()
            #Debug
            #print("Received request: %s" % message)

            #  Process client request
            self.messageQueue.put(message)
            self.event.set()
            #Debug
            #print('Message thread set event')
            self.event.wait()
            #Debug
            #print('Message thread passed wait')
            
            response = self.responseQueue.get()

            if response is None:
                response = 'Done'

            #Debug
            #print ("Response: " + response)
            
            #  Send response back to client
            self.socket.send(response.encode())


    def getMessageQueue(self):
        return self.messageQueue

    def getResponseQueue(self):
        return self.responseQueue
            