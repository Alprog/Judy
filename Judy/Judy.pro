
TEMPLATE = subdirs
SUBDIRS += Engine Player IDE

Player.depends = Engine
IDE.depends = Engine
