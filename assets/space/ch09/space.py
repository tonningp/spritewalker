""" space.py 
    simulate a spacecraft with
    no traction at all
"""

import pygame, math
pygame.init()

class Ship(pygame.sprite.Sprite):
    def __init__(self, screen):
        pygame.sprite.Sprite.__init__(self)
        self.screen = screen

        self.imageThrust = pygame.image.load("shipThrust.png")
        self.imageThrust = self.imageThrust.convert()
        self.imageCruise = pygame.image.load("shipCruise.png")
        self.imageCruise = self.imageCruise.convert()
        self.imageLeft = pygame.image.load("shipLeft.png")
        self.imageLeft = self.imageLeft.convert()
        self.imageRight = pygame.image.load("shipRight.png")
        self.imageRight = self.imageRight.convert()
        
        self.imageMaster = self.imageCruise
        self.image = self.imageMaster
        self.rect = self.image.get_rect()
        
        self.x = 100
        self.y = 100
        self.dx = 0
        self.dy = 0
        self.dir = 0
        self.turnRate = 5
        self.thrust = 0
        
    def update(self):
        self.checkKeys()
        self.rotate()
        self.calcVector()
        self.setPos()
        self.checkBounds()
        self.rect.center = (self.x, self.y)
        
    def checkKeys(self):
        keys = pygame.key.get_pressed()
        self.imageMaster = self.imageCruise
        if keys[pygame.K_RIGHT]:
            self.dir -= self.turnRate
            if self.dir < 0:
                self.dir = 360 - self.turnRate
            self.imageMaster = self.imageRight
        if keys[pygame.K_LEFT]:
            self.dir += self.turnRate
            if self.dir > 360:
                self.dir = self.turnRate
            self.imageMaster = self.imageLeft
        if keys[pygame.K_UP]:
            self.thrust = .1
            self.imageMaster = self.imageThrust
        else:
            self.thrust = 0
        
    def rotate(self):
        oldCenter = self.rect.center
        self.image = pygame.transform.rotate(self.imageMaster, self.dir)
        self.rect = self.image.get_rect()
        self.rect.center = oldCenter

    def calcVector(self):
        radians = self.dir * math.pi / 180
        
        thrustDx = self.thrust * math.cos(radians)
        thrustDy = self.thrust * math.sin(radians)
        thrustDy *= -1
        
        self.dx += thrustDx
        self.dy += thrustDy
        self.speed = math.sqrt((self.dx * self.dx) + (self.dy * self.dy))
        
    def setPos(self):
        self.x += self.dx
        self.y += self.dy
    
    def checkBounds(self):
        screen = self.screen
        
        if self.x > screen.get_width():
            self.x = 0
        if self.x < 0:
            self.x = screen.get_width()
        if self.y > screen.get_height():
            self.y = 0
        if self.y < 0:
            self.y = screen.get_height()
    
def main():
    screen = pygame.display.set_mode((640, 480))
    pygame.display.set_caption("Space craft")
    
    background = pygame.Surface(screen.get_size())
    background.fill((0, 0, 0))
    screen.blit(background, (0, 0))
    
    ship = Ship(screen)
    allSprites = pygame.sprite.Group(ship)
    
    clock = pygame.time.Clock()
    keepGoing = True
    while keepGoing:
        clock.tick(30)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                keepGoing = False
        
        allSprites.clear(screen, background)
        allSprites.update()
        allSprites.draw(screen)
        
        pygame.display.flip()
        
if __name__ == "__main__":
    main()
    
    