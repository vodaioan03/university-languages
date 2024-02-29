import unittest
from ui import *
from service import *
from repository import *
from domain import *


class TestLogicalThings(unittest.TestCase):

    def setUp(self):
       self.service = Service()

    def test_forCreateQuiz(self):
      self.service.createQuiz("easy",10,"testquiz10.txt")
      fileopen = open("testquiz10.txt","r")
      self.assertNotEqual(fileopen,None)
      allquestions = fileopen.readlines()
      
      self.assertEqual(len(allquestions),10)
      fileopen.close()
      
      
    def test_createNewQuizFile(self):
      self.service.repository.createNewQuizFile("testfile123.txt",[])
      fileopen = open("testfile123.txt","r")
      self.assertNotEqual(fileopen,None)
      
      fileopen.close()
      
      
if __name__ == '__main__': 
    unittest.main() 
    