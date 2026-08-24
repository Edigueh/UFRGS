-- Nome: André Schaidhauer Luckmann
-- Matricula: 00601117

-- Criação de tabelas.
CREATE TABLE disciplinas
(
	codd CHAR(2) NOT NULL PRIMARY KEY,
	nomed VARCHAR(20) NOT NULL UNIQUE,
	creditos SMALLINT NOT NULL
);

CREATE TABLE salas
(
	numero SMALLINT NOT NULL PRIMARY KEY,
	predio VARCHAR(10) NOT NULL,
	capacidade SMALLINT NOT NULL
);

CREATE TABLE turmas
(
	codd CHAR(2) NOT NULL,
	turma CHAR(1) NOT NULL,
	local SMALLINT,
	PRIMARY KEY (codd, turma),
	FOREIGN KEY(codd) REFERENCES disciplinas,
	FOREIGN KEY(local) REFERENCES salas
);

-- Instanciar valores de salas.
INSERT INTO salas VALUES (10, 'P1', 40);
INSERT INTO salas VALUES (20, 'P2', 10);
INSERT INTO salas VALUES (30, 'P3', 10);
SELECT * FROM salas;

-- Instanciar valores de disciplinas.
INSERT INTO disciplinas VALUES ('d1', 'matematica', 4);
INSERT INTO disciplinas VALUES ('d2', 'portugues', 6);
INSERT INTO disciplinas VALUES ('d3', 'geografia', 4);
SELECT * FROM disciplinas;

-- Instanciar valores de turmas.
INSERT INTO turmas VALUES ('d1', 'A', 10);
INSERT INTO turmas VALUES ('d1', 'B', 20);
INSERT INTO turmas VALUES ('d2', 'A', NULL);
INSERT INTO turmas VALUES ('d2', 'B', 20);
INSERT INTO turmas VALUES ('d3', 'A', NULL);
SELECT * FROM turmas;

-- Testando política Restricted.
-- Trocar o numero das salas 10 e 30
UPDATE salas SET numero = 300 WHERE numero = 30;
UPDATE salas SET numero = 100 WHERE numero = 10;
SELECT * FROM salas;

-- Remover as salas 10 e 300.
DELETE FROM salas WHERE numero = 300;
DELETE FROM salas WHERE numero = 10;
SELECT * FROM salas;

-- Q1: Descreva o erro que ocorre e o porquê.
-- qual a diferença entre trocar o número da sala 30 e da 10?
-- qual a diferença entre remover a sala 300 e a sala 10?
-- O erro ocorre pela violação restrita da integridade referencial da 
-- chave primária. Como algum valor da tabela turmas referencia o numero 10 como foreign key,
-- a entrada de número 10 é referenciada e não pode ser deletado. Logo, a 
-- transação é abortada. O mesmo não ocorre com a sala 30/300 pois essa sala não está
-- referencia em nenhuma outra tabela.

-- Tarefa 4 - Políticas compensatórias
DROP TABLE turmas;

-- Q2: Como ficou o comando create table TURMAS2 para contemplar as políticas acima?
CREATE TABLE turmas2
(
	codd CHAR(2) NOT NULL,
	turma CHAR(1) NOT NULL,
	local SMALLINT,
	PRIMARY KEY (codd, turma),
	FOREIGN KEY(codd) REFERENCES disciplinas 
	ON DELETE CASCADE,
	FOREIGN KEY(local) REFERENCES salas
	ON DELETE SET NULL
	ON UPDATE CASCADE
);

-- Inclusão de instâncias em turmas2
INSERT INTO turmas2 VALUES ('d1', 'A', 10);
INSERT INTO turmas2 VALUES ('d1', 'B', 20);
INSERT INTO turmas2 VALUES ('d2', 'A', NULL);
INSERT INTO turmas2 VALUES ('d2', 'B', 20);
INSERT INTO turmas2 VALUES ('d3', 'A', NULL);

-- Q3: Descreva o que acontece em cada uma das situações abaixo, explicando porque o comando ocorre com sucesso ou com erro:
-- a) trocar o numero da sala 10.
UPDATE salas SET numero = 100 WHERE numero = 10;
SELECT * FROM salas;
SELECT * FROM turmas2;
-- Aqui, o numero da entrada onde numero = 10, vira numero = 100 na tabela salas.
-- Na tabela turmas2, a mudança é refletida no atributo local, isso é possóivel pois
-- a politica CASCADE de ON UPDATE foi acionada, atualizando todas as ocorrências daquele valor
-- e suas referências.

