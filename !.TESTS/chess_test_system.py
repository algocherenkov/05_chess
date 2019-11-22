import glob

for filenameIn in glob.glob('*.in'):
    inputData = open(filenameIn)
    length = 0
    for line in inputData:
        length = len(line)

        if line.find('\n') != -1:
            length -= 1;
        if line.find('\r') != -1:
            length -= 1;

    inputData.close()
    filenameOut = filenameIn.replace('.in', '.out')

    outputData = open(filenameOut)
    for line in outputData:
        if int(line) == length:
            break
        else:
            assert False, 'file %s has wrong number of symbols (%d against %d)' % (filenameOut, int(line), length)
    outputData.close()

print("all tests passed")
