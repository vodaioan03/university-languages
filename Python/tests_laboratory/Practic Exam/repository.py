from domain import *



class Repository():
  
  def __init__(self,questionsClass: Questions) -> None:
    self.questionsFile = "src/questions.txt"
    self.questionsClass = questionsClass
    self.__loadQuestions()
  
  def _getAllIds(self):
    questionsFileOpen = open(self.questionsFile,"r")
    
    allquestions = questionsFileOpen.readlines()
    idUsed = []
    for each in allquestions:
      questionSplitted = each.split(";")
      idQuestion = int(questionSplitted[0])
      idUsed.append(idQuestion)
      
    questionsFileOpen.close()
    return idUsed
  
  def addQuestionInFile(self,question):
    questionsFileOpen = open(self.questionsFile,"a")
    questionsFileOpen.write(question)
    questionsFileOpen.close()
    
  
  def createNewQuiz(self,file:str,quiz:Quiz):
    questionsFileOpen = open(file,"r")
    allquestions = questionsFileOpen.readlines()
    
    for each in allquestions:
      quiz.addQuestion(each)
    questionsFileOpen.close()
    
    
  def createNewQuizFile(self,file:str,allQuestions :list):
    """Create file and add questions for quiz

    Args:
        file (str): file name
        allQuestions (list): questions generated
    """
    fileOpened = open(file,"w")
    fileOpened.writelines(allQuestions)
    fileOpened.close()
    
  
  def __saveQuestions(self):
    pass
  
  
  def __loadQuestions(self):
    questionsFileOpen = open(self.questionsFile,"r")
    
    allquestions = questionsFileOpen.readlines()
    
    for each in allquestions:
      questionSplitted = each.split(";")
      self.questionsClass.addQuestion(each,questionSplitted[6])
    questionsFileOpen.close()