-- b) remover a sala 20;
DELETE FROM salas WHERE numero = 20;
SELECT * FROM salas;
SELECT * FROM turmas2;
-- A remoção da sala com numero 20 ocorre com sucesso na tabela salas.
-- Como a tabela turmas2 referencia o local com a política de ON DELETE SET NULL.
-- Todas as turmas que antes referenciavam a sala de numero 20 ficam com o local como NULL agora.

-- c) remover a disciplina d3;
DELETE FROM disciplinas WHERE codd = 'd3';
SELECT * FROM disciplinas;
SELECT * FROM turmas2;
-- A remoção da disciplina de codigo d3 é concluida corretamente na tabela disciplinas.
-- Na tabela turmas2, a politica referencia a FK codd como ON DELETE CASCADE,
-- logo, todas as entradas em turmas2 que referenciavama a disciplina de codd 'd3' são deletadas também.

-- d) trocar o código da disciplina d1
UPDATE disciplinas SET codd = 'd8' WHERE codd = 'd1';
SELECT * FROM disciplinas;
SELECT * FROM turmas2;
-- Aqui a operação não é realizada, não é setada uma política de integridade
-- para a atualização de codd em turmas2. Como existem valores que referenciam 'd1',
-- a política DEFAULT é aplicada, e a operação é rejeitada.

-- Tarefa 5 -- Criação de nova tabela professores.
CREATE TABLE professores
(
	codprof INTEGER NOT NULL PRIMARY KEY,
	nomeprof CHAR(20) NOT NULL,
	disc CHAR(2) NOT NULL,
	FOREIGN KEY (disc) REFERENCES disciplinas
);

INSERT INTO disciplinas VALUES ('d3', 'geografia', 4);
INSERT INTO turmas2 VALUES ('d3', 'A', NULL);
INSERT INTO professores VALUES (1, 'joao', 'd3');

-- Q4: Na tarefa 4 excluímos uma disciplina de DISCIPLINAS, observando seus efeitos em TURMAS2. O que acontece se tentarmos excluir a disciplina de código ‘d3’? Relate se o comando ocorre com sucesso ou erro, explicando.
-- Aqui a remoção da disciplina e código 'd3' não irá funcionar, pois a política DEFAULT,
-- está aplicada na tabela professores, que referencia uma discplina de código 'd3', rejeitando a remoção.
DELETE FROM disciplinas WHERE codd = 'd3';

-- Tarefa 6 - definição de chaves estrangeiras para o esquema AEROPORTO. Complete os esquemas com as chaves estrangeiras necessárias.
CREATE TABLE aeroportos
(
	coda CHAR(3) NOT NULL,
	nome VARCHAR(60) NOT NULL,
	cidade VARCHAR(30) NOT NULL,
	pais VARCHAR NOT NULL,
	PRIMARY KEY(coda)
);

INSERT INTO aeroportos VALUES ('a1', 'aeroporto1', 'Porto Alegre', 'BR');
INSERT INTO aeroportos VALUES ('a2', 'aeroporto2', 'Sao Paulo', 'BR');
INSERT INTO aeroportos VALUES ('a3', 'aeroporto3', 'Rio de Janeiro', 'BR');

-- tabela de voos - representa um voo regular disponível
-- um voo sai de um aeroporto origem, e chega em um aeroporto destino
-- complete a definição da tabela VOOS para que reflita a relaçao com aeroportos
CREATE TABLE voos
(
	codv CHAR(5) NOT NULL,
	origem CHAR(3) NOT NULL,
	destino CHAR(3) NOT NULL,
	horapartida TIME,
	PRIMARY KEY (codv),
	FOREIGN KEY(origem) REFERENCES aeroportos,
	FOREIGN KEY(destino) REFERENCES aeroportos
);

-- deve executar sem erro
insert into voos values ('v1', 'a1', 'a2', '9:30');
insert into voos values ('v2', 'a2', 'a1', '11:30');
insert into voos values ('v3', 'a1', 'a3', '16:00');

-- deve executar com erro
insert into voos values ('v4', 'a1', 'a4', '9:30');

