-- Task1. create a schema for this data in a plain relational database (each attribute in each table should be
-- of a basic data type; no complex types, no collections). That is, shred the data to a plain relational
-- database schema following the procedure outlined in class. All the tables should in 3NF. Avoid the
-- possibility of nulls as much as possible. Make sure to declare all primary keys and all foreign keys.
-- Populate the tables with the data in the file.

DROP SCHEMA IF EXISTS hw1_task1 CASCADE;
CREATE SCHEMA hw1_task1;
SET client_encoding = 'UTF8';
SET search_path TO hw1_task1;
SET DATESTYLE TO US;

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
    name varchar(30) NOT NULL UNIQUE,
    price numeric(10,2) NOT NULL
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
        contact xml;
        "order" xml;
        item xml;
        customer_id int;
	name varchar(30);
        "number" int;
        street varchar(30);
        city varchar(15);
        country varchar(15);
        contact_name varchar(30);
        contact_phone varchar(30);
        contact_email varchar(30);
        contact_type varchar(30);
        contact_type_id int;
        contact_info varchar(30);
        order_id int;
        order_date date;
        order_ship_by date;
        order_discount int;
        item_id int;
        item_name varchar(30);
        item_quantity int;
        item_price numeric(10,2);

BEGIN 
       -- myxml := (SELECT unnest(xpath('/Customers/Customer',(SELECT documents
       --                                                      FROM hw1_task1.xmldata
       --                                                    LIMIT 1))));
       
       FOR customer IN (select unnest(xpath('/Customers/Customer',(select documents from hw1_task1.xmldata LIMIT 1)))) LOOP
           --  Get customer information
           name := (SELECT (xpath('//Name/text()', customer))[1]::text);
           "number" := (SELECT (xpath('//Address/Street/@number', customer))[1]::text);
           street := (SELECT (xpath('//Address/Street/text()', customer))[1]::text);
           city := (SELECT (xpath('//Address/City/text()', customer))[1]::text);
           country := (SELECT (xpath('//Address/Country/text()', customer))[1]::text);

           INSERT INTO customers (name, "number", street, city, country) VALUES (name, "number", street, city, country);
           -- Get customer primary key 
           customer_id := (SELECT currval(pg_get_serial_sequence('customers','id'))); 
          
           -- Add customer personal contact information   
           FOR contact_type IN (SELECT ct.name FROM contact_types as ct) LOOP
               contact_info := (SELECT (xpath('//Address/' || contact_type || '/text()', customer))[1]::text);
               IF contact_info IS NOT NULL THEN
                    contact_type_id := (SELECT ct.id FROM contact_types as ct WHERE ct.name = contact_type);
                    INSERT INTO customer_personal_contacts (customer_id, contact_types_id,contact_info)
                    VALUES (customer_id, contact_type_id, contact_info); 
               END IF;
           END LOOP;           

          FOR contact IN (select unnest((xpath('//Contacts/Contact', customer)))) LOOP
               -- Get cusotmer contact info
               contact_name := (SELECT (xpath('//Contact//Name/text()', contact))[1]::text);
               contact_phone := (SELECT (xpath('//Contact/Phone/text()', contact))[1]::text);
               contact_email := (SELECT (xpath('//Contact/email/text()', contact))[1]::text);
               INSERT INTO customer_contacts (customer_id, name, phone, email)
               VALUES (customer_id, contact_name, contact_phone, contact_email);
          END LOOP;
    
          FOR "order" IN (select unnest((xpath('//Orders/order', customer)))) LOOP
               -- Get order information for customer
               order_date := (SELECT (xpath('//order/date/text()', "order"))[1]::text);
               order_ship_by := (SELECT (xpath('//order/ship-by/text()', "order"))[1]::text);
               order_discount := (SELECT (xpath('//order/discount/text()', "order"))[1]::text);
               INSERT INTO orders (customer_id, order_date, ship_by, discount)
               VALUES (customer_id, order_date, order_ship_by, order_discount);
               order_id := (SELECT currval(pg_get_serial_sequence('orders','id')));
               FOR item IN (select unnest((xpath('//items/item', "order")))) LOOP
                   -- Insert item information
                   item_name := (SELECT (xpath('//item/name/text()', item))[1]::text);
                   item_quantity := (SELECT (xpath('//item/quantity/text()', item))[1]::text);
                   item_price := REPLACE((SELECT (xpath('//item/price/text()', item))[1]::text), ',','');
                   INSERT INTO items (name, price) VALUES (item_name, item_price);
                   item_id := (SELECT currval(pg_get_serial_sequence('items','id')));
                   -- Insert order details
                   INSERT INTO order_details (order_id, items_id, quantity) VALUES (order_id, item_id, item_quantity);
               END LOOP;
          END LOOP;
    
       END LOOP;
      
RETURN;
END;
$$
LANGUAGE plpgsql;

SELECT xmlparser();



