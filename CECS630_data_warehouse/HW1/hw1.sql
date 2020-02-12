-- Task1. create a schema for this data in a plain relational database (each attribute in each table should be
-- of a basic data type; no complex types, no collections). That is, shred the data to a plain relational
-- database schema following the procedure outlined in class. All the tables should in 3NF. Avoid the
-- possibility of nulls as much as possible. Make sure to declare all primary keys and all foreign keys.
-- Populate the tables with the data in the file.

DROP SCHEMA IF EXISTS hw1_task1 CASCADE;
CREATE SCHEMA hw1_task1;
SET client_encoding = 'UTF8';
SET search_path TO hw1_task1;

-- TABLES

CREATE TABLE customers (
        id serial PRIMARY KEY,
	name varchar(30) NOT NULL,
        "number" varchar(20) NOT NULL,
        street varchar(50) NOT NULL,
        city varchar(30) NOT NULL,
        country varchar(15) NOT NULL
);

-- Table will store contact types such as phone, email. Since that field is optional
CREATE TABLE contact_types (
    id serial PRIMARY KEY,
    name varchar(15) NOT NULL
);


CREATE TABLE customer_personal_contacts (
    customer_id serial NOT NULL REFERENCES customers (id),
    contact_types_id serial NOT NULL REFERENCES contact_types (id),
    contact_info  varchar(30) NOT NULL,
    PRIMARY KEY (customer_id, contact_types_id)
);


CREATE TABLE customer_contacts (
    customer_id serial NOT NULL REFERENCES customers (id),
    name varchar(30) NOT NULL,
    phone varchar(15) NOT NULL UNIQUE,
    email varchar(30) NOT NULL UNIQUE,
    PRIMARY KEY (customer_id, name)
);


CREATE TABLE orders (
    -- Use id as promary key because customer can place multiple orders in one day
    id serial PRIMARY KEY,
    customer_id serial NOT NULL REFERENCES customers (id),
    order_date date NOT NULL,
    ship_by date NOT NULL, 
    discount int NOT NULL 
);


CREATE TABLE items (
    id serial PRIMARY KEY,
    name varchar(30) NOT NULL,
    price int NOT NULL
);


CREATE TABLE order_details (
    order_id serial NOT NULL REFERENCES orders (id),
    items_id serial NOT NULL REFERENCES items (id),
    quantity int NOT NULL, 
    PRIMARY KEY (order_id, items_id)
);


CREATE TABLE xmldata (
    id serial PRIMARY KEY,
    documents xml
);

-- INSERTION

INSERT INTO contact_types (name) VALUES ('email'), ('phone'), ('secretary');