-- Q5: Modifique o(s) esquemas da(s) tabela(s) com a chave estrangeira apropriada. Como ficam as definições das tabelas que foram modificadas?
-- tabela de pilotos
CREATE TABLE PILOTOS
(
	codp CHAR(4) NOT NULL,
	nomep VARCHAR(60),
	companhia varchar(50),
	primary key(codp)
);

insert into pilotos values ('p1', 'maria', 'gol');
insert into pilotos values ('p2', 'joana', 'gol');
insert into pilotos values ('p3', 'pedro', 'tam');

-- tabela de escalacoes --
-- escalacoes de voos regulares em alguma data, com o piloto e aviao definido na escalaçao
-- complete a definição da tabela ESCALACOES para que reflita a relaçao com voos e pilotos
CREATE TABLE ESCALACOES 
(
	codv CHAR(5) NOT NULL, 
	data DATE NOT NULL, 
	aviao VARCHAR(10),
	codp CHAR(4), 
	primary key(codv, data),
	FOREIGN KEY(codp) REFERENCES PILOTOS,
	FOREIGN KEY(codv) REFERENCES voos
);

-- deve executar sem erro
insert into escalacoes values ('v1', '1-1-2025', '737', 'p1');
insert into escalacoes values ('v1', '2-2-2025', '777', 'p2');
insert into escalacoes values ('v2', '1-1-2025', '777', 'p1');
insert into escalacoes values ('v3', '3-3-2025', '737', 'p3');

-- deve executar com erro
insert into escalacoes values ('v4', '3-3-2025', '737', 'p3');
insert into escalacoes values ('v3', '3-3-2025', '737', 'p4');

-- tarefa 7
-- Q6: Modifique o(s) esquemas da(s) tabela(s) com a chave estrangeira apropriada.
-- Como ficam as definições das tabelas que foram modificadas?
-- vamos refazer as tabelas para poder atender as seguintes políticas do UdD
drop table escalacoes;
drop table voos;
drop table pilotos;
drop table aeroportos;

-- Regras de Negócio: 
-- A companhia se reserva o direito de suprimir um vôo, sendo canceladas (i.e. removidas) assim todas as escalas para ele previstas. 
-- Se um piloto escalado para um vôo for demitido (i.e. removido), a escala daquele vôo fica em aberto (i.e. a escala não é removida, e fica aguardando a designação de um novo piloto). 
-- Pilotos e vôos não podem ter sua identificação alterada (codp e codv, respectivamente).
-- Aeroportos podem ter seu código alterado, mas todos os vôos correspondentes devem ser atualizados de forma correspondente.
-- Q7: Como ficam as definições das tabelas ?
CREATE TABLE aeroportos
(
	coda CHAR(3) NOT NULL,
	nome VARCHAR(60) NOT NULL,
	cidade VARCHAR(30) NOT NULL,
	pais VARCHAR NOT NULL,
	PRIMARY KEY(coda)
);

CREATE TABLE voos
(
	codv CHAR(5) NOT NULL,
	origem CHAR(3) NOT NULL,
	destino CHAR(3) NOT NULL,
	horapartida TIME,
	PRIMARY KEY (codv),
	FOREIGN KEY(origem) REFERENCES aeroportos
	ON UPDATE CASCADE,
	FOREIGN KEY(destino) REFERENCES aeroportos
	ON UPDATE CASCADE
);

CREATE TABLE PILOTOS
(
	codp CHAR(4) NOT NULL,
	nomep VARCHAR(60),
	companhia varchar(50),
	primary key(codp)
);

CREATE TABLE ESCALACOES 
(
	codv CHAR(5) NOT NULL, 
	data DATE NOT NULL, 
	aviao VARCHAR(10),
	codp CHAR(4), 
	primary key(codv, data),
	FOREIGN KEY(codp) REFERENCES PILOTOS
	ON DELETE SET NULL,
	FOREIGN KEY(codv) REFERENCES voos
	ON DELETE CASCADE
);

-- As politicas de integridade são sempre definidas nas chaves estrangeiras,
-- nunca nas chaves primárias.

-- Teste seu esquema fazendo remoções e atualizações em todas as tabelas. 
-- Q8: Forneça um comando de atualização e de remoção por tabela que afetem as restrições de integridade referencial definidas.
