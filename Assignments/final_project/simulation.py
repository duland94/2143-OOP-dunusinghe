# Import and initialize the pygame library
import pygame
import random
import math
from datetime import datetime
import json
import os

class simulation():
    def __init__(self):
        self.days = 1
        self.infected = 0
        self.deaths = 0
        self.maxdays = 50

    # Simple function that will advance a day every 60 ticks
    def set_days(self):
        self.days += 1

    def runsim(self, model):
        pygame.init()

        random.seed(datetime.now())
        # Title of project
        pygame.display.set_caption('Corona Simulation')

        # Set up the drawing window
        screen = pygame.display.set_mode([Config["width"], Config["height"]])

        # sprites should be in a sprite group
        sprites_list = pygame.sprite.Group()

        # a list to hold all of our people sprites
        population = []

        # Set our font
        font = pygame.font.Font('./text/Roboto-Black.ttf', 20)

        # loop N times
        for i in range(Config["population_count"]):
            # add a "person" to our list of people
            # create an "instance" of our class
            population.append(Person(Config["width"], Config["height"], model.SIR[i],Config["sprite_width"],Config["sprite_height"],Config["sprite_speed"])) #random.choice(speeds)

            # Add last person to our sprites list
            # list[-1] give you the last item
            sprites_list.add(population[-1])  

        clock=pygame.time.Clock() # Used to control fps
        seconds = 0

        # Run until the user asks to quit
        running = True

        ## this is our simulation object??
        while running:

            # Did the user click the window close button?
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False

                if event.type == pygame.MOUSEBUTTONUP:
                    pos = pygame.mouse.get_pos()
                    #print(pos)
                    population.append(Person(Config["width"], Config["height"], model.SIR[50],15,15,1,pos[0],pos[1])) #random.choice(speeds)

                    # Add last person to our sprites list
                    # list[-1] give you the last item
                    sprites_list.add(population[-1]) 


            # Fill the background with blackish
            screen.fill((30, 30, 30))

            # loop through each person
            # and call a move method
            for i in range(len(population)):
                population[i].move()

            # Check for collisions
            for j in range(len(population)):
                if population[i] != population[j]:
                    collided = population[i].checkCollide(
                        population[j])
                    if collided:
                        dx, dy = population[i].getDxDy()
                        population[j].setDxDy(dx * -1, dy * -1)

            # See if a person is ready to recover
            for i in range(len(population)):
                population[i].recover(self.days)

            sprites_list.draw(screen)

            # We will count the number infected each time
            for i in range(len(population)):
                if population[i].state == "infected":
                    self.infected += 1

            # Render the text and put it in a text box
            text = font.render("Day " + str(self.days) + " Infected: " + str(self.infected) 
            + " Deaths: " + str(self.deaths), 
            True, (30, 255, 30), (30, 30, 255))
            textbox = text.get_rect()

            # Set the boundaries for the textbox
            textbox.right = Config["width"]
            textbox.bottom = Config["height"]

            # Put the text on screen
            screen.blit(text, textbox)

            # Flip the display
            pygame.display.flip()

            # Advance a day every 60 ticks
            if seconds % 60 == 0:
                self.set_days()

                # Everyone infected has a chance to die once a day
                for i in range(len(population)):
                    if population[i].death() == True and population[i].state == "infected":
                        sprites_list.remove(population[i])
                        self.deaths += 1

            #Number of frames per second e.g. 60
            clock.tick(40) # 40 fps

            Config["myClock"] += 1
            seconds += 1
            self.infected = 0

            # If the number of days reaches a certain value, 
            # stop the sim
            if self.days > self.maxdays:
                running = False


# This class contains general information about the virus such as recovery time,
# infection radius, and more.
class virus():
    days_infected = 14
    fatality_rate = 5 # percent out of 100
    infection_rate = 80 # used when people touch

# Class for creating an SIR model
class SIR_Model():
    # This isn't part of an constructed object, but is here for organization
    SIR_images = {
        "yellow":  "./images/person_yellow.png",
        "red" :  "./images/person_red.png",
        "green":  "./images/person_green.png",
    }

    def __init__(self):
        self.initial_infect = .20
        self.recovered_prob = .10
        self.susceptible_prob = .70
        self.SIR = []
    
    def make_model(self):

        S = ["S"] * int(self.susceptible_prob * 100)
        I = ["I"] * int(self.initial_infect * 100)
        R = ["R"] * int(self.recovered_prob * 100)

        self.SIR = S + I + R

        random.shuffle(self.SIR)

# Read in data from a json file into a dictionary
if os.path.isfile("config.json"):

    f = open("config.json", "r")

    data = f.read()

    Config = json.loads(data)

