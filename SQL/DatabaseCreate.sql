----------------------------------------------------------------------
--	Piotr Lewandowski - Creating database schema for HomeLibrary
----------------------------------------------------------------------

CREATE PROCEDURE DatabaseCreation
AS
BEGIN

	IF NOT EXISTS (SELECT * FROM sys.tables WHERE [name] = 'Books')
	BEGIN

		CREATE TABLE Books
			(
				BooksId				int IDENTITY(1,1) PRIMARY KEY,
				Title				varchar(200) NOT NULL,
				Author				varchar(200),
				Publisher			varchar(150),
				CreationTImestamp	datetime DEFAULT GETUTCDATE(),				
			);

		PRINT 'Table Books has been created'
	END
	ELSE
		PRINT 'Table Books already exists'



END

