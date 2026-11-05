
@* The World. The next few sections specify the world map of \TT.

@ Data Structures.  The world of \TT\ is composed essentially of an
undirected graph.  Vertices represent ``nodes'' and edges represent
``paths''.  Associated with each node is an art set, a puzzle, and a set
of attached paths.  Associated with each path is an art set, a map, and
the nodes attached to each of its ends.

@<Typedef...@>=

typedef struct node_t {
  struct art_t *artSet;
  int puzzle;
  struct path_t *paths[4];
}Node, *NodePtr;@#

typedef struct path_t {
  struct art_t *artSet;
  struct square_t *map;
  NodePtr leftEnd;
  NodePtr rightEnd;
  short xSize;
  short ySize;
  short xStart;
  short yStart;
}Path, *PathPtr;

@ \TT\ is composed of five levels, each consisting of a network of nodes
connected by paths.

@<Global variables@>=
  @<Level declarations@>@;
  @<Level layouts@>@;

@ @<Level declarations@>=
  @<Level 1 declarations@>@;
  @<Level 2 declarations@>@;
  @<Level 3 declarations@>@;
  @<Level 4 declarations@>@;
  @<Level 5 declarations@>@;

@ @<Level 1 declarations@>=
Node n1_1, n1_2, n1_3, n1_4, n1_5, n1_6, n1_7, n1_8;
Path p1_1, p1_2, p1_3, p1_4, p1_5, p1_6, p1_7;
Path p1_8, p1_9, p1_10, p1_11, p1_12;

@ @<Level 2 declarations@>=
Node n2_1, n2_2, n2_3, n2_4, n2_5, n2_6, n2_7, n2_8, n2_9, n2_10, n2_11;
Path p2_1, p2_2, p2_3, p2_4, p2_5, p2_6, p2_7,p2_8, p2_9, p2_10;
Path p2_11, p2_12, p2_13, p2_14, p2_15, p2_16, p2_17;

@ @<Level 3 declarations@>=
Node n3_1, n3_2, n3_3, n3_4, n3_5, n3_6, n3_7, n3_8, n3_9, n3_10, n3_11;
Path p3_1, p3_2, p3_3, p3_4, p3_5, p3_6, p3_7;
Path p3_8, p3_9, p3_10, p3_11, p3_12, p3_13;

@ @<Level 4 declarations@>=
Node n4_1, n4_2, n4_3, n4_4, n4_5, n4_6, n4_7, n4_8;
Node n4_9, n4_10, n4_11, n4_12, n4_13, n4_14, n4_15;
Path p4_1, p4_2, p4_3, p4_4, p4_5, p4_6, p4_7,p4_8, p4_9, p4_10;
Path p4_11, p4_12, p4_13, p4_14, p4_15, p4_16, p4_17;

@ @<Level 5 declarations@>=
Node n5_1, n5_2, n5_3, n5_4, n5_5, n5_6, n5_7, n5_8;
Node n5_9, n5_10, n5_11, n5_12, n5_13, n5_14, n5_15;
Path p5_1, p5_2, p5_3, p5_4, p5_5, p5_6, p5_7,p5_8, p5_9, p5_10;
Path p5_11, p5_12, p5_13, p5_14, p5_15, p5_16, p5_17,p5_18, p5_19, p5_20;
Path NormalExit;
Path SpecialExit;

@ @<Level layouts@>=
  @<Level 1 layout@>@;
  @<Level 2 layout@>@;
  @<Level 3 layout@>@;
  @<Level 4 layout@>@;
  @<Level 5 layout@>@;

@ @<Level 1 layout@>=
  @<Level 1 paths@>@;
  @<Level 1 nodes@>@;

@ @<Level 1 paths@>=
Path p1_1 = {&round1PathArt, &round1Path1Map, NULL, &n1_1, 20, 20, 3, 0};
Path p1_2 = {&round1PathArt, NULL, &n1_1, &n1_2, 0, 0, 0, 0};
Path p1_3 = {&round1PathArt, NULL, &n1_2, &n1_3, 0, 0, 0, 0};
Path p1_4 = {&round1PathArt, NULL, &n1_3, &n1_4, 0, 0, 0, 0};
Path p1_5 = {&round1PathArt, NULL, &n1_4, &n1_5, 0, 0, 0, 0};
Path p1_6 = {&round1PathArt, NULL, &n1_4, &n1_6, 0, 0, 0, 0};
Path p1_7 = {&round1PathArt, NULL, &n1_5, &n1_6, 0, 0, 0, 0};
Path p1_8 = {&round1PathArt, NULL, &n1_5, &n1_6, 0, 0, 0, 0};
Path p1_9 = {&round1PathArt, NULL, &n1_5, &n1_7, 0, 0, 0, 0};
Path p1_10 = {&round1PathArt, NULL, &n1_6, &n1_7, 0, 0, 0, 0};
Path p1_11 = {&round1PathArt, NULL, &n1_3, &n1_8, 0, 0, 0, 0};
Path p1_12 = {&round1PathArt, NULL, &n1_8, &n1_4, 0, 0, 0, 0};

