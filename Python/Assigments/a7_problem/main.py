from src.ui.ui_class import *
import tests
import unittest
import configparser

if __name__ == "__main__":
  config = configparser.RawConfigParser()
  config.read('config.properties')
  rep = config.get('RepositorySection','repository.name')
  filename = config.get('RepositorySection',f'repository.filename_for_{rep.lower()}')
  test_suite = unittest.defaultTestLoader.loadTestsFromModule(tests)
  
  ui = UI(rep,filename)
  ui.start()