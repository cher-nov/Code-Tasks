import sys

frmt = int(sys.stdin.readline())
hh, mm = map(int, sys.stdin.read().split(':'))

#fix minutes
mms = ''
if mm > 59:
    mms = '5' + str(mm % 10)
else:
    mms = str(mm).zfill(2)

#fix hours
if frmt == 24:
    frmt -= 1
hhs = ''
if hh > frmt:
    hhs = '0' + str(hh % 10)
    if hhs == '00':
        hhs = '10'
elif (frmt == 12) and (hh == 0):
    hhs = '01'
else:
    hhs = str(hh).zfill(2)

print(hhs + ':' + mms)
