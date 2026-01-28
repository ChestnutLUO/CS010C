#!/usr/bin/env python3
"""
Generates test datasets for the sighting search program.
Usage: ./create_dataset.py <num_sightings> <num_signatures> <suffix>
"""

import sys
import random
import math

def generate_dataset(num_sightings, num_signatures, suffix):
    """Generate test datasets for sighting search program."""
    
    random.seed(hash(suffix) % 2**32)
    
    sightings = []
    for _ in range(num_sightings):
        speed = random.randint(1, 50)
        brightness = random.randint(-30, 30)
        sightings.append((speed, brightness))

    all_signatures = []
    for speed, brightness in sightings:
        signature = math.ceil((speed * brightness) / 10.0)
        all_signatures.append(signature)

    if num_signatures <= len(all_signatures):
        signatures = random.sample(all_signatures, num_signatures)
    else:
        signatures = []
        for _ in range(num_signatures):
            signatures.append(random.choice(all_signatures))

    random.shuffle(signatures)
    
    with open(f'sightings_{suffix}.dat', 'w') as f:
        for speed, brightness in sightings:
            f.write(f'{speed} {brightness}\n')

    with open(f'signatures_{suffix}.dat', 'w') as f:
        for signature in signatures:
            f.write(f'{signature}\n')
    
    print(f"Generated {num_sightings} sightings and {num_signatures} signatures with suffix {suffix}")

def main():
    if len(sys.argv) != 4:
        print("Usage: ./create_dataset.py <num_sightings> <num_signatures> <suffix>")
        sys.exit(1)
    
    try:
        num_sightings = int(sys.argv[1])
        num_signatures = int(sys.argv[2])
        suffix = sys.argv[3] 
    except ValueError:
        print("Error: First two arguments must be integers")
        sys.exit(1)
    
    if num_sightings <= 0 or num_signatures <= 0:
        print("Error: Number of sightings and signatures must be positive")
        sys.exit(1)
    
    generate_dataset(num_sightings, num_signatures, suffix)

if __name__ == "__main__":
    main()


