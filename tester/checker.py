#!/usr/bin/env python3
"""Run push_swap on random inputs, replay every move, and check the result.

Usage:
    python3 tester/checker.py              # default suite (42 limits)
    python3 tester/checker.py 100 50       # 50 random runs of 100 numbers
    python3 tester/checker.py 100 50 700   # same, and fail above 700 moves

A run passes only if stack A ends sorted, stack B ends empty and the move
count is within the limit. Exit code is 1 if any run fails.
"""
import itertools
import os
import random
import statistics
import subprocess
import sys

PUSH_SWAP = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "push_swap")

# Full-score limits from the 42 subject (3 and 5 are the max allowed).
SUITE = [  # (size, runs, limit)
    (3, "all", 3),
    (4, "all", 12),
    (5, "all", 12),
    (10, 50, None),
    (50, 50, None),
    (100, 100, 700),
    (500, 30, 5500),
]


def replay(nums, ops):
    a, b = list(nums), []
    for op in ops:
        if op in ("sa", "ss") and len(a) > 1:
            a[0], a[1] = a[1], a[0]
        if op in ("sb", "ss") and len(b) > 1:
            b[0], b[1] = b[1], b[0]
        if op == "pa" and b:
            a.insert(0, b.pop(0))
        if op == "pb" and a:
            b.insert(0, a.pop(0))
        if op in ("ra", "rr") and len(a) > 1:
            a.append(a.pop(0))
        if op in ("rb", "rr") and len(b) > 1:
            b.append(b.pop(0))
        if op in ("rra", "rrr") and len(a) > 1:
            a.insert(0, a.pop())
        if op in ("rrb", "rrr") and len(b) > 1:
            b.insert(0, b.pop())
        if op not in ("sa", "sb", "ss", "pa", "pb", "ra", "rb", "rr", "rra", "rrb", "rrr"):
            return False, f"unknown move '{op}'"
    if b:
        return False, "stack B not empty"
    if a != sorted(nums):
        return False, "stack A not sorted"
    return True, ""


def run(nums):
    try:
        out = subprocess.run([PUSH_SWAP] + [str(n) for n in nums],
                             capture_output=True, text=True, timeout=10).stdout
    except subprocess.TimeoutExpired:
        return None, False, "timeout (10 s)"
    ops = out.split()
    ok, why = replay(nums, ops)
    return len(ops), ok, why


def test_size(size, runs, limit):
    if runs == "all":
        inputs = [list(p) for p in itertools.permutations(range(size))]
    else:
        inputs = [random.sample(range(-100000, 100000), size) for _ in range(runs)]
    moves, failures = [], []
    for nums in inputs:
        count, ok, why = run(nums)
        if ok and limit is not None and count > limit:
            ok, why = False, f"{count} moves > {limit}"
        if ok:
            moves.append(count)
        else:
            failures.append((nums, why))
    label = "every order" if runs == "all" else f"{runs} random"
    if moves:
        stats = f"avg {statistics.mean(moves):7.0f}   max {max(moves):6}"
    else:
        stats = " " * 25
    limit_txt = f"limit {limit}" if limit is not None else ""
    status = "\033[32mOK\033[0m" if not failures else f"\033[31mKO ({len(failures)})\033[0m"
    print(f"{size:>4} numbers  {label:>12}   {stats}   {limit_txt:<11} {status}")
    for nums, why in failures[:3]:
        shown = " ".join(map(str, nums[:12])) + (" ..." if len(nums) > 12 else "")
        print(f"      {why}: {shown}")
    return not failures


def main():
    if not os.path.exists(PUSH_SWAP):
        sys.exit("push_swap not found. Run 'make' first.")
    if len(sys.argv) > 1:
        size = int(sys.argv[1])
        runs = int(sys.argv[2]) if len(sys.argv) > 2 else 20
        limit = int(sys.argv[3]) if len(sys.argv) > 3 else None
        suite = [(size, runs, limit)]
    else:
        suite = SUITE
    passed = all([test_size(*case) for case in suite])
    sys.exit(0 if passed else 1)


if __name__ == "__main__":
    main()
