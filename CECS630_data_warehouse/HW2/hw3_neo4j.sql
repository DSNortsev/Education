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
MERGE (book:BOOK {isbn:value.isbn}) ON CREATE
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





UNWIND value.authors as a
MERGE (author:Author {first_name:a.`first-name`, last_name:a.`last-name`}) ON CREATE
 SET author.age = a.age
MERGE (author)-[:Author_of]->(book)





FOREACH (a IN value.author |
	MERGE (author:Author {first_name = a.first-name, last-name = a.last-name}) ON CREATE
 	 SET author.age = a.age
	MERGE (author)-[:Author-of]->(book)
)


MATCH (n)
DETACH DELETE n



MERGE (publisher:Publisher {name:value.publisher.name, }) ON CREATE
 SET publisher.address = value.publisher.street-number
 	 + " "
 	 + value.publisher.street-name 
 	 + ","
 	 + value.publisher.city, 
 	 publisher.country = value.publisher.country,
 	 publisher.phone = value.publisher.ph