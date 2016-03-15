# Assignment 4 - YOUR NAME HERE
Comp Org assignment 4

DUE DATE: 11:59 p.m., Friday, March 11th, 2016.

## Assignment Description

For this  INDIVIDUAL assignment (no groups allowed) you will implement a *carry lookahead adder* as described in [cla.pdf](http://rpi-csci-2500-2016-spring.github.io/slides/pdf/cla.pdf).
This adder improves upon the partial adder that you implemented in [Lab 06](http://rpi-csci-2500-2016-spring.github.io/lab/2016/03/09/lab06.html).  In that lab you constructed a 4-bit [ripple carry adder](https://en.wikipedia.org/wiki/Adder_(electronics)#Ripple-carry_adder).  Now you must build a 64-bit carry lookahead adder.  This can be achieved by building a "hierarchy" of progressively larger groups, sections, etc.  See the PDF for more information.  Also, additional details may be found starting on page B-38 in your text book.

## Grading Criteria

* Correctness: 85%
  - Compute sum<sub>i</sub>, a<sub>i</sub>, b<sub>i</sub>, and c<sub>i</sub> correctly
  - Compute gg<sub>i</sub>, gp<sub>i</sub>, and gc<sub>i</sub> correctly
  - Compute sg<sub>i</sub>, sp<sub>i</sub>, and sc<sub>i</sub> correctly
  - Print out the correctly computed sum
* Documentation/Comments: 15% (i.e., liberal use of comments so we can
  understand your program).

Excuses  involving a  lack  of  understanding of  Github  will not  be
tolerated and  will result in a  20 point penalty in  addition to late
day  usage.  It  is a  simple enough  task to  check whether  you have
pushed your work to Github or not: in a web browser, go to your Github
user page  and find Assignment  3.  If it  says the last change  was X
minutes ago, you're probably all set.   If not, contact one of the TAs
immediately.  If  you still have  uncertainties about Github,  talk to
one of the TAs or an undergraduate mentor sooner rather than later.
