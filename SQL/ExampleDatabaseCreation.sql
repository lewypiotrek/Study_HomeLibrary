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
	
	INSERT INTO Notes (Title,Note)
	VALUES ('Test Note' + CAST(@Counter as varchar),'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin hendrerit urna dui, sed eleifend ligula dictum commodo. Suspendisse potenti. Aenean non ex nec diam elementum pharetra. Aliquam eget orci vehicula, blandit tellus nec, fringilla leo.' +  CAST(@Counter as varchar))

	SET @Counter = @Counter + 1;
END;
-----------------------
