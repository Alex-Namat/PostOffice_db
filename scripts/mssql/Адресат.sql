CREATE TABLE [dbo].[Адресат]
(
	[ИД_Адресат]    INT NOT NULL IDENTITY(1,1) PRIMARY KEY,
    [ФИО]           TEXT NOT NULL,
    [Индекс]        INT NOT NULL,
    [Город]         TEXT NOT NULL,
    [Улица]         TEXT NOT NULL,
    [Дом]           INT NOT NULL,
    [Корпус]        INT NULL,
    [Квартира]      INT NOT NULL
)
