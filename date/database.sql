CREATE TABLE book (
    id UUID NOT NULL PRIMARY KEY,
    title VARCHAR(50) NOT NULL,
    author VARCHAR(50) NOT NULL,
    year_published INT NOT NULL,
    is_available BOOLEAN DEFAULT TRUE
);

CREATE TABLE person (
    reader_id UUID NOT NULL PRIMARY KEY,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    email VARCHAR(50),
    gender VARCHAR(50) NOT NULL,
    phone_number VARCHAR(50) NOT NULL,
    book_id UUID REFERENCES book(id),
    UNIQUE(email),
    UNIQUE(phone_number)
);

CREATE TABLE borrow (
    borrow_id UUID NOT NULL PRIMARY KEY,
    reader_id UUID NOT NULL,
    book_id UUID NOT NULL,
    borrow_date DATE NOT NULL,
    return_date DATE,
    CONSTRAINT fk_reader
        FOREIGN KEY(reader_id) 
        REFERENCES person(reader_id),
    CONSTRAINT fk_book
        FOREIGN KEY(book_id) 
        REFERENCES book(id)
);

-- Insert data into the person table with reader_id auto-generated
INSERT INTO person (reader_id, first_name, last_name, email, gender, phone_number) VALUES 
(uuid_generate_v4(), 'Ania', 'Kowalska', 'akowalska0@edublogs.org', 'Kobieta', '694-688-721'),
(uuid_generate_v4(), 'Jan', 'Nowak', 'jnowak1@kickstarter.com', 'Mezczyzna', '606-364-225'),
(uuid_generate_v4(), 'Kasia', 'Wisniewska', 'kwisniewska2@youku.com', 'Kobieta', '791-968-997'),
(uuid_generate_v4(), 'Patryk', 'Sikora', 'psikora3@hatena.ne.jp', 'Mezczyzna', '999-999-999'),
(uuid_generate_v4(), 'Artur', 'Lach', 'alach4@buzzfeed.com', 'Mezczyzna', '606-342-123');

-- Insert data into the books table
INSERT INTO book (id, title, author, year_published) VALUES 
(uuid_generate_v4(), 'Zabic, Dziecko, Zabic (Operacja strach)', 'Emanuele Perkis', 2010),
(uuid_generate_v4(), 'Rownolegli synowie', 'Virgil Bachellier', 2011),
(uuid_generate_v4(), 'Noc otwarcia', 'Liza Allcock', 2012),
(uuid_generate_v4(), 'Zycie jak dom', 'Dov Randalston', 1999),
(uuid_generate_v4(), 'Rick', 'Dallas Abelov', 2006),
(uuid_generate_v4(), 'Szyb', 'Danette Tancock', 1985),
(uuid_generate_v4(), 'Dryfujac w Tokio (Tenten)', 'Susie Nawton', 2005),
(uuid_generate_v4(), 'Odcięte ramie', 'Esme Duham', 2004),
(uuid_generate_v4(), 'Nawiedzony w Connecticut', 'Angela Bartelet', 2009),
(uuid_generate_v4(), 'Wsciekli szalency', 'Jenifer Woodcraft', 1997);
