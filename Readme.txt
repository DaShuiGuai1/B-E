Environment: Windows 7
IDE: Visual Studio 2017
Author: Wu Zhiqiu
Instructions: To solve the question below ,this program exhausts all possibilities to find the max prefix (according the possibilities). The files in the root path are as followings:
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


Excuting this program:

	Content of file Result.txt:
{
			The max prefix is (       4)!

			The following stacks are:


				Stacks        1:
					   1       2       3       5       4
					The sequence is :
					   1       2       3       5       4

				Stacks        2:
							   2       3       5       4
													   1
					The sequence is :
					   1       2       3       5       4

				Stacks        3:
									   3       5       4
											   1       2
					The sequence is :
					   1       2       3       5       4

				Stacks        4:
									   3       5       4
													   2
													   1
					The sequence is :
					   1       2       3       5       4

				Stacks        5:
											   5       4
									   1       2       3
					The sequence is :
					   1       2       3       5       4

				Stacks        6:
											   5       4
											   2       3
													   1
					The sequence is :
					   1       2       3       5       4

				Stacks        7:
											   5       4
													   3
											   1       2
					The sequence is :
					   1       2       3       5       4

				Stacks        8:
											   5       4
													   3
													   2
													   1
					The sequence is :
					   1       2       3       5       4

				Stacks        9:
													   4
							   1       2       3       5
					The sequence is :
					   1       2       3       5       4

				Stacks       10:
													   4
									   2       3       5
													   1
					The sequence is :
					   1       2       3       5       4

				Stacks       11:
													   4
											   3       5
											   1       2
					The sequence is :
					   1       2       3       5       4

				Stacks       12:
													   4
											   3       5
													   2
													   1
					The sequence is :
					   1       2       3       5       4

				Stacks       13:
													   4
													   5
									   1       2       3
					The sequence is :
					   1       2       3       5       4

				Stacks       14:
													   4
													   5
											   2       3
													   1
					The sequence is :
					   1       2       3       5       4

				Stacks       15:
													   4
													   5
													   3
											   1       2
					The sequence is :
					   1       2       3       5       4

				Stacks       16:
													   4
													   5
													   3
													   2
													   1
					The sequence is :
					   1       2       3       5       4
}
	Content of file Numbers.txt:
{
				The result is :(total       52)

				Sequence        1:
					   1       2       3       5       4
				Sequence        2:
					   1       2       3       5       4
				Sequence        3:
					   2       1       3       5       4
				Sequence        4:
					   1       2       3       5       4
				Sequence        5:
					   1       2       3       5       4
				Sequence        6:
					   3       1       2       5       4
				Sequence        7:
					   1       3       2       5       4
				Sequence        8:
					   1       3       2       5       4
				Sequence        9:
					   2       3       1       5       4
				Sequence       10:
					   1       2       3       5       4
				Sequence       11:
					   1       2       3       5       4
				Sequence       12:
					   2       3       1       5       4
				Sequence       13:
					   2       1       3       5       4
				Sequence       14:
					   1       2       3       5       4
				Sequence       15:
					   1       2       3       5       4
				Sequence       16:
					   5       1       2       3       4
				Sequence       17:
					   1       5       2       3       4
				Sequence       18:
					   1       5       2       3       4
				Sequence       19:
					   2       5       1       3       4
				Sequence       20:
					   1       2       5       3       4
				Sequence       21:
					   1       2       5       3       4
				Sequence       22:
					   2       5       1       3       4
				Sequence       23:
					   2       1       5       3       4
				Sequence       24:
					   1       2       5       3       4
				Sequence       25:
					   1       2       5       3       4
				Sequence       26:
					   3       5       1       2       4
				Sequence       27:
					   1       3       5       2       4
				Sequence       28:
					   1       3       5       2       4
				Sequence       29:
					   2       3       5       1       4
				Sequence       30:
					   1       2       3       5       4
				Sequence       31:
					   1       2       3       5       4
				Sequence       32:
					   2       3       5       1       4
				Sequence       33:
					   2       1       3       5       4
				Sequence       34:
					   1       2       3       5       4
				Sequence       35:
					   1       2       3       5       4
				Sequence       36:
					   3       5       1       2       4
				Sequence       37:
					   3       1       5       2       4
				Sequence       38:
					   1       3       5       2       4
				Sequence       39:
					   1       3       5       2       4
				Sequence       40:
					   3       2       5       1       4
				Sequence       41:
					   3       1       2       5       4
				Sequence       42:
					   1       3       2       5       4
				Sequence       43:
					   1       3       2       5       4
				Sequence       44:
					   2       3       5       1       4
				Sequence       45:
					   2       3       1       5       4
				Sequence       46:
					   1       2       3       5       4
				Sequence       47:
					   1       2       3       5       4
				Sequence       48:
					   2       3       5       1       4
				Sequence       49:
					   2       3       1       5       4
				Sequence       50:
					   2       1       3       5       4
				Sequence       51:
					   1       2       3       5       4
				Sequence       52:
					   1       2       3       5       4
}
	Content of file Record.txt:
{
				The stacks(   1) are:

													   4
				The stacks(   1) are:

											   5       4
				The stacks(   2) are:

													   4
													   5
				The stacks(   1) are:

									   3       5       4
				The stacks(   2) are:

											   5       4
													   3
				The stacks(   3) are:

											   3       4
													   5
				The stacks(   4) are:

													   4
											   3       5
				The stacks(   5) are:

													   4
													   5
													   3
				The stacks(   1) are:

							   2       3       5       4
				The stacks(   2) are:

									   3       5       4
													   2
				The stacks(   3) are:

									   2       5       4
													   3
				The stacks(   4) are:

											   5       4
											   2       3
				The stacks(   5) are:

											   5       4
													   3
													   2
				The stacks(   6) are:

									   2       3       4
													   5
				The stacks(   7) are:

											   3       4
											   2       5
				The stacks(   8) are:

											   3       4
													   5
													   2
				The stacks(   9) are:

											   2       4
											   3       5
				The stacks(  10) are:

													   4
									   2       3       5
				The stacks(  11) are:

													   4
											   3       5
													   2
				The stacks(  12) are:

											   2       4
													   5
													   3
				The stacks(  13) are:

													   4
											   2       5
													   3
				The stacks(  14) are:

													   4
													   5
											   2       3
				The stacks(  15) are:

													   4
													   5
													   3
													   2
				The stacks(   1) are:

					   1       2       3       5       4
				The stacks(   2) are:

							   2       3       5       4
													   1
				The stacks(   3) are:

							   1       3       5       4
													   2
				The stacks(   4) are:

									   3       5       4
											   1       2
				The stacks(   5) are:

									   3       5       4
													   2
													   1
				The stacks(   6) are:

							   1       2       5       4
													   3
				The stacks(   7) are:

									   2       5       4
											   1       3
				The stacks(   8) are:

									   2       5       4
													   3
													   1
				The stacks(   9) are:

									   1       5       4
											   2       3
				The stacks(  10) are:

											   5       4
									   1       2       3
				The stacks(  11) are:

											   5       4
											   2       3
													   1
				The stacks(  12) are:

									   1       5       4
													   3
													   2
				The stacks(  13) are:

											   5       4
											   1       3
													   2
				The stacks(  14) are:

											   5       4
													   3
											   1       2
				The stacks(  15) are:

											   5       4
													   3
													   2
													   1
				The stacks(  16) are:

							   1       2       3       4
													   5
				The stacks(  17) are:

									   2       3       4
											   1       5
				The stacks(  18) are:

									   2       3       4
													   5
													   1
				The stacks(  19) are:

									   1       3       4
											   2       5
				The stacks(  20) are:

											   3       4
									   1       2       5
				The stacks(  21) are:

											   3       4
											   2       5
													   1
				The stacks(  22) are:

									   1       3       4
													   5
													   2
				The stacks(  23) are:

											   3       4
											   1       5
													   2
				The stacks(  24) are:

											   3       4
													   5
											   1       2
				The stacks(  25) are:

											   3       4
													   5
													   2
													   1
				The stacks(  26) are:

									   1       2       4
											   3       5
				The stacks(  27) are:

											   2       4
									   1       3       5
				The stacks(  28) are:

											   2       4
											   3       5
													   1
				The stacks(  29) are:

											   1       4
									   2       3       5
				The stacks(  30) are:

													   4
							   1       2       3       5
				The stacks(  31) are:

													   4
									   2       3       5
													   1
				The stacks(  32) are:

											   1       4
											   3       5
													   2
				The stacks(  33) are:

													   4
									   1       3       5
													   2
				The stacks(  34) are:

													   4
											   3       5
											   1       2
				The stacks(  35) are:

													   4
											   3       5
													   2
													   1
				The stacks(  36) are:

									   1       2       4
													   5
													   3
				The stacks(  37) are:

											   2       4
											   1       5
													   3
				The stacks(  38) are:

											   2       4
													   5
											   1       3
				The stacks(  39) are:

											   2       4
													   5
													   3
													   1
				The stacks(  40) are:

											   1       4
											   2       5
													   3
				The stacks(  41) are:

													   4
									   1       2       5
													   3
				The stacks(  42) are:

													   4
											   2       5
											   1       3
				The stacks(  43) are:

													   4
											   2       5
													   3
													   1
				The stacks(  44) are:

											   1       4
													   5
											   2       3
				The stacks(  45) are:

													   4
											   1       5
											   2       3
				The stacks(  46) are:

													   4
													   5
									   1       2       3
				The stacks(  47) are:

													   4
													   5
											   2       3
													   1
				The stacks(  48) are:

											   1       4
													   5
													   3
													   2
				The stacks(  49) are:

													   4
											   1       5
													   3
													   2
				The stacks(  50) are:

													   4
													   5
											   1       3
													   2
				The stacks(  51) are:

													   4
													   5
													   3
											   1       2
				The stacks(  52) are:

													   4
													   5
													   3
													   2
													   1
}
