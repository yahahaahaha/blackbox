from datetime import datetime
import math
import time
import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data

def conv_op( input_op, name, kh, kw, n_out, dh, dw, p ):
    n_in = input_op.get_shape()[-1].value

    with tf.name_scope( name ) as scope:
        kernel = tf.get_variable( scope + "w",
            shape = [kh, kw, n_in, n_out], dtype = tf.float32,
            initializer = tf.contrib.layers.xavier_initializer_conv2d() )   
            #Xavier in chapter 4

        conv = tf.nn.conv2d( input_op, kernel, (1, dh, dw, 1), 
                        padding = 'SAME' )
        bias_init_val = tf.constant( 0.0, shape = [n_out], 
                                    dtype = tf.float32 )
        biases = tf.Variable( bias_init_val, trainable = True, name = 'b' )
        z = tf.nn.bias_add( conv, biases )
        activation = tf.nn.relu( z, name = scope )
        p += [kernel, biases]
        return activation

def fc_op( input_op, name, n_out, p ):
    n_in = input_op.get_shape()[-1].value

    with tf.name_scope( name ) as scope:
        kernel = tf.get_variable( scope + "w", 
            shape = [n_in, n_out], dtype = tf.float32,
            initializer = tf.contrib.layers.xavier_initializer() )
        biases = tf.Variable( tf.constant( 0.1, shape = [n_out],
                                        dtype = tf.float32), name = 'b' )
        activation = tf.nn.relu_layer( input_op, kernel, biases, 
                                    name = scope )
        p += [kernel, biases]
        return activation

def mpool_op( input_op, name, kh, kw, dh, dw ):
    return tf.nn.max_pool( input_op, ksize = [1, kh, kw, 1],
                                     strides = [1, kh, kw, 1],
                                     padding = 'SAME',
                                     name = name )

def inference_op( input_op, keep_prob ):
    p = []
    
    #convolution1:
    conv1_1 = conv_op( input_op, name = "conv1_1", kh = 3, kw = 3,
                        n_out = 64, dh = 1, dw = 1, p = p )
    conv1_2 = conv_op( conv1_1, name = "conv1_2", kh = 3, kw = 3,
                        n_out = 64, dh = 1, dw = 1, p = p )
    pool1 = mpool_op( conv1_2, name = "pool1", kh = 2, kw = 2,
                        dh = 2, dw = 2 )

    #convolution2:
    conv2_1 = conv_op( pool1, name = "conv2_1", kh = 3, kw = 3,
                        n_out = 128, dh = 1, dw = 1, p = p )
    conv2_2 = conv_op( conv2_1, name = "conv2_2", kh = 3, kw = 3,
                        n_out = 128, dh = 1, dw = 1, p = p )
    pool2 = mpool_op( conv2_2, name = "pool2", kh = 2, kw = 2,
                        dh = 2, dw = 2 )

    #convolution3
    conv3_1 = conv_op( pool2, name = "conv3_1", kh = 3, kw = 3,
                        n_out = 256, dh = 1, dw = 1, p = p )
    conv3_2 = conv_op( conv3_1, name = "conv3_2", kh = 3, kw = 3,
                        n_out = 256, dh = 1, dw = 1, p = p )
    conv3_3 = conv_op( conv3_2, name = "conv3_3", kh = 3, kw = 3,
                        n_out = 256, dh = 1, dw = 1, p = p )
    pool3 = mpool_op( conv3_3, name = "pool3", kh = 2, kw = 2,
                        dh = 2, dw = 2 )
    
    #convolution4
    conv4_1 = conv_op( pool3, name = "conv4_1", kh = 3, kw = 3,
                        n_out = 512, dh = 1, dw = 1, p = p )
    conv4_2 = conv_op( conv4_1, name = "conv4_2", kh = 3, kw = 3,
                        n_out = 512, dh = 1, dw = 1, p = p )
    conv4_3 = conv_op( conv4_2, name = "conv4_3", kh = 3, kw = 3,
                        n_out = 512, dh = 1, dw = 1, p = p )
    pool4 = mpool_op( conv4_3, name = "pool4", kh = 2, kw = 2,
                        dh = 2, dw = 2 )

    #convolution5
    conv5_1 = conv_op( pool4, name = "conv5_1", kh = 3, kw = 3,
                        n_out = 512, dh = 1, dw = 1, p = p )
    conv5_2 = conv_op( conv5_1, name = "conv5_2", kh = 3, kw = 3,
                        n_out = 512, dh = 1, dw = 1, p = p )
    conv5_3 = conv_op( conv5_2, name = "conv5_3", kh = 3, kw = 3,
                        n_out = 512, dh = 1, dw = 1, p = p )
    pool5 = mpool_op( conv5_3, name = "pool5", kh = 2, kw = 2,
                        dh = 2, dw = 2 )
    
    #reshape
    shp = pool5.get_shape()
    flattened_shape = shp[1].value * shp[2].value * shp[3].value
    resh1 = tf.reshape( pool5, [-1, flattened_shape], name = "resh1" )

    #full connection6
    fc6 = fc_op( resh1, name = "fc6", n_out = 64, p = p )
    fc6_drop = tf.nn.dropout( fc6, keep_prob, name = "fc6_drop" )

    #full conneciton7
    fc7 = fc_op( fc6_drop, name = "fc7", n_out = 64, p = p )
    fc7_drop = tf.nn.dropout( fc7, keep_prob, name = "fc7_drop" )
    
    fc8 = fc_op( fc7_drop, name = "fc8", n_out = 10, p = p )
    softmax = tf.nn.softmax( fc8 )
    predictions = tf.argmax( softmax, 1 )
    return predictions, softmax, fc8, p

def time_tensorflow_run( session, target, feed, info_string ):
    _ = session.run( target, feed_dict = feed )

def run_benchmark():
    with tf.Graph().as_default():
        sess = tf.InteractiveSession()

        image_size = 32
        x = tf.placeholder( tf.float32, [None, 784] )
        x_image = tf.reshape( x, [-1, 28, 28, 1] )
        images = tf.image.resize_image_with_crop_or_pad( x_image, image_size, image_size )
        y_ = tf.placeholder( tf.float32, [None, 10] )
        
        keep_prob = tf.placeholder( tf.float32 )
        predictions, softmax, fc8, p = inference_op( images, keep_prob )
        cross_entropy = tf.reduce_mean( -tf.reduce_sum( y_ * tf.log(softmax), reduction_indices = [1] ) )
        train_step = tf.train.AdamOptimizer( 1e-4 ).minimize( cross_entropy )
        correct_prediction = tf.equal( predictions, tf.argmax( y_, 1 ) )
        accuracy = tf.reduce_mean( tf.cast( correct_prediction, tf.float32 ) )
        

        tf.global_variables_initializer().run()

        for i in range( 20000 ):
            batch = mnist.train.next_batch( 50 )
            if i % 50 == 0:
                train_accuracy = accuracy.eval( feed_dict={x:batch[0], y_: batch[1], keep_prob:1.0} )
                print( "step %d, training accuracy %g"%( i, train_accuracy ) )
            train_step.run( feed_dict={x:batch[0], y_:batch[1], keep_prob:0.5} )

        print("test accuracy %g"%accuracy.eval( feed_dict={x:mnist.test.images, y_:mnist.test.labels, keep_prob:1.0} ) )

mnist = input_data.read_data_sets( "MNIST_data/", one_hot = True )
run_benchmark()
