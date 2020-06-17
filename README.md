# Study_HomeLibrary

Home Library managment software. This program allows user to managment his own library.

- TECHNOLOGIES:
  - MS SQL
  - C++
  - Qt framwork


- REQUIREMENTS:

	- Database - Application(version 1.0) works with MS SQL database, so you have to install local MS SQL instance or create some instance in the cloud. 
	- QT Framework.
	

- GUIDE HOW TO USE IT
	- Database connection:
	If you already have your SQL instance you can start using my program. Firstly, you have to create a new database. There are two ways how you can do it. 

SQL Script - You can use SQL script which you can find in the folder SQL, named "DatabaseCreate.sql". Open this file via SSMS on your SQL instance. You can also use any other managment software, than just copy the content from the 

or 

Application - Open my program, click "Options" in the top left corrner. Then select "Database settings". You'll see a new window where you can insert your connection string to the database. Plese do it and next click button "Create new database". In this case you need to be careful because application will connect to your instance and if database named "HomeLibrary" exist application will not create new database. If you want to create clear database you have to delete existing databse. 

	
	
	
	
	










