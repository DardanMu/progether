
**Progether Top Program**

The Protogether Top Program (shit name I know, suggestions welcomed) is a system analysis tool written in C and C++. It's currently in it's infancy, but we are working on getting a command line version up and running, possibly followed by a GUI version.

In a nutshell, it provides information on your systems state by parsing the information found in the /proc directory. 

**Who's working on it?**

At the moment there are only two contributors:

[Medicalizawhat](http://www.reddit.com/user/Medicalizawhat/)

[Wafflyn](http://www.reddit.com/user/Wafflyn)


**How do I contribute?**

Just send a message to one of us and we will take it from there.


**Where do I get it?**

Just go to downloads and grab the source, unpack it and compile it.

**How do I compile it?**

I haven't made a proper make file yet but if you're using gcc you can run:

 `gcc -std=gnu99 -o debug_build src/progether.c lib/defines.h lib/libMemInfo.h lib/libNetworkInfo.h -I lib`

Then: 

`./debug_build`

If you have any problems building it just message one of us and we'll try to help sort it out. 