CREATE PROCEDURE [dbo].[insertType]
	@name		TEXT,
	@maxWeight	REAL,
	@stdTariff	MONEY,
	@stdWeight  REAL,
	@addTariff	MONEY,
	@addWeight	REAL,
	@value		BIT,
	@costTariff	MONEY,
	@addCost    MONEY 
AS
	BEGIN TRAN
	INSERT INTO [dbo].[Тип_отправления]
           ([Название]
           ,[МаксВес]
           ,[СтандартТариф]
           ,[СтандартВес]
           ,[ДопТариф]
           ,[ДопВес]
           ,[Ценность]
           ,[ЦенТариф]
           ,[ДопЦен])
     VALUES (@name
			,@maxWeight
			,@stdTariff
			,@stdWeight
			,@addTariff
			,@addWeight
			,@value
			,@costTariff
			,@addCost)	

	IF(@stdWeight > @maxWeight)
	BEGIN
		ROLLBACK
		RAISERROR('[Стандарт. Вес] > [Макс. вес]',11,1)
		RETURN
	END
	IF(@addTariff >= @maxWeight)
	BEGIN
		ROLLBACK
		RAISERROR('[Доп. Вес] >= [Макс. вес]',11,1)
		RETURN
	END
	IF(@value = 1 AND (@costTariff = 0 OR @addCost = 0))
	BEGIN
		ROLLBACK
		RAISERROR('[Ценность] = True, [Цен. Тариф] = 0 OR [Доп. Цен.] = 0 ',11,1)
		RETURN
	END
	IF(@value = 0 AND (@costTariff > 0 OR @addCost > 0))
	BEGIN
		ROLLBACK
		RAISERROR('[Ценность] = False, [Цен. Тариф] > 0 OR [Доп. Цен.] > 0 ',11,1)
		RETURN
	END
	COMMIT
		
