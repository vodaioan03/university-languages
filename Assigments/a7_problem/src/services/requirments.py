from src.domain.book import *
from src.repository.memoryrep import *
from src.repository.pickelrep import *
from src.repository.textfilerep import *  
import sys

class LogicalThings:
  
  def __init__(self,rep,filename):
    self.rep = getattr(sys.modules[__name__], rep)(filename)
  
  def add_book(self,isbn,author,title):
    print("Add")
    self.rep.add_book(Book(isbn,author,title))

  def display_list_of_books(self):
    print("display in \n")
    books = self.rep.get_books()
    for book in books:
      string = f'[{books.index(book)}] {book.isbn} | {book.author} | {book.title}'
      print(string)
  
  def filter_list(self,title_for_delete):
    print("filter")
    books = self.rep.get_books()
    new_books = []
    for i in range(len(books)):
      title = books[i].title
      title = title.split()
      if title[0].lower() != title_for_delete.lower():
        new_books.append(books[i])
    self.rep.modify_list(new_books)
  
  def undo_last_operation(self):
    print("undo")
    self.rep.undo_list()


class VerifyInput:
  
  def __init__(self,logicthings) -> None:
    self.logic = logicthings
  
  def verify_add_Book(self,isbn_verify):
    books = self.logic.rep.get_books()
    for book in books:
      if book.isbn.lower() == isbn_verify.lower():
        raise ValueError("The isbn is alredy added.")
  
  def verify_display(self):
    books = self.logic.rep.get_books()
    if len(books) == 0:
      raise ValueError("List is empty. You can use only Add command.")
  
  def verify_filter(self,input_title):
    books = self.logic.rep.get_books()
    if len(books) == 0:
      raise ValueError("List is empty. You can use only Add command.")
    if len(input_title.split()) != 1:
       raise ValueError("Type only one word for filter.")
  
  def verify_undo(self):
    books = self.logic.rep.get_books()
    if len(books) == 0:
      raise ValueError("List is empty. You can use only Add command.")