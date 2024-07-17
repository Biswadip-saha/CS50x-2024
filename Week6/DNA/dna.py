import csv
import sys

def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit(1)

    # Read database file into a variable
    file = open(sys.argv[1], 'r')
    reader = csv.DictReader(file)
    fieldNames = reader.fieldnames
    rows = []
    for row in reader:
        rows.append(row)

    # Read DNA sequence file into a variable
    file2 = open(sys.argv[2], 'r')
    DNASeq = file2.read()
    DNASeqDict = {}
    # Find longest match of each STR in DNA sequence
    for field in fieldNames:
        if (field == "name"):
            continue
        i = 0
        j = 0
        maxCnt = 0
        cnt = 0
        while i<len(DNASeq):
            if (DNASeq[i] == field[j]):
                if (j == len(field)-1):
                    cnt += 1
                    j = 0
                    if (cnt > maxCnt):
                        maxCnt = cnt
                    i+=1
                    continue
                j += 1
            else:
                if (j > 0):
                    i = i-j
                j = 0
                cnt = 0
            i+=1
        DNASeqDict[field] = str(maxCnt)
    # Check database for matching profiles
    for row in rows:
        name = row.pop("name")
        if (DNASeqDict == row):
            print(name)
            break
    else:
        print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
