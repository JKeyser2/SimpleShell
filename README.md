[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/ZhE-zmlt)
# Project 1
Answer these questions please:

Project Overview:
-----------------------------------
What is the project about? Provide a brief overview that includes the project's name, purpose, and target audience.

The project's name is Project 1. The purpose of the project is to build a simple shell that mimics much of the functionality of a real shell. It can peform file I/O on several types of files, and return to the user many of their computer's statistics. The simple shell can also execute several commands such as ls, cd, rm, make, and many more. Lastly, the simple shell can return the user's last 10 entered commands. The target audience is anayone who would like to understand more about operating systems and system programming.

Solution Approach:
------------------------------------------------------------

How did you approach the problem? Outline the steps or phases in your project development process?

I approached the problem by breaking it down into manageable steps.

1. Get user command works
2. Parse command works
3. /proc /cpuinfo, /proc /loadavg, /proc /uptime works
4. /proc /procces_id_no/status, /proc /process_id_no/environ, /proc /proces_id_no/sched works
5. Command history works
6. Unescape works
7. cd, removing .421sh from terminal works
8. Can execute multiple commands at once works
9. $ ? works

Challenges and Solutions?
---------------------------
What challenges did you encounter while completeing your project, and how did you overcome them?

One challenge I encountered was how to create processes to be able to execute many of the commands. I had to learn about fork(), parent processes, and child processes to overcome this challenge. Googling around was how I found my answers. Another challenge I encountered was allocating space for strings. This was challenging as I have little experience with "C". GeeksForGeeks helped me in solving this problem. 

LLM Disclosure
--------------
Are there any external resources or references that might be helpful?

Stack Overflow
GeeksForGeeks

Testing and Validation
-----------------------
Testing Methodology: How did you test your project? Discuss any unit tests, integration tests, or user acceptance testing conducted.
Are there any specific commands or scripts that should be known?

I tested my project through the use of all of the commands listed in the examples.


Example session
---------------
Provide examples on running your project

** AS A SPECIAL NOTE **
My History file is a bit bugged.
If you remove the file from the simple shell, you have to leave the simple shell and come back for it to be able to be created again. Also, if the history file does not yet exist, the very first command will not be stored in it. Afterwards, it should work fine.

Examples of running my project:
/proc /cpuinfo
/proc /loadavg
/proc /uptime
/proc /127258/status
/proc /127258/environ
/proc /127258/sched
ls
$ps -el
/bin/ls -la
echo \x48\151\x20\157\165\164\040\x74\x68\x65\x72\x65\041
echo Goodbye, \'World\'\a
rm ~/.421sh && make && ./simple_shell
echo hello world
ls -al
history
echo $?
$?
./simple_shell
pwd
cd /usr
bin/gcc

