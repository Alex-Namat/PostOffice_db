SELECT *
FROM [dbo].[Отделение_Связи]
WHERE [Индекс] = ANY
(SELECT [Индекс] FROM [dbo].[Адресат])