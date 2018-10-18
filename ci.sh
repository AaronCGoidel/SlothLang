#!/usr/bin/env bash

# blow up for any error
set -e

# Build and run tests
echo "Building tests..."
make test

echo "Running tests..."
./slothTest
make cleanTest

# Build sloth.
echo "Building sloth..."
make sloth

# Run all the examples.
echo "Running examples..."
for file in ./Examples/*.sloth; do
	echo ""
	echo "--- Example: $file"
	./sloth "$file"
done
