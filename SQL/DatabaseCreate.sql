----------------------------------------------------------------------
--	Piotr Lewandowski - Creating database schema for HomeLibrary
----------------------------------------------------------------------


CREATE TABLE Books
	(
		BooksId				int IDENTITY(1,1) PRIMARY KEY,
		Title				varchar(200) NOT NULL,
		Author				varchar(200),
		Publisher			varchar(150),
		CreationTImestamp	datetime DEFAULT GETUTCDATE(),				
	)	

