""" vecProj 
    given any angle and distance,
    converts to dx and dy
    No GUI.
"""

import math

def main():
    keepGoing = True
    while keepGoing:
        print
        print "Give me an angle and distance,"
        print "and I'll convert to dx and dy values"
        print
        r = float(raw_input("distance: "))
        degrees = float(raw_input("angle (degrees): "))
        
        theta = degrees * math.pi / 180
        dx = r * math.cos(theta)
        dy = r * math.sin(theta)
        
        # compensate for inverted y axis
        dy *= -1
        
        print "dx: %f, dy: %f" % (dx, dy)
        response = raw_input("Again? (Y/N)")
        if response.upper() != "Y":
            keepGoing = False

if __name__ == "__main__":
    main()