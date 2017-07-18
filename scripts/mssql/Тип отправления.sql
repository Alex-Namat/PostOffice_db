CREATE TABLE [dbo].[Тип_отправления]
(
	[ИД_Тип]			INT NOT NULL IDENTITY(1,1) PRIMARY KEY,
	[Название]			TEXT NOT NULL,
	[МаксВес]			REAL DEFAULT 0 NOT NULL,
	[СтандартТариф]	MONEY DEFAULT 0 NOT NULL,
	[СтандартВес]     REAL DEFAULT 0 NOT NULL
		CHECK ([СтандартВес] <= [МаксВес]),
	[ДопТариф]		MONEY DEFAULT 0 NOT NULL,
	[ДопВес]			REAL DEFAULT 0 NOT NULL
		CHECK ([ДопВес] <= [МаксВес]),
	[Ценность]			BIT DEFAULT 0 NOT NULL,
	[ЦенТариф]		MONEY DEFAULT 0 NOT NULL
		CHECK ( ([Ценность] = 1) OR ([ЦенТариф] = 0)),
	[ДопЦен]			    MONEY DEFAULT 0 NOT NULL
		CHECK ( ([Ценность] = 1) OR ([ДопЦен] = 0))
)
