-- Matricula 00601117
-- Nome: André Schaidhauer Luckmann
drop table if exists alocacoes;
drop table if exists projetos;
drop table if exists funcionarios;

create table projetos
(codp char(2) not null primary key,
nomep varchar(50) not null,
linguagem varchar(20),
custo numeric not null,
cliente varchar(30));

insert into projetos values ('p1', 'projeto1', 'python', 300000, 'cli1');
insert into projetos values ('p2', 'projeto2', 'python', 400000, 'cli1');
insert into projetos values ('p3', 'projeto3', 'cobol', 400000, 'cli1');
insert into projetos values ('p4', 'projeto4', 'java', 200000, 'cli2');
insert into projetos values ('p5', 'projeto5', 'java', 50000, 'cli2');
insert into projetos values ('p6', 'projeto6', 'java', 200000, 'cli3');
insert into projetos values ('p7', 'projeto7', NULL, 50000, 'cli3');

-- ====================
-- Funções de sumarização min, max, sum e avg
-- a)	Considerando os projetos do cliente cli1, o custo do projeto mais barato, 
-- mais caro, a médio do custo dos projetos, e o custo total de todos seus projetos
select
MIN(custo) custo_proj_mais_barato,
MAX(custo) custo_proj_mais_caro,
AVG(custo) custo_medio_proj,
SUM(custo) custo_total_projs
from projetos 
where cliente = 'cli1';

-- ====================
-- Função count: count(*) vs count(atributo) vs count(distinct atributo)
-- b)	Considerando os projetos do cliente cli3, o número de projetos e de linguagens usadas
select
COUNT(*) numero_projs,
COUNT(codp) numer_projs,
COUNT(DISTINCT codp) n_projs,
COUNT(linguagem) numer_langs,
COUNT(DISTINCT linguagem) n_langs
from projetos
where cliente = 'cli3';


-- c)	considerando os projetos em java, o número de projetos e o número de clientes envolvidos
select
COUNT(codp) num_projs_java,
COUNT(DISTINCT cliente) clientes_envolvidos_projs_java
from projetos
where linguagem = 'java';

-- ====================
--	Cláusula group by
-- d)	Para cada linguagem, o número de projetos, o custo do projeto mais barato e mais caro. 
select
linguagem,
COUNT(codp) num_projs,
MAX(custo) proj_mais_caro,
MIN(custo) proj_mais_barato
from projetos
GROUP BY linguagem;

-- e)	para cada cliente, o custo total de seus projetos em java
select
cliente,
SUM(custo) custo_total_proj_java
from projetos
where linguagem = 'java'
GROUP BY cliente;

-- ====================
-- 	Cláusula Where vs Having
-- f)	considerando apenas projetos de no mínimo 100000, para cada cliente que tem projetos 
-- em mais de uma linguagem, o nome do cliente, e o número de projetos.
-- HAVING sempre deve ser acompanhado de uma função de agregação!
select
cliente,
COUNT(codp) num_projs
from projetos
where custo >= 100000
GROUP BY cliente
HAVING COUNT(codp) > 1;

-- g)	considerando apenas projetos em java, o nome do cliente e custo total de seus projetos, 
-- desde que o cliente só tenha projetos com custo acima de 100000.
-- HAVING sempre deve ser acompanhado de uma função de agregação!
select
cliente,
SUM(custo) custo_total_projs
from projetos
where linguagem = 'java'
GROUP BY cliente
HAVING MIN(custo) > 100000;


-- ===== ESCOLHENDO TABELAS
-- considere funcionários que são alocados em projetos (tabelas funcionarios e alocacoes)
create table funcionarios
(codf char(2) not null primary key,
nomef varchar(10) not null,
salario numeric not null);

insert into funcionarios values ('f1', 'maria', 10000);
insert into funcionarios values ('f2', 'pedro', 5000);
insert into funcionarios values ('f3', 'carlos', 7000);
insert into funcionarios values ('f4', 'pedro', 15000);

