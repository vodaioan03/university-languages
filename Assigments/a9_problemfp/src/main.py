#VODA IOAN
from ui.gui import *
from ui.errors import *
import sys
from services.undo_service import *

import tests
import unittest
import configparser

if __name__ == "__main__":
  
  config = configparser.RawConfigParser()
  config.read('src\\settingsa9.properties')
  rep = config.get('RepositorySetting','repository.name')
  filename_books = config.get('RepositorySetting','repository.books')
  filename_clients = config.get('RepositorySetting','repository.clients')
  filename_rentals = config.get('RepositorySetting','repository.rentals')
  test_suite = unittest.defaultTestLoader.loadTestsFromModule(tests)
  test_result = unittest.TextTestRunner(verbosity=2).run(test_suite)
  undo_service = UndoService()
  ui_use = "UI"
  ui_class = getattr(sys.modules[__name__], ui_use)(rep,filename_books,filename_clients,filename_rentals,undo_service)
  ui_class.start()
