-- Nome: André Schaidhauer Luckmann
-- Matrícula: 00601117
drop table if exists matricula;
drop table if exists aluno ;
drop table if exists professor;

create table aluno
(coda char(3) not null primary key,
nomea varchar(30) not null);

create table professor
(codp char(3) not null primary key,
nomep varchar(20) not null);

create table matricula
(coda char(3) not null,
codd char(3) not null,
codp char(3) not null,
nota int,
primary key (coda,codd),
foreign key(coda) references aluno,
foreign key (codp) references professor);

insert into aluno values ('a1', 'joao');
insert into aluno values ('a2', 'maria');
insert into aluno values ('a3', 'aline');
insert into aluno values ('a4', 'pedro');
insert into aluno  values ('a5', 'xico');

insert into professor values ('p1', 'jose');
insert into professor values ('p2', 'marta');
insert into professor values ('p3', 'paulo');
insert into professor values ('p4', 'zeca');
insert into professor values ('p5', 'carlos');

insert into matricula values ('a1', 'd1', 'p1', 7);
insert into matricula values ('a1', 'd2', 'p1', 8);
insert into matricula values ('a2', 'd1', 'p2', 10);
insert into matricula values ('a2', 'd2', 'p2', 10);
insert into matricula values ('a3', 'd1', 'p3', 8);
insert into matricula values ('a3', 'd3', 'p3', 8);
insert into matricula values ('a4', 'd3', 'p4', 8);
insert into matricula values ('a4', 'd4', 'p4', 8);
insert into matricula values ('a5', 'd1', 'p5', 7);
insert into matricula values ('a5', 'd2', 'p5', 8);
insert into matricula values ('a5', 'd3', 'p5', 10);

-- O código das disciplinas cursadas por joao (pelo menos uma vez).
Select distinct codd
From aluno natural join matricula
Where nomea = 'joao';

-- o nome dos alunos, o código das disciplinas cursadas e a nota tirada, considerando apenas disciplinas que foram cursadas por joao
Select distinct nomea, codd, nota
From aluno natural join matricula
Where nomea <> 'joao' and
codd IN (
	select distinct codd
	From aluno natural join matricula
	Where nomea = 'joao'
);

Select distinct nomea, codd, nota
From aluno natural join matricula MEXT
Where nomea <> 'joao' and
EXISTS (
	select distinct codd
	From aluno natural join matricula MINT
	Where nomea = 'joao' and MINT.codd = MEXT.codd
);

-- o nome dos alunos, o código das disciplinas cursadas e a nota tirada, considerando apenas disciplinas que não foram cursadas por joao
Select distinct nomea, codd, nota
From aluno natural join matricula
Where codd NOT IN (
	select distinct codd
	From aluno natural join matricula
	Where nomea = 'joao'
);

Select distinct nomea, codd, nota
From aluno natural join matricula MEXT
Where NOT EXISTS (
	select distinct codd
	From aluno natural join matricula MINT
	Where nomea = 'joao' and MINT.codd = MEXT.codd
);

-- Q1: Um mesmo aluno pode aparecer nos resultados das duas consultas? Por quê?
-- Sim, pois pode haver alunos que cursaram tanto disciplinas que João cursou quanto disciplinas que João não cursou. Existindo nos dois conjuntos.

-- quem não cursou nenhuma disciplina cursada por joao: pedro
-- quem cursou todas as disciplinas cursadas por joao (e talvez outras): maria e xico
-- quem cursou exatamente as mesmas disciplinas cursadas por joao (nem mais, nem menos) -- maria

-- Alunos que não cursaram nenhuma disciplina cursada por João
SELECT nomea
FROM aluno a1
WHERE NOT EXISTS (
	-- intersecção com IN
	SELECT coda
	FROM matricula
	WHERE coda = a1.coda
	AND codd IN (
		SELECT codd
		FROM aluno NATURAL JOIN matricula
		WHERE nomea = 'joao'
	)
);

-- Alunos que não cursaram nenhuma disciplina cursada por João
SELECT nomea
FROM aluno a1
WHERE NOT EXISTS (
	-- intersecção com intersect
	SELECT codd
	FROM matricula
	WHERE coda = a1.coda
	
	INTERSECT
	
	SELECT codd
	FROM aluno NATURAL JOIN matricula
	WHERE nomea = 'joao'
);

-- Alunos que não cursaram nenhuma disciplina cursada por João
SELECT nomea
FROM aluno a1
WHERE NOT EXISTS (
	-- intersecção com EXISTS
	SELECT codd
	FROM matricula MEXT
	WHERE coda = a1.coda and
	EXISTS (
		SELECT *
		FROM aluno NATURAL JOIN matricula MINT
		WHERE nomea = 'joao' and MINT.codd = MEXT.codd
	)
);

