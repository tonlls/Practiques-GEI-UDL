--1
R1 = text(autor='C.J.Date')[ISBN]
R2 = utilitza(ISBN/ISBN)R1[idassignatura]
R3 = matricula[idassignatura=idassignatura]R2
R4 = R3[nota=10 ^ idalumne<>idalumne ^ idassignatura=idassignatura]R3[idassignatura]
R = assignatura[idassignatura=idassignatura]R4[nom]

--2
R1 = estudiant(ciutat<>'Lleida')[idalumne]
R2 = matricula(idalumne<>idalumne v nota=null)R1[idassignatura]
R = assignatura(idassignatura<>idassignatura)R2[nom]

------------
DROP TABLE utilitzat;
DROP TABLE matricula;
DROP TABLE estudiant;
DROP TABLE assignatura;
DROP TABLE text;
--------
CREATE TABLE estudiant(
	idalumne SERIAL PRIMARY KEY,
	DNI VARCHAR(9),
	nom VARCHAR(50),
	ciutat VARCHAR(100),
	data_naixement DATE
);
CREATE TABLE assignatura(
	idassignatura SERIAL PRIMARY KEY,
	nom VARCHAR(50),
	departament VARCHAR(50)
);
CREATE TABLE text(
	ISBN VARCHAR(20) PRIMARY KEY,
	titol VARCHAR(50),
	editorial VARCHAR(50),
	autor VARCHAR(50)
);
CREATE TABLE matricula(
	idalumne INT REFERENCES estudiant(idalumne),
	idassignatura INT REFERENCES assignatura(idassignatura),
	nota FLOAT,
	PRIMARY KEY(idalumne,idassignatura),
);
CREATE TABLE utilitzat(
	idassignatura INT REFERENCES assignatura(idassignatura),
	ISBN VARCHAR(20) REFERENCES text(ISBN),
	PRIMARY KEY(idassignatura,ISBN)
);
------------
INSERT INTO estudiant(DNI,nom,ciutat,data_naixement) 
VALUES ('47125160T','Ton','Igualada',null),
	   ('49539818A','Hatty','Ciutat dels Rics rucs',null),
	   ('69696969X','aduardomanostijeras','he dont sleep',null);
INSERT INTO assignatura(nom,departament)
VALUES ('Sistemes Operatius','Sistemes'),
	   ('Administració de Xarxes','Sistemes'),
	   ('Fisica','tu puta madre'),
	   ('Bases de Dades','Sistemes Informatics');
INSERT INTO text(ISBN,titol,editorial)
VALUES ('9','una merda de manual','ton'),
	   ('10','manual de c','edu'),
	   ('11','el gran manual de unix',''),
	   ('12','aixo no es un bon llibre','aduardumanostijeras'),
	   ('13','manual','ton');
INSERT INTO utilitzat(idassignatura,ISBN)
VALUES (3,'9'),
	   (3,'10'),
	   (3,'11'),
	   (3,'12'),
	   (4,'10'),
	   (4,'11'),
	   (4,'12');
INSERT INTO matricula(idalumne,idassignatura,nota) 
VALUES (1,4,10),
	   (2,4,4),
	   (2,1,2); 
	   
--3
SELECT e.nom,m.nota
FROM estudiant e 
	INNER JOIN matricula m
		ON e.idalumne=m.idalumne 
	INNER JOIN assignatura a 
		ON a.idassignatura=m.idassignatura
WHERE a.nom LIKE 'Bases de Dades'
AND a.departament LIKE 'Sistemes Informatics'
ORDER BY m.nota LIMIT 5;
--4
ALTER TABLE assignatura 
ADD COLUMN numalumnes INT 
CHECK(numalumnes<101 AND numalumnes>0);
--5
UPDATE matricula m SET nota=nota+1 
FROM estudiant e,assignatura a 
WHERE m.idalumne=e.idalumne 
AND e.nom LIKE 'F%'
AND e.ciutat LIKE 'Mollerussa'
AND m.idassignatura=a.idassignatura
AND a.departament LIKE 'Sistemes Informàtics';
--6
DELETE FROM matricula m 
WHERE m.idalumne=(SELECT e.idalumne 
				  FROM estudiant e 
				  WHERE e.DNI LIKE '87654321Z');
DELETE FROM estudiant e 
WHERE e.DNI LIKE '87654321Z';
--7
SELECT a.nom, COUNT(u.ISBN)
FROM assignatura a 
	INNER JOIN utilitzat u 
	ON a.idassignatura=u.idassignatura 
	INNER JOIN text t 
	ON u.ISBN=t.ISBN
WHERE a.departament LIKE 'Sistemes'
AND t.titol LIKE '%manual%'
GROUP BY a.idassignatura
HAVING COUNT(*) > 2
ORDER BY COUNT(*) DESC LIMIT 10;
--8
SELECT a.idassignatura,a.nom,a.departament,COUNT(m.idassignatura) AS ALUMNES,MAX(m.nota) AS NOTA_MAX,AVG(m.nota) AS NOTA_MITJA
FROM assignatura a INNER JOIN matricula m 
ON a.idassignatura=m.idassignatura
GROUP BY a.idassignatura
ORDER BY a.nom;
--9
SELECT a.nom,m.nota
FROM matricula m INNER JOIN assignatura a
ON m.idassignatura=a.idassignatura
WHERE m.nota=(SELECT MAX(nota) 
			  FROM matricula 
			  WHERE idalumne=1)
AND m.idalumne=1

CREATE FUNCTION getMaxNota(id INTEGER) RETURNS VARCHAR(50) AS $$
	DECLARE
		Assignatura Varchar(50);
	BEGIN
		SELECT INTO Assignatura a.nom 
		FROM matricula m 
			INNER JOIN assignatura a
			ON m.idassignatura=a.idassignatura
		WHERE m.nota=(SELECT MAX(nota) 
					  FROM matricula 
					  WHERE idalumne=id)
		AND m.idalumne=id
		LIMIT 1;
		RETURN Assignatura;
	END;
$$ LANGUAGE 'plpgsql';
--10
CREATE OR REPLACE FUNCTION myFunction() RETURNS TRIGGER AS $$
	DECLARE
		texts INTEGER;
	BEGIN
		SELECT INTO texts COUNT(*)
		FROM text t
			INNER JOIN utilitzat u
			ON t.ISBN=u.ISBN
		WHERE t.editorial=(SELECT editorial FROM text WHERE ISBN=new.ISBN)
		AND u.idassignatura=new.idassignatura;
		IF texts > 0 THEN
			RAISE EXCEPTION 'la editorial del llibre que tractes d''inserir ja s''esta utilitzant en la mateixa assignatura';
			RETURN OLD;
		END IF;
		RETURN NEW;
	END;
$$ LANGUAGE 'plpgsql';

CREATE TRIGGER myTrigger AFTER INSERT ON utilitzat FOR EACH ROW EXECUTE PROCEDURE myFunction();


INSERT INTO utilitzat(idassignatura,ISBN) 
VALUES(3,'13');