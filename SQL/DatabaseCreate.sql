----------------------------------------------------------------------
--	Piotr Lewandowski - Creating database schema for HomeLibrary
----------------------------------------------------------------------

USE [master];
GO
--DROP DATABASE HomeLibrary
----------------------------------------------------------------
-- CREATING DATABASE --
----------------------------------------------------------------
BEGIN TRY
IF EXISTS (SELECT * FROM sys.databases WHERE [name] = 'HomeLibrary')
	BEGIN
		DROP DATABASE HomeLibrary;
		CREATE DATABASE HomeLibrary;
	END
ELSE
	BEGIN
		CREATE DATABASE HomeLibrary;
	END
END TRY

BEGIN CATCH
	PRINT 'Somethings went wrong, please check databases on your SQL instance. We are not able to create database';
END CATCH
GO

USE HomeLibrary;

----------------------------------------------------------------
-- CREATING STORED PROCEDURE TO CREATE DATABASE --
----------------------------------------------------------------

--DROP PROCEDURE IF EXISTS dbo.DatabaseCreation;  Syntax for SQL 2016
 
IF EXISTS ( SELECT * FROM sys.procedures WHERE [name] = 'DatabaseCreation')
BEGIN
	DROP PROCEDURE dbo.DatabaseCreation;
END
GO

-- Procedure that will create database schema
CREATE PROCEDURE DatabaseCreation
AS
BEGIN

-- Books
	IF NOT EXISTS (SELECT * FROM sys.tables WHERE [name] = 'Books')
	BEGIN
		CREATE TABLE Books
			(
				BooksId				int IDENTITY(1,1) PRIMARY KEY,
				Barcode				varchar(200) UNIQUE,
				Title				varchar(200) NOT NULL,
				Author				varchar(200),
				Publisher			varchar(150),
				PublicationDate		varchar(10),
				isAvailable			bit DEFAULT 1,
				isActive			bit DEFAULT 1,
				CreationTImestamp	datetime DEFAULT GETUTCDATE(),				
			);

		PRINT 'Table Books has been created';
	END
	ELSE
		PRINT 'Table Books already exists';

-- Community
	IF NOT EXISTS (SELECT * FROM sys.tables WHERE [name] = 'Community')
	BEGIN
		CREATE TABLE Community
			(
				CommunityId				int IDENTITY(1,1) PRIMARY KEY,
				Name					varchar(200) NOT NULL,
				[Address]				varchar(200) DEFAULT NULL,
				Info					varchar(200) DEFAULT NULL,
				isActive				bit DEFAULT 1, 
				CreationDate			datetime DEFAULT GETUTCDATE(),
				LastModificationDate	datetime DEFAULT GETUTCDATE(),				
			);

		PRINT 'Table Community has been created';
	END
	ELSE
		PRINT 'Table Community already exists';

-- Lending
	IF NOT EXISTS (SELECT * FROM sys.tables WHERE [name] = 'Lending')
	BEGIN
		CREATE TABLE Lending
			(
				LendingId				int IDENTITY(1,1) PRIMARY KEY,
				CommunityId				int FOREIGN KEY REFERENCES Community(CommunityId),
				BookId					int FOREIGN KEY REFERENCES Books(BooksId),
				CreationDate			datetime DEFAULT GETUTCDATE(),
				ReturnDate				datetime DEFAULT NULL,
				LastModificationTime	datetime DEFAULT GETUTCDATE(),				
			);

		PRINT 'Table Lending has been created';
	END
	ELSE
		PRINT 'Table Lending already exists';


-- Notes
	IF NOT EXISTS (SELECT * FROM sys.tables WHERE [name] = 'Notes')
	BEGIN
		CREATE TABLE Notes
			(
				NotesId					int IDENTITY(1,1) PRIMARY KEY,
				BookId					int FOREIGN KEY REFERENCES Books(BooksId),
				Title					varchar(100),
				Note					varchar(1000),
				CreationDate			datetime DEFAULT GETUTCDATE(),
				LastModificationTime	datetime DEFAULT GETUTCDATE(),					
			);

		PRINT 'Table Notes has been created';
	END
	ELSE
		PRINT 'Table Notes already exists';


END	-- DatabaseCreation procedure end
PRINT 'Stored Procedure DatabaseCreation has been created'
GO

-- CREATING DATABASE VIA PROCEDURE
----------------------------------------------------------------
USE HomeLibrary;
GO
EXEC DatabaseCreation;
GO


----------------------------------------------------------------
-- CREATING STORED PROCEDURES --
----------------------------------------------------------------


