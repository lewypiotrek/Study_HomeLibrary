USE HomeLibrary;

---------------------
-- TESTING DATA
---------------------

DECLARE @Counter as INT = 1;
WHILE @Counter <= 25
BEGIN
	INSERT INTO Books (barcode,Title,Author,Publisher) 
	VALUES ('TestBarcode' + CAST(@Counter as varchar),'Test Title ' +  CAST(@Counter as varchar),'Test Author ' +  CAST(@Counter as varchar),'Test Publisher ' +  CAST(@Counter as varchar))
	
	SET @Counter = @Counter + 1;
END;
-----------------------


