-- Nome: André Schaidhauer Luckmann
-- Matrícula: 00601117

-- CRIAR TABELA PILOTOS
-- OBS:
-- a) supoe-se que a nacionalidade dos pilotos é a mesma da companhia para a qual trabalham
-- b) observe nas instancias caixas altas (e.g. pais) e baixa (e.g. companhia, nome)
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

-- PRATICAR CLAUSULA SELECT/WHERE/ORDER BY
-- 1) Listar o nome das companhias aéreas. ordenar os resultados alfabeticamente.
SELECT companhia AS c
FROM pilotos
ORDER BY c ASC
-- 2) Selecionar o nome e a companhia dos pilotos brasileiros. Ordenar os resultados em ordem alfabética.
SELECT nomep AS nome, companhia
FROM pilotos
WHERE pais = 'BR'
ORDER BY nome, companhia ASC

-- 3) Selecionar o nome das companhias e seu pais, para companhias que pagam menos que 3000 a pelo menos um de seus pilotos. Elimine duplicados
SELECT DISTINCT companhia, pais
FROM pilotos
WHERE salario < 3000

-- CRIAR TABELAS ESCALAÇÕES (DE PILOTOS EM VOOS)
Create table escalacoes
(CODV	char(5) not null,	
DATA	char(5)	not null,
CODP	char(3),
AVIAO	varchar(10) not null,
primary key(codv, data),
foreign key (codp) references pilotos);

-- inserir instancias
insert into escalacoes values('GL230','01/05','p11','737');
insert into escalacoes values('GL230','01/06','p11','737');
insert into escalacoes values('TM100','01/05','p21','777');
insert into escalacoes values('LF200','01/05','p31','A320');
insert into escalacoes values('GL330','01/06','p12','737');
insert into escalacoes values('GL330','01/07','p12','777');
insert into escalacoes values('GL530','01/05','p12','777');
insert into escalacoes values('GL530','01/07',NULL,'777');

-- PRATICAR CLAUSULA WHERE
-- 4) listar o código dos vôos com pilotos escalados. Elimine duplicados.
SELECT DISTINCT codv
FROM escalacoes
WHERE codp IS NOT NULL
--5) Todos os vôos que iniciam com código GL. Elimine duplicados e ordenar decrescente.
SELECT DISTINCT *
FROM escalacoes
WHERE codv LIKE 'GL%'
ORDER BY codv DESC

-- PRATICAR CLAUSULA FROM
-- 6 ) Listar o nome dos pilotos, o voo para o qual estão escalados, e o respectivo aviao. Eliminar duplicados e ordenar por aviao.
-- Fazer esta consulta em 3 versões alternativas
-- A) junçao com CLÁUSULA ON
SELECT DISTINCT 
p.nomep AS nome,
e.codv AS voo,
e.aviao
FROM pilotos AS p JOIN escalacoes AS e ON (p.codp = e.codp)
ORDER BY aviao DESC
-- B) juncao com CLÁUSULA USING
SELECT DISTINCT
p.nomep AS nome,
e.codv AS voo,
e.aviao
FROM pilotos AS p JOIN escalacoes AS e USING (codp)
ORDER BY aviao DESC
-- C) junçao JOIN natural
SELECT DISTINCT
p.nomep AS nome,
e.codv AS voo,
e.aviao
FROM pilotos AS p NATURAL JOIN escalacoes AS e
ORDER BY aviao DESC

-- OBS: nas próximas consultas, use a sintaxe de tabela de junçao que preferir ou que for necessária.
-- 7 ) Listar o código dos vôos para os quais pilotos nao brasileiros foram escalados, junto com o nome do respectivo piloto. Elimine duplicados.
SELECT DISTINCT
p.nomep AS nome,
e.codv AS voo,
e.aviao
FROM pilotos AS p JOIN escalacoes AS e USING (codp)
WHERE p.pais != 'BR'

-- 8) Listar os pilotos (nome), código de vôo com a respectivas aeronaves para as quais estão escalados. Eliminar os duplicados, e ordene por piloto/voo.
-- Fazer a consulta nas seguintes versoes
-- a) somente os pilotos escalados vão para o resultado
SELECT DISTINCT
p.nomep AS nome,
e.codv AS voo,
e.aviao
FROM pilotos AS p RIGHT JOIN escalacoes AS e USING (codp)
WHERE p.nomep IS NOT NULL
ORDER BY nome, voo ASC
-- b) todos os pilotos, escalados ou não, vao para o resultado 
SELECT DISTINCT
p.nomep AS nome,
e.codv AS voo,
e.aviao
FROM pilotos AS p LEFT JOIN escalacoes AS e USING (codp)
WHERE p.nomep IS NOT NULL
ORDER BY nome, voo ASC
-- c) todos os vôos vão para o resultado, que hajam pilotos escalados ou nao 
SELECT DISTINCT
p.nomep AS nome,
e.codv AS voo,
e.aviao
FROM pilotos AS p RIGHT JOIN escalacoes AS e USING (codp)
ORDER BY nome, voo ASC
-- d) todos os vôos e todos os pilotos vão para o resultado, mesmo pilotos não escalados e escalacoes sem piloto
SELECT DISTINCT
p.nomep AS nome,
e.codv AS voo,
e.aviao
FROM pilotos AS p FULL JOIN escalacoes AS e USING (codp)
ORDER BY nome, voo ASC

-- CRIAR TABELAS VOOS

create table voos
(CODV	char(5)	 not null,	
ORIGEM 	char(3)	 not null,	
DEST	char(3)	 not null,
HORA	numeric not null,
primary key(codv));

insert into voos values ('GL230','gru','poa','7');
insert into voos values ('GL330','gru','poa','11');
insert into voos values ('GL430','poa','gru','14');
insert into voos values ('GL530','gru','gal','17');
insert into voos values ('GL531','gal','poa','11');
insert into voos values ('GL630','cgh','poa','7');

-- PRATICAR A ESCOLHA DE TABELAS
-- 9) os aviões usados em vôos escalados que partem do aeroporto de código gru. Eliminar duplicados.
SELECT DISTINCT
e.aviao
FROM escalacoes AS e JOIN voos as v USING (codv)
WHERE v.ORIGEM = 'gru'
-- 10) o nome dos pilotos que voam a partir do aeroporto gru
SELECT DISTINCT
p.nomep as nome
FROM (escalacoes AS e JOIN voos as v USING (codv)) NATURAL JOIN pilotos AS p 
WHERE v.ORIGEM = 'gru'