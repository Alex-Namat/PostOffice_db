CREATE TRIGGER [triggerMail]
	ON [dbo].[Почтовое_отправление]
	AFTER INSERT, UPDATE
	AS
	BEGIN
		SET NOCOUNT ON
		DECLARE @idType			INT,
				@maxWeight		REAL,
				@stdWeight		REAL,
				@value			BIT,
				@address		INT,
				@totalWeight	REAL,
				@totalCost		MONEY
		DECLARE cursorMail CURSOR LOCAL STATIC READ_ONLY
		FOR (
			SELECT TOP(1) 
					t.[ИД_Тип],
					[МаксВес],
					[СтандартВес],
					[Ценность],
					a.[ИД_Адресат],
					[Общий_Вес],
					[Общая_Ценность]
			FROM [inserted] AS i
			INNER JOIN [dbo].[Тип_отправления] AS t ON t.[ИД_Тип] = i.[ИД_Тип]
			LEFT JOIN [dbo].[Вложение] AS a ON a.[ИД_Вложение] = i.[ИД_Вложение]
			)
		OPEN cursorMail
		FETCH FIRST FROM cursorMail
		INTO @idType,@maxWeight,@stdWeight,@value,@address,@totalWeight,@totalCost

		IF EXISTS (SELECT TOP(1) [ИД_Вложение] FROM [inserted] WHERE [ИД_Вложение] IS NOT NULL)
		BEGIN 
			IF(@value = 1)
				BEGIN
					IF NOT EXISTS(
						SELECT TOP(1) [ИД_Адресат]
						FROM [inserted]
						WHERE [ИД_Адресат] = @address
						)
					BEGIN
						ROLLBACK TRAN
						RAISERROR('[Почтовое отправление].[ИД Адресат] != [Вложение].[ИД Адресат]',11,1)
						RETURN
					END
					IF(@totalWeight <= @maxWeight)
						IF(@totalWeight = 0)
							UPDATE [dbo].[Почтовое_отправление]
							SET [Вес] = @stdWeight,
								[Стоимость] = [dbo].[cost](@idType,@totalWeight,@totalCost)
							WHERE [ИД_Отправление] IN (SELECT TOP(1) [ИД_Отправление] FROM [inserted])	
						ELSE
							UPDATE [dbo].[Почтовое_отправление]
							SET [Вес] = @totalWeight,
								[Стоимость] = [dbo].[cost](@idType,@totalWeight,@totalCost)
							WHERE [ИД_Отправление] IN (SELECT TOP(1) [ИД_Отправление] FROM [inserted])
					ELSE 
					BEGIN
						ROLLBACK TRAN
						RAISERROR('[Вложение].[Общий вес] > [Тип отправления].[Макс. вес]',11,1)
						RETURN
					END
				END
			ELSE
			BEGIN
				ROLLBACK TRAN
				RAISERROR('[Тип отправления].[Ценность] - False, [Почтовое отправление].[ИД Вложение] - NOT NULL',11,1)
				RETURN
			END
		END
		ELSE
			IF(@value = 0)
			BEGIN
				DECLARE @weight REAL
				SELECT TOP(1) @weight = [Вес] FROM [inserted]
				IF (@weight = 0)
					UPDATE [dbo].[Почтовое_отправление]
					SET [Вес] = @stdWeight
					WHERE [ИД_Отправление] IN (SELECT TOP(1) [ИД_Отправление] FROM [inserted])	
				IF (@weight > @maxWeight)	
				BEGIN
					ROLLBACK TRAN
					RAISERROR('[Вес] > [Тип отправления].[Макс. вес]',11,1)
					RETURN
				END
				UPDATE [dbo].[Почтовое_отправление]
				SET [Стоимость] = [dbo].[cost](@idType,@weight,0)
				WHERE [ИД_Отправление] IN (SELECT TOP(1) [ИД_Отправление] FROM [inserted])	
			END
			ELSE 
			BEGIN
				ROLLBACK TRAN
				RAISERROR('[Тип отправления].[Ценность] - True, [Почтовое отправление].[ИД Вложение] - NULL',11,1)
				RETURN
			END

		CLOSE cursorMail
		DEALLOCATE cursorMail
	END
	