# -*- coding: utf-8 -*-
from PIL import Image
import os

for file in os.listdir( "/Users/alala/codes/python/contest/guangdong_round1_train2_20180916/1" ):
   im = Image.open( file )
   for i in range( 1, 3 ):
       out = im.rotate( 90 * i )
       out.save( file+str(i), "JPG" )

