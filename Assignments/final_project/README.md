Basically, I read in game data from config.json.I then created three classes: simulation, person, and SIR model. I then make a simulation object that is used to run the game. My comments in the code also talk about specific functions. Be sure to read those.hahaaa
-----------------------------------------------------------------------------------------------------------------------------------------

Corona Simulation Program

How to Run: 
Downloading the files: First, download all of the files in this homework folder(final_project folder). You will need to make a new folder where you
will store all of the files here into it. Within the folder, you will have the simulation.py file, config.json, and two sub folders: images
and text(fonts). Make sure all of the files in images and text are saved in their respective folders. 

Necessary prerequisites:
You will need Python version 3 installed on your computer to run this code. You can find the latest version on Python's website.
You will also need pip installed as well. You can do this by running, install pip, in a command window. Once pip has been installed,
run the command: pip install pygame in order to install pygame.

Running the code:
Once all prerequisites are done, open the main folder in Vscode or any text editor/IDE that can run python. These instruction assume you
are running vscode, however. With simulation.py as your active code (you can click within it and edit it), right click and select run python
file in terminal. This should run the simulation if no errors are found.

Changing the simulation:
If you want to change how the simulation runs, you can do so by changing values in config.json. Only change the values to the right of
the colon(:) though. Don't change the keys, just the values.

Simulation Description:
This program simulates the effects of a virus on a population of people. Using the SIR model, people are randomly assigned to be infected,
recovered, or vulnerable. Vulnerable people may be infected by a virus, infected people may die or recover, and recovered people are immune.
If an infected person comes into contact with a vulnerable person, the vulnerable person will become sick as well. The simulation runs for 
50 days, with each day being represented by a certain amount of processor "ticks". Information about how many people are infected, recovered, 
and died from the virus are printed on screen. If the user wants to end the program early, they may do so by clicking on the x button in the game window.

Classes:
Simulation - This class basically runs the whole simulation. It creates objects of every other class in the program and uses them as data in 
the sim. Simulation begins by creating a list of people, or population, that is randomly filled with people with different conditions.
After that, the class begins simulating the outbreak, moving sprites around the screen and determining how the virus spreads among other
things. This class keeps track of the number of days passed, and will end the simulation once enough days occur.

SIR - This class is used to randomly create a model of the outbreak. This model will be used to determine the initial conditions of the
virus in the population.

Virus - Just contains information about the virus such as death rate, infection rate, and days infected.

Person - all of the information about a person in the population is stored here. This class also creates a sprite representation of every 
individual in the population, and assigns a picture to each of them. There are methods here that determine how the people move around the
game board, and also determine when a collision is made. There are also methods that determine whether an infected person will die or
not. Most of the functions in this class are constantly used by simulation class to run the program. It is one of the most important classes.
