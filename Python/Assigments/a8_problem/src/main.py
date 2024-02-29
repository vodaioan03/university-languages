from ui.ui_conolse import UI
from ui.errors import *

import tests
import unittest

if __name__ == "__main__":
  test_suite = unittest.defaultTestLoader.loadTestsFromModule(tests)
  test_result = unittest.TextTestRunner(verbosity=2).run(test_suite)
  ui_class = UI()
  ui_class.start()
