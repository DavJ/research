# research
files related to my research
#author David Jaros
#URL https://sites.google.com/site/davidjarosresearcher/ 

A-field-cavity:

     this directory contains different versions of file num-sol.wxm. This is wxMaxima file which contains calculation of shape of A-field-cavity excited by torroidal coil. The cavity
     boundary should be manufactured from conductive material.
 
green-book:

     contains scans of my green book read my blog for more info about green book.   

     subdirectories:

     metric-tensor          - contains calculations of several metric tensors (for Einstein theory but also for Kaluza-Klein theory) 

     non-local-transformer  - design and theory of potential free-energy device exploiting feedback and finite propagation time of vector potential changes
                              device must be properly tuned (core length must match used frequency), worth to try but will be expensive 
                              (free sheets in green book). the design of transformer must "double circular" (coils must be side by side).
                              
     philadelphia           - contains some naive reasoning related to philadelphia experiment. it's mostly not correct, check my blog why.
     
     something              - ??? don't remember what is this
    
     something-insane       - ??? don't remember what is this but it looks completely insane 

     scanned-calculations   - this was not originally in green book, I added this in Richmond should contain solutions for "faster then light" quaternion problem  
                              found 3 solutions 1 (general vector),2a (scalar) and 3 (linear dependend vector) 
                              2b is not a solution 

ionospheric-transfer:
  
     contains circuit design and some circuit analysis for Tesla-like solution for energy transfer via ionosphere. high voltage is not required here, just tune everything to resonance.  

FTL-problem:

    directory contains wxMaxima calculations related to (bi)quaternion solution of FTL-problem
     
    files:

     lorentz_transform.wxm - this is just nice introduction to Lorentz transform, nothing special. there are nice charts.

     pauli12.wxm         - this file is crucial for whole derivation. On the begining Pauli-like matrices are introduced, and they are used for quaternion representation.
                             then 4 vectors are coverted also to quaternions. then formula for %i36 Tq:expand(gQC . Q .gCC); is used for conversion of matrix multiplication 
                             to quaternion left and right multiplication. Finaly quaternion left and right multiplication is compared to matrix of Lorentz transform, and all
                             elements are symbolicaly evaluated. Then follows simplification.

     new_dev.wxm          -  in this file I substituted in 25 equations from pauli12.wxm for lij coeficients from FTL lorentz transform, and then simplified equations to 5 only
                             for case that by=0,bz=0 (i.e. reference frame is moving in x direction only)
                             k2_7 - contains the solution

     conversion_table_lorentz_to_biquats.wxm - this file contains brief summary of results from pauli12.wxm and new_dev.wxm, use as reference for further derivation 
                                               r matrix contains the solution
 
     directory scanned-calculations is link to directory of same name in green-book and contains final solutions 
















Copyright (C) 2016 David Jaros. All rights reserved.
