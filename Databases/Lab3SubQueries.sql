-- Nome: André Schaidhauer Luckmann
-- Matrícula: 00601117

-- Base de Dados

-- Medico(crm, nomem, especialidade, idadem) - Representa dados de médicos
-- Paciente(pront, nomep, idadep) -  Representa dados de pacientes
-- Consulta(pront, crm, data) pront references paciente, crm references medico -- Representa dados de consultas médicas

-- Crie a base dados Hospital, com suas tabelas e instâncias.

drop Table if exists  consulta;
drop Table if exists  paciente;
drop Table if exists  medico;

create table paciente
(pront	char(2) not null,
nomep 	varchar(20) not null,	
idadep 	smallint not null,
primary key(pront));

create table medico
(crm		char(2) not null,
nomem		varchar(20) not null,	
especialidade varchar(15) not null,
idadem 	smallint not null,	
primary key(crm));

create table consulta
(pront	char(5)	 not null,	
crm 	char(3)	 not null,	
data	char(5)	 not null,
primary key(pront,crm,data),
foreign key (pront) references paciente,
foreign key (crm) references medico);

insert into paciente values ('p1','joao',7);
insert into paciente values ('p2','pedro',10);
insert into paciente values ('p3','maria',14);
insert into paciente values ('p4','jose',30);
insert into paciente values ('p5','marta',60);
insert into paciente values ('p6','paulo',65);

insert into medico values ('m1','ricardo','oftalmologia', 29);
insert into medico values ('m2','romualdo','pediatria', 24);
insert into medico values ('m3','roberto','pediatria', 35);
insert into medico values ('m4','sheila','endocrinologia', 22);
insert into medico values ('m5', 'paula', 'oftalmologia', 60);
insert into medico values ('m6', 'tereza', 'geriatria', 34);
insert into medico values ('m7', 'carla', 'pediatria', 45);

insert into consulta values ('p1','m2','01/01');
insert into consulta values ('p1','m2','01/02');
insert into consulta values ('p1','m3','01/02');
insert into consulta values ('p2','m2','01/01');
insert into consulta values ('p2','m3','01/02');
insert into consulta values ('p2','m1','01/02');
insert into consulta values ('p5','m4','01/02');
insert into consulta values ('p3', 'm2', '01/01');
insert into consulta values ('p4', 'm4', '01/01');
insert into consulta values ('p4', 'm1', '01/01');
insert into consulta values ('p4', 'm3', '01/01');
insert into consulta values ('p1', 'm5', '01/01');
insert into consulta values ('p1', 'm5', '01/02');
insert into consulta values ('p6', 'm5', '01/02');
insert into consulta values ('p6', 'm6', '01/02');
insert into consulta values ('p6', 'm6', '03/03');
insert into consulta values ('p1', 'm7', '04/04');
insert into consulta values ('p2', 'm7', '05/05');

-- Lab SQL 4 - Praticando subconsultas
-- Objetivos: Reconhecer situações que necessitam a resolução por subconsultas.


-- Questao 0  - RELEMBRANDO A CONSTRUCAO DE UMA CONSULTA USANDO SUBCONSULTAS (IN, EXISTS)
-- O nome dos médicos que atenderam pacientes no dia 01/02
-- a)	Resolver usando JOIN
select nomem
from medico natural join consulta
where data = '01/02'

-- b)	Resolver usando subconsulta conectada com o predicado IN
SELECT nomem
FROM medico
WHERE crm IN (SELECT crm FROM consulta WHERE data = '01/02')
-- c)	Resolver usando subconsulta conectada com o predicado EXISTS
SELECT nomem
FROM medico
WHERE EXISTS(SELECT crm FROM consulta WHERE data = '01/02' AND medico.crm = consulta.crm)

-- NAS PROXIMAS QUESTÕES, CONCENTRE-SE NAS PARTES ONDE A SUBCONSULTA É NECESSARIA. PARA AS DEMAIS PARTES, USE JOIN LIVREMENTE. O Objetivo é reconhecer a NECESSIDADE de subconsultas.

-- Cada questao é comparativa, para que note a necessidade de uso deste construto para formular a consulta.
-- Questão 1

