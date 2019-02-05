#!/usr/bin/python

import random, sys, string, argparse
from optparse import OptionParser

class shuf:
        def __init__(self, ir, stdarr, read):
                #ir = input range
                #hir = high input
                #lir = low input
                #read = filename

                #create an array of lines that could be output
                lines = []

                #if input range, input the range of numbers
                if ir:
                    r = ir.split("-")
                    hir = int(r[1])
                    lir = int(r[0])
                    while (hir >= lir):
                        lines.append(str(lir) + '\n')
                        lir = lir + 1
                #if no file was given or "-" read from standard input
                elif read == "nf" or read == "-":
                    lines = stdarr
                    if len(stdarr) < 1:
                        return
                #else a file was given.  read from the file
                else:
                    f = open(read, 'r')
                    lines = f.readlines()
                    f.close()

                #store the array in a member variable
                self.validlines = lines

        #member function to return a random line
        def chooseline(self):
                #return the permutation
                return random.choice(self.validlines)

        #member function to return a random line and then remove it
        #so it can't be returned again.
        def choosethenremove(self):
                choice = random.choice(self.validlines)
                self.validlines.remove(choice)
                return choice


def main():
        #output version message and how to use it
        version_msg = "%prog 2.0"
        usage_msg = """%prog [OPTION]... FILE

Output random permuations of input lines from FILE."""

        #create parser
        parser = OptionParser(version=version_msg, usage=usage_msg)

        #implement options
        parser.add_option("-n", "--head-count", action="store", dest="count", default=False, help="ouput at most COUNT lines (default all)")
        parser.add_option("-i", "--input-range", action="store", dest="ir", default=False, help="treat each number LO through HI as an input line")
        parser.add_option("-r", "--repeat", action="store_true", dest="repeat", default=False, help="output lines can be repeated")

        #read the input line and store options
        options, args = parser.parse_args(sys.argv[1:])


        #implement -n tag
        try:
            count = int(options.count)
        except:
            parser.error("invalid COUNT: {0}".format(options.count))

        if count < 0:
            parser.error("invalid COUNT: {0}".format(options.count))

        #implment -i tag
        if options.ir:
            try:
                inpt = options.ir.split("-")
                hir = int(inpt[1])
                lir = int(inpt[0])
            except:
                parser.error("invalid input range '" + str(options.ir) + "'".format(options.ir))

            if hir < lir:
                parser.error("invalid input range '" + str(options.ir) + "'".format(options.ir))

        #no error handling for -r tag necessary

        #error handling for input file
        try:
            filename = args[0]
        except:
            filename = "nf"

        #if lo-hi, there shouldn't be an input file
        if options.ir and filename != "nf":
            parser.error("Segmentation fault")

        #shouldn't be more than one input file
        if len(args) > 1:
            parser.error("Wrong number of Operands")

        #create a standard realcount for how many lines to be output
        #and an array for the standard input
        stdarr = []
        realcount = 0

        if options.ir:
            realcount = (hir - lir + 1)
        elif filename == "nf" or filename == "-":
            stdarr = sys.stdin.readlines()
            realcount = len(stdarr)
        else:
            f = open(filename, 'r')
            for i in f:
                realcount = realcount + 1

        #if -n was used, overwrite the realcount unless -n > possible lines
        if options.count:
            if count < realcount:
                realcount = count
                
        #generate the class and run shuf with the options
        try:
            generator = shuf(options.ir, stdarr, filename)
            
            #if just -r was called, run permutations forever
            if options.repeat and not options.count:
                    realcount = sys.maxsize
            #if -n was called with -r, allow repititions but only ouput -n lines
            i = 0
            while i < realcount:
                if options.repeat:
                    sys.stdout.write(generator.chooseline())
                else:
                    sys.stdout.write(generator.choosethenremove())
                i = i + 1
            
        #if theres in error, return I/O error
        except IOError as err:
            parser.error("I/O error({0}): {1}".format(errno, strerror))

if __name__ == "__main__":
    main()