@ @<Level 1 nodes@>=
Node n1_1 = {NULL, 0, NULL, &p1_2, NULL, NULL};
Node n1_2 = {NULL, 0, &p1_2, &p1_3, NULL, NULL};
Node n1_3 = {NULL, 0, &p1_3, &p1_4, &p1_11, NULL};
Node n1_4 = {NULL, 0, &p1_4, &p1_5, &p1_6, &p1_12};
Node n1_5 = {NULL, 0, &p1_5, &p1_7, &p1_8, &p1_9};
Node n1_6 = {NULL, 0, &p1_6, &p1_7, &p1_8, &p1_10};
Node n1_7 = {NULL, 0, &p1_9, &p1_10, &p2_1, NULL};
Node n1_8 = {NULL, 0, &p1_11, &p1_12, NULL, NULL};

@ @<Level 2 layout@>=
  @<Level 2 paths@>@;
  @<Level 2 nodes@>@;

@ @<Level 2 paths@>=
Path p2_1 = {NULL, NULL, &n1_7, &n2_1, 0, 0, 0, 0};
Path p2_2 = {NULL, NULL, &n2_1, &n2_2, 0, 0, 0, 0};
Path p2_3 = {NULL, NULL, &n2_2, &n2_3, 0, 0, 0, 0};
Path p2_4 = {NULL, NULL, &n2_2, &n2_4, 0, 0, 0, 0};
Path p2_5 = {NULL, NULL, &n2_3, &n2_3, 0, 0, 0, 0};
Path p2_6 = {NULL, NULL, &n2_3, &n2_5, 0, 0, 0, 0};
Path p2_7 = {NULL, NULL, &n2_4, &n2_5, 0, 0, 0, 0};
Path p2_8 = {NULL, NULL, &n2_5, &n2_6, 0, 0, 0, 0};
Path p2_9 = {NULL, NULL, &n2_5, &n2_7, 0, 0, 0, 0};
Path p2_10 = {NULL, NULL, &n2_6, &n2_7, 0, 0, 0, 0};
Path p2_11 = {NULL, NULL, &n2_6, &n2_8, 0, 0, 0, 0};
Path p2_12 = {NULL, NULL, &n2_7, &n2_9, 0, 0, 0, 0};
Path p2_13 = {NULL, NULL, &n2_8, &n2_10, 0, 0, 0, 0};
Path p2_14 = {NULL, NULL, &n2_9, &n2_10, 0, 0, 0, 0};
Path p2_15 = {NULL, NULL, &n2_4, &n2_7, 0, 0, 0, 0};
Path p2_16 = {NULL, NULL, &n2_6, &n2_11, 0, 0, 0, 0};
Path p2_17 = {NULL, NULL, &n2_11, &n2_10, 0, 0, 0, 0};

@ @<Level 2 nodes@>=
Node n2_1 = {NULL, 0, &p2_1, &p2_2, NULL, NULL};
Node n2_2 = {NULL, 0, &p2_2, &p2_3, &p2_4, NULL};
Node n2_3 = {NULL, 0, &p2_3, &p2_5, &p2_6, NULL};
Node n2_4 = {NULL, 0, &p2_3, &p2_5, &p2_7, &p2_15};
Node n2_5 = {NULL, 0, &p2_6, &p2_7, &p2_8, &p2_9};
Node n2_6 = {NULL, 0, &p2_8, &p2_10, &p2_11, &p2_16};
Node n2_7 = {NULL, 0, &p2_15, &p2_9, &p2_10, &p2_12};
Node n2_8 = {NULL, 0, &p2_11, &p2_13, NULL, NULL};
Node n2_9 = {NULL, 0, &p2_12, &p2_14, NULL, NULL};
Node n2_10 = {NULL, 0, &p2_14, &p2_13, &p2_17, &p3_1};
Node n2_11 = {NULL, 0, &p2_16, &p2_17, NULL, NULL};

@ @<Level 3 layout@>=
  @<Level 3 paths@>@;
  @<Level 3 nodes@>@;

