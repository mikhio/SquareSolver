SquareSolver
----------
CLI utility that can solve square equation in realtime user interaction.

Installing
----------
Supporting only UNIX-like systems.

Firstly, clone repo locally. For that open terminal and paste:

    git clone https://github.com/mikhio/SquareSolver
    cd SquareSolver

Secondly, build with Makefile:

    make

And now in `./build` folder will be builded utility. Can check installation like this:

    build/SquareSolver --help

If you see help info, all builded normally.

Get started
-----------
If utility builed normally, then you can use it!

Default mode is LOOP. It means you will see constantly `Enter a b c or q (to quit): ` and give endless inputs untill `q` or `quit` command 
or if max amount of error attempts will be reached.

Also can be in modes ONCE_WITH_ATTEMPTS and ONCE_WITHOUT_ATTEMPTS and run tests from `tests/ss_tests.txt` check `--help`.


Contributing
------------
![alt text](https://media.makeameme.org/created/how-can-i-5072fab500.jpg)

It's fully open source project and anyone can join to development!
