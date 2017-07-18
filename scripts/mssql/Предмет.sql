CREATE TABLE [dbo].[Предмет]
(
	[ИД_Предмет]    INT NOT NULL IDENTITY(1,1) PRIMARY KEY,
    [ИД_Вложение]   INT NOT NULL,
    [Название]      TEXT NOT NULL,
    [Количество]    INT NOT NULL DEFAULT 1 ,
    [Ценность]      MONEY NOT NULL DEFAULT 0 ,
    [Вес]           REAL NOT NULL DEFAULT 0,
    FOREIGN KEY ([ИД_Вложение]) REFERENCES [Вложение]([ИД_Вложение]) 
        ON DELETE CASCADE
        ON UPDATE NO ACTION
)
