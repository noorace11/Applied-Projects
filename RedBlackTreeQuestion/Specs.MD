Wow, Sierra wasn’t kidding! She’s got important tasks that she’s forced to leave waiting for a long time. S
urely the game developers wouldn’t mind if you helped them optimize their NPC code, right? You decide to help her.

Of course, this isn’t an open source game, so technically rewriting her decision-making algorithm would require hacking the server. 
You’d rather not get banned from the game, so you decide that you should try to make sure your activity doesn’t look suspicious. 

As you’re working, you decide to keep an eye on the load that all other users are placing on the server and ensure that you do not use more than the median amount of bandwidth. 
Hopefully that will help you avoid detection!

You will be given a series of load values to add or remove as other users join and leave the server. Write code to help you efficiently keep track of the median

Warning: This game is popular, so you might be handling a LOT of data!

The median of M numbers is defined as the middle number after sorting them in order if M is odd. Or it is the average of the middle two numbers if M is even. You start with an empty number list. Then, you can add numbers to the list, or remove existing numbers from it. After each add or remove operation, output the median.

Input Format

The first line is an integer, N, that indicates the number of operations. 
Each of the next N lines is either “a x” or “r x”, with ‘x’ being an integer. 
An “a x” indicates that the value x is inserted (added) into the set, and “r x” indicates that the value x is removed from the set.

Constraints

1 ≤ N ≤ 106

-2,147,483,649 ≤ x ≤ 2,147,483,648

Output Format

For each operation:

If the operation is remove and the number x is not in the list, output “Wrong!” in a single line, but make not other modifications to the set of numbers.
If the operation is remove and the number x is in the list, output the median after deleting x in a single line.
NOTE: If your median is 3.0, print only 3. And if your median is 3.50, print only 3.5. Whenever you need to print the median and the list is empty, print “Wrong!”.
