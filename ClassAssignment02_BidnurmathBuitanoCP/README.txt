EECE 7205 - In-Class Work: Deleting from a Binary Search Tree
=============================================================

Rohini Bidnurmath (NUID 003916201)
Catalina Buitano  (NUID 002330106)
Professor: Dr. Fatema Nafa
October 2026


FILES
-----
ClassAssignment_3_FCE_Bidnurmath_Buitanoo.pdf
    Written answers, tree drawings, changed lines and execution screenshots

case1_original_Q1_Q2.cpp   Case 1 original: delete the root (40) of tree T using the inorder successor
case1_modified_q1.cpp      Case 1 Q3: delete the root using the inorder predecessor

case2_original_Q1.cpp      Case 2 original: delete a leaf (10) from tree T
case2_modified_q2.cpp      Case 2 Q2: delete the leaf 70 instead

case3_original.cpp         Case 3 original: delete a node with one child (60) from tree T
case3_modified_q2q3.cpp    Case 3 Q2 and Q3: delete 35, then 55, from tree P
case3_modified_q4.cpp      Case 3 Q4: build the tree 10, 20, 30 and delete the root 10 (rule B6)

case4_original.cpp         Case 4 original: delete a node with two children (20) from tree T
case4_modified_Q1.cpp      Case 4 Q1: delete 60 instead

case5_original_Q1.cpp      Case 5 original: search for a key not in the tree (25)
case5_modified_q3.cpp      Case 5 Q3: insert the key at the NULL link where the search stops
case5_modified_q4.cpp      Case 5 Q4: print "the tree is empty" when root is null (rule B2)

bonus.cpp                  Bonus: one deleteNode(Node* root, int key) function for every case


HOW TO COMPILE AND RUN
----------------------
Each program is self-contained and takes no input. From this folder:

    g++ -o <name> <file>.cpp
    ./<name>

Example:

    g++ -o case1 case1_original_Q1_Q2.cpp
    ./case1


EXPECTED OUTPUT (the "After" line)
----------------------------------
case1_original_Q1_Q2    10 20 30 50 60 70           (root = 50)
case1_modified_q1       10 20 30 50 60 70           (root = 30)
case2_original_Q1       20 30 40 50 60 70           (root = 40)
case2_modified_q2       10 20 30 40 50 60           (root = 40)
case3_original          10 20 30 40 70              (root = 40)
case3_modified_q2q3     delete 35: 15 25 30 45 55 60 65 75   (root = 45)
                        delete 55: 15 25 30 35 45 60 65 75   (root = 45)
case3_modified_q4       20 30                       (root = 20)
case4_original          10 30 40 50 60 70           (root = 40)
case4_modified_Q1       10 20 30 40 50 70           (root = 40)
case5_original_Q1       25 is not in the tree: nothing to delete
                        10 20 30 40 50 60 70        (root = 40)
case5_modified_q3       10 20 25 30 40 50 60 70     (root = 40)
case5_modified_q4       the tree is empty
bonus                   after deleting 40, 10, 60, 25: 20 30 50 70   (root = 50)


TREES USED
----------
Tree T: 40, 20, 60, 10, 30, 50, 70           inorder: 10 20 30 40 50 60 70
Tree P: insert 45, 25, 65, 15, 35, 55, 75, 30, 60
                                             inorder: 15 25 30 35 45 55 60 65 75
