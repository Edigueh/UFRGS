CREATE TABLE FUNCIONARIO (
    codf    char(4)     NOT NULL,
    nome    varchar(20) NOT NULL,
    salario numeric(8,2),
    primary key(codf),
    -- Insert Your changes here:
);

CREATE TABLE PROJETO (
    codp      char(5)       NOT NULL,
    nome      char(3)       NOT NULL,
    orcamento numeric(10,2) NOT NULL,
    gerente   char(4),
    -- Insert Your changes here:
    PRIMARY KEY (codp),
    FOREIGN KEY (gerente) REFERENCES FUNCIONARIO
    ON DELETE SET NULL
);

CREATE TABLE ALOCACAO (
    codf  char(4)      NOT NULL,
    codp  char(5)      NOT NULL,
    horas smallinteger NOT NULL,
    primary key(codp,codf),
    -- Insert Your changes here:
    FOREIGN KEY (codp) REFERENCES PROJETO
    ON UPDATE CASCADE,
    FOREIGN KEY (codf) REFERENCES FUNCIONARIO
    ON DELETE CASCADE
);
