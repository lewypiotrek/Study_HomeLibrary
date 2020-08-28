# Study_HomeLibrary


Home Library allows users to manage their own library! Check it!

- TECHNOLOGIES:
  - MS SQL
  - C++
  - T-SQL
  - Qt framework


- REQUIREMENTS:
	- Database engine- Application(version 1.0) works with MS SQL database.
	- QT Framework.
	
-------------------------------------------------------------------------	

- **GUIDE HOW TO USE IT**

	- **Database connection**:
	If you already installed your SQL instance you can start using my program. Firstly, you have to create a new database. There are two ways how you can do it. 

	SQL Script - You can use SQL script which you can find in the folder SQL, named "DatabaseCreate.sql". Open this file via SSMS on your SQL instance and execute. You can also use any other management software, then just copy the content from the file and paste in a new query window.

	or 

	Application - Open my program, click "Options" in the top left corner. Then select "Database settings". You'll see a new window where you can insert your connection string to the database. Please do it and next click button "Create new database". In this case, you need to be careful because application will connect to your instance, and if a database named "HomeLibrary" already exists, application will not create a any database, so If you want to create a clear database, firstly you have to ensure that you don't have the same database on this SQL instance.


	- **Database - Save connection string**:
	You don't have to insert connections string every time when you open the program. There is an option to save your connection string in the file Config.txt. You can do it via app Option > Database Settings > Insert your connection string and click "Save" button, your credentials will be saved in Config.txt file. After that when you will open program again you can just click Option > Check connection... and the program will automatically check credentials and perform connection attemp.

	- **Tab: Your Books**:
	In this tab you can add/ modify and delete your books. On the right side you have main GroupBox with all functionalities. The data in your view should be refreshed automaticly, but you can also do it manually via Options > Refresh.
	
	- **Tab: Lending**
	In this place you can lend your book to your friends. On the left side select book and on the right side select friend. After that click button "Lend a book"
	If you want to add a new friend click option > Add User. The User creation window will be opend where you will be able to add a new friend.
	
	- **Tab: History:**
	There you can check lending history of specific books. If somebody bring your book back, you can mark this book as received. 
		
	- **Tab: Note**
	In this tab you can add your notes for example some thoughts about your new book. 
 


-------------------------------------------------------------------------



