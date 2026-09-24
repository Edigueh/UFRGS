-- CRIAR TABELAS AEROPORTOS
Create table aeroportos
(CODA	char(3) not null,
NOMEA 	varchar(20) not null,	
CIDADE 	varchar(20) not null,	
PAIS 	char(2) not null,
primary key(CODA));

insert into aeroportos values ('poa','salgado filho','porto alegre','BR');
insert into aeroportos values ('gru','guarulhos','sao paulo','BR');
insert into aeroportos values ('cgh','congonhas','sao paulo','BR');
insert into aeroportos values ('gal','galeao','rio de janeiro','BR');
insert into aeroportos values ('fra','frankfurt','frankfurt','AL');

-- CRIAR TABELAS VOOS

DROP TABLE voos
create table voos
(CODV	char(5)	 not null,	
ORIGEM 	char(3)	 not null,	
DEST	char(3)	 not null,
HORA	numeric not null,
primary key(codv),
foreign key(origem) references aeroportos,
foreign key(dest) references aeroportos);

insert into voos values ('GL230','gru','poa','7');
insert into voos values ('GL330','gru','poa','11');
insert into voos values ('GL430','poa','gru','14');
insert into voos values ('GL530','gru','gal','17');
insert into voos values ('GL531','gal','poa','11');
insert into voos values ('GL630','cgh','poa','7');
insert into voos values ('TM100','poa','cgh','9');
insert into voos values ('LF200','gal','fra','15');

-- USANDO ALIASES
-- 1) o código dos vôos que partem de gru e que chegam em poa. Elimine duplicados
SELECT DISTINCT CODV
FROM voos
WHERE (ORIGEM = 'gru' AND DEST = 'poa')
-- 2) o código dos vôos que partem do aeroporto guarulhos e que chegam no aeroporto salgado filho
SELECT v.codv
FROM voos AS v
JOIN aeroportos AS a_origem
ON v.origem = a_origem.coda
JOIN aeroportos AS a_dest
ON v.dest = a_dest.coda
WHERE a_origem.nomea = 'guarulhos' 
  AND a_dest.nomea = 'salgado filho'

-- CRIAR TABELA PILOTOS
 -- OBS: 
 -- a) supoe-se que a nacionalidade dos pilotos é a mesma da companhia para a qual trabalham
 -- b) observe nas instancias caixas altas (e.g. pais) e baixa (e.g. companhia, nome) 

DROP TABLE pilotos, escalacoes

Create table pilotos
(CODP		char(3) not null,
NOMEP		varchar(10) not null,	
SALARIO		numeric not null,	
GRATIFICACOES	numeric not null,		
TEMPO		numeric not null,	
PAIS		char(2) not null,
COMPANHIA	varchar(10) not null,
primary key(codp));

-- INSTANCIAR TABELA PILOTOS
insert into pilotos values ('p11','joao', 3000, 200, 5,'BR','gol');
insert into pilotos values ('p13','pedro', 2000, 100, 5,'BR','gol');
insert into pilotos values ('p12','paulo', 3000, 200, 3,'BR','gol');
insert into pilotos values ('p21','antonio', 1500, 300, 7,'BR','tam');
insert into pilotos values ('p22','carlos', 5000, 200, 10,'BR','tam');
insert into pilotos values ('p31','hanz', 5000, 1000, 6,'AL','lufthansa');
insert into pilotos values ('p41','roel', 5000, 2000, 5,'NL','klm');

-- CRIAR TABELAS ESCALAÇÕES (DE PILOTOS EM VOOS)
Create table escalacoes
(CODV	char(5) not null,	
DATA	char(5)	not null,
CODP	char(3),
AVIAO	varchar(10) not null,
primary key(codv, data),
foreign key (codp) references pilotos,
Foreign key (codv) references voos);

-- inserir instancias
insert into escalacoes values('GL230','01/05','p11','737'); 
insert into escalacoes values('GL230','01/06','p11','737');
insert into escalacoes values('TM100','01/05','p21','777');
insert into escalacoes values('LF200','01/05','p31','A320');
insert into escalacoes values('GL330','01/06','p12','737');
insert into escalacoes values('GL330','01/07','p12','777');
insert into escalacoes values('GL530','01/05','p12','777');
insert into escalacoes values('GL530','01/07',NULL,'777');

-- OPERAÇÕES DE CONJUNTO (UNION, INTERSECT, EXCEPT)

-- 3) A lista de todos os aeroportos onde vôos de 737 operam (nao interessa se é origem ou destino). Elimine duplicados.
SELECT DISTINCT a.nomea
FROM escalacoes e
JOIN voos v ON e.codv = v.codv
JOIN aeroportos a ON (a.coda = v.origem OR a.coda = v.dest)
WHERE e.aviao = '737';

SELECT nomea
FROM aeroportos a
JOIN voos v ON (v.origem = a.coda)
JOIN escalacoes e USING (codv)
WHERE e.aviao = '737'

UNION

SELECT nomea
FROM aeroportos a
JOIN voos v ON (v.dest = a.coda)
JOIN escalacoes e USING (codv)
WHERE e.aviao = '737'
-- 4) O código dos pilotos que voam de 777 e 737.
SELECT DISTINCT e.codp
FROM escalacoes e
WHERE (e.aviao = '777')

INTERSECT

SELECT DISTINCT e.codp
FROM escalacoes e
WHERE (e.aviao = '737')

-- Alternativa
SELECT DISTINCT e1.codp
FROM escalacoes e1
JOIN escalacoes e2 ON e1.codp = e2.codp
WHERE e1.aviao = '777' AND e2.aviao = '737'

