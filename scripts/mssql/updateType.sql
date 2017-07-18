CREATE PROCEDURE [dbo].[updateType]
	@id			INT, 
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
	UPDATE [dbo].[typeTable](@id)
	SET [Название] = @name
       ,[МаксВес] = @maxWeight
	   ,[СтандартТариф] = @stdTariff
	   ,[СтандартВес] = @stdWeight
       ,[ДопТариф] = @addTariff
       ,[ДопВес] = @addWeight
       ,[Ценность] = @value
       ,[ЦенТариф] = @costTariff
       ,[ДопЦен] = @addCost
	IF(@stdWeight > @maxWeight)
	BEGIN
		ROLLBACK
		RAISERROR('[Стандарт. Вес] > [Макс. вес]',11,2)
		RETURN
	END
	IF(@addTariff >= @maxWeight)
	BEGIN
		ROLLBACK
		RAISERROR('[Доп. Вес] >= [Макс. вес]',11,2)
		RETURN
	END
	IF(@value = 1 AND (@costTariff = 0 OR @addCost = 0))
	BEGIN
		ROLLBACK
		RAISERROR('[Ценность] = True, [Цен. Тариф] = 0 OR [Доп. Цен.] = 0 ',11,2)
		RETURN
	END
	IF(@value = 0 AND (@costTariff > 0 OR @addCost > 0))
	BEGIN
		ROLLBACK
		RAISERROR('[Ценность] = False, [Цен. Тариф] > 0 OR [Доп. Цен.] > 0 ',11,2)
		RETURN
	END
	COMMIT