@ @<Level 3 paths@>=
Path p3_1 = {NULL, NULL, &n2_10, &n3_1, 0, 0, 0, 0};
Path p3_2 = {NULL, NULL, &n3_1, &n3_2, 0, 0, 0, 0};
Path p3_3 = {NULL, NULL, &n3_2, &n3_3, 0, 0, 0, 0};
Path p3_4 = {NULL, NULL, &n3_3, &n3_5, 0, 0, 0, 0};
Path p3_5 = {NULL, NULL, &n3_3, &n3_4, 0, 0, 0, 0};
Path p3_6 = {NULL, NULL, &n3_5, &n3_6, 0, 0, 0, 0};
Path p3_7 = {NULL, NULL, &n3_6, &n3_7, 0, 0, 0, 0};
Path p3_8 = {NULL, NULL, &n3_4, &n3_7, 0, 0, 0, 0};
Path p3_9 = {NULL, NULL, &n3_5, &n3_8, 0, 0, 0, 0};
Path p3_10 = {NULL, NULL, &n3_7, &n3_8, 0, 0, 0, 0};
Path p3_11 = {NULL, NULL, &n3_6, &n3_9, 0, 0, 0, 0};
Path p3_12 = {NULL, NULL, &n3_9, &n3_10, 0, 0, 0, 0};
Path p3_13 = {NULL, NULL, &n3_10, &n3_11, 0, 0, 0, 0};

@ @<Level 3 nodes@>=
Node n3_1 = {NULL, 0, &p3_1, &p3_2, NULL, NULL};
Node n3_2 = {NULL, 0, &p3_2, &p3_3, NULL, NULL};
Node n3_3 = {NULL, 0, &p3_3, &p3_4, &p3_5, NULL};
Node n3_4 = {NULL, 0, &p3_5, &p3_8, NULL, NULL};
Node n3_5 = {NULL, 0, &p3_4, &p3_6, &p3_9, NULL};
Node n3_6 = {NULL, 0, &p3_6, &p3_7, &p3_11, NULL};
Node n3_7 = {NULL, 0, &p3_8, &p3_7, &p3_10, NULL};
Node n3_8 = {NULL, 0, &p3_9, &p3_10, &p4_1, NULL};
Node n3_9 = {NULL, 0, &p3_11, &p3_12, NULL, NULL};
Node n3_10 = {NULL, 0, &p3_12, &p3_13, NULL, NULL};
Node n3_11 = {NULL, 0, &p3_13, &p4_13, NULL, NULL};

@ @<Level 4 layout@>=
  @<Level 4 paths@>@;
  @<Level 4 nodes@>@;

@ @<Level 4 paths@>=
Path p4_1 = {NULL, NULL, &n3_8, &n4_1, 0, 0, 0, 0};
Path p4_2 = {NULL, NULL, &n4_1, &n4_3, 0, 0, 0, 0};
Path p4_3 = {NULL, NULL, &n4_2, &n4_5, 0, 0, 0, 0};
Path p4_4 = {NULL, NULL, &n4_3, &n4_6, 0, 0, 0, 0};
Path p4_5 = {NULL, NULL, &n4_5, &n4_7, 0, 0, 0, 0};
Path p4_6 = {NULL, NULL, &n4_6, &n4_7, 0, 0, 0, 0};
Path p4_7 = {NULL, NULL, &n4_6, &n4_8, 0, 0, 0, 0};
Path p4_8 = {NULL, NULL, &n4_8, &n4_9, 0, 0, 0, 0};
Path p4_9 = {NULL, NULL, &n4_8, &n4_10, 0, 0, 0, 0};
Path p4_10 = {NULL, NULL, &n4_9, &n4_12, 0, 0, 0, 0};
Path p4_11 = {NULL, NULL, &n4_10, &n4_11, 0, 0, 0, 0};
Path p4_12 = {NULL, NULL, &n4_11, &n4_12, 0, 0, 0, 0};
Path p4_13 = {NULL, NULL, &n3_11, &n4_2, 0, 0, 0, 0};
Path p4_14 = {NULL, NULL, &n4_2, &n4_13, 0, 0, 0, 0};
Path p4_15 = {NULL, NULL, &n4_13, &n4_14, 0, 0, 0, 0};
Path p4_16 = {NULL, NULL, &n4_14, &n4_15, 0, 0, 0, 0};
Path p4_17 = {NULL, NULL, &n4_15, &n4_12, 0, 0, 0, 0};

