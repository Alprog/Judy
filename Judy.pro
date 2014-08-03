
TEMPLATE = subdirs
SUBDIRS += Engine Player IDE 3rd-party

Player.depends = Engine
IDE.depends = Engine
