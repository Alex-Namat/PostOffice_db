CREATE FUNCTION 
	[dbo].[totalCost](	@id int)
RETURNS MONEY
AS
BEGIN
	DECLARE @sum MONEY
	SET @sum = (
				SELECT SUM([Ценность] * [Количество]) 
				FROM [dbo].[Предмет]
				WHERE @id = [ИД_Вложение]
				)
	RETURN ISNULL(@sum,0)
END
