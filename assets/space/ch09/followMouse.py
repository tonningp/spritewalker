""" followMouse.py 
    a version of the turret game that
    uses the arctangent function 
    and pythagoras to get
    angle and distance from dx and dy
"""

import pygame, math 
import turretFire
pygame.init()
class Turret(pygame.sprite.Sprite):
    def __init__(self):
        pygame.sprite.Sprite.__init__(self)
        self.imageMaster = pygame.image.load("turret.gif")
        self.imageMaster = self.imageMaster.convert()
        self.imageMaster = pygame.transform.scale2x(self.imageMaster)
        self.rect = self.imageMaster.get_rect()
        self.rect.center = (320, 240)

    def update(self):
        self.followMouse()
        self.rotate()
    
    def followMouse(self):
        (mouseX, mouseY) = pygame.mouse.get_pos()
        dx = self.rect.centerx - mouseX
        dy = self.rect.centery - mouseY
        dy *= -1
        
        radians = math.atan2(dy, dx)
        self.dir = radians * 180 / math.pi
        self.dir += 180
        
        #calculate distance
        self.distance = math.sqrt((dx * dx) + (dy * dy))
    
    def rotate(self):
        oldCenter = self.rect.center
        self.image = pygame.transform.rotate(self.imageMaster, self.dir)
        self.rect = self.image.get_rect()
        self.rect.center = oldCenter

class LblDist(turretFire.Label):
    def __init__(self, turret):
        turretFire.Label.__init__(self)
        self.turret = turret
        self.center = (150, 20)
    
    def update(self):
        turretFire.Label.update(self)
        self.text = "angle: %d, dist: %d px" % \
        (self.turret.dir, self.turret.distance)

def main():
    screen = pygame.display.set_mode((640, 480))
    pygame.display.set_caption ("Rotating Turret")
    
    background = pygame.Surface(screen.get_size())
    background.fill((0x00, 0xCC, 0x00))
    screen.blit(background, (0, 0))
    
    turret = Turret()
    lblDist = LblDist(turret)
    allSprites = pygame.sprite.Group(turret, lblDist)
    
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

   