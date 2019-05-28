CONTENT:
This is the assignment I did for Data Structure & Algorithm class. Please read "Assignment.pdf" for the problem statement.


To compile, type this in console:
   g++ command.cpp database.cpp


WHAT IS SUPPORTED:
-----------------
CREATE:
1. Missing colon in 1 of the line will cause error.
2. Missing the string "PRIMARy KEY" in the first attribute will cause error.
3. Adding "additional" colon in each line will cause error.
4. You must specify the size of the string type attribute in bracket.It can contain many
   space in the bracket as long as there must be a number inside.No number / put some alphabet / 
   put number < 1 or > 40 in the bracket will cause error.
   E.g. (   30) is accepted.
5. Trying to add some "extra" string after each line will cause error.
   E.g. ID string(5) sadasd, <--- error.
   E.g. price number dsfs,   <--- error.
6. The command must be "CREATE" "TABLE" "XXX",they must seperated by a least 1 space,
   else it will show error.
7. If there is no '(' and ')' to include those attributes lines,error.
8. If the attribute type is other than string and number,error.
9. Maximum 6 attributes can be created only as mention in the assignment.More than 6 = error.


INSERT:
1. The command must be "INSERT" "INTO" "TABLENAME",they must be seperated by a least a space,
   else = error.
2. The table name must be correct,else = error.
3. Missing '"' to include the data for string type will cause error.
4. Adding '"' to include number type data will cause error.
5. The range or the size of data that exceed the length allow = error.
6. Primary key cannot be null.
7. There can be many space between each data.
e.g. ("abc",     "efg"   , 12345).


SELECT:
1. The table name to be selected must be correct,else = error.
2. The command must be "SELECT" "FROM" "TABLENAME".There must be a least a space between them,
   else = error.
3. The attributes to be selected must be correct,else = error.
4. Select repeated attribute = error.
5. The operator for WHERE condition must be '=',else = error.
6. For string type, the word after WHERE must enclose with '"',else = error.
7. For number type, the word after WHERE cannot enclose with "'" and all the data must be
   digit, else = error.
8. For order by, the command must be "ORDER" "BY" "ATTRIBUTE(sort key)" "ASC/DESC",
   they must be seperated by a least a space, and the sort key must be correct.Else = error.
9. WHERE just support 1 condition(attribute) only.

DELETE:
1. The command must be "DELETE" "FROM" "TABLENAME" "WHERE",they must be seperated by a 
   least a space,and the table name must be correct,else = error.
2. The attribute name for WHERE condition must be correct,else = error.
3. WHERE just support 1 condition(attribute) only.
4. STRING type data for WHERE must enclose with '"', and vice versa.

DROP:
1. The command must be "DROP" "TABLE" "TABLENAME",the table name must be correct,and they must 
   be seperated by at least a space.
2. Adding some "additional" words after the table name will cause error.

UPDATE:
1. The table name must be correct,else = error.
2. The size for the new data must be in the range,else it will set to NULL.
3. WHERE just support 1 condition(attribute) only.
4. STRING type data for SET and WHERE must enclose with "'",and vice versa.

Others:
1. Missing semicolon ';' in each command will cause error.
2. A nonspace character between each command will cause error.

Eg.
Insert into xxxxxx;
asdasd	   		<--- error.
select from xxxxx;

3. All the strings,except the data(how the data is written,it will be stored like that too)
   can be written in upper case,or lower case,or combination of two.

E.g.
InSeRt InTO xxxx;	<--- accepted.
SelECt aBc fRom xxxx;	<--- accepted.

4. For WHERE and SET condition,whether there is a space or not space between '=' is accepted.
E.g.
WhEre xxx=yyy;      <--- accepted.
SET zzz     = yyyy;   <--- accepted



Written by,
Soh Yee, Lee
2009 May
