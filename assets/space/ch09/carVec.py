""" carVec.py
    Use vector projection to create a smoothly-turning
    car sprite.
"""

import pygame, math
pygame.init()

class Car(pygame.sprite.Sprite):
    def __init__(self, screen):
        pygame.sprite.Sprite.__init__(self)
        self.screen = screen
        self.imageMaster = pygame.image.load("car.gif")
        self.imageMaster = self.imageMaster.convert()
        self.imageMaster = pygame.transform.scale(self.imageMaster, (50, 35))
        self.rect = self.imageMaster.get_rect()
        self.dir = 0
        self.turnRate = 3
        self.accel = .1
        self.x = 320.0
        self.y = 240.0
        self.speed = 0
        self.rect.center = (self.x, self.y)
    
    def update(self):
        self.checkKeys()
        self.rotate()
        self.calcVector()
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
            self.speed += self.accel
            if self.speed > 10:
                self.speed = 10
        if keys[pygame.K_DOWN]:
            self.speed -= self.accel
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
        
        self.dx *= self.speed
        self.dy *= self.speed
        self.dy *= -1
        
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
    pygame.display.set_caption("vector projection")
    
    background = pygame.Surface(screen.get_size())
    background.fill((0xcc, 0xcc, 0xcc))
    screen.blit(background, (0, 0))
    
    car = Car(screen)
    allSprites = pygame.sprite.Group(car)
    
    keepGoing = True
    clock = pygame.time.Clock()
    
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
    