-- CREATING ShowBooks
----------------------------------------------------------------

IF EXISTS ( SELECT * FROM sys.procedures WHERE [name] = 'ShowBooks')
BEGIN
	DROP PROCEDURE dbo.ShowBooks;
END
GO

CREATE PROCEDURE ShowBooks @Barcode varchar(200), @Title varchar(200), @Author varchar(200), @Publisher varchar(150), @top int
AS
BEGIN
	SELECT TOP (@top)
		Barcode,
		Title,
		Author,
		Publisher,
		PublicationDate as [Publication Date]
	FROM
		dbo.Books
	WHERE
		Barcode LIKE '%'+ @Barcode + '%' AND
		Title LIKE '%'+ @Title + '%' AND
		Author LIKE '%'+ @Author + '%' AND
		Publisher LIKE '%'+ @Publisher + '%'AND
		isActive = 1 AND
		isAvailable = 1
	ORDER BY
		Title;
END
GO

-- CREATING ShowUsers
----------------------------------------------------------------

IF EXISTS ( SELECT * FROM sys.procedures WHERE [name] = 'ShowUsers')
BEGIN
	DROP PROCEDURE dbo.ShowUsers;
END
GO

CREATE PROCEDURE ShowUsers @Name varchar(200), @Address varchar(200), @Info varchar(200), @top int
AS
BEGIN
	SELECT TOP (@top)
		[Name],
		[Address],
		[Info]
	FROM
		dbo.Community
	WHERE
		[Name] LIKE '%'+ @Name + '%' AND
		[Address] LIKE '%'+ @Address + '%' AND
		Info LIKE '%'+ @Info + '%' AND
		isActive = 1
	ORDER BY
		[Name]
END
GO

-- CREATING AddNote
----------------------------------------------------------------

IF EXISTS ( SELECT * FROM sys.procedures WHERE [name] = 'AddNote')
BEGIN
	DROP PROCEDURE dbo.AddNote;
END
GO

CREATE PROCEDURE AddNote @Title varchar(300), @Note varchar(MAX)
AS
BEGIN
	IF NOT EXISTS(SELECT * FROM Notes WHERE Title = @Title)
		BEGIN
			INSERT INTO Notes (Title,Note,LastModificationTime)
			VALUES (@Title,@Note,GETUTCDATE());
		END
	ELSE
		BEGIN
			UPDATE Notes
			SET Note = @Note
			WHERE Title = @Title
		END
END
GO

-- CREATING DeleteNote
----------------------------------------------------------------

IF EXISTS ( SELECT * FROM sys.procedures WHERE [name] = 'DeleteNote')
BEGIN
	DROP PROCEDURE dbo.DeleteNote;
END
GO

CREATE PROCEDURE DeleteNote @Title varchar(300)
AS
BEGIN
	DELETE FROM Notes
	WHERE Title = @Title;

END
GO


-- CREATING DeleteBook
----------------------------------------------------------------

IF EXISTS ( SELECT * FROM sys.procedures WHERE [name] = 'DeleteBook')
BEGIN
	DROP PROCEDURE dbo.DeleteBook;
END
GO

CREATE PROCEDURE DeleteBook @barcode varchar(300)
AS
BEGIN
	DELETE FROM Books
	WHERE Barcode = @barcode;

END
GO

-- CREATING AddBook
----------------------------------------------------------------

IF EXISTS ( SELECT * FROM sys.procedures WHERE [name] = 'AddBook')
BEGIN
	DROP PROCEDURE dbo.AddBook;
END
GO

CREATE PROCEDURE AddBook @barcode varchar(200), @title varchar(200), @author varchar(200), @publisher varchar(200), @publicationDate varchar(200)
AS
BEGIN
	IF NOT EXISTS (SELECT * FROM Books WHERE Barcode = @barcode)
		BEGIN
			INSERT INTO Books (barcode,Title,Author,Publisher,PublicationDate)
			VALUES (@barcode,@title,@author,@publisher,@publicationDate);
		END
	ELSE
		BEGIN
			UPDATE Books
			SET Title = @title, Author = @author, Publisher = @publisher, PublicationDate = @publicationDate
			WHERE Barcode = @barcode 
		END
END
GO


-- CREATING DeleteBook
----------------------------------------------------------------

IF EXISTS ( SELECT * FROM sys.procedures WHERE [name] = 'DeleteBook')
BEGIN
	DROP PROCEDURE dbo.DeleteBook;
END
GO