INSERT INTO xmldata (documents) VALUES (
'<Customers>
<Customer>
<Name>Peter Gabriel</Name>
<Address>
  <Street number="123">Main Street</Street>
  <City>Louisville</City>
  <Country>USA</Country>
  <email>pgabriel@genesis.com</email>
</Address>
<Contacts>
 <Contact>
   <Name>Phil Collins</Name>
   <Phone>(502) 555-5555</Phone>
   <email>pcollins@genesis.com</email>
 </Contact>
 <Contact>
   <Name>Tony Banks</Name>
   <Phone>(502) 555-5556</Phone>
   <email>tbanks@genesis.com</email>
 </Contact> 
</Contacts>
<Orders>
 <order>
   <date>1/20/2020</date>
   <ship-by>2/20/2020</ship-by>
   <discount>5</discount>  
   <items>
     <item>
      <name>Drumset</name>
      <quantity>1</quantity>
      <price>1100</price>
     </item>
     <item>
      <name>Cymbal</name> 
      <quantity>3</quantity>
      <price>280</price>
     </item>
     <item>
      <name>Synthetiser</name>
      <quantity>2</quantity>
      <price>2,000</price>
     </item>
   </items>     
 </order>
  <order>
   <date>1/30/2020</date>
   <ship-by>2/25/2020</ship-by>
   <discount>4</discount>  
   <items>
     <item>
      <name>Piano</name>
      <quantity>1</quantity>
      <price>5000</price>
     </item>
     <item>
      <name>Keyboard</name>
      <quantity>3</quantity>
      <price>1500</price>
     </item>
     <item>
      <name>Organ</name>
      <quantity>1</quantity>
      <price>2500</price>
     </item>
   </items>     
  </order>
 </Orders>
</Customer>
<Customer>
<Name>Anthony Phillips</Name>
<Address>
  <Street number="232">Sesame Street</Street>
  <City>Louisville</City>
  <Country>USA</Country>
  <phone>(502) 502-5002</phone>
</Address>
<Contacts>
 <Contact>
   <Name>Mike Rutherford</Name>
   <Phone>(502) 555-5557</Phone>
   <email>mrutherford@genesis.com</email>
 </Contact>
</Contacts>
<Orders>
 <order>
   <date>1/15/2020</date>
   <ship-by>2/25/2020</ship-by>
   <discount>3</discount>  
   <items>
     <item>
      <name>Electric guitar</name>
      <quantity>4</quantity>
      <price>1800</price>
     </item>
     <item>
      <name>Acoustic guitar</name>
      <quantity>2</quantity>
      <price>3000</price>
     </item>
     <item>
      <name>pick</name>
      <quantity>50</quantity>
      <price>1.10</price>
     </item>
   </items>     
 </order>
  <order>
   <date>2/1/2020</date>
   <ship-by>4/1/2020</ship-by>
   <discount>4</discount>  
   <items>
     <item>
      <name>Strap</name>
      <quantity>10</quantity>
      <price>150</price>
     </item>
     <item>
      <name>Tuner</name>
      <quantity>1</quantity>
      <price>300</price>
     </item>
   </items>     
  </order>
 </Orders>
</Customer>
<Customer>
<Name>Ray Wilson</Name>
<Address>
  <Street number="123">Nowhere Street</Street>
  <City>London</City>
  <Country>UK</Country>
  <secretary>Jonathan King</secretary>
</Address>
<Contacts>
 <Contact>
   <Name>Steve Hacket</Name>
   <Phone>(502) 555-5558</Phone>
   <email>shacket@genesis.com</email>
 </Contact>
</Contacts>
<Orders>
 <order>
   <date>11/20/2019</date>
   <ship-by>12/20/2019</ship-by>
   <discount>8</discount>  
   <items>
     <item>
      <name>Case</name>
      <quantity>12</quantity>
      <price>25</price>
     </item>
     <item>
      <name>Amplifier</name>
      <quantity>10</quantity>
      <price>1400</price>
     </item>
   </items>     
 </order>
  <order>
   <date>10/5/2019</date>
   <ship-by>11/15/2019</ship-by>
   <discount>2</discount>  
   <items>
     <item>
      <name>Electric Bass</name>
      <quantity>4</quantity>
      <price>1,600</price>
     </item>
     <item>
      <name>Microphone</name>
      <quantity>10</quantity>
      <price>500</price>
     </item>
   </items>     
  </order>
 </Orders>
</Customer>
</Customers>');

CREATE FUNCTION xmlparser() RETURNS void AS $$
DECLARE
        customer xml;
	name varchar(30);
        "number" int;
        street varchar(30);
        city varchar(15);
        country varchar(15);
        email varchar(30);
        phone varchar(15);
        secretary varchar(15);
BEGIN 
       -- myxml := (SELECT unnest(xpath('/Customers/Customer',(SELECT documents
       --                                                      FROM hw1_task1.xmldata
       --                                                    LIMIT 1))));
       
       FOR customer IN (select unnest(xpath('/Customers/Customer',(select documents from hw1_task1.xmldata LIMIT 1)))) LOOP
           name := (SELECT (xpath('//Name/text()', customer))[1]::text);
           "number" := (SELECT (xpath('//Address/Street/@number', customer))[1]::text);
           street := (SELECT (xpath('//Address/Street/text()', customer))[1]::text);
           city := (SELECT (xpath('//Address/City/text()', customer))[1]::text);
           country := (SELECT (xpath('//Address/Country/text()', customer))[1]::text);
          
           INSERT INTO customers (name, "number", street, city, country) VALUES 
           (name, "number", street, city, country); 
           RAISE NOTICE '%', name;
           RAISE NOTICE '%', "number";
           RAISE NOTICE '%', street;
           RAISE NOTICE '%', city;
           RAISE NOTICE '%', country;
    

    


    
       END LOOP;
      
RETURN;
END;
$$
LANGUAGE plpgsql;

SELECT xmlparser();
