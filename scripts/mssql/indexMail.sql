CREATE UNIQUE NONCLUSTERED INDEX [ИД_Вложение]
ON [Почтовое_отправление]([ИД_Вложение])
WHERE [ИД_Вложение] IS NOT NULL
