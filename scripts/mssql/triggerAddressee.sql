CREATE TRIGGER [triggerAddressee]
	ON [dbo].[Адресат]
	INSTEAD OF DELETE
	AS
	BEGIN
		SET NOCOUNT ON
		DELETE FROM [dbo].[Почтовое_отправление] WHERE [ИД_Адресат] IN (SELECT [ИД_Адресат] FROM [deleted])
		DELETE FROM [dbo].[Адресат] WHERE [ИД_Адресат] IN (SELECT [ИД_Адресат] FROM [deleted])
	END
