from cs50 import SQL
import csv
import sys

if len(sys.argv) != 2:
    print("Usage: python roster.py house_name")
    sys.exit(1)

# print(sys.argv[1])

db = SQL("sqlite:///students.db")
select_ret = db.execute("SELECT first, middle, last, birth from students WHERE house = ? ORDER BY last, first;", sys.argv[1])
for row in select_ret:
    if row["middle"]:
        # middle is not NONE
        print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")
    else:
        # middle name is NONE
        print(f"{row['first']} {row['last']}, born {row['birth']}")