from PIL import Image, ImageOps
#import curses  

size = 150

output_size = (size,size//5)
symbols = "        :-=+*#%@"
#symbols = "  ♂"

def choise_symbol(pixel_color, symbols):
    symbol_id = pixel_color//len(symbols)
    if symbol_id <len(symbols):
        return symbols[pixel_color//len(symbols)]
    else:
         return symbols[len(symbols)-1]


file = open('image.txt', 'a')

def draw_list(pixels_colors):   
    for y in range(len(pixels_colors)):
        for x in range(len(pixels_colors[y])):
            file.write(choise_symbol(pixels_colors[y][x], symbols))
            if len(pixels_colors[y]) == x+1:
                file.write('\n')


image = Image.open('gigachadd.jpg')

image = image.resize(output_size)

image = image.convert("L") 
image = ImageOps.invert(image)
pix = image.load()

pixels_colors = []
for y in range(image.size[1]):
    local_list = list()
    for x in  range(image.size[0]):
        local_list.append(pix[x,y])
    pixels_colors.append(local_list)

draw_list(pixels_colors)
