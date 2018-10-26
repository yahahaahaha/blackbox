import os
import numpy as np
import tensorflow as tf
import matplotlib.pyplot as plt

def get_files( file_dir ):
    flower = []
    label = []
    for i in range(17):
        for file in os.listdir( file_dir + '/' + str( i ) ):
            flower.append( file_dir + '/' + str( i ) + '/' + file )
            label.append( i )
    temp = np.array([ flower, label ])
    temp = temp.transpose()
    np.random.shuffle( temp )

    flower_list = list( temp[:, 0] )
    label_list = list( temp[:, 1] )
    label_list = [int(i) for i in label_list]

    return flower_list, label_list

def get_batch( image, label, image_width, image_height, batch_size, capacity):
    image = tf.cast( image, tf.string )
    label = tf.cast( label, tf.int32 )
    
    input_queue = tf.train.slice_input_producer( [image, label] )
    
    label = input_queue[1]
    image_contents = tf.read_file( input_queue[0] )
    image = tf.image.decode_jpeg(image_contents, channels=3) 
    image = tf.image.resize_image_with_crop_or_pad(image, image_width, image_height)
    
    image_batch, label_batch = tf.train.batch( [image, label],
                                                                 batch_size = batch_size,
                                                                 capacity = capacity )
    label_batch = tf.reshape(  label_batch, [batch_size] )
    image_batch = tf.cast( image_batch, tf.float32 )
    
    return label_batch, image_batch

image_list, label_list = get_files('jpg')
image_batch, label_batch = get_batch(image_list, label_list, 512, 512, 2, 256)

with tf.Session() as sess:
    img, label = sess.run([image_batch, label_batch])
    plt.imshow(img[0])
    plt.show()
