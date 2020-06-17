# Study_HomeLibrary

Home Library management software. This program allows users to manage their own library.

- TECHNOLOGIES:
  - MS SQL
  - C++
  - Qt framework


- REQUIREMENTS:

	- Database - Application(version 1.0) works with MS SQL database, so you have to install local MS SQL instance or create an instance in the cloud. 
	- QT Framework.
-------------------------------------------------------------------------	

- **GUIDE HOW TO USE IT**

	- **Database connection**:
	If you already have your SQL instance you can start using my program. Firstly, you have to create a new database. There are two ways how you can do it. 

	SQL Script - You can use SQL script which you can find in the folder SQL, named "DatabaseCreate.sql". Open this file via SSMS on your SQL instance. You can also use any other management software, then just copy the content from the 

	or 

	Application - Open my program, click "Options" in the top left corner. Then select "Database settings". You'll see a new window where you can insert your connection string to the database. Please do it and next click button "Create new database". In this case, you need to be careful because application will connect to your instance, and if a database named "HomeLibrary" exist application will not create a new database. If you want to create a clear database you have to delete the existing database. 


	- **Database Save connection string**:
You don't have to insert connections string every time when you open the program. There is an option to save your connection string in the file Config.txt. You can do it via app Option > Database Settings > Insert your connection string and click "Save" button your credentials will be saved in Config.txt file. After that when you open program again you can just click Option > Check connection... and the program will automatically check credentials and perform connection attempt 
	



