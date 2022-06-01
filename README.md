# Contacts

Contacts App is a cross-platform contact management application created for the learning purpose with limited features to store all contacts of an individual. This application is made to create a client-server reference architecture for a desktop application using Python-PostgresSQL as backend and QT-C++ as frontend. The ZMQ (Zero Message-Queue) has been used as the communication mechanism for the application. The inspiration for this architectural model was to minify a work experience of mine by covering all the essential technology used in the professional application.

## Setting up Contacts App

### Setup PostgresSQL :
1.	Install [PostgreSQL](https://www.postgresql.org/docs/current/tutorial-install.html) on a platform of your choice.

2.	Start PostgreSQL and start psql with default user.
```
psql -U postgres
```
3.	Create a user with password.
```
CREATE USER peter WITH PASSWORD 'pabraham' CREATEDB;
```

4.	Create a database for Contacts app.
```
CREATE DATABASE contactdb OWNER peter;
```

5.	On next startup onwards, you can use following command to directly open psql with the database of your choice.
```
psql -U peter -d contactdb
```

6.	Create ‘contacts’ table.
```
CREATE TABLE contacts (
	contactid text PRIMARY KEY,
	firstname text,
	lastname text,
	phone begint,
	email text,
);
```

The identifiers used in the aforementioned examples are the exact ones used when author created the app. You can change the user, database or table name as per your preference. When changed, make sure that you make the corresponding changes to the connection string and table name in the python code as well (Database.py).

### ContactServer:
This python app interacts with the Postgres database using SQLAlchemy ORM. The application uses python3 and following dependencies are required to run this app:
```
pip install pyzmq
pip install SQLAlchemy
```

Run the app using following command:
```
Python3 ContactsServer.py
```

### ContactsGUIClient:

The Contacts client app is built using QT framework and C++ to achieve cross-platform portability. The app uses QT6 and third part libraries such as [Boost](https://www.boost.org/users/download/) and [ZMQ](https://zeromq.org/download/). Hence, the machine must be installed with all three libraries and a C++ compiler with C++14 support. [CMake](https://cmake.org/download/) is employed to build the client application, and the build requires the path to cmake under QT, boost headers and boost libs. The lines setting these paths in CMakeLists.txt are commented as they are added to the PATH environment variable. Otherwise you have to uncomment and use appropriate paths.
