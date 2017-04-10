""" MiniGUI.py
    A simple set of GUI devices
    including a label, a button,
    and a very basic scroller
"""

import pygame
pygame.init()
class Label(pygame.sprite.Sprite):
    """ a basic label 
        properties: 
            text: text to display
            fgColor: foreground color
            bgColor: background color
            center: position of label's center
    """
    
    def __init__(self):
        pygame.sprite.Sprite.__init__(self)
        self.font = pygame.font.SysFont(None, 30)
        self.text = ""
        self.fgColor = ((0x00, 0x00, 0x00))
        self.bgColor = ((0xFF, 0xFF, 0xFF))
        self.center = (100, 100)
        self.size = (150, 30)

    def update(self):
        self.image = pygame.Surface(self.size)
        self.image.fill(self.bgColor)
        fontSurface = self.font.render(self.text, True, self.fgColor, self.bgColor)
        #center the text
        xPos = (self.image.get_width() - fontSurface.get_width())/2
        
        self.image.blit(fontSurface, (xPos, 0))
        self.rect = self.image.get_rect()
        self.rect.center = self.center

class Button(Label):
    """ a button based on the label 
        same properties as label +
        active: True if user is clicking on sprite
                False if user is not currently clicking
    """

    def __init__(self):
        Label.__init__(self)
        self.active = False
        self.bgColor = (0xCC, 0xCC, 0xCC)
    
    def update(self):
        Label.update(self)
        self.active = False
        
        #check for mouse input
        if pygame.mouse.get_pressed() == (1, 0, 0):
            if self.rect.collidepoint(pygame.mouse.get_pos()):
                self.active = True
    
class Scroller(Button):
    """ like a button, but has a numeric value that 
        can be decremented by clicking on left half
        and incremented by clicking on right half.
        new properties:
            value: the scroller's numeric value
            minValue: minimum value
            maxValue: maximum value
            increment: How much is added or subtracted
    """
    
    def __init__(self):
        Button.__init__(self)
        self.minValue = 0
        self.maxValue = 10
        self.increment = 1
        self.value = 5
        
    def update(self):
        Button.update(self)
        if self.active:
            (mousex, mousey) = pygame.mouse.get_pos()
            if mousex < self.rect.centerx:
                self.value -= self.increment
                if self.value < self.minValue:
                    self.value = self.minValue
            else:
                self.value += self.increment
                if self.value > self.maxValue:
                    self.value = self.maxValue

        self.text = "<<  %.2f  >>" % self.value
   
def main():
    screen = pygame.display.set_mode((640, 480))
    pygame.display.set_caption("Label demo")
    
    background = pygame.Surface(screen.get_size())
    background.fill((0xCC, 0xCC, 0xFF))
    screen.blit(background, (0, 0))

    label = Label()
    label.text = "Can you hear me now?"
    label.size = (250, 30)
    label.center = (150, 100)
    
    button = Button()
    button.text = "Click me..."
    button.center = (100, 200)

    scroller = Scroller()
    scroller.value = .50
    scroller.increment = .01
    scroller.maxValue = 1.00
    scroller.minValue = 0
    scroller.center = (300, 300)    
    
    allSprites = pygame.sprite.Group(label, button, scroller)
    
    clock = pygame.time.Clock()
    keepGoing = True
    while keepGoing:
        clock.tick(30)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                keepGoing = False
        
        if button.active:
            background.fill((255, 0, 0))
        else:
            background.fill((0xCC, 0xCC, 0xFF))
                   
        screen.blit(background, (0, 0))
        
        allSprites.clear(screen, background)
        allSprites.update()
        allSprites.draw(screen)
        
        pygame.display.flip()

if __name__ == "__main__":
    main()
    