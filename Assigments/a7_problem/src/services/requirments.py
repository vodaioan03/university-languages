from src.domain.book import *
from src.repository.memoryrep import *
from src.repository.pickelrep import *
from src.repository.textfilerep import *  
from src.repository.repository import *
from src.repository.jsonrep import *
import sys

class LogicalThings:
  
  def __init__(self,rep,filename):
    """Logical things

    Args:
        rep (_type_): name of repository function
        filename (_type_): filename for add
    """
    self.rep = getattr(sys.modules[__name__], rep)(filename)
  
  def add_book(self,isbn,author,title):
    """Adding book function

    Args:
        isbn (str): idbn for book, need to be unique
        author (str): author of book
        title (str): title of book
    """

    self.rep.add_book(Book(isbn,author,title))
  
  def filter_list(self,title_for_delete):
    """Delete from list all books starting with an word

    Args:
        title_for_delete (str): word for delete
    """
    books = self.rep.get_books()
    new_books = []
    for i in range(len(books)):
      title = books[i].title
      title = title.split()
      if title[0].lower() != title_for_delete.lower():
        new_books.append(books[i])
    self.rep.modify_list(new_books)
  
  def undo_last_operation(self):
    """Undo last operation
    """
    self.rep.undo_list()
    
    
  def get_book_for_display(self):
    """Return list of books for display in UI

    Returns:
        list: list of books
    """
    return self.rep.get_books()


class VerifyInput:
  
  def __init__(self,logicthings) -> None:
    """Init verify inpput

    Args:
        logicthings (_type_): class logic
    """
    self.logic = logicthings
  
  def verify_add_Book(self,isbn_verify):
    """Verify if all conditions for add are good

    Args:
        isbn_verify (str): new isbn for book

    Raises:
        ValueError: The isbn is alredy added.
    """
    books = self.logic.rep.get_books()
    for book in books:
      if book.isbn.lower() == isbn_verify.lower():
        raise ValueError("The isbn is alredy added.")
  
  def verify_display(self):
    """Verify if all conditions for display are good.

    Raises:
        ValueError: List is empty
    """
    books = self.logic.rep.get_books()
    if len(books) == 0:
      raise ValueError("List is empty. You can use add or undo.")
  
  def verify_filter(self,input_title):
    """Verify if all conditions are been respected

    Args:
        input_title (_type_): _description_

    Raises:
        ValueError: List is empty
        ValueError: Type only one word for filter.
    """
    books = self.logic.rep.get_books()
    if len(books) == 0:
      raise ValueError("List is empty. You can use only Add command.")
    if len(input_title.split()) != 1:
       raise ValueError("Type only one word for filter.")
  
  def verify_undo(self):
    """Verify if all conditions for undo are respected

    Raises:
        ValueError: List is empty
    """
    books = self.logic.rep.length_of()
    if books == 1:
      raise ValueError("List is empty. You can use only Add command.")