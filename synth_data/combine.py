import sys
import Image
from math import exp

count = len(sys.argv)

if count != 5:
    exit

img1 = Image.open(sys.argv[1])
pix1 = img1.load()

img2 = Image.open(sys.argv[3])
pix2 = img2.load()

tau1 = float(sys.argv[2])
tau2 = float(sys.argv[4])

dims = img1.size

f = open('output.simple', 'w')

f.write('%d %d %d\n' % (dims[0], dims[1], 256))

for x in range(0, dims[0]):
    for y in range(0, dims[1]):
        for z in range(0, 256):
          value = int(float(pix1[x, y]) * exp(-float(z) / tau1) + float(pix2[x, y]) * exp(-float(z) / tau2))

          line = '%d %d %d %d \n' % (x, y, z, int(value))

          f.write(line)

f.close()
