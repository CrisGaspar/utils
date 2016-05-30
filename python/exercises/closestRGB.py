import sys

Red = (255, 0, 0)
Green = (0, 255, 0)
Blue = (0, 0, 255)
White = (255, 255, 255)
Black = (0,0,0)

colors = { "White": White,
           "Black": Black,
           "Red": Red,
           "Green": Green,
           "Blue": Blue}

def distSquared(val1, val2):
    return (val1[0] - val2[0]) ** 2 + (val1[1] - val2[1]) ** 2 + (val1[2] - val2[2]) ** 2

def findClosest(colorTuple):
    closest = ""
    closestVal = sys.maxint

    for color, val in colors.items():
        distSquare =  distSquared(colorTuple, val)
        if distSquare < closestVal:
            closestVal = distSquare
            closest = color
        elif distSquare == closestVal:
            closest = "Inconclusive"
    return closest

def findColorCode(hex):
    x = int(hex[0:8], 2)
    y = int(hex[8:16],2)
    z = int(hex[16:24],2)
    return (x,y,z)

def  ClosestColor( hexcodes):
    res = []
    for hex in hexcodes:
        closest = findClosest(findColorCode(hex))
        res.append(closest)
    return res

if __name__ == "__main__":
    hexcodes = ['000000110000011100001111']
    results = ClosestColor(hexcodes)
    for res in results:
        print "{}".format(res)
