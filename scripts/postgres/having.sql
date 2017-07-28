SELECT a."ИД_Вложение",COUNT(*) "Количество"
FROM public."Вложение" AS a, public."Предмет" AS i 
WHERE i."ИД_Вложение" = a."ИД_Вложение"
GROUP BY a."ИД_Вложение" HAVING COUNT(*) > 1