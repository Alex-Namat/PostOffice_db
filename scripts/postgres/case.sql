SELECT 
p."ИД_Отправление",
a."ФИО",
t."Название",
CASE
WHEN t."Ценность" = true THEN 1
WHEN t."Ценность" = false THEN 0
END "Ценность",
p."Стоимость" 
FROM public."Почтовое_отправление" AS p
INNER JOIN public."Тип_отправления" AS t ON t."ИД_Тип" = p."ИД_Тип" 
INNER JOIN public."Адресат" AS a ON a."ИД_Адресат" = p."ИД_Адресат"