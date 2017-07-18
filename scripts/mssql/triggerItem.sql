CREATE TRIGGER [triggerItem]
ON [dbo].[Предмет]
AFTER INSERT, UPDATE, DELETE
AS
BEGIN
	SET NOCOUNT ON;
	IF NOT EXISTS (SELECT TOP(1) * FROM [inserted])
	--DELETE
		UPDATE [dbo].[Вложение] 
		SET 
			[Общая_Ценность] = [dbo].[totalCost]([deleted].[ИД_Вложение]),
			[Общий_Вес] = [dbo].totalWeight([deleted].[ИД_Вложение])
		FROM [deleted]
		WHERE [Вложение].[ИД_Вложение] = [deleted].[ИД_Вложение]
	ELSE
	BEGIN
		IF EXISTS (SELECT TOP(1) * FROM [deleted])
		--UPDATE
		BEGIN
			IF UPDATE([ИД_Вложение])
			BEGIN
				UPDATE [dbo].[Вложение] 
				SET 
					[Общая_Ценность] = [dbo].[totalCost]([deleted].[ИД_Вложение]),
					[Общий_Вес] = [dbo].totalWeight([deleted].[ИД_Вложение])
				FROM [deleted]
				WHERE [Вложение].[ИД_Вложение] = [deleted].[ИД_Вложение]
			END
			UPDATE [dbo].[Вложение] 
			SET 
				[Общая_Ценность] = [dbo].[totalCost]([inserted].[ИД_Вложение]),
				[Общий_Вес] = [dbo].totalWeight([inserted].[ИД_Вложение])
			FROM [inserted]
			WHERE [Вложение].[ИД_Вложение] = [inserted].[ИД_Вложение]
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
END
