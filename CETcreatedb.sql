--CET Application 
--This file is for creating and populating data into tables

--Type: sqlite3 nameofdatabase.extension
--      .read CETcreatedb.sql
--in console

--NOTES
--QSQLITE SQLite version 3 data type | SQL type description 						  | Recommended input (C++ or Qt data type)
--NULL								 | NULL value.	    	 					      | NULL
--									 |												  |
--INTEGER							 | Signed integer, stored in 8, 16, 24, 32, 48,   |	typedef qint8/16/32/64
--									 | or 64-bits depending on the magnitude of the   |
--									 | value.										  |							   
--									 |												  |
--REAL								 | 64-bit floating point value.					  | By default mapping to QString	  
--									 | 												  |
--TEXT								 | Character string (UTF-8, UTF-16BE or  		  | Mapped to QString
--									 | UTF-16-LE).									  |	
--									 |												  |
--CLOB								 | Character large string object				  | Mapped to QString
--									 |												  |
--BLOB								 | The value is a BLOB of data, stored exactly    | Mapped to QByteArray
--									 | as it was input.								  |


--The is delete table if there are table with the same name in the current database
--Will display error if table with the same namwe does not exist, can be ignored

drop table CaseReport;
drop table DiseaseType;
drop table Region;
drop table Shipment;
drop table ShipmentDetail;
drop table Inventory;
drop table SupplyType;
drop table User;
drop table IdNumbers;
drop table Province;


--CaseReport
--creating the Table called CaseReport
create table CaseReport(
	id integer NOT NULL primary key,
	regionId integer NOT NULL references Region(id),
	dateOfReport varchar(15) NOT NULL,
	diseaseType integer NOT NULL references DiseaseType(id),
	correction integer NOT NULL,
	quantity integer NOT NULL
	);

--inserting data into the table CaseReport
insert into CaseReport values (14, 5931, "2010-06-09", 6202, 0, 15);
insert into CaseReport values (15, 5932, "2010-06-12", 6202, 0, 45);
insert into CaseReport values (16, 5932, "2010-07-30", 6203, 0, 16);
insert into CaseReport values (17, 4615, "2010-08-10", 6207, 0, 100);
insert into CaseReport values (18, 1218, "2010-08-11", 6209, 0, 260);
insert into CaseReport values (19, 4615, "2010-09-19", 6210, 0, 19);
insert into CaseReport values (20, 4707, "2010-10-16", 6206, 0, 78);
insert into CaseReport values (21, 4826, "2010-10-23", 6209, 0, 24);
insert into CaseReport values (22, 1011, "2010-11-18", 6208, 0, 47);
insert into CaseReport values (23, 1305, "2010-11-23", 6208, 0, 57);


--DiseaseType
--creating the Table called DiseaseType
create table DiseaseType(
	id integer NOT NULL primary key,
	name varchar(50) NOT NULL,
	colorIndex integer NOT NULL,
	enabled integer NOT NULL
	);

--inserting data into the table DiseaseType
insert into DiseaseType values (6202, "Smallpox", 0, 1);
insert into DiseaseType values (6203, "Measles", 1, 1);
insert into DiseaseType values (6204, "Yellow Fever", 2, 1);
insert into DiseaseType values (6205, "Influenza", 3, 1);
insert into DiseaseType values (6206, "Cholera", 4, 1);
insert into DiseaseType values (6207, "Typhus", 5, 1);
insert into DiseaseType values (6208, "HIV/AIDS", 7, 1);
insert into DiseaseType values (6209, "H1N1", 8, 1);
insert into DiseaseType values (6210, "Dengue Fever", 9, 1);



--Province
--creating the Table called Province
create table Province(
	id integer NOT NULL primary key,
	name varchar(50) NOT NULL
	);

--inserting data into the table Province
insert into Province values(1, "Alberta");
insert into Province values(2, "British Columbia");
insert into Province values(3, "Manitoba");
insert into Province values(4, "New Brunswick");
insert into Province values(5, "Newfoundland and Labrador");
insert into Province values(6, "Northwest Territories");
insert into Province values(7, "Nova Scotia");
insert into Province values(8, "Nunavut");
insert into Province values(9, "Ontario");
insert into Province values(10, "Prince Edward Island");
insert into Province values(11, "Quebec");
insert into Province values(12, "Saskatchewan");
insert into Province values(13, "Yukon");



