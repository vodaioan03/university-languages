import random

questionEasy = "Which number is "
questionsEasyWord = ["prime", "even", "odd", "largest", "smallest","multiple of 10","multiple of 2"]
questionEasyAnswers = {0:["3","5","7","13","19","17","29"],1:["202","404","560","788","920","1023592"],2:["121","333","575","677","10923"],3:["9999","8739","909090","9875572","19348738"],4:["-1","-4","-8","0"],5:["10","100","30","40","50"],6:["2","4","8","16","32","48"]}

questionMedium = "Which country has "
questionsMediumWord = ["most population", "chepeast","in europe"]
questionMediumAnswers = {0:["Rusia","China","America"],1:["Romania","Bulgaria","Republica Moldova","Ucraina"],2:["Belgia","Romania","Bulgaria","germania","franta"]}

questionHard = "Which is not a "
questionHardWord = ["fish","mamifer","bird","game","movie","book","car","country"]
questionHardAnswers = {0:["biban","somn","crab","delfin"],1:["cow","horse","cat","dog"],2:["Randunica","Cioara","Papagal"],3:["Minecraft","CS2","Gta5","Tetris","battleship","candy crush"],4:["Casa de papel", "Fast and Furios", "BD"],5:["How to code", "Amintiri din copilarie","Ion"],6:["BMW","Audi","ford","Porsche","ferrari","dodge","logan","dacia"],7:["Romania","Bulgaria","ucraina","Germania","Franta","Slovacia"]}

def generate_function():
  questionNumber = 1
  easy = 35
  medium = 30
  hard = 35
  allQuestionEasy = []
  allQuestionMedium = []
  allQuestionHard = []
  while easy>0:
    easy -= 1
    question = []
    numberWord =random.randint(0,6)
    question.append(questionEasy + questionsEasyWord[numberWord])
    answers = []
    correctAnswer = random.choice(questionEasyAnswers[numberWord])
    answers.append(correctAnswer)
    while len(answers) < 3:
      choiceAnother = random.randint(0,6)
      while choiceAnother == numberWord:
        choiceAnother = random.randint(0,6)
      if numberWord == 2:
        choiceAnother = 1
      if numberWord == 5:
        choiceAnother = random.randint(1,2)
      if numberWord == 6:
        choiceAnother = random.randint(1,2)
      if numberWord == 1:
        choiceAnother = random.randint(5,6)
      answers.append(random.choice(questionEasyAnswers[choiceAnother]))
    allQuestionEasy.append([questionNumber,question,answers,correctAnswer])
    questionNumber += 1
  while medium>0:
    medium -= 1
    question = []
    numberWord =random.randint(0,2)
    question.append(questionMedium + questionsMediumWord[numberWord])
    answers = []
    correctAnswer = random.choice(questionMediumAnswers[numberWord])
    answers.append(correctAnswer)
    while len(answers) < 3:
      choiceAnother = random.randint(0,2)
      while choiceAnother == numberWord:
        choiceAnother = random.randint(0,2)
      answers.append(random.choice(questionMediumAnswers[choiceAnother]))
    allQuestionMedium.append([questionNumber,question,answers,correctAnswer])
    questionNumber += 1
  while hard>0:
    hard -= 1
    question = []
    numberWord =random.randint(0,7)
    question.append(questionHard + questionHardWord[numberWord])
    answers = []
    correctAnswer = random.choice(questionHardAnswers[numberWord])
    answers.append(correctAnswer)
    while len(answers) < 3:
      choiceAnother = random.randint(0,7)
      while choiceAnother == numberWord:
        choiceAnother = random.randint(0,7)
      answers.append(random.choice(questionHardAnswers[choiceAnother]))
    random.shuffle(answers)
    allQuestionHard.append([questionNumber,question,answers,correctAnswer])
    questionNumber += 1
  
  file_open = open("src/questions.txt","w")
  string = []
  for each in allQuestionEasy:
    stringquestion = f"{each[0]};{each[1][0]};{each[2][0]};{each[2][1]};{each[2][2]};{each[3]};easy; \n"
    string.append(stringquestion)
  for each in allQuestionMedium:
    stringquestion = f"{each[0]};{each[1][0]};{each[2][0]};{each[2][1]};{each[2][2]};{each[3]};medium; \n"
    string.append(stringquestion)
  for each in allQuestionHard:
    stringquestion = f"{each[0]};{each[1][0]};{each[2][0]};{each[2][1]};{each[2][2]};{each[3]};hard; \n"
    string.append(stringquestion)
  
  file_open.writelines(string)
  file_open.close()
  
    
questions = generate_function()

    