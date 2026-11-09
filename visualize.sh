#!/bin/bash

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    visualize.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cadenegr <cadenegr@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/30 14:00:00 by cadenegr          #+#    #+#              #
#    Updated: 2024/12/30 14:00:00 by cadenegr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Opens the push_swap visualizer in your browser with fresh runs loaded.
#
#   ./visualize.sh              runs 100 and 500 random numbers
#   ./visualize.sh 20 100       runs 20 and 100 random numbers
#   ./visualize.sh -n 5 3 8 1   runs exactly these numbers
#
# The runs are written to visualizer/data.js; the page reads that file.

cd "$(dirname "$0")" || exit 1

if [ ! -x ./push_swap ]; then
    echo "push_swap not found. Run 'make' first."
    exit 1
fi

if [ "$1" = "-n" ]; then
    shift
    MODE=numbers
else
    MODE=sizes
fi
[ $# -eq 0 ] && set -- 100 500

python3 - "$MODE" "$@" <<'PY' || exit 1
import json, random, subprocess, sys

mode, args = sys.argv[1], sys.argv[2:]
if mode == "numbers":
    inputs = [[int(v) for v in args]]
else:
    inputs = [random.sample(range(1, 10 * int(n) + 1), int(n)) for n in args]

runs = {}
for i, nums in enumerate(inputs):
    res = subprocess.run(["./push_swap"] + [str(v) for v in nums],
                         capture_output=True, text=True, timeout=10)
    if res.stderr.strip():
        sys.exit(f"push_swap says: {res.stderr.strip()}")
    ops = res.stdout.split()
    key = f"run{i}"
    runs[key] = {"label": f"{len(nums)} numbers · {len(ops)} moves",
                 "nums": nums, "ops": " ".join(ops)}
    print(f"{len(nums):>5} numbers -> {len(ops)} moves")

with open("visualizer/data.js", "w") as f:
    f.write("window.PUSH_SWAP_RUNS = " + json.dumps(runs, separators=(",", ":")) + ";\n")
PY

PAGE="$(pwd)/visualizer/index.html"
echo "Visualizer: file://$PAGE"
if command -v xdg-open >/dev/null 2>&1; then
    xdg-open "$PAGE" >/dev/null 2>&1 &
elif command -v open >/dev/null 2>&1; then
    open "$PAGE"
fi