CREATE PROCEDURE DeleteBook @barcode varchar(200)
AS
BEGIN
	IF EXISTS (SELECT * FROM Books WHERE Barcode = @barcode)
		BEGIN
			UPDATE Books
			SET isActive = 0
			WHERE Barcode = @barcode
		END
END
GO


-- CREATING LendBook
----------------------------------------------------------------

IF EXISTS ( SELECT * FROM sys.procedures WHERE [name] = 'LendBook')
BEGIN
	DROP PROCEDURE dbo.LendBook;
END
GO

CREATE PROCEDURE LendBook @barcode varchar(200), @user varchar(200)
AS
BEGIN
	DECLARE @Bookid INT;
	DECLARE @CommunityID INT;

	SET @Bookid = (SELECT TOP 1 BooksId FROM Books WHERE Barcode = @barcode);
	SET @CommunityID = (SELECT TOP 1 CommunityId FROM Community WHERE [Name] = @user);

	INSERT INTO Lending (CommunityId,BookId)
	VALUES (@CommunityID,@Bookid);

	UPDATE Books
	SET isAvailable = 0
	WHERE Barcode = @barcode;
	
END
GO


-- CREATING ShowBorrowedBooks
----------------------------------------------------------------

IF EXISTS ( SELECT * FROM sys.procedures WHERE [name] = 'ShowBorrowedBooks')
BEGIN
	DROP PROCEDURE dbo.ShowBorrowedBooks;
END
GO

CREATE PROCEDURE ShowBorrowedBooks 
AS
BEGIN

	SELECT 
		b.Barcode AS Barcode,
		b.Title AS Title,
		c.[name] AS [User name],
		l.CreationDate AS [Borrow Date]	
	FROM
		Lending l
		INNER JOIN Community c on l.CommunityId = c.CommunityId
		INNER JOIN Books b on b.BooksId = l.BookId
	WHERE
		l.ReturnDate IS NULL AND
		b.isAvailable = 0;
			
END
GO

-- CREATING CompleteLending
----------------------------------------------------------------

IF EXISTS ( SELECT * FROM sys.procedures WHERE [name] = 'CompleteLending')
BEGIN
	DROP PROCEDURE dbo.CompleteLending;
END
GO

CREATE PROCEDURE CompleteLending  @barcode varchar(200)
AS
BEGIN
	
	UPDATE Books
	SET isAvailable = 1
	WHERE Barcode = @barcode;

	UPDATE Lending
	SET LastModificationTime = GETUTCDATE(), ReturnDate = GETUTCDATE()
	WHERE bookid = (SELECT BooksId FROM Books WHERE Barcode = @barcode)
			
END
GO


-- CREATING ShowHistoryByFilter
----------------------------------------------------------------

IF EXISTS ( SELECT * FROM sys.procedures WHERE [name] = 'ShowHistoryByFilter')
BEGIN
	DROP PROCEDURE dbo.ShowHistoryByFilter;
END
GO

CREATE PROCEDURE ShowHistoryByFilter  @barcode varchar(200)
AS
BEGIN
	SELECT 
		b.Barcode AS Barcode,
		b.Title AS Title,
		c.[name] AS [User name],
		l.CreationDate AS [Borrow Date]	
	FROM
		Lending l
		INNER JOIN Community c on l.CommunityId = c.CommunityId
		INNER JOIN Books b on b.BooksId = l.BookId
	WHERE
		l.ReturnDate IS NULL AND
		b.isAvailable = 0 AND
		b.Barcode = @barcode;			
END
GO

-- CREATING AddUser
----------------------------------------------------------------

IF EXISTS ( SELECT * FROM sys.procedures WHERE [name] = 'AddUser')
BEGIN
	DROP PROCEDURE dbo.AddUser;
END
GO

CREATE PROCEDURE AddUser  @username varchar(200),@address varchar(200),@info varchar(200)
AS
BEGIN
	IF NOT EXISTS (SELECT * FROM Community WHERE [Name] = @username)
	BEGIN
		INSERT INTO Community ([Name],[Address],Info)
		VALUES (@username,@address,@info);
	END		
END
GO


-- CREATING DeleteUser
----------------------------------------------------------------

IF EXISTS ( SELECT * FROM sys.procedures WHERE [name] = 'DeleteUser')
BEGIN
	DROP PROCEDURE dbo.DeleteUser;
END
GO

CREATE PROCEDURE DeleteUser  @username varchar(200)
AS
BEGIN
	UPDATE Community
	SET isActive = 0
	WHERE [Name] = @username;	
END
GO

--------------------------------------------------------------------------
--------------------------------------------------------------------------