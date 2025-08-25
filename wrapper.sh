#!/bin/bash

# Check if user provided number of elements
if [ -z "$1" ]; then
  echo "Usage: $0 <number_of_elements>"
  exit 1
fi

NUM_ELEMENTS=$1
OUTFILE="sorted.txt"

# Generate unique random numbers
ARG=$(awk -v loop=$NUM_ELEMENTS -v range=$NUM_ELEMENTS 'BEGIN {
  srand()
  count = 0
  while (count < loop) {
    num = 1 + int(rand() * range)
    if (!(num in used)) {
      used[num] = 1
      printf "%d ", num
      count++
    }
  }
}')

# Function to truncate long list
truncate_list() {
  local list="$1"
  local count=$(echo "$list" | wc -w)
  if [ "$count" -le 42 ]; then
    echo "$list"
  else
    local head=$(echo "$list" | cut -d' ' -f1-5)
    local tail=$(echo "$list" | rev | cut -d' ' -f1-4 | rev)
    echo "$head [...] $tail"
  fi
}

echo "Generated input: $(truncate_list "$ARG")"

# Measure time and capture output
echo "Running ./merge with $NUM_ELEMENTS elements..."

START_TIME=$(gdate +%s%N)
OUTPUT=$(echo $ARG | ./merge)
END_TIME=$(gdate +%s%N)

# Calculate elapsed time in milliseconds
ELAPSED=$(( (END_TIME - START_TIME) / 1000000 ))

echo "Time taken: ${ELAPSED} ms"

# Validate output is sorted
SORTED=$(echo "$ARG" | tr ' ' '\n' | sort -n | tr '\n' ' ')

# Remove trailing spaces
SORTED=$(echo "$SORTED" | tr -s '[:space:]' ' ' | sed 's/^ *//;s/ *$//')
OUTPUT=$(echo "$OUTPUT" | tr -s '[:space:]' ' ' | sed 's/^ *//;s/ *$//')

# Compare and print result
if [ "$OUTPUT" == "$SORTED" ]; then
  echo "✅ Output is correctly sorted!"
else
  echo "❌ Output is NOT sorted correctly."
  echo "Expected: $(truncate_list "$SORTED")"
  echo "Got     : $(truncate_list "$OUTPUT")"
fi

# Save full output to file
{
  echo "INPUT:"
  echo "$ARG"
  echo
  echo "EXPECTED SORTED:"
  echo "$SORTED"
  echo
  echo "GOT:"
  echo "$OUTPUT"
} > "$OUTFILE"

echo "Full output written to $OUTFILE"