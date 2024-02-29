from service import *


class UI:
  def __init__(self) -> None:
    self.__isRunning = False
    self.__service = Service()
    
  def commandsPrint(self):
    print("\nCommands:")
    print("add <id>;<text>;<choice_a>;<choice_b>;<choice_c>;<correct_choice>;<difficulty>")
    print("create <difficulty> <number_of_questions> <file>")
    print("start <file>")
    print("exit \n")
    
    
  def addQuestion(self,command):
    if len(command) != 7:
      raise ValueError("invalid command")
    print(command)
    idQuestion = command[0][1]
    textQuestion = command[1]
    choices = [command[2].strip(),command[3].strip(),command[4].strip()]
    correctChoice = command[5].strip()
    difficultyQuestion = command[6]
    try:
      idQuestion = int(idQuestion)
    except Exception as e:
      raise ValueError("Id Question needs to be integer")
    if idQuestion < 1:
      raise ValueError("Id needs to be > 1")
    if not self.__service.checkValbilityForId(idQuestion):
      raise ValueError("Id already used.")
    found = False
    for each in choices:
      if correctChoice.lower() == each.lower():
        found = True
        break
    if not found:
      raise ValueError("Correct Choice needs to be in choices.")
    
    difficulties = ['hard','easy','medium']
    if difficultyQuestion not in difficulties:
      raise ValueError("Invalid Difficulty")
    
    difficultyQuestion += ';'
    
    self.__service.addQuestionInList(idQuestion,textQuestion,choices,correctChoice,difficultyQuestion)
    
    
  def createQuiz(self,command):
    if len(command) != 4:
      raise ValueError("Command too short!")
    difficultyQuiz = command[1]
    numberQuestions = command[2]
    file = command[3]
    
    difficulties = ['hard','easy','medium']
    if difficultyQuiz not in difficulties:
      raise ValueError("Invalid Difficulty")
    
    try:
      numberQuestions = int(numberQuestions)
    except Exception as e:
      raise ValueError("Number of questions need to be integer")
    
    if ".txt" not in file:
      raise ValueError("Files needs to be txt.")
    
    self.__service.createQuiz(difficultyQuiz,numberQuestions,file)
   
  def startPlayQuiz(self): 
    self.playingQuiz = True
    numberOfQuestions = self.__service.getNumberOfQuestions()
    while numberOfQuestions > 0:
      numberOfQuestions -= 1
      question = self.__service.getQuestion()
      question = question.split(';')
      textQuestion = question[1]
      answers = [question[2],question[3],question[4]]
      difficulty = question[6].strip()
      corrrectAnswer = question[5].strip()
      idquestion = question[0]
      print(f"{numberOfQuestions+1} more questions.")
      print(f"[{idquestion}] {textQuestion}? Difficulty: {difficulty} Correct Answer:{corrrectAnswer.lower()}")
      print(f"{answers[0]}\n{answers[1]}\n{answers[2]}")
      answerUser = input("Type Your answer: ").strip()
      self.__service.checkWin(answerUser)
    scorePlayer = self.__service.getScoreforPlayyer()
    print(f"\nGames End. Your final score is: {scorePlayer}")
    self.__service.endQuiz()
    
  def startQuiz(self,command):
    filequiz = command[1]
    quizOk = True
    try:
      self.__service.startQuiz(filequiz)
    except Exception as e:
      quizOk = False
      print(e)
    if quizOk:
      self.startPlayQuiz()
      
  def commandInput(self):
    command = input("Type Command: ").strip()
    if command.lower() == "exit":
      self.__isRunning = False
      print("Program exiting...")
      return
    command = command.split(";")
    if len(command) > 1:
      command[0] = command[0].split(" ")
      command[0][0].strip()
      if command[0][0].lower() == "add":
        self.addQuestion(command)
    else:
      if len(command) == 1:
        command = command[0]
        command = command.split(" ")
        command[0] = command[0].strip()
        if command[0].lower() == "create":
          self.createQuiz(command)
        if command[0].lower() == "start":
          self.startQuiz(command)
        
    
  def startProgram(self):
    self.__isRunning = True
    self.commandsPrint()
    while self.__isRunning:
      try:
        self.commandInput()
      except ValueError as e:
        print(e)