-- 1 Compare
-- a) Some 1 à idade dos pacientes que têm mais de 60 anos 
UPDATE paciente
SET idadep = idadep + 1
WHERE idadep > 60
-- b) Some 1 à idade dos pacientes que foram atendidos na data 03/03
UPDATE paciente
SET idadep = idadep + 1
WHERE pront IN (
	SELECT pront
	FROM consulta
	WHERE data = '03/03'
)
SELECT * FROM paciente
-- 2 Compare
-- a) Remova as consultas que ocorreram na data 03/03
DELETE
FROM consulta
WHERE data = '03/03'
-- b) Remova as consultas que foram atendidas por médicos geriatras
DELETE
FROM consulta
WHERE crm IN (
	SELECT crm
	FROM medico
	WHERE especialidade = 'geriatria'
)
SELECT * FROM consulta
-- 3. Compare
-- a) a idade média dos pacientes
SELECT AVG(idadep)
FROM paciente
-- b) o crm dos médicos que atenderam pacientes mais velhos que a idade média dos pacientes
SELECT crm
FROM consulta
WHERE pront IN (
	SELECT pront
	FROM paciente
	WHERE idadep > (
		SELECT AVG(idadep)
		FROM paciente
	)
)
-- 4. O nome dos médicos que 
-- a. atenderam crianças (criança <= 12 anos)
SELECT DISTINCT nomem
FROM medico
JOIN consulta USING(crm)
JOIN paciente USING (pront)
WHERE idadep <= 12
-- b. não atenderam crianças
SELECT DISTINCT nomem
FROM medico
WHERE NOT EXISTS (
	SELECT crm
	FROM consulta
	JOIN paciente USING(pront)
	WHERE idadep <= 12 AND medico.crm = consulta.crm
)
-- c. atenderam crianças e adultos (adulto >=18)
SELECT DISTINCT nomem
FROM medico
WHERE crm IN (
	SELECT crm
	FROM consulta
	JOIN paciente USING(pront)
	WHERE idadep <= 12
) AND crm IN (
	SELECT crm
	FROM consulta
	JOIN paciente USING(pront)
	WHERE idadep > 12
)
-- c. só atenderam crianças
SELECT DISTINCT nomem
FROM medico
WHERE NOT EXISTS (
	SELECT crm
	FROM consulta
	JOIN paciente USING(pront)
	WHERE idadep > 12 AND medico.crm = consulta.crm
) AND EXISTS (
	SELECT crm
	FROM consulta
	JOIN paciente USING(pront)
	WHERE idadep <= 12 AND medico.crm = consulta.crm
)

-- 5. Compare
-- a. O nome dos pacientes que consultaram a endocrinologia
SELECT DISTINCT nomep
FROM paciente
JOIN consulta USING (pront)
JOIN medico USING (crm)
WHERE especialidade = 'endocrinologia'
-- b. O nome dos pacientes e das especialidades consultadas, para todos pacientes que foram 
-- atendidos pelo menos uma vez por um endocrinologista 
SELECT nomep, especialidade
FROM paciente
JOIN consulta USING (pront)
JOIN medico USING (crm)
WHERE consulta.crm IN (
	SELECT crm
	FROM medico
	WHERE medico.especialidade = 'endocrinologia' AND paciente.pront = consulta.pront
)
-- 6. O nome dos pacientes que foram atendidos por 
-- a) no mínimo 3 médicos distintos
SELECT nomep
FROM paciente
JOIN consulta USING (pront)
GROUP BY nomep, pront
HAVING COUNT(DISTINCT crm) >= 3
-- b) por médicos que atenderam pelo menos 3 pessoas distintas
SELECT DISTINCT nomep
FROM paciente
JOIN consulta USING (pront)
WHERE crm IN (
	SELECT crm
	FROM consulta
	JOIN medico USING (crm)
	GROUP BY crm
	HAVING COUNT(DISTINCT pront) >= 3
)
-- 7. O nome e idade dos médicos que são mais velhos que todos pacientes que atenderam
SELECT nomem, idadem
FROM medico
WHERE idadem > (
	SELECT MAX(idadep)
	FROM paciente
	JOIN consulta USING (pront)
	WHERE medico.crm = consulta.crm
)
-- 8. 
-- a) Para cada especialidade, a idade do paciente mais velho
SELECT especialidade, MAX(idadep)
FROM paciente
JOIN consulta USING (pront)
JOIN medico USING (crm)
GROUP BY especialidade
-- b) Para cada especialidade, a média da idade dos médicos
SELECT especialidade, AVG(idadem)
FROM medico
GROUP BY especialidade
-- b) O nome das especialidades cuja idade média dos médicos é menor que a idade do paciente 
-- mais velho que atenderam 
SELECT DISTINCT especialidade
FROM medico
GROUP BY especialidade, crm
HAVING AVG(idadem) < (
	SELECT MAX(idadep)
	FROM paciente
	JOIN consulta USING (pront)
	WHERE medico.crm = consulta.crm
)

-- 9. Compare
-- a. O nome dos médicos pediatras e o número de consultas que atendeu
SELECT nomem, COUNT((pront,crm,data))
FROM medico
JOIN consulta USING (crm)
WHERE especialidade = 'pediatria'
GROUP BY crm, nomem

-- b. O nome dos médicos e número total de consultas que atenderam, para todo o médico 
-- pediatra que atendeu pelo menos um paciente que consultou também outra especialidade
SELECT nomem, COUNT((pront,crm,data))
FROM medico
JOIN consulta C1 USING (crm)
WHERE especialidade = 'pediatria' AND pront IN (
	SELECT pront
	FROM consulta C2
	JOIN medico USING (crm)
	WHERE medico.especialidade != 'pediatria'
)
GROUP BY crm, nomem
