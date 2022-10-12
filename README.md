# cryptoCurrency
Just a simple cryptocurrency I made because I was bored and someone said it would be too hard to make. 

The code has heaps of comments in it explaining how it works as well as some notes of what I could fix/improve.

Since I see a lot of code on github that doesn't have compile instructions and I know a lot of people complain about not knowing how to compile it, so I'll give a quick tutorial.

So you are going to need cmake to compile it, if you don't have that just google an install link.
Open a command line and create a build directory. It doesn't matter what you name it though naming it build is more conveniant (at least to me). 
You can make this directory with the command `mkdir build` after switching to whatever directory you have saved the repository to.
Then cd into the build file. Once you have done that, initialise the cmake project with `cmake -G "compiler" ..`. Replace compiler with whatever compiler you are using, I used MinGW to compile this though most compilers should work. Then, go back into the project directory and run the command `cmake --build "build dir` and it will compile the project, make sure you replace "build dir" with the folder you created before for the build directory. 
