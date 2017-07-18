CREATE FUNCTION [dbo].[typeTable]
(
	@id int
)
RETURNS TABLE
AS	
	RETURN (SELECT * FROM [dbo].[Тип_отправления] WHERE [ИД_Тип] = @id)

