class Book:
  def __init__(self,isbn,author,title):
    self.isbn = isbn
    self.author = author
    self.title = title
    
  def modify_isbn(self,new_isbn):
    self.isbn = new_isbn
    
  def modify_title(self,new_title):
    self.title = new_title
    
  def modify_author(self,new_author):
    self.author = new_author
  