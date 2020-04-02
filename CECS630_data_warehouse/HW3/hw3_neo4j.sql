-- Load the table into Neo4j with the following schema: nodes for Book (with properties isbn, title,
-- price, date), Author (with properties last-name, first-name, age) and Publisher (with properties name,
-- address, phone, country; property address should be composed of street-number, street-name,
-- city); edges for relation 'Author-of' between Book and Author nodes, an for relation 'Publisher-
-- of' between Book and Publisher nodes. Note: there are several ways to load data into Neo4j; see
-- https://neo4j.com/developer/data-import/ for a description of the options. You can either dump
-- your relational data into csv les and use the LOAD CSV command, or use the original Json data and the
-- apoc.load.json command, or the ETL tool. What you have to turn in is a list of the commands/steps
-- that you used to get your data into Neo4j, but you can choose how you prefer to do it.


-- Steps:

-- 1. Copy BOOKSDATA.json to project_database/import directory
-- 2. Load data from json file 

WITH "BOOKSDATA.json" AS data
CALL apoc.load.json(data) YIELD value
MERGE (book:Book {isbn:value.isbn}) ON CREATE
  SET book.title = value.title, book.price = value.price, book.date = value.date

MERGE (publisher:Publisher {name:value.publisher.name, city:value.publisher.address.city}) ON CREATE
 SET publisher.name = value.publisher.name,
 	 publisher.street_number = value.publisher.address.`street-number`,
  	 publisher.street_name = value.publisher.address.`street-name`,
  	 publisher.city = value.publisher.address.city,
 	 publisher.country = value.publisher.address.country,
 	 publisher.phone = value.publisher.phone
MERGE (publisher)-[:Publisher_of]->(book)

FOREACH (a IN value.authors |
	MERGE (author:Author {first_name:a.first, last_name:a.last}) ON CREATE
 	 SET author.age = a.age
	MERGE (author)-[:Author_of]->(book)
)

-- (a) List the title and price of books published in 2017 (any date in 2017) with a price less than $20.
--     Sort the result by price, from cheapest to most expensive.

MATCH (:Publisher)-[:Publisher_of]->(b:Book)
WHERE b.date ENDS WITH "2017" AND b.price < 20
RETURN b.title, b.price
ORDER BY b.price

-- (b) List the first and last name of authors of books published by a German publisher.

MATCH (p:Publisher)-[:Publisher_of]->(:Book)<-[:Author_of]-(a:Author)
WHERE p.country = 'Germany'
RETURN a.first_name, a.last_name

-- (c) List the name and city of publishers of books where all the authors are over the age of 35.

MATCH (p:Publisher)-[:Publisher_of]->(b:Book)<-[:Author_of]-(a:Author)
WITH p, b, collect(a.age) as array_of_ages
WHERE ALL ( age in array_of_ages  WHERE age > 35)
RETURN p.name, p.city

-- (d) List the title and publisher names for books with more than 2 authors.

MATCH (p:Publisher)-[:Publisher_of]->(b:Book)<-[:Author_of]-(a:Author)
WITH p, b, count(a) as count
WHERE count > 2
RETURN b.title, p.name