-- TASK3. Create a table with an id and an XMLType column, and write a query over the plain relational database
-- that will generate the data in XML format to populate this database.

-- !!! NOTES: I have create four table where I have stored part of xml messages, but I didn't figure out how easily I can merge them 
CREATE TABLE customer_info_xml AS
SELECT c.id as customer_id, (xmlelement(name "Customer", xmlelement(name "Name", c.name),
                                    xmlelement(name "Address", xmlelement(name "Street", xmlattributes(c.number as number),c.street),
                                                                xmlelement(name "City", c.city),
                                                                xmlelement(name "Country", c.country),
                                                                xmlelement(name "email", cps.contact_info)
                                                                  )
 --                                   xmlelement(name "Contacts", xmlelement(name "Contact", xmlforest(cc.name as "Name",
 --                                                                                                    cc.phone as "Phone",
  --                                                                                                   cc.email as "Email")))                                     
)) AS xml
FROM customers as c, contact_types as ct, customer_personal_contacts as cps
WHERE ct.id = cps.contact_types_id AND c.id = cps.customer_id;


CREATE TABLE customer_contact_xml AS 
SELECT cc.customer_id as customer_id, (xmlelement(name "Contacts",xmlagg(xmlelement(name "Customer",xmlforest(cc.name as "Name", cc.phone as "Phone", cc.email as "Email"))))) AS xml 
FROM customers as c, customer_contacts as cc
WHERE c.id = cc.customer_id
GROUP BY cc.customer_id;

CREATE TABLE customer_order_xml AS
SELECT o.customer_id as customer_id, (xmlelement(name "Orders",xmlagg(xmlelement(name "order",xmlforest(o.order_date as "date", o.ship_by as "ship_by", o.discount as "discount"))))) AS xml

--SELECT *
FROM orders as o
GROUP BY o.customer_id
ORDER BY o.customer_id;

CREATE TABLE customer_item_xml AS
SELECT o.customer_id as customer_id, o.id as order_id, (xmlelement(name "Items",xmlagg(xmlelement(name "item", xmlforest(i.name as "name", od.quantity as "quantity", i.price as "price"))))) AS xml
FROM orders as o, items as i, order_details as od
WHERE o.id = od.order_id AND i.id = items_id 
GROUP BY o.customer_id, o.id
ORDER BY o.id;

-- SELECT * FROM customer_info_xml;
-- SELECT * FROM customer_contact_xml;
-- SELECT * FROM customer_order_xml;
-- SELECT * FROM customer_item_xml;

CREATE TABLE customers_xml (
    id serial PRIMARY KEY,
    customer_details xml
);

CREATE FUNCTION insert_xml() RETURNS void AS $$
DECLARE
        customer xml;
BEGIN 
       FOR customer IN (select unnest(xpath('/Customers/Customer',(select documents from hw1_task1.xmldata LIMIT 1)))) LOOP
           -- Insert customers info 
           INSERT INTO customers_xml (customer_details) VALUES (customer);
       END LOOP;
      
RETURN;
END;
$$
LANGUAGE plpgsql;

SELECT insert_xml();

-- TASK4: 4. On each one of these databases, write and run the following queries:
-- (a) List the names of customers who have placed an order with an item that has quantity > 2.

-- Plain Relationa tables
SELECT name 
FROM order_details as od, orders as o, customers as c 
WHERE od.order_id = o.id AND c.id = o.customer_id and od.quantity = 4;
-- (b) List the names of customers who have placed an order where all the items in the order have
-- quantity > 2.

-- Plain relational tables
SELECT DISTINCT c.name 
FROM (SELECT t1.customer_id 
      FROM (SELECT o.customer_id as customer_id, o.id as order_id, count(od.quantity) 
            FROM orders as o, order_details as od 
            WHERE od.order_id = o.id
            GROUP BY o.customer_id, o.id
            ORDER BY o.customer_id) as t1,
            (SELECT order_id, count(quantity) 
             FROM order_details as od 
             WHERE quantity > 2 
             GROUP BY od.order_id
              ORDER BY od.order_id) as t2 
     WHERE t1.order_id = t2.order_id and t1.count = t2.count) as t1, customers as c
 WHERE t1.customer_id = c.id;

-- (c) List the customers who have placed the most expensive order (to nd the cost of an order, you
-- need to add up the cost of all items; the cost of each item is the price of that item times the
-- quantity).

--Plain Relational tables
SELECT c.name FROM (SELECT t1.order_id, sum(t1.total) as total 
                    FROM (SELECT od.order_id,  sum(od.quantity* i.price) as total
			  FROM order_details as od, items as i 
			  WHERE od.items_id = i.id 
                          GROUP BY od.order_id, od.items_id
                          ORDER BY od.order_id) as t1
                    GROUP BY order_id 
                    ORDER BY total DESC LIMIT 1) as t1, orders as o, customers as c
WHERE t1.order_id = o.id AND c.id = o.customer_id;
