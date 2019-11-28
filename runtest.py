#! /usr/bin/env python3
from contextlib import ExitStack
import filecmp
import sys
import os
import glob
import subprocess

D1 = {
    'A': ('radioprize', 3),
    'B': ('perfectflush', 2),
    'C': ('coloringgraphedgesgame', 1),
    'D': ('dividingbytwo', 1),
    'E': ('rainbowstrings', 1),
    'F': ('fixedpointpermutations', 1),
    'G': ('glowpixel', 2),
    'H': ('windmillpivot', 10),
    'I': ('errorcorrection', 1),
    'J': ('interstellartravel', 5),
    'K': ('computercache', 5),
    'L': ('carrylesssquareroot', 1),
    'M': ('mazeconnect', 5),
}
DIR = os.path.dirname(os.path.abspath(__file__))
DATASET_SUBDIRS = ('sample', 'secret')

assert sys.argv[1] == 'd1'

problem, *program = sys.argv[2:]

problem_name, time_limit = D1[problem]
problem_data_path = os.path.join(DIR, 'editorial', problem_name, 'data')

def globext(kind, ext):
    return sorted(glob.glob(os.path.join(problem_data_path, kind, ext)))


def datasets(kind):
    return zip(globext(kind, '*.in'), globext(kind, '*.ans'))


output_path = '{}.output'.format(problem)

for input_path, result_path in list(datasets('sample')) + list(datasets('secret')):
    with ExitStack() as stack:
        input_file = stack.enter_context(open(input_path, 'r'))
        output_file = stack.enter_context(open(output_path, 'w'))

        try:
            result = subprocess.run(program,
                stdin=input_file,
                stdout=output_file, stderr=sys.stderr,
                timeout=time_limit
            )
        except subprocess.TimeoutExpired as e:
            print('Time Limit Exceeded: {} second(s). On {}'.format(time_limit, result_path), file=sys.stderr)
            os.remove(output_path)
            exit(1)

        result.check_returncode()

        same = filecmp.cmp(output_path, result_path)
        if not same:
            raise AssertionError('Failed on {}'.format(result_path))

print('Passed all tests')
os.remove(output_path)
