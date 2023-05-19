#ifndef Z_OUTPUT_H
#define Z_OUTPUT_H
/*
***** ALL RESULTS ARE VERIFIED ******
*---------------------------------------------------------------------
* Normal Run:
*---------------------------------------------------------------------


Welcome to SQL. Enter your command:
> batch sample.txt

[-1]: batch sample.txt


//****************************************************************************

//              CREATE AND INSERT

//****************************************************************************

//---- employee table ----------

[0]: make table employee fields  last,          first,                  dep


SQL: DONE.



[1]: insert into employee values Blow,          Joe,                    CS


SQL::run: inserted.

SQL: DONE.



[2]: insert into employee values Johnson,       "Jimmy",                Chemistry


SQL::run: inserted.

SQL: DONE.



[3]: insert into employee values Yang,          Bo,                     CS


SQL::run: inserted.

SQL: DONE.



[4]: insert into employee values "Jackson",     Billy,                  Math


SQL::run: inserted.

SQL: DONE.



[5]: insert into employee values Johnson,       Billy,                  "Phys Ed"


SQL::run: inserted.

SQL: DONE.



[6]: insert into employee values "Van Gogh",    "Jim Bob",              "Phys Ed"


SQL::run: inserted.

SQL: DONE.



[7]: select * from employee

    record            last           first             dep

------------------------------------------------------------------------------------------------------------------------
         0            Blow             Joe              CS
         1         Johnson           Jimmy       Chemistry
         2            Yang              Bo              CS
         3         Jackson           Billy            Math
         4         Johnson           Billy         Phys Ed
         5        Van Gogh         Jim Bob         Phys Ed


SQL: DONE.



//----- student table ----------

[8]: make table student fields  fname,                  lname,          major,                          age


SQL: DONE.



[9]: insert into student values         Flo,                    Yao,            CS,                             20


SQL::run: inserted.

SQL: DONE.



[10]: insert into student values        "Flo",                  "Jackson",      Math,                           21


SQL::run: inserted.

SQL: DONE.



[11]: insert into student values        Calvin,                 Woo,            Physics,                        22


SQL::run: inserted.

SQL: DONE.



[12]: insert into student values        "Anna Grace",   "Del Rio",      CS,                                     22


SQL::run: inserted.

SQL: DONE.



[13]: select * from student

    record           fname           lname           major             age

------------------------------------------------------------------------------------------------------------------------
         0             Flo             Yao              CS              20
         1             Flo         Jackson            Math              21
         2          Calvin             Woo         Physics              22
         3      Anna Grace         Del Rio              CS              22


SQL: DONE.



//****************************************************************************

//              SIMPLE SELECT

//****************************************************************************

[14]: select * from student

    record           fname           lname           major             age

------------------------------------------------------------------------------------------------------------------------
         0             Flo             Yao              CS              20
         1             Flo         Jackson            Math              21
         2          Calvin             Woo         Physics              22
         3      Anna Grace         Del Rio              CS              22


SQL: DONE.



//------- simple strings -------------------

[15]: select * from student where lname = Jackson

    record           fname           lname           major             age

------------------------------------------------------------------------------------------------------------------------
         0             Flo         Jackson            Math              21


SQL: DONE.



//----- quoted strings ---------------------

[16]: select * from student where lname = "Del Rio"

    record           fname           lname           major             age

------------------------------------------------------------------------------------------------------------------------
         0      Anna Grace         Del Rio              CS              22


SQL: DONE.



//-------- non-existing string ------------------

[17]: select * from student where lname = "Does Not Exist"

    record           fname           lname           major             age


SQL: DONE.



//****************************************************************************

//              RELATIONAL OPERATORS:

//****************************************************************************

//.................

//:Greater Than   :

//.................

[18]: select * from student where lname > Yang

    record           fname           lname           major             age

------------------------------------------------------------------------------------------------------------------------
         0             Flo             Yao              CS              20


SQL: DONE.



//. . . . . . . . . . . . . (Greater Than: Non-existing) . . . . . . . . . . . . . . . . . . . . .

[19]: select * from student where age > 50

    record           fname           lname           major             age


SQL: DONE.



//. . . . . . . . . . . . . (Greater than: last item) . . . . . . . . . . . . . . . . . .

[20]: select * from student where age  > 53

    record           fname           lname           major             age


SQL: DONE.



//. . . . . . . . . . . . . (Greater Than: Passed last item) . . . . . . . . . . . . . . . . . . . . .

[21]: select * from student where age > 54

    record           fname           lname           major             age


SQL: DONE.



//.................

//:Greater Equal  :

//.................

[22]: select * from student where lname >= Yang

    record           fname           lname           major             age

------------------------------------------------------------------------------------------------------------------------
         0             Flo             Yao              CS              20


SQL: DONE.



//. . . . . .  (Greater Equal non-existing: ) . . . . . . . . . . .

[23]: select * from employee where last >= Jack

    record            last           first             dep

------------------------------------------------------------------------------------------------------------------------
         0         Jackson           Billy            Math
         1         Johnson           Jimmy       Chemistry
         2         Johnson           Billy         Phys Ed
         3        Van Gogh         Jim Bob         Phys Ed
         4            Yang              Bo              CS


SQL: DONE.



//.................

//:Less Than      :

//.................

//. . . . . . . . . . . . . (Less Than: Non-existing) . . . . . . . . . . . . . . . . . . . . .

[24]: select * from student where lname < Jackson

    record           fname           lname           major             age

------------------------------------------------------------------------------------------------------------------------
         0      Anna Grace         Del Rio              CS              22


SQL: DONE.



//. . . . . . . . . . . . . (Less than: first item) . . . . . . . . . . . . . . . . . .

[25]: select * from student where age  < 20

    record           fname           lname           major             age


SQL: DONE.



//. . . . . . . . . . . . . (Less Than: before first item) . . . . . . . . . . . . . . . . . . . . .

[26]: select * from student where age  < 19

    record           fname           lname           major             age


SQL: DONE.



//.................

//:Less Equal     :

//.................

[27]: select * from student where lname <= Smith

    record           fname           lname           major             age

------------------------------------------------------------------------------------------------------------------------
         0      Anna Grace         Del Rio              CS              22
         1             Flo         Jackson            Math              21


SQL: DONE.



//. . . . . .  (Less Equal non-existing: ) . . . . . . . . . . .

[28]: select * from employee where last <= Peach

    record            last           first             dep

------------------------------------------------------------------------------------------------------------------------
         0            Blow             Joe              CS
         1         Jackson           Billy            Math
         2         Johnson           Jimmy       Chemistry
         3         Johnson           Billy         Phys Ed


SQL: DONE.



//****************************************************************************

//              LOGICAL OPERATORS

//****************************************************************************

//.................

//:AND            :

//.................

[29]: select * from student where fname = "Flo" and lname = "Yao"

    record           fname           lname           major             age

------------------------------------------------------------------------------------------------------------------------
         0             Flo             Yao              CS              20


SQL: DONE.



//.................

//:OR            :

//.................

[30]: select * from student where fname = Flo or lname = Jackson

    record           fname           lname           major             age

------------------------------------------------------------------------------------------------------------------------
         0             Flo             Yao              CS              20
         1             Flo         Jackson            Math              21


SQL: DONE.



//.................

//:OR AND         :

//.................

[31]: select * from student where fname = Flo or major = CS and age <= 23

    record           fname           lname           major             age

------------------------------------------------------------------------------------------------------------------------
         0             Flo             Yao              CS              20
         1             Flo         Jackson            Math              21
         2      Anna Grace         Del Rio              CS              22


SQL: DONE.



//.................

//:AND OR AND     :

//.................

[32]: select * from student where age <30 and major=CS or major = Physics and lname = Jackson

    record           fname           lname           major             age

------------------------------------------------------------------------------------------------------------------------
         0             Flo             Yao              CS              20
         1      Anna Grace         Del Rio              CS              22


SQL: DONE.



//.................

//:OR AND OR      :

//.................

[33]: select * from student where lname = Yang or major = CS and age < 23 or lname = Jackson

    record           fname           lname           major             age

------------------------------------------------------------------------------------------------------------------------
         0             Flo             Yao              CS              20
         1             Flo         Jackson            Math              21
         2      Anna Grace         Del Rio              CS              22


SQL: DONE.



SQL: DONE.



> batch final.txt

[34]: batch final.txt


//****************************************************************************

//              CREATE TABLES AND INSERT RECORDS

//****************************************************************************

[35]: make table employee fields  last,                 first,                  dep,            salary,         year


SQL: DONE.



[36]: insert into employee values Blow,                 Joe,                    CS,                     100000,
        2018


SQL::run: inserted.

SQL: DONE.



[37]: insert into employee values Blow,                 JoAnn,                  Physics,        200000,         2016


SQL::run: inserted.

SQL: DONE.



[38]: insert into employee values Johnson,      Jack,                   HR,             150000,         2014


SQL::run: inserted.

SQL: DONE.



[39]: insert into employee values Johnson,      "Jimmy",                Chemistry,      140000,         2018


SQL::run: inserted.

SQL: DONE.



[40]: insert into employee values Yao,          Jimmy,                  Math,           145000,         2014


SQL::run: inserted.

SQL: DONE.



[41]: insert into employee values "Yao",                Flo,                    CS,                     147000,
        2012


SQL::run: inserted.

SQL: DONE.



[42]: insert into employee values Yang,                 Bo,                     CS,                     160000,
        2013


SQL::run: inserted.

SQL: DONE.



[43]: insert into employee values Jackson,      "Flo",                  Math,           165000,         2017


SQL::run: inserted.

SQL: DONE.



[44]: insert into employee values Jackson,      Bo,                             Chemistry,      130000,         2011


SQL::run: inserted.

SQL: DONE.



[45]: insert into employee values "Jackson",    Billy,                  Math,           170000,         2017


SQL::run: inserted.

SQL: DONE.



[46]: insert into employee values Johnson,      "Mary Ann",     Math,           165000,         2014


SQL::run: inserted.

SQL: DONE.



[47]: insert into employee values Johnson,      "Billy Bob",    Physics,        142000,         2014


SQL::run: inserted.

SQL: DONE.



[48]: insert into employee values Johnson,      Billy,                  "Phys Ed",      102000,         2014


SQL::run: inserted.

SQL: DONE.



[49]: insert into employee values "Van Gogh",   Vincent,                Art,            240000,         2015


SQL::run: inserted.

SQL: DONE.



[50]: insert into employee values "Van Gogh",   Vincent,                CS,                     245000,         2015


SQL::run: inserted.

SQL: DONE.



[51]: insert into employee values "Van Gogh",   "Jim Bob",              "Phys Ed",      230000,         2010


SQL::run: inserted.

SQL: DONE.



[52]: select * from employee

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0            Blow             Joe              CS          100000            2018
         1            Blow           JoAnn         Physics          200000            2016
         2         Johnson            Jack              HR          150000            2014
         3         Johnson           Jimmy       Chemistry          140000            2018
         4             Yao           Jimmy            Math          145000            2014
         5             Yao             Flo              CS          147000            2012
         6            Yang              Bo              CS          160000            2013
         7         Jackson             Flo            Math          165000            2017
         8         Jackson              Bo       Chemistry          130000            2011
         9         Jackson           Billy            Math          170000            2017
        10         Johnson        Mary Ann            Math          165000            2014
        11         Johnson       Billy Bob         Physics          142000            2014
        12         Johnson           Billy         Phys Ed          102000            2014
        13        Van Gogh         Vincent             Art          240000            2015
        14        Van Gogh         Vincent              CS          245000            2015
        15        Van Gogh         Jim Bob         Phys Ed          230000            2010


SQL: DONE.



[53]: make table student fields fname, lname, major, age, company


SQL: DONE.



[54]: insert into student values Flo,                   Yao,            CS,                             20,     Google


SQL::run: inserted.

SQL: DONE.



[55]: insert into student values Bo,                            Yang,           CS,                             28,
                Microsoft


SQL::run: inserted.

SQL: DONE.



[56]: insert into student values "Sammuel L.",  Jackson,        CS,                             40,             Uber


SQL::run: inserted.

SQL: DONE.



[57]: insert into student values "Flo",                         "Jackson",      Math,                           21,
                Google


SQL::run: inserted.

SQL: DONE.



[58]: insert into student values "Greg",                        "Pearson",      Physics,                        20,
                Amazon


SQL::run: inserted.

SQL: DONE.



[59]: insert into student values "Jim Bob",             Smith,          Math,                           23,
        Verizon


SQL::run: inserted.

SQL: DONE.



[60]: insert into student values Calvin,                        Woo,            Physics,                        22,
                Uber


SQL::run: inserted.

SQL: DONE.



[61]: insert into student values "Anna Grace",  "Del Rio",      CS,                                     22,
        USAF


SQL::run: inserted.

SQL: DONE.



[62]: insert into student values "Teresa Mae",  Gowers,         Chemistry,                      22,             Verizon


SQL::run: inserted.

SQL: DONE.



[63]: insert into student values Alex,                  Smith,          "Gender Studies",       53,             Amazon


SQL::run: inserted.

SQL: DONE.



[64]: select * from student

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0             Flo             Yao              CS              20          Google
         1              Bo            Yang              CS              28       Microsoft
         2      Sammuel L.         Jackson              CS              40            Uber
         3             Flo         Jackson            Math              21          Google
         4            Greg         Pearson         Physics              20          Amazon
         5         Jim Bob           Smith            Math              23         Verizon
         6          Calvin             Woo         Physics              22            Uber
         7      Anna Grace         Del Rio              CS              22            USAF
         8      Teresa Mae          Gowers       Chemistry              22         Verizon
         9            Alex           Smith  Gender Studies              53          Amazon


SQL: DONE.



//****************************************************************************

//              SIMPLE SELECT:

//****************************************************************************

[65]: select * from student

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0             Flo             Yao              CS              20          Google
         1              Bo            Yang              CS              28       Microsoft
         2      Sammuel L.         Jackson              CS              40            Uber
         3             Flo         Jackson            Math              21          Google
         4            Greg         Pearson         Physics              20          Amazon
         5         Jim Bob           Smith            Math              23         Verizon
         6          Calvin             Woo         Physics              22            Uber
         7      Anna Grace         Del Rio              CS              22            USAF
         8      Teresa Mae          Gowers       Chemistry              22         Verizon
         9            Alex           Smith  Gender Studies              53          Amazon


SQL: DONE.



//------- simple strings -------------------

[66]: select * from student where lname = Jackson

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0      Sammuel L.         Jackson              CS              40            Uber
         1             Flo         Jackson            Math              21          Google


SQL: DONE.



[67]: select * from student where major = CS

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0             Flo             Yao              CS              20          Google
         1              Bo            Yang              CS              28       Microsoft
         2      Sammuel L.         Jackson              CS              40            Uber
         3      Anna Grace         Del Rio              CS              22            USAF


SQL: DONE.



[68]: select * from student where company = Uber

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0      Sammuel L.         Jackson              CS              40            Uber
         1          Calvin             Woo         Physics              22            Uber


SQL: DONE.



//----- quoted strings ---------------------

[69]: select * from student where lname = "Del Rio"

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0      Anna Grace         Del Rio              CS              22            USAF


SQL: DONE.



[70]: select * from student where fname = "Jim Bob"

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0         Jim Bob           Smith            Math              23         Verizon


SQL: DONE.



[71]: select * from student where fname = "Anna Grace"

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0      Anna Grace         Del Rio              CS              22            USAF


SQL: DONE.



[72]: select * from student where fname = "Teresa Mae"

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0      Teresa Mae          Gowers       Chemistry              22         Verizon


SQL: DONE.



//-------- non-existing string ------------------

[73]: select * from student where lname = "Does Not Exist"

    record           fname           lname           major             age         company


SQL: DONE.



//****************************************************************************

//              RELATIONAL OPERATORS:

//****************************************************************************

//.................

//:Greater Than   :

//.................

[74]: select * from student where lname > Yang

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0             Flo             Yao              CS              20          Google


SQL: DONE.



[75]: select * from student where major > Math

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0            Greg         Pearson         Physics              20          Amazon
         1          Calvin             Woo         Physics              22            Uber


SQL: DONE.



[76]: select * from student where fname > "Sammuel L."

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0      Teresa Mae          Gowers       Chemistry              22         Verizon


SQL: DONE.



[77]: select * from employee where salary > 200000

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0        Van Gogh         Jim Bob         Phys Ed          230000            2010
         1        Van Gogh         Vincent             Art          240000            2015
         2        Van Gogh         Vincent              CS          245000            2015


SQL: DONE.



[78]: select * from employee where dep > Chemistry

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0         Johnson            Jack              HR          150000            2014
         1             Yao           Jimmy            Math          145000            2014
         2         Jackson             Flo            Math          165000            2017
         3         Jackson           Billy            Math          170000            2017
         4         Johnson        Mary Ann            Math          165000            2014
         5         Johnson           Billy         Phys Ed          102000            2014
         6        Van Gogh         Jim Bob         Phys Ed          230000            2010
         7            Blow           JoAnn         Physics          200000            2016
         8         Johnson       Billy Bob         Physics          142000            2014


SQL: DONE.



[79]: select * from employee where last > Jackson

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0         Johnson            Jack              HR          150000            2014
         1         Johnson           Jimmy       Chemistry          140000            2018
         2         Johnson        Mary Ann            Math          165000            2014
         3         Johnson       Billy Bob         Physics          142000            2014
         4         Johnson           Billy         Phys Ed          102000            2014
         5        Van Gogh         Vincent             Art          240000            2015
         6        Van Gogh         Vincent              CS          245000            2015
         7        Van Gogh         Jim Bob         Phys Ed          230000            2010
         8            Yang              Bo              CS          160000            2013
         9             Yao           Jimmy            Math          145000            2014
        10             Yao             Flo              CS          147000            2012


SQL: DONE.



[80]: select * from employee where first > "Billy Bob"

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0            Yang              Bo              CS          160000            2013
         1         Jackson              Bo       Chemistry          130000            2011
         2             Yao             Flo              CS          147000            2012
         3         Jackson             Flo            Math          165000            2017
         4         Johnson            Jack              HR          150000            2014
         5        Van Gogh         Jim Bob         Phys Ed          230000            2010
         6         Johnson           Jimmy       Chemistry          140000            2018
         7             Yao           Jimmy            Math          145000            2014
         8            Blow           JoAnn         Physics          200000            2016
         9            Blow             Joe              CS          100000            2018
        10         Johnson        Mary Ann            Math          165000            2014
        11        Van Gogh         Vincent             Art          240000            2015
        12        Van Gogh         Vincent              CS          245000            2015


SQL: DONE.



//. . . . . . . . . . . . . (Greater Than: Non-existing) . . . . . . . . . . . . . . . . . . . . .

[81]: select * from student where age > 50

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0            Alex           Smith  Gender Studies              53          Amazon


SQL: DONE.



[82]: select * from student where age > 35

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0      Sammuel L.         Jackson              CS              40            Uber
         1            Alex           Smith  Gender Studies              53          Amazon


SQL: DONE.



[83]: select * from student where fname > T

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0      Teresa Mae          Gowers       Chemistry              22         Verizon


SQL: DONE.



[84]: select * from employee where salary > 130000

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0         Johnson           Jimmy       Chemistry          140000            2018
         1         Johnson       Billy Bob         Physics          142000            2014
         2             Yao           Jimmy            Math          145000            2014
         3             Yao             Flo              CS          147000            2012
         4         Johnson            Jack              HR          150000            2014
         5            Yang              Bo              CS          160000            2013
         6         Jackson             Flo            Math          165000            2017
         7         Johnson        Mary Ann            Math          165000            2014
         8         Jackson           Billy            Math          170000            2017
         9            Blow           JoAnn         Physics          200000            2016
        10        Van Gogh         Jim Bob         Phys Ed          230000            2010
        11        Van Gogh         Vincent             Art          240000            2015
        12        Van Gogh         Vincent              CS          245000            2015


SQL: DONE.



[85]: select * from employee where  year > 2009

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0        Van Gogh         Jim Bob         Phys Ed          230000            2010
         1         Jackson              Bo       Chemistry          130000            2011
         2             Yao             Flo              CS          147000            2012
         3            Yang              Bo              CS          160000            2013
         4         Johnson            Jack              HR          150000            2014
         5             Yao           Jimmy            Math          145000            2014
         6         Johnson        Mary Ann            Math          165000            2014
         7         Johnson       Billy Bob         Physics          142000            2014
         8         Johnson           Billy         Phys Ed          102000            2014
         9        Van Gogh         Vincent             Art          240000            2015
        10        Van Gogh         Vincent              CS          245000            2015
        11            Blow           JoAnn         Physics          200000            2016
        12         Jackson             Flo            Math          165000            2017
        13         Jackson           Billy            Math          170000            2017
        14            Blow             Joe              CS          100000            2018
        15         Johnson           Jimmy       Chemistry          140000            2018


SQL: DONE.



//. . . . . . . . . . . . . (Greater than: last item) . . . . . . . . . . . . . . . . . .

[86]: select * from student where age  > 53

    record           fname           lname           major             age         company


SQL: DONE.



[87]: select * from student where lname > Yao

    record           fname           lname           major             age         company


SQL: DONE.



[88]: select * from student where fname > "Teresa Mae"

    record           fname           lname           major             age         company


SQL: DONE.



[89]: select * from employee where last > "Van Gogh"

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0            Yang              Bo              CS          160000            2013
         1             Yao           Jimmy            Math          145000            2014
         2             Yao             Flo              CS          147000            2012


SQL: DONE.



[90]: select * from employee where first > Vincent

    record            last           first             dep          salary            year


SQL: DONE.



[91]: select * from employee where salary > 260000

    record            last           first             dep          salary            year


SQL: DONE.



//. . . . . . . . . . . . . (Greater Than: Passed last item) . . . . . . . . . . . . . . . . . . . . .

[92]: select * from student where age > 54

    record           fname           lname           major             age         company


SQL: DONE.



[93]: select * from student where lname > Zoolander

    record           fname           lname           major             age         company


SQL: DONE.



[94]: select * from employee where last > Zoolaner

    record            last           first             dep          salary            year


SQL: DONE.



[95]: select * from employee where first > Xu

    record            last           first             dep          salary            year


SQL: DONE.



//.................

//:Greater Equal  :

//.................

[96]: select * from student where lname >= Yang

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0              Bo            Yang              CS              28       Microsoft
         1             Flo             Yao              CS              20          Google


SQL: DONE.



[97]: select * from student where fname >= "Sammuel L."

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0      Sammuel L.         Jackson              CS              40            Uber
         1      Teresa Mae          Gowers       Chemistry              22         Verizon


SQL: DONE.



[98]: select * from student where age >= 40

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0      Sammuel L.         Jackson              CS              40            Uber
         1            Alex           Smith  Gender Studies              53          Amazon


SQL: DONE.



//. . . . . .  (Greater Equal non-existing: ) . . . . . . . . . . .

[99]: select * from employee where last >= Jack

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0         Jackson             Flo            Math          165000            2017
         1         Jackson              Bo       Chemistry          130000            2011
         2         Jackson           Billy            Math          170000            2017
         3         Johnson            Jack              HR          150000            2014
         4         Johnson           Jimmy       Chemistry          140000            2018
         5         Johnson        Mary Ann            Math          165000            2014
         6         Johnson       Billy Bob         Physics          142000            2014
         7         Johnson           Billy         Phys Ed          102000            2014
         8        Van Gogh         Vincent             Art          240000            2015
         9        Van Gogh         Vincent              CS          245000            2015
        10        Van Gogh         Jim Bob         Phys Ed          230000            2010
        11            Yang              Bo              CS          160000            2013
        12             Yao           Jimmy            Math          145000            2014
        13             Yao             Flo              CS          147000            2012


SQL: DONE.



[100]: select * from employee where first >= Bill

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0         Jackson           Billy            Math          170000            2017
         1         Johnson           Billy         Phys Ed          102000            2014
         2         Johnson       Billy Bob         Physics          142000            2014
         3            Yang              Bo              CS          160000            2013
         4         Jackson              Bo       Chemistry          130000            2011
         5             Yao             Flo              CS          147000            2012
         6         Jackson             Flo            Math          165000            2017
         7         Johnson            Jack              HR          150000            2014
         8        Van Gogh         Jim Bob         Phys Ed          230000            2010
         9         Johnson           Jimmy       Chemistry          140000            2018
        10             Yao           Jimmy            Math          145000            2014
        11            Blow           JoAnn         Physics          200000            2016
        12            Blow             Joe              CS          100000            2018
        13         Johnson        Mary Ann            Math          165000            2014
        14        Van Gogh         Vincent             Art          240000            2015
        15        Van Gogh         Vincent              CS          245000            2015


SQL: DONE.



[101]: select * from employee where salary >= 235000

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0        Van Gogh         Vincent             Art          240000            2015
         1        Van Gogh         Vincent              CS          245000            2015


SQL: DONE.



//.................

//:Less Than      :

//.................

//. . . . . . . . . . . . . (Less Than: Non-existing) . . . . . . . . . . . . . . . . . . . . .

[102]: select * from student where lname < Jackson

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0      Anna Grace         Del Rio              CS              22            USAF
         1      Teresa Mae          Gowers       Chemistry              22         Verizon


SQL: DONE.



[103]: select * from student where major < Math

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0             Flo             Yao              CS              20          Google
         1              Bo            Yang              CS              28       Microsoft
         2      Sammuel L.         Jackson              CS              40            Uber
         3      Anna Grace         Del Rio              CS              22            USAF
         4      Teresa Mae          Gowers       Chemistry              22         Verizon
         5            Alex           Smith  Gender Studies              53          Amazon


SQL: DONE.



[104]: select * from student where fname < "Jim Bob"

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0            Alex           Smith  Gender Studies              53          Amazon
         1      Anna Grace         Del Rio              CS              22            USAF
         2              Bo            Yang              CS              28       Microsoft
         3          Calvin             Woo         Physics              22            Uber
         4             Flo             Yao              CS              20          Google
         5             Flo         Jackson            Math              21          Google
         6            Greg         Pearson         Physics              20          Amazon


SQL: DONE.



[105]: select * from employee where salary < 200000

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0            Blow             Joe              CS          100000            2018
         1         Johnson           Billy         Phys Ed          102000            2014
         2         Jackson              Bo       Chemistry          130000            2011
         3         Johnson           Jimmy       Chemistry          140000            2018
         4         Johnson       Billy Bob         Physics          142000            2014
         5             Yao           Jimmy            Math          145000            2014
         6             Yao             Flo              CS          147000            2012
         7         Johnson            Jack              HR          150000            2014
         8            Yang              Bo              CS          160000            2013
         9         Jackson             Flo            Math          165000            2017
        10         Johnson        Mary Ann            Math          165000            2014
        11         Jackson           Billy            Math          170000            2017


SQL: DONE.



[106]: select * from employee where dep < CS

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0        Van Gogh         Vincent             Art          240000            2015


SQL: DONE.



[107]: select * from employee where last < Jackson

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0            Blow             Joe              CS          100000            2018
         1            Blow           JoAnn         Physics          200000            2016


SQL: DONE.



[108]: select * from employee where first < "Billy Bob"

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0         Jackson           Billy            Math          170000            2017
         1         Johnson           Billy         Phys Ed          102000            2014


SQL: DONE.



//. . . . . . . . . . . . . (Less than: first item) . . . . . . . . . . . . . . . . . .

[109]: select * from student where age  < 20

    record           fname           lname           major             age         company


SQL: DONE.



[110]: select * from student where lname < "Del Rio"

    record           fname           lname           major             age         company


SQL: DONE.



[111]: select * from student where fname < Alex

    record           fname           lname           major             age         company


SQL: DONE.



[112]: select * from employee where last < Blow

    record            last           first             dep          salary            year


SQL: DONE.



[113]: select * from employee where first < Billy

    record            last           first             dep          salary            year


SQL: DONE.



[114]: select * from employee where salary < 100000

    record            last           first             dep          salary            year


SQL: DONE.



//. . . . . . . . . . . . . (Less Than: before first item) . . . . . . . . . . . . . . . . . . . . .

[115]: select * from student where age  < 19

    record           fname           lname           major             age         company


SQL: DONE.



[116]: select * from student where lname < Adams

    record           fname           lname           major             age         company


SQL: DONE.



[117]: select * from student where fname < Adam

    record           fname           lname           major             age         company


SQL: DONE.



[118]: select * from employee where last < Alex

    record            last           first             dep          salary            year


SQL: DONE.



[119]: select * from employee where first < Avory

    record            last           first             dep          salary            year


SQL: DONE.



[120]: select * from employee where dep < Alchemy

    record            last           first             dep          salary            year


SQL: DONE.



//.................

//:Less Equal     :

//.................

[121]: select * from student where lname <= Smith

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0      Anna Grace         Del Rio              CS              22            USAF
         1      Teresa Mae          Gowers       Chemistry              22         Verizon
         2      Sammuel L.         Jackson              CS              40            Uber
         3             Flo         Jackson            Math              21          Google
         4            Greg         Pearson         Physics              20          Amazon
         5         Jim Bob           Smith            Math              23         Verizon
         6            Alex           Smith  Gender Studies              53          Amazon


SQL: DONE.



[122]: select * from student where fname <= Greg

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0            Alex           Smith  Gender Studies              53          Amazon
         1      Anna Grace         Del Rio              CS              22            USAF
         2              Bo            Yang              CS              28       Microsoft
         3          Calvin             Woo         Physics              22            Uber
         4             Flo             Yao              CS              20          Google
         5             Flo         Jackson            Math              21          Google
         6            Greg         Pearson         Physics              20          Amazon


SQL: DONE.



[123]: select * from student where age <= 40

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0             Flo             Yao              CS              20          Google
         1            Greg         Pearson         Physics              20          Amazon
         2             Flo         Jackson            Math              21          Google
         3          Calvin             Woo         Physics              22            Uber
         4      Anna Grace         Del Rio              CS              22            USAF
         5      Teresa Mae          Gowers       Chemistry              22         Verizon
         6         Jim Bob           Smith            Math              23         Verizon
         7              Bo            Yang              CS              28       Microsoft
         8      Sammuel L.         Jackson              CS              40            Uber


SQL: DONE.



//. . . . . .  (Less Equal non-existing: ) . . . . . . . . . . .

[124]: select * from employee where last <= Peach

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0            Blow             Joe              CS          100000            2018
         1            Blow           JoAnn         Physics          200000            2016
         2         Jackson             Flo            Math          165000            2017
         3         Jackson              Bo       Chemistry          130000            2011
         4         Jackson           Billy            Math          170000            2017
         5         Johnson            Jack              HR          150000            2014
         6         Johnson           Jimmy       Chemistry          140000            2018
         7         Johnson        Mary Ann            Math          165000            2014
         8         Johnson       Billy Bob         Physics          142000            2014
         9         Johnson           Billy         Phys Ed          102000            2014


SQL: DONE.



[125]: select * from employee where first <= Gary

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0         Jackson           Billy            Math          170000            2017
         1         Johnson           Billy         Phys Ed          102000            2014
         2         Johnson       Billy Bob         Physics          142000            2014
         3            Yang              Bo              CS          160000            2013
         4         Jackson              Bo       Chemistry          130000            2011
         5             Yao             Flo              CS          147000            2012
         6         Jackson             Flo            Math          165000            2017


SQL: DONE.



[126]: select * from employee where salary <= 23500

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0            Blow             Joe              CS          100000            2018
         1         Johnson           Billy         Phys Ed          102000            2014
         2         Jackson              Bo       Chemistry          130000            2011
         3         Johnson           Jimmy       Chemistry          140000            2018
         4         Johnson       Billy Bob         Physics          142000            2014
         5             Yao           Jimmy            Math          145000            2014
         6             Yao             Flo              CS          147000            2012
         7         Johnson            Jack              HR          150000            2014
         8            Yang              Bo              CS          160000            2013
         9         Jackson             Flo            Math          165000            2017
        10         Johnson        Mary Ann            Math          165000            2014
        11         Jackson           Billy            Math          170000            2017
        12            Blow           JoAnn         Physics          200000            2016
        13        Van Gogh         Jim Bob         Phys Ed          230000            2010


SQL: DONE.



//****************************************************************************

//              LOGICAL OPERATORS

//****************************************************************************

//.................

//:AND            :

//.................

[127]: select * from student where fname = "Flo" and lname = "Yao"

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0             Flo             Yao              CS              20          Google


SQL: DONE.



[128]: select * from student where major = "CS" and age < 25

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0             Flo             Yao              CS              20          Google
         1      Anna Grace         Del Rio              CS              22            USAF


SQL: DONE.



[129]: select * from student where major < Math and age > 25

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0              Bo            Yang              CS              28       Microsoft
         1      Sammuel L.         Jackson              CS              40            Uber
         2            Alex           Smith  Gender Studies              53          Amazon


SQL: DONE.



[130]: select * from employee where dep = CS and salary > 150000

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0            Yang              Bo              CS          160000            2013
         1        Van Gogh         Vincent              CS          245000            2015


SQL: DONE.



[131]: select * from employee where last = Jackson and year < 2015

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0         Jackson              Bo       Chemistry          130000            2011


SQL: DONE.



[132]: select * from employee where last = Johnson and year >=2014

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0         Johnson            Jack              HR          150000            2014
         1         Johnson        Mary Ann            Math          165000            2014
         2         Johnson       Billy Bob         Physics          142000            2014
         3         Johnson           Billy         Phys Ed          102000            2014
         4         Johnson           Jimmy       Chemistry          140000            2018


SQL: DONE.



//.................

//:OR            :

//.................

[133]: select * from student where fname = Flo or lname = Jackson

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0             Flo             Yao              CS              20          Google
         1      Sammuel L.         Jackson              CS              40            Uber
         2             Flo         Jackson            Math              21          Google


SQL: DONE.



[134]: select * from student where age >=40  or company = Verizon

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0      Sammuel L.         Jackson              CS              40            Uber
         1         Jim Bob           Smith            Math              23         Verizon
         2      Teresa Mae          Gowers       Chemistry              22         Verizon
         3            Alex           Smith  Gender Studies              53          Amazon


SQL: DONE.



[135]: select * from employee where first = Bo or last = Johnson

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0         Johnson            Jack              HR          150000            2014
         1         Johnson           Jimmy       Chemistry          140000            2018
         2            Yang              Bo              CS          160000            2013
         3         Jackson              Bo       Chemistry          130000            2011
         4         Johnson        Mary Ann            Math          165000            2014
         5         Johnson       Billy Bob         Physics          142000            2014
         6         Johnson           Billy         Phys Ed          102000            2014


SQL: DONE.



[136]: select * from employee where year >= 2015 or dep = CS

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0            Blow             Joe              CS          100000            2018
         1            Blow           JoAnn         Physics          200000            2016
         2         Johnson           Jimmy       Chemistry          140000            2018
         3             Yao             Flo              CS          147000            2012
         4            Yang              Bo              CS          160000            2013
         5         Jackson             Flo            Math          165000            2017
         6         Jackson           Billy            Math          170000            2017
         7        Van Gogh         Vincent             Art          240000            2015
         8        Van Gogh         Vincent              CS          245000            2015


SQL: DONE.



[137]: select * from employee where year >= 2020 or dep = CompSci

    record            last           first             dep          salary            year


SQL: DONE.



[138]: select * from employee where year < 2010 or dep = CS

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0            Blow             Joe              CS          100000            2018
         1             Yao             Flo              CS          147000            2012
         2            Yang              Bo              CS          160000            2013
         3        Van Gogh         Vincent              CS          245000            2015


SQL: DONE.



//.................

//:OR AND         :

//.................

[139]: select * from student where fname = Flo or major = CS and age <= 23

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0             Flo             Yao              CS              20          Google
         1             Flo         Jackson            Math              21          Google
         2      Anna Grace         Del Rio              CS              22            USAF


SQL: DONE.



[140]: select * from employee where last = "Van Gogh" or last = Jackson and salary >= 165000

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0         Jackson             Flo            Math          165000            2017
         1         Jackson           Billy            Math          170000            2017
         2        Van Gogh         Vincent             Art          240000            2015
         3        Van Gogh         Vincent              CS          245000            2015
         4        Van Gogh         Jim Bob         Phys Ed          230000            2010


SQL: DONE.



[141]: select * from student where lname = Jackson or age < 23 and company > Uber

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0      Sammuel L.         Jackson              CS              40            Uber
         1             Flo         Jackson            Math              21          Google
         2      Teresa Mae          Gowers       Chemistry              22         Verizon


SQL: DONE.



[142]: select * from student where lname = Jackson or age > 23 and company > Uber

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0      Sammuel L.         Jackson              CS              40            Uber
         1             Flo         Jackson            Math              21          Google


SQL: DONE.



[143]: select * from student where lname = Jackson or age > 73 and company > Uber

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0      Sammuel L.         Jackson              CS              40            Uber
         1             Flo         Jackson            Math              21          Google


SQL: DONE.



[144]: select * from student where lname = "Jackson" or age > 73 and company > Uber

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0      Sammuel L.         Jackson              CS              40            Uber
         1             Flo         Jackson            Math              21          Google


SQL: DONE.



[145]: select * from student where lname = "Solis" or age > 73 and company > Uber

    record           fname           lname           major             age         company


SQL: DONE.



[146]: select * from student where lname = "Solis" or age > 23 and company > Uber

    record           fname           lname           major             age         company


SQL: DONE.



//.................

//:AND OR AND     :

//.................

[147]: select * from student where age <30 and major=CS or major = Physics and company = Amazon

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0             Flo             Yao              CS              20          Google
         1              Bo            Yang              CS              28       Microsoft
         2            Greg         Pearson         Physics              20          Amazon
         3      Anna Grace         Del Rio              CS              22            USAF


SQL: DONE.



[148]: select * from student where age <=40 and company=Uber or major = CS and company = Google

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0             Flo             Yao              CS              20          Google
         1      Sammuel L.         Jackson              CS              40            Uber
         2          Calvin             Woo         Physics              22            Uber


SQL: DONE.



[149]: select * from employee where dep = CS and salary >= 160000 or year > 2014 and last = "Van Gogh"

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0            Yang              Bo              CS          160000            2013
         1        Van Gogh         Vincent             Art          240000            2015
         2        Van Gogh         Vincent              CS          245000            2015


SQL: DONE.



[150]: select * from employee where dep = CS and salary >= 160000 or year > 2015 and last = "Van Gogh"

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0            Yang              Bo              CS          160000            2013
         1        Van Gogh         Vincent              CS          245000            2015


SQL: DONE.



//.................

//:OR AND OR      :

//.................

[151]: select * from student where lname = Yang or major = CS and age < 23 or company = Google

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0             Flo             Yao              CS              20          Google
         1              Bo            Yang              CS              28       Microsoft
         2             Flo         Jackson            Math              21          Google
         3      Anna Grace         Del Rio              CS              22            USAF


SQL: DONE.



[152]: select * from student where major = Physics or major = Math and company = Google or lname = Jackson

    record           fname           lname           major             age         company

------------------------------------------------------------------------------------------------------------------------
         0      Sammuel L.         Jackson              CS              40            Uber
         1             Flo         Jackson            Math              21          Google
         2            Greg         Pearson         Physics              20          Amazon
         3          Calvin             Woo         Physics              22            Uber


SQL: DONE.



[153]: select * from employee where dep = CS or year >2014 and year < 2018 or salary >= 240000

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0            Blow             Joe              CS          100000            2018
         1            Blow           JoAnn         Physics          200000            2016
         2             Yao             Flo              CS          147000            2012
         3            Yang              Bo              CS          160000            2013
         4         Jackson             Flo            Math          165000            2017
         5         Jackson           Billy            Math          170000            2017
         6        Van Gogh         Vincent             Art          240000            2015
         7        Van Gogh         Vincent              CS          245000            2015


SQL: DONE.



[154]: select * from employee where dep = CS or year >2014 and year < 2018 or salary >= 242000

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0            Blow             Joe              CS          100000            2018
         1            Blow           JoAnn         Physics          200000            2016
         2             Yao             Flo              CS          147000            2012
         3            Yang              Bo              CS          160000            2013
         4         Jackson             Flo            Math          165000            2017
         5         Jackson           Billy            Math          170000            2017
         6        Van Gogh         Vincent             Art          240000            2015
         7        Van Gogh         Vincent              CS          245000            2015


SQL: DONE.



[155]: select * from employee where dep = CS or year >2014 and year < 2018 or salary > 240000

    record            last           first             dep          salary            year

------------------------------------------------------------------------------------------------------------------------
         0            Blow             Joe              CS          100000            2018
         1            Blow           JoAnn         Physics          200000            2016
         2             Yao             Flo              CS          147000            2012
         3            Yang              Bo              CS          160000            2013
         4         Jackson             Flo            Math          165000            2017
         5         Jackson           Billy            Math          170000            2017
         6        Van Gogh         Vincent             Art          240000            2015
         7        Van Gogh         Vincent              CS          245000            2015


SQL: DONE.



SQL: DONE.



>

*---------------------------------------------------------------------
* Help:
*---------------------------------------------------------------------

N/A

*---------------------------------------------------------------------
* No Input:
*---------------------------------------------------------------------

*---------------------------------------------------------------------
* Bad Input:
*---------------------------------------------------------------------


*/

#endif // Z_OUTPUT_H
