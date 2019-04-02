Environment: Windows 7
IDE: Visual Studio 2017
Author: Wu Zhiqiu
Instructions: To solve the question below ,this program exhausts all possibilities to find the max prefix according the possibilities. The files in the root path are as followings:
	Record.txt: listing all possibilities
	Numbers.txt: listing all prefixs from the possibilities
	Result.txt: showing the max prefix and listing all possibilities which have the max prefix

Notes: I got this question from my friend, Qiu. Since I know exhauting all possibilities is not an effective method to sovle this question, hope you could share better algorithms. Giving suggests about my poor coding is also grateful. Thank you.

Question:

Bessie and Elsie are helping Farmer John wash the dishes, a more complicated process than one might think due to their lack of opposable thumbs.
The two cows decide that Bessie will apply soap, and Elsie will rinse. Bessie is given a dirty stack of plates labeled1 through N ( 1< N< 100000) Elsie has an empty stack, where clean plates will go. There is a counter in between Bessie and Elsie for soapy stacks.
At each step, either:
Bessie takes a plate from the top of the dirty stack, applies soap, and then places it on the counter. When placing a soapy plate on the counter, Bessie must either (i) place the plate on top of an existing non-empty soapy stack or (i) create a new soapy stack to the right of all existing soapy stacks.
Elsie takes a plate from the top of the leftmost soapy stack. Elsie rinses the plate, then places it on top of the clean stack.
The goal is for the clean stack to have all plates in order, with the smallest label on the bottom and the largest label on the top. It may not be possible for the cows to achieve this goal for the entire stack of plates, so please determine the length of the largest prefix of the input ordering for which the goal is achievable.
INPUT FORMAT (file dishes.in):
The first line of input contains N The next N lines specify the order of the dishes in Bessie's stack, with the first number being the dish on top of the stack.
OUTPUT FORMAT (file dishes.out):
Please output the length of the longest prefix of the input stack that can be successfully washed so that the plates end up ordered properly in the clean stack.
SAMPLE INPUT:
5
4
5
2
3
1
SAMPLE OUTPUT:
4
Problem credits: George Xing
