# import module
from pdf2image import convert_from_path
from PIL import Image

 
 
# Store Pdf with convert_from_path function
image1 = convert_from_path('/home/maximilian/Git/WCO/PDF/001.pdf')
image2 = convert_from_path('/home/maximilian/Git/WCO/PDF/001_Losungen.pdf')
 
newsize = (400, 400)
image1 = image1.resize(newsize)
image2 = image2.resize(newsize)

image1.save('/home/maximilian/Git/WCO/bin/png/Task.png', 'JPEG')
image2.save('//home/maximilian/Git/WCO/bin/png/Solution.png', 'JPEG')

print("converted")