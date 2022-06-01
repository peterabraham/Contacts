from MessageHandler import MessageHandler
from time import sleep
from ContactsHandler import ContactsHandler
import threading

## Server App main thread
event = threading.Event()
messageHandler = MessageHandler(event)
responseQueue  = messageHandler.getResponseQueue()
messageQueue   = messageHandler.getMessageQueue()

contactsHandler = ContactsHandler(responseQueue)

while True: 
    event.wait()

    request = messageQueue.get()
    if request is None:
        continue

    contactsHandler.processRequestMessage(request)
    event.set()
    #Debug
    #print('Main thread - event set')
    