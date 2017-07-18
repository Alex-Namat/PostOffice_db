CREATE TABLE [dbo].[Отделение_Связи]
(
    [Индекс]    INT NOT NULL PRIMARY KEY,
    [ИД_Отправление]   INT NOT NULL,
    FOREIGN KEY ([ИД_Отправление]) REFERENCES [Почтовое_отправление]([ИД_Отправление]) 
        ON DELETE CASCADE
        ON UPDATE CASCADE)
