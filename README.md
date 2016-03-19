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
  
     contains circuit design and some analysis for Tesla like solution for energy transfer via ionosphere  

FTL-problem:

    directory contains wxMaxima calculations related to (bi)quaternion solution of FTL-problem
     
    files:

     lorentz_transform.wxm - this is just nice introduction to Lorentz transform, nothing special. there are nice charts.

     pauli12-H.wxm         - this file is crucial for whole derivation. On the begining Pauli-like matrices are introduced, and they are used for quaternion representation.
                             then 4 vectors are coverted also to quaternions. then formula for %i36 Tq:expand(gQC . Q .gCC); is used for conversion of matrix multiplication 
                             to quaternion left and right multiplication. Finaly quaternion left and right multiplication is compared to matrix of Lorentz transform, and all
                             elements are symbolicaly evaluated. Then follows simplyfication.




















Copyright (C) 2016 David Jaros. All rights reserved.
