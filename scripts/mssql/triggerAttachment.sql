CREATE TRIGGER [triggerAttachment]
	ON [dbo].[Вложение]
	AFTER INSERT, UPDATE
	AS
	BEGIN
	SET NOCOUNT ON
	IF EXISTS (SELECT TOP(1) * FROM [deleted])
	BEGIN
	--UPDATE
		IF EXISTS(SELECT TOP(1)  *
				  FROM [dbo].[Почтовое_отправление], [inserted]
				  WHERE [Почтовое_отправление].[ИД_Вложение] = [inserted].[ИД_Вложение]
				  )
		BEGIN
			IF UPDATE([ИД_Адресат])
				IF NOT EXISTS(
						SELECT TOP(1) *
						FROM  [inserted]
						WHERE [inserted].[ИД_Адресат] IN
							(SELECT [Почтовое_отправление].[ИД_Адресат]
							 FROM [dbo].[Почтовое_отправление]
							 WHERE [Почтовое_отправление].[ИД_Вложение] = [inserted].[ИД_Вложение])
						)
				BEGIN
					ROLLBACK TRAN
					RAISERROR('[Вложение].[ИД Адресат] != [Почтовое отправление].[ИД Адресат]',11,1)
					RETURN
				END
			UPDATE [dbo].[Почтовое_отправление]
			SET
				[Вес] = [inserted].[Общий_Вес],
				[Стоимость] = [dbo].[cost](
					(SELECT [ИД_Тип]
					 FROM [dbo].[Почтовое_отправление]
					 WHERE [Почтовое_отправление].[ИД_Вложение] = [inserted].[ИД_Вложение]),
					 [inserted].[Общий_Вес],
					 [inserted].[Общая_Ценность]
				)
			FROM [inserted]
			WHERE [Почтовое_отправление].[ИД_Вложение] = [inserted].[ИД_Вложение]
		END
	END
	ELSE
	--INSERT
		UPDATE [dbo].[Вложение]
		SET
			[Общая_Ценность] = [dbo].[totalCost]([inserted].[ИД_Вложение]),
			[Общий_Вес] = [dbo].totalWeight([inserted].[ИД_Вложение])
		FROM [inserted]
		WHERE [Вложение].[ИД_Вложение] = [inserted].[ИД_Вложение]
	END
