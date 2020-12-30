import csv
import sys

if len(sys.argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    sys.exit(1)

with open(sys.argv[2], 'r') as sequences_file, open(sys.argv[1], 'r') as data_file:
    reader = csv.reader(data_file)
    csv_headers = next(reader)
    sequences = sequences_file.read()

    current_dna = {}
    for header in csv_headers[1:]:
        tmp_count = []
        for i in range(len(sequences)):
            tmp = 1
            while True:
                if (header * tmp) == sequences[i: i + len(header) * tmp]:
                    tmp += 1
                else:
                    break
            tmp_count.append(tmp - 1)
        current_dna[header] = max(tmp_count)

    # print(current_dna)


with open(sys.argv[1], 'r') as data_file:
    reader_dict = csv.DictReader(data_file)
    for row in reader_dict:
        match_count = 0
        for STR in current_dna:
            if current_dna[STR] == int(row[STR]):
                match_count += 1
            else:
                break
        if match_count == (len(csv_headers) - 1):
            print(row['name'])
            sys.exit(0)
    print("No match")
    sys.exit(0)