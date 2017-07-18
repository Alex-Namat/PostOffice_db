CREATE FUNCTION
	[dbo].[totalWeight] ( @id INT)
RETURNS REAL
AS
BEGIN
	DECLARE @sum REAL
	SET @sum = (
				SELECT SUM([Вес] * [Количество]) 
				FROM [dbo].[Предмет]
				WHERE @id = [ИД_Вложение]
				)
	RETURN ISNULL(@sum,0)
END
