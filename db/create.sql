DROP TABLE IF EXISTS tag;
DROP TABLE IF EXISTS user;
DROP TABLE IF EXISTS ext;
DROP TABLE IF EXISTS tag_user;
DROP TABLE IF EXISTS content;
DROP TABLE IF EXISTS tag_user_content;

CREATE TABLE tag (
       id INTEGER PRIMARY KEY,
       name TEXT unique
);

CREATE TABLE user (
       id INTEGER PRIMARY KEY,
       name TEXT UNIQUE
);

CREATE TABLE ext (
       id INTEGER PRIMARY KEY,
       ip TEXT UNIQUE
);

CREATE TABLE tag_user(
       id INTEGER PRIMARY KEY,
       tid INTEGER NOT NULL,
       target INTEGER NOT NULL,
       uid INTEGER NOT NULL
);

CREATE TABLE content (
       id INTEGER PRIMARY KEY,
       content TEXT,
       updated DATE
);

CREATE TABLE tag_user_content(
       id INTEGER PRIMARY KEY,
       tid INTEGER NOT NULL,
       uid INTEGER NOT NULL, -- target
       cid INTEGER NOT NULL
);