SELECT p.[��_�����������], a.[���], t.[��������],
CASE
	WHEN t.[��������] = 1 THEN 'TRUE'
	WHEN t.[��������] = 0 THEN 'FALSE'
END [��������],
p.[���������]
FROM [dbo].[��������_�����������] AS p
INNER JOIN [dbo].[���_�����������] AS t ON t.[��_���] = p.[��_���]
INNER JOIN [dbo].[�������] AS a ON a.[��_�������] = p.[��_�������]
