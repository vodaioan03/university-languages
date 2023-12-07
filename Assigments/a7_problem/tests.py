from src.services.requirments import *
from src.repository.memoryrep import *
from src.repository.pickelrep import *
from src.repository.textfilerep import *

import unittest


class TestLogicalThings(unittest.TestCase):

    def setUp(self):
        self.repository = "Memory"
        self.logical_things = LogicalThings(self.repository, "test_filename")

    def test_add_book(self):
        self.logical_things.add_book("100", "Author", "Title")
        self.logical_things.add_book("101", "Author", "Title")
        self.logical_things.add_book("102", "Author", "Title")
        self.logical_things.add_book("103", "Author", "Title")
        self.logical_things.add_book("104", "Author", "Title")
        books = self.logical_things.get_book_for_display()
        self.assertEqual(len(books), 5)
        self.assertEqual(books[0].isbn, "100")
        self.assertEqual(books[1].isbn, "101")
        self.assertEqual(books[2].isbn, "102")
        self.assertEqual(books[3].isbn, "103")
        self.assertEqual(books[4].isbn, "104")
    
    def test_undo(self):
      self.logical_things.add_book("100", "Author", "Title")
      self.logical_things.add_book("101", "Author", "Title")
      self.logical_things.add_book("102", "Author", "Title")
      self.logical_things.add_book("103", "Author", "Title")
      self.logical_things.add_book("104", "Author", "Title")
      self.logical_things.undo_last_operation()
      self.logical_things.undo_last_operation()
      books = self.logical_things.get_book_for_display()
      self.assertEqual(len(books), 3)
      self.assertEqual(books[0].isbn, "100")
      self.assertEqual(books[1].isbn, "101")
      self.assertEqual(books[2].isbn, "102")
      
    def test_filter(self):
      self.logical_things.add_book("100", "Author", "Title")
      self.logical_things.add_book("101", "Author", "Tait")
      self.logical_things.add_book("102", "Author", "Title")
      self.logical_things.add_book("103", "Author", "Title")
      self.logical_things.add_book("104", "Author", "Title")
      self.logical_things.filter_list("Title")
      books = self.logical_things.get_book_for_display()
      self.assertEqual(len(books),1)
      self.assertEqual(books[0].isbn, "101")
      
    def test_get_book_for_display(self):
        self.logical_things.add_book("100", "Author", "Title")
        self.logical_things.add_book("101", "Author", "Tait")
        self.logical_things.add_book("102", "Author", "Title")
        self.logical_things.add_book("103", "Author", "Title")
        self.logical_things.add_book("104", "Author", "Title")
        books = self.logical_things.get_book_for_display()
        self.assertEqual(len(books),5)
    
class TestVerifyInput(unittest.TestCase):

    def setUp(self):
        self.repository = "Memory"
        self.logical_things = LogicalThings(self.repository, "test_filename")
        self.verify_input = VerifyInput(self.logical_things)
    
    def test_verify_display(self):
        with self.assertRaises(ValueError):
            self.verify_input.verify_display()
        pass

    def test_verify_add_Book_existing_isbn(self):
        self.logical_things.add_book("100", "Author", "Title")
        self.logical_things.add_book("101", "Author", "Title")
        self.logical_things.add_book("102", "Author", "Title")
        self.logical_things.add_book("103", "Author", "Marc")
        with self.assertRaises(ValueError):
            self.verify_input.verify_add_Book("100")
            self.verify_input.verify_add_Book("101")
            self.verify_input.verify_add_Book("102")
            self.verify_input.verify_add_Book("103")
    
    def test_verify_filter(self):
        books = self.logical_things.get_book_for_display()
        with self.assertRaises(ValueError):
            self.verify_input.verify_filter("MArcel 2")
            self.verify_input.verify_filter("")
    
    def test_verify_undo(self):
        with self.assertRaises(ValueError):
            self.verify_input.verify_undo()
            self.verify_input.verify_undo()
            self.verify_input.verify_undo()
            self.verify_input.verify_undo()
            self.verify_input.verify_undo()
            self.verify_input.verify_undo()
            
            
            
