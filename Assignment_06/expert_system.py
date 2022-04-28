# Name: Omkar Gaikwad
# Roll No: 31126
# Batch: L1

# Healthcare Expert System
# We will be using experta, which is a python libarary to
# implement Rule-Based expert systems using Python.
# It is similar to CLIPS language, which is the most popular
# Language to implement Rule-Based logic.
from experta import *
from experta.fact import *

# This expert systems aims at identifying whether a patient has a cold, flu
# or covid. Flu is caused only by influenza based viruses while common cold
# can be caused by a number of viruses. COVID'19 is a deadly virus which is caused
# by corona virus, and can lead to fatality very quickly. Cold is usually a milder disease 
# as compared to Flu, hence the symptoms of Flu are stronger. COVID on the other hand,
# is charaterised by even stronger symptoms.

# Class to define an Expert System with a Knowledge Engine
# Note here that the class must be subclass of KnowledgeEngine
class FluOrCold(KnowledgeEngine):

    def __init__(self):
        self.cold_symptoms = 0      # Count of the no. of cold symptoms
        self.flu_symptoms = 0       # Count of the no. of flu symptoms
        self.covid_symptoms = 0     # Count of the no. of covid symptoms
        self.symptom_list = {}      # Stores all the symptoms shown by user
        super().__init__()

# Expert systems needs a set of Facts to be present for the system to work.
# DefFacts is called every time the reset method is called.
    @DefFacts()
    def symptoms(self):
        yield Fact(action="flu_or_cold")

    # <---- Defining rules to classify as Cold, Flu and COVID ---->

    # Important: Since having shortness of breath is one of the most common causes
    # of covid, it is advisable to immediately contact a doctor and get an RT-PCR test.
    # Hence if any patient that shows this symptom is told that he/she is COVID +ve.
    @Rule(Fact(action='flu_or_cold'),
          OR 
          (Fact(shortness_of_breath="yes"))
        )
    def emergency(self):
        self.covid_symptoms += 100

    # Cold based Symptoms
    @Rule(Fact(action='flu_or_cold'),
          OR 
          (
            Fact(fever="no"),
            Fact(headache="no"),
            Fact(aches="slight"),
            Fact(weakness="mild"),
            Fact(stuffy_runny_nose="yes"),
            Fact(sneezing="yes"),
            Fact(sore_throat="yes"),
            Fact(cough="mild"),
            Fact(shortness_of_breath="no")
          )
        )
    def cold(self):
        self.cold_symptoms += 1
    
    # Flu based Symptoms
    @Rule(Fact(action='flu_or_cold'),
          OR 
          (
            Fact(fever="high"),
            Fact(headache="yes"),
            Fact(aches="severe"),
            Fact(weakness="intense"),
            Fact(stuffy_runny_nose="no"),
            Fact(sneezing="no"),
            Fact(sore_throat="yes"),
            Fact(cough="severe"),
            Fact(shortness_of_breath="no")
          )
        )
    def flu(self):
        self.flu_symptoms += 1

    # COVID based Symptoms
    @Rule(Fact(action='flu_or_cold'),
          OR 
          (
            Fact(fever="high"),
            Fact(headache="no"),
            Fact(aches="moderate"),
            Fact(weakness="intense"),
            Fact(stuffy_runny_nose="no"),
            Fact(sneezing="no"),
            Fact(sore_throat="yes"),
            Fact(cough="severe")
          )
        )
    def covid(self):
        self.covid_symptoms += 1

    # <---- End of Rule Definition ---->

    # This function will store all the symptoms taken as input into a dictionary.
    def setSymptoms(self):
        # The last fact that we get using experta is dummy. Ignore that.
        total_syp = 0
        for key, value in self.facts[2].items():
            if (total_syp <= 8):
                self.symptom_list[key] = value
                total_syp += 1
            else: 
                break
    
    # Function to print all the symptoms entered by user.
    def getSymptoms(self):
        print("\n\nHere are the Symptoms that you are having:")
        for key, value in self.symptom_list.items():
            print ("{:<20} | {:<20}".format(key, value))

    def compLogic(self):
        order_list = [self.covid_symptoms, self.cold_symptoms, self.flu_symptoms]
        order_list.sort(reverse=True)
        
        print("\n")
        print("-"*150)
        print("The final result is:", end=" ")
        if order_list[0] == self.covid_symptoms:
            print("It is likely that you have COVID. Please contact your trusted Doctor Immediately.")
        elif order_list[0] == self.flu_symptoms:
            print("It is likely that you have a Flu. Please contact your trusted Doctor so that",  
                    "he/she can perform full diagonsis.")
        else:
            print("It is likely that you have common cold. Since this is not an emergency, you may choose not",
                    "to contact your Doctor immediately.") 
            print("However, contact the Doctor to get a prescription of the", 
                    "medicines that need to be taken.")
        print("-"*150)
        print("\n\n")

    def getFluCount(self):
        return self.flu_symptoms

    def getColdCount(self):
        return self.cold_symptoms

    def getCovidCount(self):
        return self.covid_symptoms


