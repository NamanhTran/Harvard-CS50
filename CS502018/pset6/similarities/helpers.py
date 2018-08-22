from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""
    return set(a.splitlines()) & set(b.splitlines())


def sentences(a, b):
    """Return sentences in both a and b"""
    return set(sent_tokenize(a)) & set(sent_tokenize(b))

def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    a = set(subgetter(a.split(), n))
    b = set(subgetter(b.split(), n))
    return a & b


def subgetter(a, n):

    #declare substring list
    substring = []

    #use length to find if length is less than n
    length = len(a)

    for i in range(length):

        #variable to move the end of the string
        end = 0
        counter = 0

        #store the current word in question
        temp = a[i]

        #if substring size is not greater than the size of the word itself create substring
        if not len(temp) < n:

            #loops until end of string
            while end != len(temp):

                #calculate where to put the end of string
                end = n + counter

                #append substring to the list
                substring.append(temp[counter:end])

                #increment the substring
                counter += 1

    #return the substring list
    return substring