


class Quiz:
  
  def __init__(self) -> None:
    self.questions = []
    self.score = 0
    self.scores = {"easy":1,"medium":2,"hard":3}

  def addScore(self,difficulty):
    difficulty = difficulty.strip()
    if difficulty not in self.scores:
      raise ValueError("invalid difficulty in score")
    self.score += self.scores[difficulty]
    
  def addQuestion(self,question):
    self.questions.append(question)  
  
  def getScore(self):
    return self.score
  
  def getQuestions(self):
    return self.questions
  
  def getOneQuestion(self):
    if len(self.questions) == 0:
      raise ValueError("No questions")
    firstquestion = self.questions[0]
    del self.questions[0]
    return firstquestion

class Questions:
  
  def __init__(self) -> None:
    self.questionsEasy = []
    self.questionsMedium = []
    self.questionsHard = []
    
  def addQuestion(self,question,diff):
    diff = diff.strip()
    if diff == "easy":
      self.questionsEasy.append(question)
    elif diff =="medium":
      self.questionsMedium.append(question)
    elif diff =="hard":
      self.questionsHard.append(question)
  
  
  def getQuestions(self,diff):
    if diff == "easy":
      return self.questionsEasy
    elif diff =="medium":
      return self.questionsMedium
    elif diff =="hard":
      return self.questionsHard

class IdQuestionAvalible():
  
  def __init__(self) -> None:
    self.usedIDS = []
    
    
  def setUsedIDS(self,data):
    self.usedIDS = data
    
  def addUsedId(self,idUsed):
    self.usedIDS.append(idUsed)
    
  def checkAvalbility(self,checkId):
    return checkId not in self.usedIDS