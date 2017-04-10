""" turret.py 
    Use vector projection
    and enhanced keyboard input
    to build a rotating turret"""
    
import pygame, math
pygame.init()

class Turret(pygame.sprite.Sprite):
    def __init__(self):
        pygame.sprite.Sprite.__init__(self)
        self.imageMaster = pygame.image.load("turret.gif")
        self.imageMaster = self.imageMaster.convert()
        self.imageMaster = pygame.transform.scale2x(self.imageMaster)
        self.rect = self.imageMaster.get_rect()
        self.rect.center = (320, 240)
        self.turnRate = 10
        self.dir = 0
        
    def update(self):
        self.checkKeys()
        self.rotate()
    
    def checkKeys(self):
        keys = pygame.key.get_pressed()
        if keys[pygame.K_LEFT]:
            self.dir += self.turnRate
            if self.dir > 360:
                self.dir = self.turnRate
        if keys[pygame.K_RIGHT]:
            self.dir -= self.turnRate
            if self.dir < 0:
                self.dir = 360 - self.turnRate
    
    def rotate(self):
        oldCenter = self.rect.center
        self.image = pygame.transform.rotate(self.imageMaster, self.dir)
        self.rect = self.image.get_rect()
        self.rect.center = oldCenter
    
def main():
    screen = pygame.display.set_mode((640, 480))
    pygame.display.set_caption ("Rotating Turret")
    
    background = pygame.Surface(screen.get_size())
    background.fill((0x00, 0xCC, 0x00))
    screen.blit(background, (0, 0))
    
    turret = Turret()
    allSprites = pygame.sprite.Group(turret)
    
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
    