
TEMPLATE = subdirs
SUBDIRS += Engine Player IDE 3rd-Party

Player.depends = Engine
IDE.depends = Engine