class TestLogicalThingsForText(unittest.TestCase):

    def setUp(self):
        self.repository = "Text"
        self.logical_things = LogicalThings(self.repository, "test_filename")

    def test_add_book(self):
        self.logical_things.add_book("100", "Author", "Title")
        self.logical_things.add_book("101", "Author", "Title")
        self.logical_things.add_book("102", "Author", "Title")
        self.logical_things.add_book("103", "Author", "Title")
        self.logical_things.add_book("104", "Author", "Title")
        books = self.logical_things.get_book_for_display()
        self.assertEqual(len(books), 5)
        self.assertEqual(books[0].isbn, "100")
        self.assertEqual(books[1].isbn, "101")
        self.assertEqual(books[2].isbn, "102")
        self.assertEqual(books[3].isbn, "103")
        self.assertEqual(books[4].isbn, "104")
    
    def test_undo(self):
      self.logical_things.add_book("100", "Author", "Title")
      self.logical_things.add_book("101", "Author", "Title")
      self.logical_things.add_book("102", "Author", "Title")
      self.logical_things.add_book("103", "Author", "Title")
      self.logical_things.add_book("104", "Author", "Title")
      self.logical_things.undo_last_operation()
      self.logical_things.undo_last_operation()
      books = self.logical_things.get_book_for_display()
      self.assertEqual(books[0].isbn, "100")
      self.assertEqual(books[1].isbn, "101")
      self.assertEqual(books[2].isbn, "102")
      
    def test_filter(self):
      self.logical_things.add_book("100", "Author", "Title")
      self.logical_things.add_book("101", "Author", "Tait")
      self.logical_things.add_book("102", "Author", "Title")
      self.logical_things.add_book("103", "Author", "Title")
      self.logical_things.add_book("104", "Author", "Title")
      self.logical_things.filter_list("Title")
      books = self.logical_things.get_book_for_display()
      self.assertEqual(books[0].isbn, "101")
      
    def test_get_book_for_display(self):
        self.logical_things.add_book("100", "Author", "Title")
        self.logical_things.add_book("101", "Author", "Tait")
        self.logical_things.add_book("102", "Author", "Title")
        self.logical_things.add_book("103", "Author", "Title")
        self.logical_things.add_book("104", "Author", "Title")
        books = self.logical_things.get_book_for_display()
        
        
class TestLogicalThingsForPickle(unittest.TestCase):

    def setUp(self):
        self.repository = "Pickle"
        self.logical_things = LogicalThings(self.repository, "test_filename")

    def test_add_book(self):
        self.logical_things.add_book("100", "Author", "Title")
        self.logical_things.add_book("101", "Author", "Title")
        self.logical_things.add_book("102", "Author", "Title")
        self.logical_things.add_book("103", "Author", "Title")
        self.logical_things.add_book("104", "Author", "Title")
        books = self.logical_things.get_book_for_display()
        self.assertEqual(books[0].isbn, "100")
        self.assertEqual(books[1].isbn, "101")
        self.assertEqual(books[2].isbn, "102")
        self.assertEqual(books[3].isbn, "103")
        self.assertEqual(books[4].isbn, "104")
    
    def test_undo(self):
      self.logical_things.add_book("100", "Author", "Title")
      self.logical_things.add_book("101", "Author", "Title")
      self.logical_things.add_book("102", "Author", "Title")
      self.logical_things.add_book("103", "Author", "Title")
      self.logical_things.add_book("104", "Author", "Title")
      self.logical_things.undo_last_operation()
      self.logical_things.undo_last_operation()
      books = self.logical_things.get_book_for_display()
      self.assertEqual(books[0].isbn, "100")
      self.assertEqual(books[1].isbn, "101")
      self.assertEqual(books[2].isbn, "102")
      
    def test_filter(self):
      self.logical_things.add_book("100", "Author", "Title")
      self.logical_things.add_book("101", "Author", "Tait")
      self.logical_things.add_book("102", "Author", "Title")
      self.logical_things.add_book("103", "Author", "Title")
      self.logical_things.add_book("104", "Author", "Title")
      self.logical_things.filter_list("Title")
      books = self.logical_things.get_book_for_display()
      self.assertEqual(books[0].isbn, "101")
      
    def test_get_book_for_display(self):
        self.logical_things.add_book("100", "Author", "Title")
        self.logical_things.add_book("101", "Author", "Tait")
        self.logical_things.add_book("102", "Author", "Title")
        self.logical_things.add_book("103", "Author", "Title")
        self.logical_things.add_book("104", "Author", "Title")
        books = self.logical_things.get_book_for_display()
        self.assertEqual(len(books),5)