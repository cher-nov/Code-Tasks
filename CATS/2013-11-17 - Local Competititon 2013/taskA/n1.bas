#lang "fb"

Dim AS Short FreeMins, LastFree
Dim AS Integer Calls, CostSecs

ReDim AS Short CallMins()
ReDim AS Byte CallSecs()

'getting data from file
Open "input.txt" For Input AS #1
Input #1, Calls, FreeMins
Redim CallMins(1 To Calls)
Redim CallSecs(1 To Calls)
For ReadData AS Integer = 1 To Calls
    Input #1, CallMins(ReadData), CallSecs(ReadData)
Next ReadData
Close #1

'processing free time
'it's awful code bikoz i'm stupid today
For LastFree = 1 To Calls
    If FreeMins > CallMins(LastFree) Then
        'lol "rounding"
        If CallSecs(LastFree) > 0 Then
            CallMins(LastFree) += 1
            CallSecs(LastFree) = 0
        End If
        FreeMins -= CallMins(LastFree)
        CallMins(LastFree) = 0
        CallSecs(LastFree) = 0
    Else
        CallMins(LastFree) -= FreeMins
        FreeMins = 0
        Exit For
    End If
Next LastFree

'processing left time
For ProcLeft AS Short = LastFree To Calls
    CostSecs += CallMins(ProcLeft) * 60 + CallSecs(ProcLeft)
Next ProcLeft

'lol we done
Open "output.txt" For Output AS #1
Print #1, Str(CostSecs)
Close #1

'AND ERASING ALL USED SPACE
Erase CallMins, CallSecs
End(0)
