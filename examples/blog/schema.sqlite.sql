CREATE TABLE IF NOT EXISTS `authors` (
  `id` INTEGER NOT NULL PRIMARY KEY ASC AUTOINCREMENT,
  `email` varchar(255) NOT NULL,
  `password` varchar(64) NOT NULL,
  `salt` varchar(64) NOT NULL
);
CREATE UNIQUE INDEX `unique_email` ON `authors` (`email`);

CREATE TABLE IF NOT EXISTS `blogentries` (
  `id` INTEGER NOT NULL PRIMARY KEY ASC AUTOINCREMENT,
  `author` INTEGER NOT NULL,
  `title` varchar(255) NOT NULL,
  `text` text NOT NULL
);
CREATE INDEX `authors_key` ON `blogentries` (`author`);

CREATE TABLE IF NOT EXISTS `relatedTags` (
  `id` INTEGER NOT NULL PRIMARY KEY ASC AUTOINCREMENT,
  `blogentry` INTEGER NOT NULL,
  `tag` INTEGER NOT NULL
);
CREATE UNIQUE INDEX `blogentries_key` ON `relatedTags` (`blogentry`);
CREATE UNIQUE INDEX `tags_key` ON `relatedTags` (`tag`);

CREATE TABLE IF NOT EXISTS `tags` (
  `id` INTEGER NOT NULL PRIMARY KEY ASC AUTOINCREMENT,
  `name` varchar(255) NOT NULL
);