SELECT DISTINCT e.codp
FROM escalacoes e
WHERE e.aviao = '737'
AND e.codp IN (
	SELECT e.codp
	FROM escalacoes e
	WHERE e.aviao = '777'
)

-- 5) O código dos pilotos que voam de 777 e não voam de 737.
SELECT DISTINCT e.codp
FROM escalacoes e
WHERE (e.aviao = '777') AND e.codp IS NOT NULL

EXCEPT

SELECT DISTINCT e.codp
FROM escalacoes e
WHERE (e.aviao = '737')

-- Alternativas
SELECT DISTINCT e1.codp
FROM escalacoes e1
LEFT JOIN escalacoes e2 ON e1.codp = e2.codp AND e2.aviao = '737'
WHERE e1.aviao = '777' AND e2.codp IS NULL AND e1.codp IS NOT NULL

SELECT DISTINCT e.codp
FROM escalacoes e
WHERE e.aviao = '777'
AND NOT e.codp IN (
	SELECT e.codp
	FROM escalacoes e
	WHERE e.aviao = '737'
)

-- MISTURANDO TUDO 

-- 6 Liste o código dos pilotos da companhia gol que já foram escalados para pilotar aeronaves 777. Elimine duplicados.
SELECT DISTINCT codp
FROM escalacoes
WHERE aviao = '777' AND codp IS NOT NULL
--7 Liste o nome dos pilotos brasileiros, o código do voo e a data da escalação dos pilotos, considerando apenas vôos com destino a Porto Alegre. Ordene por data e codigo de voo.
SELECT p.nomep, e.codv, e.data
FROM aeroportos a
JOIN voos v ON(a.coda = v.dest)
JOIN escalacoes e ON (e.codv = v.codv)
JOIN pilotos p ON (e.codp = p.codp)
WHERE a.cidade = 'porto alegre'
  AND p.pais = 'BR'
ORDER BY e.data, e.codv ASC

-- 8  Liste o código do piloto, o código do voo e o nome do aeroporto de destino das escalações de pilotos da companhia gol em voos cujo aeroporto de destino tem como código poa.
-- elimine duplicados, e ordene por nome de aeroporto
SELECT DISTINCT p.codp, v.codv, a.nomea
FROM pilotos p
JOIN escalacoes e ON p.codp = e.codp
JOIN voos v ON e.codv = v.codv
JOIN aeroportos a ON a.coda = v.dest
WHERE p.companhia = 'gol'
  AND v.dest = 'poa'
ORDER BY a.nomea ASC

--9 Liste o nome do piloto, o código do voo, o nome do aeroporto de origem e o nome do aeroporto de destino das escalações realizadas em aeronaves 777.
SELECT DISTINCT p.nomep, v.codv, a.nomea AS origem, a2.nomea AS destino
FROM pilotos p
JOIN escalacoes e  ON p.codp = e.codp
JOIN voos v        ON e.codv = v.codv
JOIN aeroportos a  ON a.coda = v.origem
JOIN aeroportos a2 ON a2.coda = v.dest
WHERE e.aviao = '777'

-- 10 O código de todos os aeroportos de/para onde pilotos da gol voam (origem e/ou destino) - sem duplicados no resultado.
SELECT DISTINCT a.coda
FROM pilotos p
JOIN escalacoes e  ON p.codp  = e.codp
JOIN voos v        ON e.codv  = v.codv
JOIN aeroportos a  ON a.coda  = v.origem OR a.coda = v.dest
WHERE p.companhia = 'gol'

-- Alternativa mais otimizada.

-- Busca os códigos de ORIGEM
SELECT v.origem AS coda
FROM pilotos p
JOIN escalacoes e ON p.codp = e.codp
JOIN voos v ON e.codv = v.codv
WHERE p.companhia = 'gol'

UNION

-- Busca os códigos de DESTINO
SELECT v.dest AS coda
FROM pilotos p
JOIN escalacoes e ON p.codp = e.codp
JOIN voos v ON e.codv = v.codv
WHERE p.companhia = 'gol';


-- 11 O código dos aeroportos que é destino de vôos em 737 e 777.
SELECT v.dest AS coda
FROM escalacoes e
JOIN voos v ON v.codv = e.codv
WHERE e.aviao = '737'

INTERSECT

SELECT v.dest AS coda
FROM escalacoes e
JOIN voos v ON v.codv = e.codv
WHERE e.aviao = '777';

-- Alternativa
SELECT v.dest AS coda
FROM escalacoes e
JOIN voos v ON v.codv = e.codv
WHERE e.aviao IN ('737', '777')
GROUP BY v.dest
HAVING COUNT(DISTINCT e.aviao) = 2;

-- 12 O código dos aeroportos que é destino apenas de vôos 777.
-- Destinos que recebem o 777
SELECT v.dest AS coda
FROM escalacoes e
JOIN voos v ON v.codv = e.codv
WHERE e.aviao = '777'

EXCEPT

-- Destinos que recebem QUALQUER OUTRO avião
SELECT v.dest AS coda
FROM escalacoes e
JOIN voos v ON v.codv = e.codv
WHERE e.aviao != '777';

SELECT DISTINCT v.dest AS coda
FROM escalacoes e
JOIN voos v ON v.codv = e.codv
WHERE e.aviao = '777'
  AND v.dest NOT IN (
      SELECT v2.dest
      FROM escalacoes e2
      JOIN voos v2 ON v2.codv = e2.codv
      WHERE e2.aviao != '777'
  );

SELECT v.dest AS coda
FROM escalacoes e
JOIN voos v ON v.codv = e.codv
GROUP BY v.dest
HAVING MIN(e.aviao) = '777' 
   AND MAX(e.aviao) = '777';