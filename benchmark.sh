#!/bin/bash

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    benchmark.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cadenegr <cadenegr@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/30 14:00:00 by cadenegr          #+#    #+#              #
#    Updated: 2024/12/30 14:00:00 by cadenegr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# push_swap test suite: input errors first, then sorting at the 42 limits.
# Every sorting run is replayed by tester/checker.py, so a run only passes
# if the moves really sort the stack.

cd "$(dirname "$0")" || exit 1

GREEN='\033[32m'
RED='\033[31m'
BOLD='\033[1m'
NC='\033[0m'
FAILED=0

if [ ! -x ./push_swap ]; then
    echo "push_swap not found. Run 'make' first."
    exit 1
fi

# expect_error "<description>" args...  -> must print "Error" on stderr, nothing on stdout
expect_error() {
    local desc="$1"; shift
    local out err
    out=$(./push_swap "$@" 2>/dev/null)
    err=$(./push_swap "$@" 2>&1 >/dev/null)
    if [ -z "$out" ] && [ "$err" = "Error" ]; then
        printf "  %-34s ${GREEN}OK${NC}\n" "$desc"
    else
        printf "  %-34s ${RED}KO${NC} (stdout: '%s', stderr: '%s')\n" "$desc" "$out" "$err"
        FAILED=1
    fi
}

# expect_silent "<description>" args... -> must print nothing at all
expect_silent() {
    local desc="$1"; shift
    local all
    all=$(./push_swap "$@" 2>&1)
    if [ -z "$all" ]; then
        printf "  %-34s ${GREEN}OK${NC}\n" "$desc"
    else
        printf "  %-34s ${RED}KO${NC} (printed: '%s')\n" "$desc" "$all"
        FAILED=1
    fi
}

echo -e "${BOLD}Input handling${NC}"
expect_silent "no arguments"
expect_silent "one number"                 42
expect_silent "already sorted"             1 2 3 4 5
expect_silent "already sorted, quoted"     "1 2 3 4 5"
expect_silent "spaces around quoted list"  " 1 2 3 "
expect_silent "quoted group + single"      "1 2" 3 "4 5"
expect_error  "duplicate"                  1 2 2 3
expect_error  "letter"                     1 a 3
expect_error  "lone minus sign"            -
expect_error  "sign inside a number"       1-2
expect_error  "above INT_MAX"              2147483648
expect_error  "below INT_MIN"              -2147483649
expect_error  "huge number"                99999999999999999999
expect_error  "empty argument"             "" 1
expect_error  "more than 1000 numbers"     $(seq 1 1001)
echo

echo -e "${BOLD}Sorting (moves replayed and checked)${NC}"
python3 tester/checker.py || FAILED=1
echo

if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}${BOLD}All tests passed.${NC}"
else
    echo -e "${RED}${BOLD}Some tests failed.${NC}"
fi
exit $FAILED
