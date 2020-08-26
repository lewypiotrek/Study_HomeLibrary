USE HomeLibrary;

---------------------
-- TESTING DATA
---------------------

DECLARE @Counter as INT = 1;
WHILE @Counter <= 25
BEGIN
	INSERT INTO Books (barcode,Title,Author,Publisher) 
	VALUES ('TestBarcode' + CAST(@Counter as varchar),'Test Title ' +  CAST(@Counter as varchar),'Test Author ' +  CAST(@Counter as varchar),'Test Publisher ' +  CAST(@Counter as varchar))

	INSERT INTO Community (Name,[Address],Info,isActive) 
	VALUES ('Test User' + CAST(@Counter as varchar),'Test Adddress ' +  CAST(@Counter as varchar),'Test info ' +  CAST(@Counter as varchar),1);
	
	SET @Counter = @Counter + 1;
END;
-----------------------


