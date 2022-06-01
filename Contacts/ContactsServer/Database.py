#from flask import Flask
#from flask_sqlalchemy import SQLAlchemy
from operator import contains
import sqlalchemy as db
from sqlalchemy import MetaData, Table, Column, String, Integer, or_
from sqlalchemy.orm import Session
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.dialects.postgresql import UUID
import uuid

Base = declarative_base()

class Contact(Base):
    __tablename__ = 'contacts'
    firstname = Column(String)
    lastname = Column(String)
    phone = Column(Integer)
    email = Column(String)
    contactid = Column(String, primary_key=True, default=str(uuid.uuid4))
        
    # def __repr__(self):
    #     return "Contact<First Name = '%s', Last Name = '%s', Phone = '%d', Email = '%s'>" %(self.firstname, self.lastname, self.phone, self.email)

class Database():
    engine = db.create_engine('postgresql://peter:pabraham@localhost:5432/contactdb')
    
    def __init__(self):
        self.connection = self.engine.connect()
        #Debug
        #print('DB instance created!')
        
        
    def fetchAllByTable(self, table):
        fetchQuery = self.connection.execute(f"SELECT * FROM {table}")
        
        # for data in fetchQuery:
        #     print(data)
        return fetchQuery.all()
            
    def createNewContact(self, contact):
        #Debug
        #print('Database - create new contact')
        session = Session(bind = self.connection)
        session.add(contact)
        session.commit()
            
    def fetchAllContactsMinimal(self):
        meta = MetaData()
        contact = Table('contacts', meta, 
                            Column('firstname'),
                            Column('phone'))
        contacts = self.connection.execute(contact.select())
        # for i in contacts:
        #     print(i)
        return contacts
            
    def fetchAllContacts(self):
        #Debug
        #print('Database - Get all contacts')
        # if self.connection.closed:
        #     self.connection = self.engine.connect()
        session = Session(bind = self.connection)
        contacts = session.query(Contact).all()
        result = []
        for contact in contacts :
            result.append(contact)
        #Debug
        #print(result)
        return result

    def updateContact(self, contact):
        session = Session(bind = self.connection)
        dataToUpdate = {Contact.firstname: contact.firstname, Contact.lastname: contact.lastname, Contact.phone:contact.phone, Contact.email:contact.email}
        contactData = session.query(Contact).filter(Contact.contactid == contact.contactid)
        contactData.update(dataToUpdate)
        session.commit()
    
    def searchContactByName(self, query):
        session = Session(bind = self.connection)
        contacts = session.query(Contact).filter(or_(Contact.firstname.contains(query), Contact.lastname.contains(query))).all()
        result = []
        for contact in contacts :
            result.append(contact)
        return result
            
    def deleteContact(self, contactid):
        session = Session(bind = self.connection)
        contact = session.query(Contact).filter(Contact.contactid == contactid).first()
        session.delete(contact)
        session.commit()