CREATE TABLE [dbo].[Почтовое_отправление]
(

    [ИД_Отправление]    INT NOT NULL IDENTITY(1,1) PRIMARY KEY,
    [ИД_Адресат]        INT NOT NULL,
    [ИД_Тип]            INT NOT NULL,
    [ИД_Вложение]       INT DEFAULT NULL NULL,
	[Вес]				REAL DEFAULT 0 NOT NULL,
    [Стоимость]         MONEY DEFAULT 0 NOT NULL,
    FOREIGN KEY ([ИД_Адресат]) REFERENCES [Адресат]([ИД_Адресат]) 
        ON DELETE NO ACTION
        ON UPDATE NO ACTION,
    FOREIGN KEY ([ИД_Тип]) REFERENCES [Тип_отправления]([ИД_Тип]) 
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    FOREIGN KEY ([ИД_Вложение]) REFERENCES [Вложение]([ИД_Вложение]) 
        ON DELETE CASCADE
        ON UPDATE NO ACTION
)