from cs50 import SQL
import csv
import sys

if len(sys.argv) != 2:
    print("Usage: python import.py filename")
    sys.exit(1)

db = SQL("sqlite:///students.db")
db.execute("DELETE FROM students;")
db.execute("UPDATE SQLITE_SEQUENCE SET SEQ=0 WHERE NAME='students';")
with open(sys.argv[1], "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        name = row["name"].split(" ")
        if len(name) == 2:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, NULL, ?, ?, ?);",
            name[0], name[1], row["house"], row["birth"])
        else:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?);",\
            name[0], name[1], name[2], row["house"], row["birth"])
sys.exit(0)