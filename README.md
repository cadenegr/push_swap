# push_swap

[![42 School](https://img.shields.io/badge/42-School_Project-000000?style=for-the-badge&logo=42&logoColor=white)](https://42.fr/)
[![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))

Sort a list of integers using two stacks and a fixed set of 11 operations, in as few operations as possible. This is the 42 school `push_swap` project, solved with my own **block division** algorithm.

| Numbers | Average moves | Worst seen | 42 full-score limit |
|---|---|---|---|
| 3 | 1 | 2 | 3 |
| 5 | 8 | 10 | 12 |
| 100 | ~580 | 617 | 700 |
| 500 | ~5 100 | 5 278 | 5 500 |

Measured with `make test`: every order of 3, 4 and 5 numbers, 100 random runs of 100 numbers and 30 random runs of 500. Every run is replayed move by move to check that the stack really ends up sorted.

## The rules

Two stacks, **A** and **B**. A starts with the numbers, B starts empty. The program prints the operations that sort A in ascending order, with the smallest number on top.

| Operation | Effect |
|---|---|
| `sa` `sb` `ss` | swap the top two numbers of A, of B, or of both |
| `pa` `pb` | move the top number of B onto A, or of A onto B |
| `ra` `rb` `rr` | rotate up: the top number goes to the bottom (A, B, both) |
| `rra` `rrb` `rrr` | rotate down: the bottom number goes to the top (A, B, both) |

## The algorithm: block division

Every number is replaced by its **rank**, its position in the sorted list (0 = smallest). Then:

### 1. Divide A into blocks and send them to B

The ranks are cut into blocks: about `0.4 × √n` blocks, so 4 blocks for 100 numbers and 9 blocks for 500. Block 1 is the smallest ranks, block 2 the next, and so on.

A is scanned with `ra`. Every number belonging to the current block is pushed to B with `pb`. When the whole block is in B, the next block starts.

### 2. Split every block in 2 inside B

Right after a `pb`, the number is compared to the **middle of its block**:

- low half of the block → `rb`, it goes to the bottom of B
- high half of the block → it stays on top

So each block of A becomes two smaller piles in B, and B ends up roughly ordered: big numbers near the top, small ones near the bottom. When an `rb` is followed by an `ra`, both are done at once with `rr`.

Example with `./push_swap 7 2 9 0 5 3 8 1 6 4` (2 blocks: ranks 0–4 and 5–9):

```
block 1: ranks 0-4, middle 2  ->  0 and 1 go to the bottom of B
B (top → bottom):  4 3 2 . 0 1

block 2: ranks 5-9, middle 7  ->  5 and 6 go to the bottom of B
B (top → bottom):  8 9 7 . 4 3 2 . 0 1 . 5 6
                   └ high ┘ └ high ┘ └ low ┘ └ low ┘
                   block 2  block 1  block 1 block 2
```

The big numbers sit on top and the small ones at the bottom, so step 3 never has to rotate far. The full output is 32 moves:
`ra pb ra pb rr pb ra pb rr pb pb pb pb rb pb pb rb pa pa sa pa rrb pa pa rrb pa sa pa pa pa pa sa`

### 3. Pull the biggest number back to A

The biggest number left in B is brought to the top with `rb` or `rrb`, whichever direction is shorter, and pushed to A with `pa`. Because A is filled from the top, it ends up sorted. If the second biggest number is closer than the biggest, it goes first, then the biggest, and one `sa` fixes the order.

### Small inputs

- **2–3 numbers:** sorted directly with `sa` / `ra` / `rra` (2 moves at most).
- **4–5 numbers:** the smallest numbers go to B until 3 are left, those 3 are sorted, and B comes back (10 moves at most).

### Why the block count matters

More blocks mean more `ra` while scanning A. Fewer blocks mean more `rb` when pulling back. I measured the totals for each block count:

| Blocks | 100 numbers | 500 numbers |
|---|---|---|
| 2 | 643 | — |
| 4 | **585** | — |
| 6 | 616 | 5 264 |
| 8 | 671 | **5 080** |
| 10 | 736 | 5 139 |
| 16 | — | 5 957 |

`how_many_blocks()` in [src/divide_blocks.c](src/divide_blocks.c) uses about `0.4 × √n`, which lands near the minimum for every size.

## Build and run

```bash
git clone https://github.com/cadenegr/push_swap.git
cd push_swap
make
./push_swap 5 3 8 1 9          # prints the moves, one per line
./push_swap "5 3 8 1 9"        # numbers in one argument also work
./push_swap 1 2 2              # prints "Error" on stderr
```

Invalid input (letters, duplicates, numbers outside the `int` range, a lone `-`, an empty argument) prints `Error` followed by a newline on stderr. No input, or input that is already sorted, prints nothing.

## Testing

```bash
make test        # input error checks + full sorting suite
make benchmark   # sorting suite only
make validate    # 20 runs of 100 numbers, limit 700
make stress      # 100 runs of 500 numbers, limit 5500
make help        # all targets
```

The checker ([tester/checker.py](tester/checker.py), Python 3) runs `push_swap`, replays every printed move on its own copy of the stacks, and fails a run if A is not sorted, B is not empty, a move is unknown, or the move count is over the limit. You can also call it directly:

```bash
python3 tester/checker.py 100 50 700   # 50 runs of 100 numbers, limit 700
```

## Visualizer

```bash
make visual                # or: ./visualize.sh
./visualize.sh 20 100      # choose the sizes
./visualize.sh -n 5 3 8 1  # choose the exact numbers
```

This runs `push_swap`, saves the runs to `visualizer/data.js` and opens [visualizer/index.html](visualizer/index.html) in your browser. You can play, pause, step with ← →, change the speed, or drag through the run. Each number is a bar: longer and warmer means bigger. The strip at the bottom shows the whole run at a glance (`pb` blue, `pa` orange, rotations grey, swaps green). Click it to jump.

You can also open `visualizer/index.html` on its own: it shows a sample run, and **Paste a run** accepts the numbers plus any program's output.

## Project layout

```
push_swap/
├── Makefile
├── benchmark.sh            input checks + sorting suite (make test)
├── visualize.sh            runs push_swap and opens the visualizer
├── include/
│   ├── push_swap.h         structures and documented prototypes
│   └── libft.h
├── src/
│   ├── push_swap.c         main: parse, build stack A, sort
│   ├── argument_processor.c  read numbers from one or many arguments
│   ├── error_handle.c      input validation (format, int range, duplicates)
│   ├── build_stacks.c      fill stack A
│   ├── stack_functions.c   push / pop / is_empty / is_full
│   ├── a_stack_fts.c       sa ra rra pb
│   ├── b_stack_fts.c       sb rb rrb pa
│   ├── both_a_b_stack_fts.c  ss rr rrr
│   ├── sort_tree.c         picks the strategy by input size
│   ├── sort_two_div.c      2–5 numbers
│   ├── divide_blocks.c     steps 1 and 2: blocks from A to B, split in 2
│   └── pull_back.c         step 3: biggest number back to A
├── tester/
│   └── checker.py          replays the moves and checks the result
├── visualizer/
│   ├── index.html          the visualizer page
│   └── sample-data.js      sample run shown when no data.js exists
└── libft/                  my C library (with ft_printf)
```

## History

The first version (the one I submitted at 42) used fixed `four()` and `eight()` strategies. Its block split had a bug: the split point was `divider / 2`, counted from 0, not the middle of the current block. It only worked for the first block. Every later block landed in B without being split, and the 500-number strategy was built around that.

Version 3 replaces both with one `divide_blocks()` that splits every block at its own middle, adds the "second biggest first" pull-back, and fixes a hang with 4 numbers.

| | v2 | v3 |
|---|---|---|
| 100 numbers | 727 avg, 802 max | 580 avg, 617 max |
| 500 numbers | 7 982 avg, 8 325 max | ~5 100 avg, 5 278 max |
| 4 numbers | hung on 23 of 24 orders | 7 moves max |