create table alocacoes
(codp char(2) not null references projetos,
codf char(2) not null references funcionarios,
horas numeric not null,
funcao varchar(15),
primary key (codp, codf));

insert into alocacoes values ('p1', 'f1', 10, 'programador');
insert into alocacoes values ('p1', 'f2', 20, 'analista');
insert into alocacoes values ('p2', 'f1', 15, 'programador');
insert into alocacoes values ('p2', 'f2', 20, 'analista');
insert into alocacoes values ('p4', 'f1', 5, 'analista');
insert into alocacoes values ('p5', 'f3', 10, 'programador');
insert into alocacoes values ('p4', 'f4', 10, 'programador');
insert into alocacoes values ('p3', 'f2', 10, 'programador');
insert into alocacoes values ('p3', 'f4', 5, 'programador');

-- Escolhendo as tabelas
-- h)	Para cada projeto em python, o nome do projeto, o número de pessoas trabalhando e o total de horas alocadas
SELECT
nomep,
COUNT(DISTINCT codf) num_pessoas_trabalhando,
SUM(horas) horas_alocadas
FROM projetos
JOIN alocacoes USING(codp)
WHERE linguagem = 'python'
GROUP BY codp


-- i)	Para cada funcionário, seu nome, e o número de projetos e de horas que trabalha
SELECT
nomef,
COUNT(DISTINCT codp) num_projs,
SUM(horas) horas_de_trabalho
FROM funcionarios
JOIN alocacoes USING (codf)
GROUP BY codf

-- j)	Para cada projeto, o número de pessoas alocadas (listar todos os projetos, mesmo os sem funcionarios alocados)
SELECT
codp,
COUNT(DISTINCT codf) pessoas_alocadas
FROM alocacoes
GROUP BY codp
-- k)	Considerando apenas os programadores, listar o nome do funcionário,
-- número de projetos nos quais trabalha nesta função, e número de clientes
SELECT
nomef,
COUNT(DISTINCT codp) numero_projetos,
COUNT(DISTINCT cliente) numero_clientes
FROM funcionarios
JOIN alocacoes USING (codf)
JOIN projetos USING (codp)
WHERE funcao = 'programador'
GROUP BY codf

-- Complicando
-- l)	listar o nome dos funcionários que exercem diferentes funções, e o número de projetos onde trabalham
SELECT
nomef,
COUNT(DISTINCT codp) num_projs
FROM funcionarios
JOIN alocacoes USING (codf)
GROUP BY codf
HAVING COUNT(DISTINCT funcao) > 1
-- m)	 listar o nome dos funcionários que exercem diferentes funções, o número de projetos onde trabalham e o número de clientes para os quais trabalham
SELECT
nomef,
COUNT(DISTINCT codp) num_projs,
COUNT(DISTINCT cliente) num_clientes
FROM funcionarios
JOIN alocacoes USING (codf)
JOIN projetos USING (codp)
GROUP BY codf
HAVING COUNT(DISTINCT funcao) > 1
-- n)	 listar o nome dos funcionários cujos projetos envolvem todos a mesma linguagem
SELECT
nomef
FROM funcionarios
JOIN alocacoes USING (codf)
JOIN projetos USING (codp)
GROUP BY codf
HAVING COUNT(DISTINCT linguagem) = 1
-- o)	 listar o nome dos funcionários que trabalham para um único cliente
SELECT
nomef
FROM funcionarios
JOIN alocacoes USING (codf)
JOIN projetos USING (codp)
GROUP BY codf
HAVING COUNT(DISTINCT cliente) = 1
-- p)	listar o nome dos funcionários cujos projetos são todos para clientes distintos
SELECT
nomef
FROM funcionarios
JOIN alocacoes USING (codf)
JOIN projetos USING (codp)
GROUP BY codf, nomef
HAVING (COUNT(DISTINCT cliente) = COUNT(codp))
