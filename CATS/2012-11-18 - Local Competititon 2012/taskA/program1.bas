'Program1. 18.11.2012

Dim CPages AS Integer

Open "input.txt" For Input As #1
Input #1, CPages
Close #1

If CPages / 2 <> Fix(CPages / 2) Then CPages = CPages + 1

Open "output.txt" For Output As #1
Write #1, CPages / 2
Close #1