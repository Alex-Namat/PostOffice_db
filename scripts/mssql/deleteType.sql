CREATE PROCEDURE [dbo].[deleteType]
	@id int
AS
	DELETE FROM [dbo].[Тип_отправления] WHERE [ИД_Тип] = @id