SELECT a.[��_��������],COUNT(*) [����������]
FROM [dbo].[��������] AS a, [dbo].[�������] AS i
WHERE i.[��_��������] = a.[��_��������]
GROUP BY a.[��_��������]
HAVING COUNT(*) > 1