# This class deals with creating a person, giving it an image, and 
# allowing them to react to its environment
class Person(pygame.sprite.Sprite):
    # Constructor for person
    def __init__(self,
                 screen_width,
                 screen_height,
                 SIR,
                 width=15,
                 height=15,
                 speed=1,inx=None,iny=None):

        # Call the parent class (Sprite) constructor
        super().__init__()

        self.id = Config["pid"]
        Config["pid"] +=1

        

        # screen width and height used to know
        # when to change direction at edge of screen
        self.screen_width = screen_width
        self.screen_height = screen_height

        # size of our sprite
        self.width = width
        self.height = height

        # direction x and direction y
        self.dx = 0
        self.dy = 0

        # Make sure the sprites will move
        while self.dx + self.dy == 0:
            self.dx = random.choice([1, -1, 0])
            self.dy = random.choice([1, -1, 0])

        # pixels per game loop
        #self.speed = random.choice([1,7])
        self.speed = speed
        self.original_speed = speed

        # Give the person a color based on their condition
        if SIR == "S":
            self.state = "susceptible"
            self.color = "yellow"
            self.dayinfected = -999

        elif SIR == "I":
            self.state = "infected"
            self.color = "red"
            self.dayinfected = 1
        
        else:
            self.state = "recovered"
            self.color = "green"
            self.dayinfected = -999

        # Load the image corresponding to the state of person
        self.image = pygame.image.load(SIR_Model.SIR_images[self.color])
        
        # Make sure the picture is to correct scale
        self.image = pygame.transform.scale(self.image,
                                            (self.width, self.height))

        # Fetch the rectangle object that has the dimensions of the image.
        # Update the position of this object by setting the values
        # of rect.x and rect.y
        if inx is None:
            # creates a random location between bounds of screen size
            self.x = int(random.random() * self.screen_width)
        else:
            self.x = inx

        if iny is None:
            # creates a random location between bounds of screen size
            self.y = int(random.random() * self.screen_height)
        else:
            self.y = iny

        # sprite hitbox
        self.rect = self.image.get_rect(center=(self.x, self.y))

    # Set a person's direction
    def setDxDy(self, dx, dy):
        self.dx = dx
        self.dy = dy

    # Discover a person's direction
    def getDxDy(self):
        return (self.dx, self.dy)

    # If two people collide, then change their direction
    def changeDirection(self, sides_contacted):
        if sides_contacted["top"]:
            self.dy = 1
        if sides_contacted["bottom"]:
            self.dy = -1
        if sides_contacted["left"]:
            self.dx = 1
        if sides_contacted["right"]:
            self.dx = -1

    # Moves the sprites around
    def move(self):

        sides_contacted = self.checkWalls()

        self.changeDirection(sides_contacted)

        if self.dx < 0:
            self.rect.x -= self.speed
        elif self.dx > 0:
            self.rect.x += self.speed

        if self.dy < 0:
            self.rect.y -= self.speed
        elif self.dy > 0:
            self.rect.y += self.speed

    # This function checks the hitboxes of the sprites, and will 
    # return a boolean that tells whether a collision has occured
    # or not. It will also know the general direction the collision
    # occured at.
    def checkCollide(self, other):
        sides_contacted = {
            "top": False,
            "bottom": False,
            "left": False,
            "right": False
        }

        if self.rect.colliderect(other.rect):

            if self.rect.top < other.rect.top:
                sides_contacted["bottom"] = True
                self.rect.y -= abs(self.rect.y - other.rect.y) // 8
            if self.rect.left < other.rect.left:
                sides_contacted["right"] = True
                self.rect.x -= abs(self.rect.x - other.rect.x) // 8
            if self.rect.right > other.rect.right:
                sides_contacted["left"] = True
                self.rect.x += abs(self.rect.x - other.rect.x) // 8
            if self.rect.bottom > other.rect.bottom:
                sides_contacted["top"] = True
                self.rect.y += abs(self.rect.y - other.rect.y) // 8
            
            infect_chance = random.randint(0, 100)

            # Determine whether the people who touch get infected or not
            if (infect_chance < virus.infection_rate and self.state == "susceptible" and 
            other.state == "infected"):
                self.state = "infected"
                self.color = "red"
                self.image = pygame.image.load(SIR_Model.SIR_images[self.color])
                self.image = pygame.transform.scale(self.image,(self.width, self.height))

            if (infect_chance < virus.infection_rate and other.state == "susceptible" and 
            self.state == "infected"):
                other.state = "infected"
                other.color = "red"
                other.image = pygame.image.load(SIR_Model.SIR_images[other.color])
                other.image = pygame.transform.scale(other.image,(other.width, other.height))

            
            self.changeDirection(sides_contacted) # People will move if they touch

            return True

        return False

    # This function makes sure the sprites won't travel beyond the borders of the screen
    def checkWalls(self):
        sides = {"top": False, "bottom": False, "left": False, "right": False}

        if self.rect.top <= 0:
            sides["top"] = True
        if self.rect.left <= 0:
            sides["left"] = True
        if self.rect.right >= self.screen_width:
            sides["right"] = True
        if self.rect.bottom >= self.screen_height:
            sides["bottom"] = True

        return sides
    
    # Every day, if someone is infected, this function will randomly determine
    # if that person dies. If they are dead, they are removed from the 
    # game screen
    def death(self):
        dead = False
        die_chance = random.randint(0, 100)

        if die_chance < virus.fatality_rate and self.state == "infected":
            dead = True

        
        return dead

    # If a person has had the virus for enough time, they will recover
    def recover(self, day):
        if day - self.dayinfected > virus.days_infected:
            self.state = "recovered"
            self.image = pygame.image.load(SIR_Model.SIR_images["green"])
            self.image = pygame.transform.scale(self.image,
                                                (self.width, self.height))
            

#__________________________________________________________________________
# This lets us run the program in a command line 
if __name__=='__main__':

    # Create instances of sim and model classes
    sim = simulation()
    model = SIR_Model()

    model.make_model() # Used to make SIR model

    sim.runsim(model) # Run Corona Simulation

    # Done! Time to quit.
    pygame.quit()