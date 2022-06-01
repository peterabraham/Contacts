
from Database import Database
from Database import Contact
from sqlalchemy.ext.declarative import DeclarativeMeta
import json
import uuid
from collections import namedtuple 

class AlchemyEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj.__class__, DeclarativeMeta):
            # an SQLAlchemy class
            fields = {}
            for field in [x for x in dir(obj) if not x.startswith('_') and x != 'metadata']:
                data = obj.__getattribute__(field)
                try:
                    json.dumps(data) # this will fail on non-encodable values, like other classes
                    fields[field] = data
                except TypeError:
                    fields[field] = None
            # a json-encodable dict
            return fields

        return json.JSONEncoder.default(self, obj)

class ContactsHandler():
    def __init__(self, responseQueue):
        self.database = Database()
        self.responseQueue = responseQueue


    def createNewContact(self, contact):
        try:
            #Debug
            #print('ContactsHandler - create new contact')
            newContact = Contact(firstname=contact.firstname, lastname=contact.lastname, phone=contact.phone, email=contact.email, contactid=str(uuid.uuid4()))
            self.database.createNewContact(newContact)
        except:
            print('An exception occurred at create contact')

    def updateContact(self, contact):
        editContact = Contact(firstname=contact.firstname, lastname=contact.lastname, phone=contact.phone, email=contact.email, contactid=contact.contactid)
        self.database.updateContact(editContact)

    def getAllContacts(self):
        #Debug
        #print('ContactsHandler - Get all contacts')
        contacts = self.database.fetchAllContacts()
        contactsString = json.dumps(contacts, cls=AlchemyEncoder)
        #print(contactsString)
        #self.responseQueue.put(contactsString)
        return contacts

    def searchContact(self, query):
        contacts = self.database.searchContactByName(query)
        contactsString = json.dumps(contacts, cls=AlchemyEncoder)
        #print(contactsString)
        #self.responseQueue.put(contactsString)
        return contacts

    def deleteContact(self, contactid):
        #Debug
        #print('Contact id to be deleted: '+ contactid)
        self.database.deleteContact(contactid)

    def processRequestMessage(self, message):
        #Debug
        #print ('Begin to process request message')
        msgObj = json.loads(message, object_hook =
               lambda d : namedtuple('X', d.keys())
               (*d.values()))
        operation = msgObj.operation

        if operation == 'create-contact':
            self.createNewContact(msgObj.data)
            response = self.buildResponseStatus('create-contact', 'Done')
            self.responseQueue.put(response)

        elif operation == 'update-contact':
            self.updateContact(msgObj.data)
            response = self.buildResponseStatus('update-contact', 'Done')
            self.responseQueue.put(response)

        elif operation == 'delete-contact':
            self.deleteContact(msgObj.contactid)
            response = self.buildResponseStatus('delete-contact', 'Done')
            self.responseQueue.put(response)

        elif operation == 'get-all-contacts':
            contacts = self.getAllContacts()
            response = self.buildResponseStatus('get-all-contacts', contacts)
            self.responseQueue.put(response)

        elif operation == 'search-contact':
            contacts = self.searchContact(msgObj.query)
            response = self.buildResponseStatus('search-contacts', contacts)
            self.responseQueue.put(response)

        else:
            print("Invalid operation")

    def buildResponseStatus(self, operation, data):
        status = {}
        status['operation'] = operation
        status['data'] = data
        statusStr = json.dumps(status, cls=AlchemyEncoder)
        #Debug
        #print ('response: ')
        #print(statusStr)
        return statusStr
