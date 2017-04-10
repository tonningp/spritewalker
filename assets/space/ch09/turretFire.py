""" turretFire.py 
    Use vector projection
    to add a shell to the turret"""
    
import pygame, math
pygame.init()

class Label(pygame.sprite.Sprite):
    """ Label Class (simplest version) 
        Attributes:
            font: any pygame font object
            text: text to display
            center: desired position of label center (x, y)
    """
    def __init__(self):
        pygame.sprite.Sprite.__init__(self)
        self.font = pygame.font.SysFont("None", 30)
        self.text = ""
        self.center = (320, 240)
                
    def update(self):
        self.image = self.font.render(self.text, 1, (0, 0, 0))
        self.rect = self.image.get_rect()
        self.rect.center = self.center

class Turret(pygame.sprite.Sprite):
    def __init__(self, shell):
        self.shell = shell
        pygame.sprite.Sprite.__init__(self)
        self.imageMaster = pygame.image.load("turret.gif")
        self.imageMaster = self.imageMaster.convert()
        self.imageMaster = pygame.transform.scale2x(self.imageMaster)
        self.rect = self.imageMaster.get_rect()
        self.rect.center = (320, 240)
        self.turnRate = 10
        self.dir = 0
        self.charge = 5
        
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
        if keys[pygame.K_UP]:
            self.charge += 1
            if self.charge > 20:
                self.charge = 20
        if keys[pygame.K_DOWN]:
            self.charge -= 1
            if self.charge < 0:
                self.charge = 0
            
        if keys[pygame.K_SPACE]:
            self.shell.x = self.rect.centerx
            self.shell.y = self.rect.centery
            self.shell.speed = self.charge
            self.shell.dir = self.dir
    
    def rotate(self):
        oldCenter = self.rect.center
        self.image = pygame.transform.rotate(self.imageMaster, self.dir)
        self.rect = self.image.get_rect()
        self.rect.center = oldCenter

class Shell(pygame.sprite.Sprite):
    def __init__(self, screen):
        pygame.sprite.Sprite.__init__(self)
        self.screen = screen
        
        self.image = pygame.Surface((10, 10))
        self.image.fill((0xff, 0xff, 0xff))
        self.image.set_colorkey((0xff, 0xff, 0xff))
        pygame.draw.circle(self.image, (0, 0, 0), (5, 5), 5)
        #self.image = pygame.transform.scale(self.image, (5, 5))
        self.rect = self.image.get_rect()
        self.rect.center = (-100, -100)
        
        self.speed = 0
        self.dir =0
        self.reset()
        
    def update(self):
        self.calcVector()
        self.calcPos()
        self.checkBounds()
        self.rect.center = (self.x, self.y)
   
    def calcVector(self):
        radians = self.dir * math.pi / 180
        
        self.dx = self.speed * math.cos(radians)
        self.dy = self.speed * math.sin(radians)
        self.dy *= -1
    
    def calcPos(self):
        self.x += self.dx
        self.y += self.dy
    
    def checkBounds(self):
        screen = self.screen
        if self.x > screen.get_width():
            self.reset()
        if self.x < 0:
            self.reset()
        if self.y > screen.get_height():
            self.reset()
        if self.y < 0:
            self.reset()
    
    def reset(self):
        """ move off stage and stop"""
        self.x = -100
        self.y = -100
        self.speed = 0

def main():
    screen = pygame.display.set_mode((640, 480))
    pygame.display.set_caption ("Firing a Shell")
    
    background = pygame.Surface(screen.get_size())
    background.fill((0x00, 0xCC, 0x00))
    screen.blit(background, (0, 0))
    
    shell = Shell(screen)
    turret = Turret(shell)
    lblOutput = Label()
    lblOutput.center = (100, 20)
    
    allSprites = pygame.sprite.Group(shell, turret, lblOutput)
    
    clock = pygame.time.Clock()
    keepGoing = True
    while keepGoing:
        clock.tick(30)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                keepGoing = False
        
        #update label
        lblOutput.text = "dir: %d  speed %d" % (turret.dir, turret.charge)
        
        allSprites.clear(screen, background)
        allSprites.update()
        allSprites.draw(screen)
        pygame.display.flip()

if __name__ == "__main__":
    main()