# User Input

print()
print("-"*150)
print("Hello, I am BayMax, your Personal Healthcare Companion!!!".center(150))
print("\nI help Doctors to carry initial phases of diagnostics, by using a Rule-Based Approach.")
print("This module will help you identify whether you have cold, flu or covid.")
print("\nMade By: Sanchit Kripalani")
print("-"*150)
print("\nFill the form which asks about the symptoms you are suffering from.")
print("\n**Important**")
print("Note: Answer to each question is a one-word response which is mentioned along the question.")
print()

# Create an Engine object
engine = FluOrCold()
ques_no = 0

while(1):
    if ques_no == 0:
        fever = input("Do you have a fever? (Ans as No, Low or High): ").strip().lower()
        if fever not in ['no', 'low', 'high']:
            print("Please enter the question properly!!!\n\n")
            continue
        else:
            ques_no += 1
            continue
    elif ques_no == 1:
        headache = input("Do you have a headache? (Ans as Yes or No): ").strip().lower()
        if headache not in ['yes', 'no']:
            print("Please enter the question properly!!!\n\n")
            continue
        else:
            ques_no += 1
            continue
    elif ques_no == 2:
        aches = input("Do you have body ache/pain? (Ans as Slight, Moderate or Severe): ").strip().lower()
        if aches not in ['slight', 'moderate', 'severe']:
            print("Please enter the question properly!!!\n\n")
            continue
        else:
            ques_no += 1
            continue
    elif ques_no == 3:
        weakness = input("Do you feel weakness? (Ans as Intense or Mild): ").strip().lower()
        if weakness not in ['intense', 'mild']:
            print("Please enter the question properly!!!\n\n")
            continue
        else:
            ques_no += 1
            continue
    elif ques_no == 4:
        stuffy_runny_nose = input("Do you have a stuffy/runny nose? (Ans as Yes or No): ").strip().lower()
        if stuffy_runny_nose not in ['yes', 'no']:
            print("Please enter the question properly!!!\n\n")
            continue
        else:
            ques_no += 1
            continue
    elif ques_no == 5:
        sneezing = input("Do you have frequent sneezing? (Ans as Yes or No): ").strip().lower()
        if sneezing not in ['yes', 'no']:
            print("Please enter the question properly!!!\n\n")
            continue
        else:
            ques_no += 1
            continue
    elif ques_no == 6:
        sore_throat = input("Do you have a soar throat? (Ans as Yes or No): ").strip().lower()
        if sore_throat not in ['yes', 'no']:
            print("Please enter the question properly!!!\n\n")
            continue
        else:
            ques_no += 1
            continue
    elif ques_no == 7:
        cough = input("Do you have cough? (Ans as Severe or Mild): ").strip().lower()
        if cough not in ['severe', 'mild']:
            print("Please enter the question properly!!!\n\n")
            continue
        else:
            ques_no += 1
            continue
    elif ques_no == 8:
        shortness_of_breath = input("Do you have shortness of breath? (Ans as Yes or No): ").strip().lower()
        if shortness_of_breath not in ['yes', 'no']:
            print("Please enter the question properly!!!\n\n")
            continue
        else:
            ques_no += 1
            continue


    engine.reset()  # Prepare the engine for the execution.
    engine.declare(Fact(fever=fever, headache=headache, aches=aches, weakness=weakness, 
                        stuffy_runny_nose=stuffy_runny_nose, sneezing=sneezing, sore_throat=sore_throat,
                        cough=cough, shortness_of_breath=shortness_of_breath))
    engine.run()  # Run the engine
    print()
    break

# Reset the engine again to perform execution
# engine.reset()
engine.setSymptoms()
engine.reset()

print("\nThank you for filling out your Symptoms Form patiently!!!")
print("The best part about using me is that I can immediately infer from the diagnosis")

choice = 0
while (1):
    print("\n\nHow may I help you?")
    print("1) Print the list of symptoms that I have entered")
    print("2) Get my test results")
    print("3) Exit\n")
    choice = int(input("Enter a choice: "))

    if choice == 1:
        engine.getSymptoms()
    elif choice == 2:
        engine.compLogic()
    elif choice == 3:
        print("\nI cannot deactivate unless you say you are satisfied with your care!!!")
        print("Type: 'I am satisfied' to exit\n")
        exit_statement = input().lower()
        if (exit_statement == 'i am satisfied'):
            print('Thank you. Deactivating now...\n\n')
            break
        else:
            print('Not able to Deactivate!!!')
            continue