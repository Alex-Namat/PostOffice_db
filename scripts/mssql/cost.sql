CREATE FUNCTION [dbo].[cost]
(
	@idType		INT,
	@weight		REAL,
	@totalValue	MONEY
)
RETURNS MONEY
AS
BEGIN
	DECLARE @cost MONEY,
			@w	 REAL
	DECLARE @stdTariff  MONEY,
			@stdWeight	REAL,
			@addTariff	MONEY,
			@addWeight	MONEY,
			@value		BIT,
			@priceTariff	MONEY,
			@addPrice		MONEY
	SELECT	@stdTariff = [СтандартТариф],
			@stdWeight = [СтандартВес],
			@addTariff = [ДопТариф],
			@addWeight = [ДопВес],
			@value = [Ценность],
			@priceTariff = [ЦенТариф],
			@addPrice = [ДопЦен]
	FROM [dbo].[Тип_отправления] WHERE [ИД_Тип] = @idType 

	SET @w = @weight - @stdWeight
	SET @cost = @stdTariff
	IF (@w > 0) 
	BEGIN
		SET @w = CEILING(@w/@addWeight)
		SET @cost += @addTariff * @w
	END
	IF (@value = 1) 
		SET @cost += @priceTariff * CEILING(@totalValue/@addPrice)
	RETURN ISNULL(@cost,0)
END