-- O nome dos alunos que cursaram TODAS as disciplinas cursadas por joao.
Select nomea
From aluno a1
Where nomea <> 'joao' and
not exists (
	select coda
	From matricula natural join aluno
	Where nomea = 'joao' and
	codd NOT IN (
		select distinct codd
		From matricula
		Where coda = a1.coda
	)
);

-- O nome dos alunos que cursaram EXATAMENTE as mesmas disciplinas cursadas por joao
Select nomea
From aluno a1
Where nomea <> 'joao' and
not exists (
	select coda
	From matricula natural join aluno
	Where nomea = 'joao' and
	codd NOT IN (
		select distinct codd
		From matricula
		Where coda = a1.coda
	)
) and not exists (
	select coda
	From matricula
	Where coda = a1.coda and
	codd NOT IN (
		select distinct codd
		From aluno natural join matricula
		Where nomea = 'joao'
	)
);

-- Q2 – Desenvolva as consultas para os enunciados abaixo:
-- O código das disciplinas que jose ministrou
SELECT codd
FROM matricula
JOIN professor USING(codp)
WHERE nomep = 'jose'

-- O código das disciplinas com os respectivos professores, para disciplinas que jose também ministra.
SELECT codd, nomep
FROM matricula m_ext
JOIN professor USING(codp)
WHERE nomep <> 'jose' AND codd IN (
	SELECT codd
	FROM matricula m_int
	JOIN professor USING(codp)
	WHERE nomep = 'jose'
)

SELECT codd, nomep
FROM matricula m_ext
JOIN professor USING(codp)
WHERE nomep <> 'jose' AND EXISTS (
	SELECT codd
	FROM matricula m_int
	JOIN professor USING(codp)
	WHERE nomep = 'jose' AND m_ext.codd = m_int.codd
)

-- O código das disciplinas com os respectivos professores, para disciplinas que jose não ministra.
SELECT codd, nomep
FROM matricula m_ext
JOIN professor USING(codp)
WHERE nomep <> 'jose' AND codd NOT IN (
	SELECT codd
	FROM matricula m_int
	JOIN professor USING(codp)
	WHERE nomep = 'jose'
)

SELECT codd, nomep
FROM matricula m_ext
JOIN professor USING(codp)
WHERE nomep <> 'jose' AND NOT EXISTS (
	SELECT codd
	FROM matricula m_int
	JOIN professor USING(codp)
	WHERE nomep = 'jose' AND m_ext.codd = m_int.codd
)

-- O nome dos professores que não ministram nenhuma das disciplinas que jose ministra
SELECT nomep
FROM professor p
WHERE nomep <> 'jose' AND NOT EXISTS (
	SELECT codd
	FROM matricula m_ext
	WHERE p.codp = m_ext.codp AND EXISTS (
		SELECT codd
		FROM matricula m_int
		JOIN professor USING (codp)
		WHERE nomep = 'jose' AND m_ext.codd = m_int.codd
	)
)

-- O nome dos professores que ministram todas as disciplinas que jose ministra (e possivelmente outras)
SELECT nomep
FROM professor p
-- Não existe nenhuma disciplina que o Jose ensina e o professor não dê, ou seja o professor ensina todas as disciplinas de José e talvez outras.
WHERE nomep <> 'jose' AND NOT EXISTS (
	-- Aqui o banco de dados pega a lista de todas as disciplinas que o 'jose' ministra e verifica:
	-- Existe alguma disciplina aqui que não está (NOT IN) na lista de disciplinas do professor p?
	-- Se essa subquery retornar algum resultado, significa que encontramos uma disciplina que o José dá, mas o professor p não dá.
	SELECT codd
	FROM matricula
	JOIN professor USING (codp)
	-- As disciplinas de jose devem estar nas disciplinas que o professor ensina.
	WHERE nomep = 'jose' AND codd NOT IN (
		-- Disciplinas que o professor ensina.
		SELECT DISTINCT codd
		FROM matricula
		WHERE codp = p.codp
	)
);

-- O nome dos professores que ministram exatamente as mesmas disciplinas que jose ministra.
SELECT nomep
FROM professor p
WHERE nomep <> 'jose' AND NOT EXISTS (
	-- Ensina todas as disciplinas que jose ministra.
	SELECT codd
	FROM matricula
	JOIN professor USING (codp)
	WHERE nomep = 'jose' AND codd NOT IN (
		SELECT DISTINCT codd
		FROM matricula
		WHERE codp = p.codp
	)
) AND NOT EXISTS (
	-- Não ensina nenhuma disciplina que jose não ensine.
	SELECT codp
	FROM matricula
	WHERE codp = p.codp AND codd NOT IN (
		SELECT codd
		FROM professor
		JOIN matricula USING (codp)
		WHERE nomep = 'jose'
	)
)