@ @<Level 4 nodes@>=
Node n4_1 = {NULL, 0, &p4_1, &p4_2, NULL, NULL};
Node n4_2 = {NULL, 0, &p4_13, &p4_14, &p4_3, NULL};
Node n4_3 = {NULL, 0, &p4_2, &p4_4, NULL, NULL};
Node n4_4 = {NULL, 0, NULL, NULL, NULL, NULL};
Node n4_5 = {NULL, 0, &p4_3, &p4_5, NULL, NULL};
Node n4_6 = {NULL, 0, &p4_4, &p4_6, &p4_7, NULL};
Node n4_7 = {NULL, 0, &p4_5, &p4_6, NULL, NULL};
Node n4_8 = {NULL, 0, &p4_7, &p4_8, &p4_9, NULL};
Node n4_9 = {NULL, 0, &p4_8, &p4_10, NULL, NULL};
Node n4_10 = {NULL, 0, &p4_9, &p4_11, NULL, NULL};
Node n4_11 = {NULL, 0, &p4_11, &p4_12, NULL, NULL};
Node n4_12 = {NULL, 0, &p4_10, &p4_12, &p5_1, &p4_17};
Node n4_13 = {NULL, 0, &p4_14, &p4_15, NULL, NULL};
Node n4_14 = {NULL, 0, &p4_15, &p4_16, NULL, NULL};
Node n4_15 = {NULL, 0, &p4_16, &p4_17, NULL, NULL};

@ @<Level 5 layout@>=
  @<Level 5 paths@>@;
  @<Level 5 nodes@>@;

@ @<Level 5 paths@>=
Path p5_1 = {NULL, NULL, &n4_12, &n5_1, 0, 0, 0, 0};
Path p5_2 = {NULL, NULL, &n5_1, &n5_2, 0, 0, 0, 0};
Path p5_3 = {NULL, NULL, &n5_1, &n5_3, 0, 0, 0, 0};
Path p5_4 = {NULL, NULL, &n5_3, &n5_7, 0, 0, 0, 0};
Path p5_5 = {NULL, NULL, &n5_2, &n5_4, 0, 0, 0, 0};
Path p5_6 = {NULL, NULL, &n5_2, &n5_5, 0, 0, 0, 0};
Path p5_7 = {NULL, NULL, &n5_2, &n5_6, 0, 0, 0, 0};
Path p5_8 = {NULL, NULL, &n5_5, &n5_6, 0, 0, 0, 0};
Path p5_9 = {NULL, NULL, &n5_6, &n5_7, 0, 0, 0, 0};
Path p5_10 = {NULL, NULL, &n5_4, &n5_8, 0, 0, 0, 0};
Path p5_11 = {NULL, NULL, &n5_6, &n5_9, 0, 0, 0, 0};
Path p5_12 = {NULL, NULL, &n5_7, &n5_11, 0, 0, 0, 0};
Path p5_13 = {NULL, NULL, &n5_8, &n5_11, 0, 0, 0, 0};
Path p5_14 = {NULL, NULL, &n5_9, &n5_10, 0, 0, 0, 0};
Path p5_15 = {NULL, NULL, &n5_10, &n5_12, 0, 0, 0, 0};
Path p5_16 = {NULL, NULL, &n5_11, &n5_12, 0, 0, 0, 0};
Path p5_17 = {NULL, NULL, &n5_7, &n5_13, 0, 0, 0, 0};
Path p5_18 = {NULL, NULL, &n5_13, &n5_12, 0, 0, 0, 0};
Path p5_19 = {NULL, NULL, &n5_8, &n5_14, 0, 0, 0, 0};
Path p5_20 = {NULL, NULL, &n5_14, &n5_15, 0, 0, 0, 0};

Path NormalExit = {NULL,NULL,NULL,NULL, 0, 0, 0, 0};
Path SpecialExit = {NULL,NULL,NULL,NULL, 0, 0, 0, 0};

@ @<Level 5 nodes@>=
Node n5_1 = {NULL, 0, &p5_1, &p5_2, &p5_3, NULL};
Node n5_2 = {NULL, 0, &p5_2, &p5_7, &p5_6, &p5_5};
Node n5_3 = {NULL, 0, &p5_1, &p5_3, NULL, NULL};
Node n5_4 = {NULL, 0, &p5_5, &p5_10, NULL, NULL};
Node n5_5 = {NULL, 0, &p5_6, &p5_8, NULL, NULL};
Node n5_6 = {NULL, 0, &p5_7, &p5_8, &p5_9, &p5_11};
Node n5_7 = {NULL, 0, &p5_4, &p5_9, &p5_12, &p5_17};
Node n5_8 = {NULL, 0, &p5_10, &p5_13, &p5_19, NULL};
Node n5_9 = {NULL, 0, &p5_11, &p5_14, NULL, NULL};
Node n5_10 = {NULL, 0, &p5_14, &p5_15, NULL, NULL};
Node n5_11 = {NULL, 0, &p5_12, &p5_13, &p5_16, NULL};
Node n5_12 = {NULL, 0, &p5_15, &p5_16, &p5_18, &NormalExit};
Node n5_13 = {NULL, 0, &p5_17, &p5_18, NULL, NULL};
Node n5_14 = {NULL, 0, &p5_19, &p5_20, NULL, NULL};
Node n5_15 = {NULL, 0, &p5_20, &SpecialExit, NULL, NULL};

