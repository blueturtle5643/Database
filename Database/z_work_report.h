#ifndef Z_WORK_REPORT_H
#define Z_WORK_REPORT_H
/*
    Features:
        -Not Implemented: Nothing of note

        -Implemented: Evrything within project requirements

        -Partly implemented: Maybe more SQL features?


    Bugs: Finished with most of the bug testing, ran the tests with
    expected output so everything should be working

    Reflections:

    Project was a mess to be honest. Not having skeletal class structures
    and an organized format for every function and their purpose/pseudo
    code was pretty difficult to deal with. RPN/SY was required after
    finding out in discord(pretty sure afternoon class had no idea).

    THAT BEING SAID, maybe the vagueness of the project is a real life
    hurdle that everyone has to jump through, and every tidbit of information
    we got is considered gods mercy :)

    Piecing together an exact run of the project was pretty hard, adding
    small details to every class along the way. Whenever we were expected to
    add a new thing into the project like RPN/SY, took a while to figure out
    the exact purpose for it. I probably should've paid more attention in
    the first week of the project but I was too focused on my B+Tree. Fixing
    the numerous errors in B+Tree despite thinking it was clean was extremely
    fustrating. Spent time fixing B+Tree even after finishing up most of the
    final project.

    Record wasn't too bad since we had a demo of what to do
    but getting garbage in the binary file was weird. I assume it's because
    we were using character arrays and the garbage values are just bytes
    in between the interesting user-placed elements when testing functions.

    Table was pretty hard, I'll put some blame on the lack of structure
    but RPN/SY came as a surprise, since my idea of the project didn't include
    it. I understood that the vector of indicies is just a vector multimaps
    and that each multimap is like a mini table that is sorted based off the
    value. I decided to change it to a map since it was easier to use instead
    of manipulating a vector everywhere. Concepts like the need for a field
    map were initially confusing, but it was just necessary after using it
    so many times. I added a few small helper functions that deviated from
    the rough sketch of the class, like a string validation function and
    some functions for RPN/SY. Overall the class was pretty bloated, and
    clunky. When trying to test the stupid class by itself, I kept running
    into syntax issues and I was playing around with the "auto" variable
    which makes the computer figure out what belongs there which was helpful
    at first, but later on trying to read the code it wasn't worth it
    especially since Table was buggy.

    RPN/SY was a mess to figure out since the usage was for numbers but
    it was supposed to be remodelled to handle tokens. Using inheritance
    was expected so I scrapped enums/numbers but kept them as backup to
    test code.

    Parser made sense in a broad term, but figuring out the multiple state
    machines and the keywords and the chaining was pretty annoying since
    I kept encountering bugs. Drawing the statemachine logic out helped
    but unfortunately a full display of the array statemachine was very
    hard to debug(I had a lot of stupid logic errors I gleamed over when I
    wrote it). With the exception of using switch statements for the
    get_parse_tree I think I did it well.

    SQL wasn't hard really, but since I could only really start doing tests
    at this stage, I was only debugging for days. Ran into so many errors
    that stemmed from core classes like B+Tree and difficult errors like
    state machine flow which clogged up so much time. I'm honestly doubting
    my belonging in computer science if my brain can't re-approach a function
    when the bug is in it. I spent too much time couting every line and testing
    them even in the most simple cases which meant my intial logic was flawed.
    I'm constantly dreading even more difficult cases, or even entering more
    than one command before closing the project and re-opening. I just hope
    my future job or career isn't as scary and draining as this project.

    Overall, I'm probably submitting this project late, I am extremely
    tired and I am a mess. If my higher level classes are just repeats of this
    but with higher level concepts I don't think I'm cut out for this. God forbid
    one day I'll be told "yo build an app that does this" and I'll be sitting
    there with nothing to work off of.

    EDIT: I broke my program last night and couldn't get jack shit to run

    Fixed issues and both final/sample to match up in terms of tables.

    Maybe I should be a instagram influencer or open an onlyfans :)



*/
#endif // Z_WORK_REPORT_H
