from repository import *
from domain import *
import random


class Service:
  
  def __init__(self) -> None:
    self.idDomain = IdQuestionAvalible()
    self.questionsClass = Questions()
    self.repository = Repository(self.questionsClass)
    
    self.idDomain.setUsedIDS(self.repository._getAllIds())
    self.actualQuiz = None
    self.actualQuestion = None
    
  def addQuestionInList(self,idQuestion,textQuestion,choices,correctChoice,difficultyQuestion):
    string = f'{idQuestion};{textQuestion};{choices[0]};{choices[1]};{choices[2]};{correctChoice};{difficultyQuestion}'
    self.repository.addQuestionInFile(string)
    
  def checkValbilityForId(self,idCheck):
    return self.idDomain.checkAvalbility(idCheck)
  
  
  def startQuiz(self,filename):
    quiz = Quiz()
    self.repository.createNewQuiz(filename,quiz)
    quizQuestions = quiz.getQuestions()
    if len(quizQuestions) == 0:
      raise ValueError("This file doesen't exist")
    self.actualQuiz = quiz
    return True
  
  def getQuestion(self):
    self.actualQuestion = self.actualQuiz.getOneQuestion()
    return self.actualQuestion
  
  def getNumberOfQuestions(self):
    return len(self.actualQuiz.getQuestions())
  
  def getScoreforPlayyer(self):
    return self.actualQuiz.getScore()
  
  def checkWin(self,answer):
    actuakQuestion = self.actualQuestion.split(';')
    correctAnswer = actuakQuestion[5].strip()
    answer = answer.lower()
    answer = answer.strip()
    correctAnswer = correctAnswer.lower()
    if correctAnswer == answer:
      self.actualQuiz.addScore(actuakQuestion[6].strip())
    return self.actualQuiz.getScore()
  
  def endQuiz(self):
    self.actualQuiz = None
    self.actualQuestion = None
  
  def createQuiz(self,difficultyQuiz,numberQuestions,file):
    """Function for create quiz and generate questions

    Args:
        difficultyQuiz (str): quiz for difficulty
        numberQuestions (int): number of questions
        file (str): file name

    Raises:
        ValueError: if number of questions is bigger than number of avalible questions for that difficulty
    """
    
    questionsForUse = self.questionsClass.getQuestions(difficultyQuiz.lower())
    
    if len(questionsForUse) < numberQuestions:
      raise ValueError(f"You can make a quiz with maximum:{len(questionsForUse)} for {difficultyQuiz} difficulty.")
    
    quizQuestions = []
    while numberQuestions > 0:
      numberQuestions -= 1
      questionForAdd = random.choice(questionsForUse)
      quizQuestions.append(questionForAdd)
      del questionsForUse[questionsForUse.index(questionForAdd)]
    self.repository.createNewQuizFile(file,quizQuestions)