--Region
--creating the Table called Region
create table Region(
	id integer NOT NULL primary key,
	provinceId integer NOT NULL references Province(id),
	name varchar(50) NOT NULL,
	centerX integer,
	centerY integer
	);

--inserting data into the table Region


--Newfoundland and Labrador
insert into Region values (1011, 5, "Eastern Regional Integrated Health Authority", 1958, 520);
insert into Region values (1012, 5, "Central Regional Integrated Health Authority", 1876, 529);
insert into Region values (1013, 5, "Western Regional Integrated Health Authority", 1820, 513);
insert into Region values (1014, 5, "Labrador-Grenfell Regional Integrated Health Authority", 1673, 621);
--Prince Edward Island
insert into Region values (1111, 10, "Prince Edward Island Health Region", 0, 0);
insert into Region values (1101, 10, "Kings County", 1769, 366);
insert into Region values (1102, 10, "Queens County", 1754, 360);
insert into Region values (1103, 10, "Prince County", 1731, 358);
--Nova Scotia
--insert into Region values (1201, 7, "Zone 1", 0, 0);
--insert into Region values (1202, 7, "Zone 2", 0, 0);
--insert into Region values (1203, 7, "Zone 3", 0, 0);
--insert into Region values (1204, 7, "Zone 4", 0, 0);
--insert into Region values (1205, 7, "Zone 5", 0, 0);
--insert into Region values (1206, 7, "Zone 6", 0, 0);
insert into Region values (1211, 7, "DHA1", 1746, 276);
insert into Region values (1212, 7, "DHA2", 1727, 255);
insert into Region values (1213, 7, "DHA3", 1733, 290);
insert into Region values (1214, 7, "DHA4", 1765, 326);
insert into Region values (1215, 7, "DHA5", 1743, 331);
insert into Region values (1216, 7, "DHA6", 1778, 341);
insert into Region values (1217, 7, "DHA7", 1807, 352);
insert into Region values (1218, 7, "DHA8", 1823, 388);
insert into Region values (1219, 7, "DHA9", 1769, 298);
--New Brunswick
insert into Region values (1301, 4, "Region 1", 1714, 336);
insert into Region values (1302, 4, "Region 2", 1700, 295);
insert into Region values (1303, 4, "Region 3", 1671, 313);
insert into Region values (1304, 4, "Region 4", 1623, 350);
insert into Region values (1305, 4, "Region 5", 1647, 374);
insert into Region values (1306, 4, "Region 6", 1677, 377);
insert into Region values (1307, 4, "Region 7", 1681, 357);
--Quebec
insert into Region values (2401, 11, "Région du Bas-Saint-Laurent", 1600, 378);
insert into Region values (2402, 11, "Région du Saguenay-Lac-Saint-Jean", 1527, 364);
insert into Region values (2403, 11, "Région de la Capitale Nationale", 1548, 304);
insert into Region values (2404, 11, "Région de la Mauricie et du Centre-du-Québec", 1495, 306);
insert into Region values (2405, 11, "Région de l'Estrie", 1552, 243);
insert into Region values (2406, 11, "Région de Montréal", 1506, 231);
insert into Region values (2407, 11, "Région de l'Outaouais", 1427, 233);
insert into Region values (2408, 11, "Région de l'Abitibi-Témiscamingue", 1378, 300);
insert into Region values (2409, 11, "Région de la Côte-Nord", 1600, 468);
insert into Region values (2410, 11, "Région du Nord-du-Québec", 1404, 464);
insert into Region values (2411, 11, "Région de la Gaspésie-Îles-de-la-Madeleine", 1669, 419);
insert into Region values (2412, 11, "Région de la Chaudière-Appalaches", 1568, 286);
insert into Region values (2413, 11, "Région de Laval", 1500, 238);
insert into Region values (2414, 11, "Région de Lanaudière", 1490, 267);
insert into Region values (2415, 11, "Région des Laurentides", 1457, 265);
insert into Region values (2416, 11, "Région de la Montérégie", 1526, 235);
insert into Region values (2417, 11, "Région du Nunavik", 1435, 665);
insert into Region values (2418, 11, "Région des Terres-Cries-de-la-Baie-James", 1313, 498);
--Ontario
--insert into Region values (3526, 9, "The District of Algoma Health Unit", 0, 0);
--insert into Region values (3527, 9, "Brant County Health Unit", 0, 0);
--insert into Region values (3530, 9, "Durham Regional Health Unit", 0, 0); 
--insert into Region values (3531, 9, "Elgin-St. Thomas Health Unit", 0, 0);
--insert into Region values (3533, 9, "Grey Bruce Health Unit", 0, 0; 
--insert into Region values (3534, 9, "Haldimand-Norfolk Health Unit", 0, 0);
--insert into Region values (3535, 9, "Haliburton, Kawartha, Pine Ridge District Health Unit", 0, 0);
--insert into Region values (3536, 9, "Halton Regional Health Unit", 0, 0);
--insert into Region values (3537, 9, "City of Hamilton Health Unit", 0, 0;
--insert into Region values (3538, 9, "Hastings and Prince Edward Counties Health Unit", 0, 0);
--insert into Region values (3539, 9, "Huron County Health Unit", 0, 0);
--insert into Region values (3540, 9, "Chatham-Kent Health Unit", 0, 0);
--insert into Region values (3541, 9, "Kingston, Frontenac, and Lennox and Addington Health Unit", 0, 0);
--insert into Region values (3542, 9, "Lambton Health Unit", 0, 0);
--insert into Region values (3543, 9, "Leeds, Grenville and Lanark District Health Unit", 0, 0);
--insert into Region values (3544, 9, "Middlesex-London Health Unit", 0, 0);
--insert into Region values (3546, 9, "Niagara Regional Area Health Unit", 0, 0);
--insert into Region values (3547, 9, "North Bay Parry Sound District Health Unit", 0, 0);
--insert into Region values (3549, 9, "Northwestern Health Unit", 0, 0);
--insert into Region values (3551, 9, "City of Ottawa Health Unit", 0, 0);
--insert into Region values (3552, 9, "Oxford County Health Unit", 0, 0);
--insert into Region values (3553, 9, "Peel Regional Health Unit", 0, 0);
--insert into Region values (3554, 9, "Perth District Health Unit", 0, 0);
--insert into Region values (3555, 9, "Peterborough County-City Health Unit", 0, 0);
--insert into Region values (3556, 9, "Porcupine Health Unit", 0, 0); 
--insert into Region values (3557, 9, "Renfrew County and District Health Unit", 0, 0);
--insert into Region values (3558, 9, "The Eastern Ontario Health Unit", 0, 0);
--insert into Region values (3560, 9, "Simcoe Muskoka District Health Unit", 0, 0);
--insert into Region values (3561, 9, "Sudbury and District Health Unit", 0, 0);
--insert into Region values (3562, 9, "Thunder Bay District Health Unit", 0, 0);
--insert into Region values (3563, 9, "Timiskaming Health Unit", 0, 0);
--insert into Region values (3565, 9, "Waterloo Health Unit", 0, 0);
--insert into Region values (3566, 9, "Wellington-Dufferin-Guelph Health Unit", 0, 0);
--insert into Region values (3568, 9, "Windsor-Essex County Health Unit", 0, 0);
--insert into Region values (3570, 9, "York Regional Health Unit", 0, 0);
--insert into Region values (3595, 9, "City of Toronto Health Unit", 0, 0);
insert into Region values (3501, 9, "Erie St. Clair", 1298, 68);
insert into Region values (3502, 9, "South West", 1323, 95);
insert into Region values (3503, 9, "Waterloo Wellington", 1340, 118);
insert into Region values (3504, 9, "Hamilton Niagara Haldimand Brant", 1360, 100);
insert into Region values (3505, 9, "Central West", 1347, 134);
insert into Region values (3506, 9, "Mississauga Halton", 1358, 119);
insert into Region values (3507, 9, "Toronto Central", 1369, 126);
insert into Region values (3508, 9, "Central", 1363, 140);
insert into Region values (3509, 9, "Central East", 1387, 162);
insert into Region values (3510, 9, "South East", 1432, 170);
insert into Region values (3511, 9, "Champlain", 1455, 210);
insert into Region values (3512, 9, "North Simcoe Muskoka", 1356, 166);
insert into Region values (3513, 9, "North East", 1278, 252);
insert into Region values (3514, 9, "North West", 1068, 300);
--Manitoba
insert into Region values (4610, 3, "Winnipeg Regional Health Authority", 896, 333);
insert into Region values (4615, 3, "Brandon Regional Health Authority", 830, 339); 
insert into Region values (4620, 3, "North Eastman Regional Health Authority", 933, 390); 
insert into Region values (4625, 3, "South Eastman Regional Health Authority", 919, 306);
insert into Region values (4630, 3, "Interlake Regional Health Authority", 886, 401);
insert into Region values (4640, 3, "Central Regional Health Authority", 868, 341); 
insert into Region values (4645, 3, "Assiniboine Regional Health Authority", 819, 362); 
insert into Region values (4660, 3, "Parkland Regional Health Authority", 827, 415); 
insert into Region values (4670, 3, "Norman Regional Health Authority", 838, 510); 
insert into Region values (4680, 3, "Burntwood Regional Health Authority", 915, 558); 
insert into Region values (4690, 3, "Churchill Regional Health Authority", 982, 655);
--Saskatchewan
insert into Region values (4701, 12, "Sun Country Regional Health Authority", 748, 332);
insert into Region values (4702, 12, "Five Hills Regional Health Authority", 688, 381);
insert into Region values (4703, 12, "Cypress Regional Health Authority", 636, 385); 
insert into Region values (4704, 12, "Regina Qu'Appelle Regional Health Authority", 729, 381); 
insert into Region values (4705, 12, "Sunrise Regional Health Authority", 775, 399);
insert into Region values (4706, 12, "Saskatoon Regional Health Authority", 701, 450); 
insert into Region values (4707, 12, "Heartland Regional Health Authority", 640, 445); 
insert into Region values (4708, 12, "Kelsey Trail Regional Health Authority", 770, 476); 
insert into Region values (4709, 12, "Prince Albert Parkland Regional Health Authority", 719, 490); 
insert into Region values (4710, 12, "Prairie North Regional Health Authority", 648, 498);
insert into Region values (4711, 12, "Mamawetan Churchill River Regional Health Authority", 775, 595); 
insert into Region values (4712, 12, "Keewatin Yatthé Regional Health Authority", 697, 622); 
insert into Region values (4713, 12, "Athabasca Health Authority", 761, 708);
--Alberta
insert into Region values (4821, 1, "Chinook Regional Health Authority", 521,399);
insert into Region values (4822, 1, "Palliser Health Region", 575,407); 
insert into Region values (4823, 1, "Calgary Health Region", 510,461); 
insert into Region values (4824, 1, "David Thompson Regional Health Authority", 531,502); 
insert into Region values (4825, 1, "East Central Health", 594,514);
insert into Region values (4826, 1, "Capital Health", 553,545); 
insert into Region values (4827, 1, "Aspen Regional Health Authority", 592,584); 
insert into Region values (4828, 1, "Peace Country Health", 482,641); 
insert into Region values (4829, 1, "Northern Lights Health Region", 640,650);
--British Columbia
insert into Region values (5911, 2, "East Kootenay", 458,428);
insert into Region values (5912, 2, "Kootenay-Boundary", 424,456); 
insert into Region values (5913, 2, "Okanagan", 359,462); 
insert into Region values (5914, 2, "Thompson/Cariboo", 373,520); 
insert into Region values (5921, 2, "Fraser East", 317,474); 
insert into Region values (5922, 2, "Fraser North", 304,491); 
insert into Region values (5923, 2, "Fraser South", 294,478);
insert into Region values (5931, 2, "Richmond", 285,484); 
insert into Region values (5932, 2, "Vancouver", 291,488); 
insert into Region values (5933, 2, "North Shore/Coast Garibaldi", 297,530); 
insert into Region values (5941, 2, "South Vancouver Island", 264,466); 
insert into Region values (5942, 2, "Central Vancouver Island", 259,499); 
insert into Region values (5943, 2, "North Vancouver Island", 252,553);
insert into Region values (5951, 2, "Northwest", 282,723); 
insert into Region values (5952, 2, "Northern Interior", 373,640); 
insert into Region values (5953, 2, "Northeast", 446,710);
--Yukon
insert into Region values (6001, 13, "Yukon Territory", 319,982);

--Northwest Territories
insert into Region values (6101, 6, "Northwest Territories", 653,866);

--Nunavut 
insert into Region values (6201, 8, "Nunavut", 1379,911);



--Shipment
--creating the Table called Shipment
create table Shipment(
	id integer NOT NULL primary key,
	srcRegion integer NOT NULL references Region(id),
	destRegion integer NOT NULL references Region(id),
	shipmentState int NOT NULL,
	createdDate varchar(15) NOT NULL,
	shippedDate varchar(15),
	receivedDate varchar(15),
	cancelledDate varchar(15),
	notes text
	);

--inserting data into the table Shipment
--insert into Shipment values ();



--ShipmentDetail
--creating the Table called ShipmentDetail
create table ShipmentDetail(
	id integer NOT NULL primary key,
	shipmentId integer NOT NULL references Shipment(id),
	supplyType integer NOT NULL references SupplyType(id),
	quantityRequested int NOT NULL,
	quantityShipped int NOT NULL
	);

--inserting data into the table ShipmentDetail
--insert into ShipmentDetail values ();


--Inventory
--creating the Table called Inventory
create table Inventory(
	id integer NOT NULL primary key,
	regionId integer NOT NULL references Region(id),
	supplyType integer NOT NULL references SupplyType(id),
	quantity integer, 
	required integer
	);

--inserting data into the table Inventory
insert into Inventory values (24, 6001, 6211, 15, 40);
insert into Inventory values (25, 5931, 6212, 9, 10);
insert into Inventory values (26, 5932, 6213, 28, 49);
insert into Inventory values (27, 1305, 6214, 44, 49);
insert into Inventory values (28, 1011, 6214, 1001, 49);
insert into Inventory values (29, 4826, 6220, 12, 49);
insert into Inventory values (30, 4707, 6217, null, 49);
insert into Inventory values (31, 4615, 6212, 117, 49);
insert into Inventory values (32, 1218, 6216, 432, 49);
insert into Inventory values (33, 5932, 6215, 49, 49);


--SupplyType
--creating the Table called SupplyType
create table SupplyType(
	id integer NOT NULL primary key,
	name varchar(50) NOT NULL,
	colorIndex integer NOT NULL,
	enabled integer NOT NULL
	);

--inserting data into the table SupplyType
insert into SupplyType values (6211, "Tamiflu", 0, 1);
insert into SupplyType values (6212, "ECMO", 1, 1);
insert into SupplyType values (6213, "Dialysis Machine", 2, 1);
insert into SupplyType values (6214, "Medical Ventilator", 3, 1);
insert into SupplyType values (6215, "Ibuprofen", 4, 1);
insert into SupplyType values (6216, "YF-Vax", 5, 1);
insert into SupplyType values (6217, "Vibramycin", 6, 1);
insert into SupplyType values (6218, "Abacavir", 7, 1);
insert into SupplyType values (6219, "Symmetrel", 8, 1);
insert into SupplyType values (6220, "Panadol", 9, 1);

--User
--creating the Table called User
create table User(
	id integer NOT NULL primary key,
	name varchar(50) NOT NULL,
	passwordHash varchar(50) NOT NULL,
	defaultRegionId integer NOT NULL references Region(id),
	locked int NOT NULL,
	role int NOT NULL
	);

--inserting data into the table User
insert into User values (6221, "Paulina", "abc", 5, 0, 1);
insert into User values (6222, "Mike", "abc", 5, 0, 0);
insert into User values (6223, "Spencer", "abc", 5, 0, 1);
insert into User values (6224, "Gavin", "abc", 5, 0, 2);


--IdNumbers
--creating the Table called IdNumbers
--Numbers will appear here when new entities are created
create table IdNumbers(
	id integer NOT NULL primary key
);

--inserting data into the table recipe
insert into IdNumbers values (6225);