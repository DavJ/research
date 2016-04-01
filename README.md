# research
files related to my research
#author David Jaros
#URL http://www.octonion-multiverse.com/ 

A-field-cavity:

     this directory contains different versions of file num-sol.wxm. This is a wxMaxima file which contains calculation of shape of A-field-cavity excited by torroidal coil. the torroidal coil was 
     idealized.the cavity boundary should be manufactured from highly conductive material. 
     notes: - this is a highly speculative teleportation device (need to have two cavities with same resonant frequencies)
            - theory of operation is very similar to clasical radio-transmission. AC scalar field G created by torroidal coil is amplified by resonant cavity (used frequency must match height of cavity).  
              scalar field is ubiqutous so it resonates also in the receiving cavity.object hidden inside the cavity, including coil, which must contain also source, will behave as macroscopic quantum system,
              and will have 50% chance that it will appear in the remote cavity, instanteously. this effect is similar to tunnel effect.once the object is teleported the source must be be switched off, otherwise 
              the object will continue to oscilate between cavities.     
            - cavity is rotationaly symetric and also symetric with respect to horizontal plane, but from theory of possible operation should work even with upper/lower half only/lower. in this case
              conductive horizontal plane must be present. in this case cavity shape will be similar to shape of dome of church. 
 
green-book:

     contains scans of my green book read my blog for more info about green book. warning: contains useful calculations but is also full of bugs and deletions.   

     subdirectories:

     metric-tensor          - contains calculations of several metric tensors (for Einstein theory but also for Kaluza-Klein theory), these calculations will be mostly correct 

     non-local-transformer  - design and theory of speculative free-energy device exploiting feedback and finite propagation time of vector potential changes
                              device must be properly tuned (core length must match used frequency), worth to try but will be expensive 
                              (free sheets in green book). the design of transformer must "double circular" (coils must be side by side).
                              
     philadelphia           - contains some naive reasoning related to philadelphia experiment. it's mostly not finished and not correct, check my blog why. I had later better ideas how could Philadelphia 
                              experiment work. 
     
     something              - ??? don't remember what is this
    
     something-insane       - ??? don't remember what is this but it looks completely insane 

     scanned-calculations   - these was not originally in green book, I added this in Richmond should contain solutions for "faster then light" quaternion problem  
                              found 3 solutions 1 (general vector),2a (scalar) and 3 (linear dependend vector),2b is not a solution 

                              warning: unfortunatelly derivation was quite difficult, and there have been too many files, and it seems I lost some of them. therefore will need to recalculate.
                                       anyway these calculations have been related to hyperspace waves, and I have also calculations employing much easier approach. 
                                         
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

theory-of-everything:

    directory contains files related to theory of everything, i.e. fundamental theory combining together electromagnetic and gravity theory. I consider the formulas in this directory to be correct. 

hyperspace-waves-simple:
   
    contains simple derivation of hyperspace waves












Copyright (C) 2016 David Jaros. All rights reserved.
