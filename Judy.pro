
TEMPLATE = subdirs
SUBDIRS += 3rd-party MetaGen Engine Player IDE

Engine.depends += 3rd-party
Engine.depends += MetaGen
Player.depends = Engine
IDE.depends = Engine
