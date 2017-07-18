CREATE TABLE [dbo].[Вложение]
(
    [ИД_Вложение]    INT IDENTITY(1,1) PRIMARY KEY,
    [ИД_Адресат]     INT NOT NULL,
    [Общий_Вес]      REAL NOT NULL DEFAULT 0,
    [Общая_Ценность] MONEY NOT NULL DEFAULT 0,
    FOREIGN KEY ([ИД_Адресат]) REFERENCES [Адресат]([ИД_Адресат]) 
        ON DELETE CASCADE
        ON UPDATE CASCADE)
