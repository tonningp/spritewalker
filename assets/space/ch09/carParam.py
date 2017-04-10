""" carParam.py 
    A car with several changeable
    parameters
"""

import pygame, math
import miniGUI
pygame.init()

class Car(pygame.sprite.Sprite):
    def __init__(self, screen):
        pygame.sprite.Sprite.__init__(self)
        
        self.screen = screen
        
        self.imageMaster = pygame.image.load("car.gif")
        self.imageMaster = self.imageMaster.convert()
        self.rect = self.imageMaster.get_rect()
        
        #define attributes
        self.x = 320
        self.y = 230
        self.dx = 0
        self.dy = 0
        self.speed = 0
        self.dir = 0
        self.turnRate = 2
        self.power = 1
        self.drag = .3
        
    def update(self):
        self.checkKeys()
        self.rotate()
        self.calcVector()
        self.calcPos()
        self.checkBounds()
        self.rect.center = (self.x, self.y)
    
    def checkKeys(self):
        keys = pygame.key.get_pressed()
        if keys[pygame.K_RIGHT]:
            self.dir -= self.turnRate
            if self.dir < 0:
                self.dir = 360 - self.turnRate
        if keys[pygame.K_LEFT]:
            self.dir += self.turnRate
            if self.dir > 360:
                self.dir = self.turnRate
        if keys[pygame.K_UP]:
            self.speed += self.power
            #no need to check for a max speed anymore
        if keys[pygame.K_DOWN]:
            self.speed -= self.power
            if self.speed < -3:
                self.speed = -3

    def rotate(self):
        oldCenter = self.rect.center
        self.image = pygame.transform.rotate(self.imageMaster, self.dir)
        self.rect = self.image.get_rect()
        self.rect.center = oldCenter

    def calcVector(self):
        radians = self.dir * math.pi / 180
        self.dx = math.cos(radians)
        self.dy = math.sin(radians)
        
        #compensate for drag
        self.speed *= (1 - self.drag)
        if self.speed < .5:
            if self.speed > -.5:
                self.speed = 0
                
        self.dx *= self.speed
        self.dy *= self.speed
        self.dy *= -1

    def calcPos(self):
        self.x += self.dx
        self.y += self.dy
        
    def checkBounds(self):
        if self.x > self.screen.get_width():
            self.x = 0
        if self.x < 0:
            self.x = self.screen.get_width()
        if self.y > self.screen.get_height():
            self.y = 0
        if self.y < 0:
            self.y = self.screen.get_height()
    
def main():
    screen = pygame.display.set_mode((640, 480))
    pygame.display.set_caption("Car with parameters")
    
    background = pygame.Surface(screen.get_size())
    background.fill((0xcc, 0xcc, 0xcc))
    screen.blit(background, (0, 0))
    
    #Make some labels and scrollers
    lblPower = miniGUI.Label()
    lblPower.center = (80, 20)
    lblPower.text = "Power"
    
    scrPower = miniGUI.Scroller()
    scrPower.center = (250, 20)
    scrPower.bgColor = (0xFF, 0xFF, 0xFF)
    scrPower.value = 5
    scrPower.maxValue = 10
    scrPower.increment = .5

    lblDrag = miniGUI.Label()
    lblDrag.center = (80, 60)
    lblDrag.text = "Drag"
    
    scrDrag = miniGUI.Scroller()
    scrDrag.center = (250, 60)
    scrDrag.bgColor = (0xFF, 0xFF, 0xFF)
    scrDrag.value = .15
    scrDrag.maxValue = 1
    scrDrag.increment = .01

    lblTurn = miniGUI.Label()
    lblTurn.center = (80, 100)
    lblTurn.text = "Turn Rate"
    
    scrTurn = miniGUI.Scroller()
    scrTurn.center = (250, 100)
    scrTurn.bgColor = (0xFF, 0xFF, 0xFF)
    
    lblSpeed0 = miniGUI.Label()
    lblSpeed0.text = "speed:"
    lblSpeed0.center = (80, 140)
    
    lblSpeed1 = miniGUI.Label()
    lblSpeed1.text = ""
    lblSpeed1.center = (250, 140)
    
    car = Car(screen)
    allSprites = pygame.sprite.OrderedUpdates(lblPower, scrPower, 
                                     lblDrag, scrDrag,
                                     lblTurn, scrTurn,
                                     lblSpeed0, lblSpeed1,
                                     car)

    keepGoing = True
    clock = pygame.time.Clock()
    
    while keepGoing:
        clock.tick(30)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                keepGoing = False

        # read scrollers
        car.power = scrPower.value
        car.turnRate = scrTurn.value
        car.drag = scrDrag.value
        lblSpeed1.text = "%.2f" % car.speed        
        
        allSprites.clear(screen, background)
        allSprites.update()
        allSprites.draw(screen)
        
        pygame.display.flip()
        
if __name__ == "__main__":
    main()