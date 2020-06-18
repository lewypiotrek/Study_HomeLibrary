----------------------------------------------------------------------
--	Piotr Lewandowski - Creating database schema for HomeLibrary
----------------------------------------------------------------------

USE [master];
GO

--------------------------------
-- CREATING DATABASE --
--------------------------------
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

--------------------------------
-- CREATING STORED PROCEDURES --
--------------------------------

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
				PublicationDate		varchar(8),
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
GO




-- CREATING DATABASE VIA PROCEDURE
USE HomeLibrary;
GO
EXEC DatabaseCreation;
GO


-- CREATING ShowBooks
--------------------------------

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
		Publisher LIKE '%'+ @Publisher + '%'
	ORDER BY
		Title
END
GO

--------------------------------
-- CREATING VIEWS --
--------------------------------

--PRINT 'Creating views...'

---- All active users
--CREATE VIEW MyCommunityView AS	
--	SELECT 
--		[Name] AS Name,
--		[Address],
--		[info] AS Information
--	FROM 
--		Community
--	WHERE
--		 isActive = 1;




---------------------
-- TESTING DATA
---------------------



DECLARE @Counter as INT = 1;
WHILE @Counter <= 25
BEGIN
	INSERT INTO Books (barcode,Title,Author,Publisher) 
	VALUES ('test' + CAST(@Counter as varchar),'test' +  CAST(@Counter as varchar),'test' +  CAST(@Counter as varchar),'test' +  CAST(@Counter as varchar))
	
	SET @Counter = @Counter + 1;
END;

-----------------------

--EXEC ShowBooks @Barcode = '', @Title = '', @Author = '', @Publisher = '', @Top = '10';