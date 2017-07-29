SELECT * 
FROM public."Почтовое_отделение" 
WHERE "Индекс" = ANY 
(SELECT "Индекс" FROM public."Адресат")