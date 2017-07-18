SELECT p.[ИД_Отправление], a.[ФИО], t.[Название],
CASE
	WHEN t.[Ценность] = 1 THEN 'TRUE'
	WHEN t.[Ценность] = 0 THEN 'FALSE'
END [Ценность],
p.[Стоимость]
FROM [dbo].[Почтовое_отправление] AS p
INNER JOIN [dbo].[Тип_отправления] AS t ON t.[ИД_Тип] = p.[ИД_Тип]
INNER JOIN [dbo].[Адресат] AS a ON a.[ИД_Адресат] = p.[ИД_Адресат]
